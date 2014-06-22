#ifndef B00PROTOCOLDECODER_H
#define B00PROTOCOLDECODER_H

#include "Decoder.h"

class B00ProtocolDecoder :
	public Decoder
{
private:
	int 			m_nPulseLength;
	unsigned long long	m_nCode;

public:
  B00ProtocolDecoder();

	boolean decode(RFPacket* pPacket);
	void	fillPacket(NinjaPacket* pPacket);
};

#endif