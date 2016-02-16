#pragma once
#ifndef	DOSBOOT_H
#define	DOSBOOT_H 5.1
/** @file dosboot.h
 * De DOS bootsector beschrijving.
 */

#include "type.h"

// NB: 'struct' == 'class' met alles public

/// Description of a DOS bootsector (plus various common values).
///
/// Also see:
/// <a target='info'
/// href='http://en.wikipedia.org/wiki/File_Allocation_Table'>FAT File System</a>
///
/// @note
/// Because this datastructure has some unusual internal alignments between
/// datafields your compiler must support the non-standard 'packed' attribute.
/// Otherwise change them to byte ...[X] (consult type.h) for the proper values of X.
///
#pragma pack(1)	// for MINGW
struct	dosboot
{
	// The basic stuff
	byte	b_bra[3];	//!< a jump instruction iff bootable
	byte	b_oem[8];	//!< The OEM name e.g. "IBM  3.3", "MSDOS5.0", "MSWIN4.1"
	word	b_bps;		//!< number of bytes per sector (usualy 512)
	byte	b_spc;		//!< number of sectors per cluster (usually 2) [1...128]
	word	b_nres;		//!< number of reserved sectors (usually 1 [FAT12/FAT16] or 32 [FAT32])
	byte	b_nfat;		//!< number of fats (usually 2)
	word	b_ndir;		//!< max number of root dir entries (0 implies FAT32 format)
	word	b_nssec;	//!< the total number of sectors on the medium
	byte	b_media;	//!< the media descriptor code
	word	b_spf;		//!< number of sectors per fat
	word	b_spt;		//!< number of sectors per track
	word	b_heads;	//!< number of sides (e.g. single side, double sided flopyy)
	quad	b_nhidden;	//!< number of hidden sectors before this filesystem
	quad	b_nlsec;	//!< the total number of sectors (IFF a large disk)

	// The next part is very much FAT version and platform dependent!
	// FAT12, FAT16 - extended BIOS param block
	byte	b_phys;		//!< the physical drive number
	byte	b_res2;		//!< a reserved field (current head)
	byte	b_ebsig;	//!< the extended boot signature (0x29 or 0x28)
	quad	b_serno;	//!< the serial number
	byte	b_label[11];//!< the volume label
	byte	b_type[8];	//!< the system type e.g. "FAT..."
	byte	b_code[448];//!< the area for the binairy bootcode iff bootable
	word	b_bsig;		//!< the boot signature 0x55 0xAA for a bootable image

	/** A function to convert a binairy mediacode to a human readable string */
	static const char *decodeMediaCode(byte mc);

}	__attribute__ ((packed));	// NOTE: This is compiler dependent!
#pragma pack()	// for MINGW

// Verify size of dosboot
STATIC_ASSERT(sizeof(struct dosboot)==512);


// Fat cluster codes (generic values)
#define	FAT_FREE	0x0000	//!< Free FAT entry code
#define	FAT_SPEC1	0x0001	//!< Special: Reserved, meaning unknown
#define	FAT_SPEC2	(-16)	//!< Special: Actually all codes 0xFFF0 upto 0xFFF6
#define	FAT_BAD		(-9)	//!< BAD cluster mark: Code 0xFFF7
#define	FAT_LAST	(-8)	//!< LAST cluster mark: Actually all codes 0xFFF8 upto 0xFFFF
				//!< (Also see: "<em>the first two entries in a FAT</em> ..." on wikipedia)

// FAT12 specific code version
#define	F12_BAD		0x0FF7  //!< The FAT12 badsector code
#define	F12_LAST	0x0FF8	//!< The FAT12 last-cluster codes 0x0FF8 upto 0xFFF

// FAT16 specific code version
#define	F16_BAD		0xFFF7  //!< The FAT16 badsector code
#define	F16_LAST	0xFFF8	//!< The FAT16 last-cluster codes 0xFFF8 upto 0xFFFF

// vim:sw=4:ts=4:ai:aw:
#endif	/*dosboot.h*/
