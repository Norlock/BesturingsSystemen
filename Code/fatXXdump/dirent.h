#pragma once
#ifndef	DIRENT_H
#define	DIRENT_H 5.1
/** @file dirent.h
 * De beschrijving van een gewone DOS directory entry.
 * Zie ook: lfnent.h
 */

#include "type.h"


// NB: 'struct' == 'class' met alles public

/** The description of an ordinary 8+3 DOS directory entry. */
#pragma pack(1)	// for MINGW
struct	dirent
{
	byte	d_name[8];	//!< space padded name
	byte	d_ext[3];	//!< space padded extension

	byte	d_attr;		//!< the file attributes
	/** Constants for the d_attr field. */
	enum d_attr_flag {
		D_RDONLY	= 0x01,		//!< d_attr: @b read @b only flag
		D_HIDDEN	= 0x02,		//!< d_attr: @b hidden @b file flag
		D_SYSTEM	= 0x04,		//!< d_attr: @b system @b file flag
		D_LABEL		= 0x08,		//!< d_attr: @b partition @b label flag
		D_DIR		= 0x10,		//!< d_attr: @b directory flag
		D_ARCHIVE	= 0x20,		//!< d_attr: @b archive flag
		D_DEVICE	= 0x40,		//!< d_attr: (internal bit)
		D_UNUSED	= 0x80,		//!< d_attr: (reserved bit)
		D_LFN		= 0x0F		//!< d_attr: the LongFileName magic constant
								//!< If 'd_attr' equals D_LFN then this entry
								//!< should be interpreted as an @ref lfnent.
								//!< Also see: lfnent.h
	};

	byte	d_case;		//!< reserved byte (WinNT: encodes the case of short names)
	/** Constants for the d_case field. */
	enum d_case_flag
	{
		D_BASECASE	= 0x08,		//!< d_case: lowercase file name flag
		D_EXTCASE	= 0x10		//!< d_case: lowercase extension flag
	};

		/// File creation time seconds:
		/// The last 2 seconds are expressed in 10ms units (0..190)
	byte	d_cms;		//!< file creation time in 10ms units (0..190)
	word	d_chms;		//!< file creation time (with 2 sec resolution)
	word	d_cymd;		//!< file creation date
	word	d_aymd;		//!< last accessed date
	word	d_eax;		//!< extended attibutes (IFF fat32 THEN msb part of first cluster)
	word	d_mhms;		//!< last modified time (with 2 sec resolution)
	word	d_mymd;		//!< last modified date
	word	d_head;		//!< the number of the first cluster
	quad	d_size;		//!< the size of the file in bytes


	// Inline functions to extract the 'time' parts from a given word

	/** Extract the hour of a time field (0-23) */
	static inline word  hour(word x)		{ return (((x)>>11)&0x1F); }
	/** Extract the minutes of a time field (0-59) */
	static inline word	minutes(word x)		{ return (((x)>>5)&0x3F); }
	/** Extract the seconds of a time field (0-58: actual resolution is in 2 seconds steps!) */
	static inline word	hsecs(word x)		{ return ((x)&0x1F)<<1; }


	// Inline functions to extract the 'date' parts from a given word

	/** Extract the year of a date field (adding 1980) */
	static inline word	year(word x)		{ return 1980 + (((x)>>9)&0x7F); }
	/** Extract the month of a date field (1-12) */
	static inline word	month(word x)		{ return (((x)>>5)&0x0F); }
	/** Extract the day of a date field (1-31) */
	static inline word	day(word x)			{ return (((x))&0x1F); }

}	__attribute__((__packed__));
#pragma pack()	// for MINGW

// Verify size of dirent
STATIC_ASSERT(sizeof(struct dirent)==32);

// vim:sw=4:ai:aw:ts=4:
#endif	/*dirent.h*/
