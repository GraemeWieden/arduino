Libraries Required
==================



Installation instructions
=========================

1. Extract / Check out to Arduino's libraries folder.
2. Ninja Arduino's sketch is located inside 
		
		libraries
				--->NinjaBock
						--->NinjaBlock.ino

DA value for RF
===============
DA value
The DA value is a string representing hexadecimal nibbles as follows:
  Bytes		Name
  1		Encoding of the RF packet
  1		[Reserved]
  2		Micro seconds, unless encoding implies otherwise (Maximum “FFFF” = 65535us)
  n		Payload (probably 4+ bytes)

Eg. {... “DA”:“0200249F95A7C”}
Encoding (02) = 2
Ignored (00)
Timing (249F) = 9375 us
Payload (95A7C) = 1001 0101 1010 0111 1100

Encoding Reference:
Magnetic Proximity switch - Encoding 0x01
Home Easy 2ch wall socket - Encoding 0x01
WT450     - Encoding 0x02
ARLEC door chime - Encoding 0x03
Home Easy Power sockets - Encoding 0x04
Oregon Scientific weather station - 0x05
Aldi Power socket Indoor - 0x06
Aldi Power socket outdoor - 0x07
Swann door chime - 0x08
