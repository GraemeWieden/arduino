#include "B00ProtocolDecoder.h"

#include "../common/Ninja.h"

B00ProtocolDecoder::B00ProtocolDecoder()
{
	m_nPulseLength = 0;
}

boolean B00ProtocolDecoder::decode(RFPacket* pPacket)
{
	if(pPacket->getSize() != 102)
		return false;

  m_nPulseLength = 300;
  m_nCode = 0;

	word nTolerance = 150;
	word nMin1 = m_nPulseLength - nTolerance;
	word nMax1 = m_nPulseLength + nTolerance;
	word nMin3 = 3*m_nPulseLength - nTolerance;
	word nMax3 = 3*m_nPulseLength + nTolerance;
	word nHighPulse = 0;

	// 50 bit => 100 pulses on/off
	for(int i = 0; i < 50; i++)
	{
		nHighPulse = pPacket->next();

		// Simply skip low pulse, for more accurate decoding this could be checked too
		pPacket->next();

		// Zero bit
		if(nHighPulse >= nMin1 && nHighPulse <= nMax1)
			;
		else if(nHighPulse >= nMin3 && nHighPulse <= nMax3)
			m_nCode += 1;
		else
		{
			m_nCode = 0;
			break;
		}
		m_nCode <<= 1;
	}

	m_nCode >>= 1;

	return (m_nCode != 0);
}

void B00ProtocolDecoder::fillPacket(NinjaPacket* pPacket)
{
  char strData[20];

  // The packet is a total of 50 bits made up of:
  // 12 bits: B00 to announce and content descriptor
  // 5 bits: 2 bit house code 3 bit channel code
  // 32 bits: content
  // 1 bit: even parity

  byte contentType = m_nCode >> 38 & 0xF;
  byte houseCode = m_nCode >> 36 & 0x3;
  byte channelCode = m_nCode >> 33 & 0x7;

  int guid = (contentType * 100) + (houseCode * 10) + channelCode;

  // we create a union of a double and unsigned long so we can use the bit pattern 
  // without modification between data types
  union
  {
    double dblValue;
    unsigned long ulValue;
  };
  ulValue = m_nCode >> 1 & 0xFFFFFFFF;

  switch (contentType)
  {
  case 0: // double precision floating point value
    dtostrf(dblValue, 7, 3, strData);
    break;
  case 1: // long signed integer value
    sprintf(strData, "%ld", ulValue);
    break;
  case 2: // long unsigned integer value
    sprintf(strData, "%lu", ulValue);
    break;
  case 3: // 2 x signed integer values
    sprintf(strData, "%d,%d", (int)(ulValue >> 16), (int)(ulValue & 0xFFFF));
    break;
  case 4: // 2 x unsigned integer values
    sprintf(strData, "%u,%u", (int)(ulValue >> 16), (int)(ulValue & 0xFFFF));
    break;
  case 5: // 4 x byte values
    sprintf(strData, "%x %x %x %x", (byte)(ulValue >> 24), (byte)(ulValue >> 16 & 0xFF), (byte)(ulValue >> 8 & 0xFF), (byte)(ulValue & 0xFF));
    break;
  }

	pPacket->setEncoding(ENCODING_B00);
	pPacket->setTiming(m_nPulseLength);
	pPacket->setType(TYPE_DEVICE);
  pPacket->setGuid(guid);
  pPacket->setDevice(ID_MOISTURE_SENSOR);
  pPacket->setData((byte*)strData, 12);
}