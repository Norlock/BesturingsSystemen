// vim:sw=4:ai:aw:ts=4:
/** @file lfnent.cc
 * The implementation of struct lfnent.
 */
#include "lfnent.h"

// The function to calculate the checksum of the
// DOS 8+3 filename belonging to an LFN entry.
byte lfnent::l_checksum(const byte *dosName)
{
	byte  sum = 0;
	for (int  i = (8+3) ; i ; --i)
		sum = ((sum & 1) << 7) + (sum >> 1) + *dosName++;
	return sum;
}
