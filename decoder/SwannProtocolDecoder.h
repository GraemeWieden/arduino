#ifndef SWANNPROTOCOLDECODER_H
#define SWANNPROTOCOLDECODER_H

#include "Decoder.h"

class SwannProtocolDecoder :
	public Decoder
{
private:
	int 			m_nPulseLength;
	unsigned long long	m_nCode;

public:
	SwannProtocolDecoder();

	boolean decode(RFPacket* pPacket);
	void	fillPacket(NinjaPacket* pPacket);
};

#endif