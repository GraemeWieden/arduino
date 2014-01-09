#ifndef SWANNPROTOCOLENCODER_H
#define SWANNPROTOCOLENCODER_H

#include "Encoder.h"

class SwannProtocolEncoder :
	public Encoder
{
private:
	unsigned long	m_nCode;
	int				m_nPulseLength;
	int				m_nTriplePulseLength;

public:
	SwannProtocolEncoder(int nPulseLength);

	void	setCode(unsigned long long nCode);
	void	encode(RFPacket* pPacket);
	void 	setCode(byte* dataPointer, byte pos);
	
};

#endif