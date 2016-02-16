// vim:sw=4:ai:aw:ts=4:
/** @file dosboot.cc
 * DOS bootsector utility functions.
 */
#include <cstdio>		// for snprintf
#include "type.h"
#include "dosboot.h"


/** A struct to map a media code to a media legend */
struct MediaCode
{
	byte		 code;			//!< media code
	const char	*legend;		//!< media legend
};

static // i.e. "only visible in this file"
MediaCode mediacode[] =
{
	{ 0xE5,
		"8\" (200 mm) Single sided, 77 tracks per side,"
		" 26 sectors per track, 128 bytes per sector (243 KB) (DR-DOS only)"
	},
	{ 0xED,
		"5.25\" (130 mm) Double sided, 80 tracks per side, 9 sector, 720 KB (Tandy 2000 only)"
	},
	{ 0xF0,
		"3.5\" Double Sided, 80 tracks per side, 18 or 36 sectors per track (1.44MB or 2.88MB)."
		" 5.25\" Double Sided, 15 sectors per track (1.2MB). Used also for other media types."
	},
	{ 0xF8, "Hard disk or Single Sided, 80 tracks per side, 9 sectors per track (360K)" },
	{ 0xF9, "3.5\" Double sided, 80 tracks per side, 9 sectors per track (720K)." },
	{ 0xFA, "5.25\" Single sided, 80 tracks per side, 8 sectors per track (320K)" },
	{ 0xFB, "3.5\" Double sided, 80 tracks per side, 8 sectors per track (640K)" },
	{ 0xFC, "5.25\" Single sided, 40 tracks per side, 9 sectors per track (180K)" },
	{ 0xFD, "5.25\" Double sided, 40 tracks per side, 9 sectors per track (360K)." },
	{ 0xFE, "5.25\" Single sided, 40 tracks per side, 8 sectors per track (160K)." },
	{ 0xFF, "5.25\" Double sided, 40 tracks per side, 8 sectors per track (320K)" },
	{ 0, "" }
};


// Converts a binairy mediacode 'mc' into some human readable text.
const char *dosboot::decodeMediaCode(byte mc)
{
	for (int  i = 0 ; mediacode[i].code != 0 ; ++i) {
		if (mediacode[i].code == mc)
			return mediacode[i].legend;
	}
	// Sorry, not found in the table
	static char	mesg[32];	// error message buffer
	snprintf(mesg, 32, "Unknown media code 0x%02X\n", mc);
	return mesg;
}
