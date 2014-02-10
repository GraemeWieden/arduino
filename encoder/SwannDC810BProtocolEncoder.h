#ifndef SWANNDC810BPROTOCOLENCODER_H
#define SWANNDC810BPROTOCOLENCODER_H

#include "Encoder.h"

class SwannDC810BProtocolEncoder :
	public Encoder
{
private:
	unsigned long	m_nCode;
	int				m_nPulseLength;
	int				m_nTriplePulseLength;

public:
  SwannDC810BProtocolEncoder(int nPulseLength);

	void	setCode(unsigned long long nCode);
	void	encode(RFPacket* pPacket);
	void 	setCode(byte* dataPointer, byte pos);
	
};

#endif