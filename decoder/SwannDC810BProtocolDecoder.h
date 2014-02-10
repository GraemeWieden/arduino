#ifndef SWANNDC810BPROTOCOLDECODER_H
#define SWANNPDC810BROTOCOLDECODER_H

#include "Decoder.h"

class SwannDC810BProtocolDecoder :
	public Decoder
{
private:
	int 			m_nPulseLength;
	unsigned long long	m_nCode;

public:
  SwannDC810BProtocolDecoder();

	boolean decode(RFPacket* pPacket);
	void	fillPacket(NinjaPacket* pPacket);
};

#endif