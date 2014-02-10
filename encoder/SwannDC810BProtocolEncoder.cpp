#include "SwannDC810BProtocolEncoder.h"

#define TOPBIT		0x80000000

SwannDC810BProtocolEncoder::SwannDC810BProtocolEncoder(int nPulseLength)
{
	m_nCode = 0;
  // m_nPulseLength = nPulseLength;
  m_nPulseLength = 500;
  //m_nTriplePulseLength = m_nPulseLength * 3;
  m_nTriplePulseLength = 1500;
}

void SwannDC810BProtocolEncoder::setCode(unsigned long long nCode)
{
	m_nCode = (unsigned long)nCode;
}

void SwannDC810BProtocolEncoder::setCode(byte* dataPointer, byte pos)
{
	return;
}

void SwannDC810BProtocolEncoder::encode(RFPacket* pPacket)
{
	pPacket->reset();

	// 23 bit code needs to be shifted 9 bits to the left so top bit is at MSB
  m_nCode <<= 9;

	// Add data
	for (int i = 0; i < 23; i++)
	{
		if(m_nCode & TOPBIT)
		{
			pPacket->append(m_nTriplePulseLength);
			pPacket->append(m_nPulseLength);
		}
		else
		{
			pPacket->append(m_nPulseLength);
			pPacket->append(m_nTriplePulseLength);
		}

		m_nCode <<= 1;
	}

	// Finish off with one pulse and a zero pulse, followed by a gap of 31 pulses
	pPacket->append(m_nPulseLength);
	pPacket->append(m_nPulseLength * 31);

	pPacket->rewind();
}