#pragma once
#ifndef	LFNENT_H
#define	LFNENT_H 5.1
/** @file lfnent.h
 * De beschrijving van een Long File Name fake directory entry.
 * Zie ook: dirent.h
 */

#include "type.h"


// NB: 'struct' == 'class' met alles public

/** The description of a Long_File_Name fake directory entry.

	To encode long file names a sequence of
	LFN fake directory entries is followed
	by a normal 8+3 DOS entry for the
	remainder of that file's information.

	For instance the name:
	&quot;<em>File with very long filename.ext</em>&quot;
	is encoded as:

	<table>
	<tr><th>seqno field</th>			<th>lfn_part (UTF16 characters)</th></tr>
	<tr><td>@c 0x03 | @c 0x40</td>		<td>"me.ext"</td></tr>
	<tr><td>@c 0x02</td>				<td>"y long filena"</td></tr>
	<tr><td>@c 0x01</td>				<td>"File with ver"</td></tr>
	<tr><td>???</td>					<td>A normal 8.3 entry</td></tr>
	</table>

*/
#pragma pack(1)	// for MINGW
struct	lfnent
{
	byte	l_seqno;	//!< the sequence number (or-ed with 0x40 [@a last] or 0x80 [@a deleted])
	byte	l_utf1[10];	//!< the first 5 characters
	byte	l_attr;		//!< must be the D_LFN code
	byte	l_zero1;	//!< must always be 0
	byte	l_sum;		//!< the checksum of the corresponding DOS filename
	byte	l_utf2[12];	//!< the middle 6 characters
	word	l_zero2;	//!< must always be 0
	byte	l_utf3[4];	//!< the last 2 characters


	/** A function to calculate the checksum of the DOS filename.
	 * @param dosName	An 8+3 dos filename.
	 * This function does not require that this string is 0-terminated.
	 * */
	static byte	l_checksum(const byte dosName[8+3]);

}	__attribute__((__packed__));
#pragma pack()	// for MINGW

// Verify size of lfnent
STATIC_ASSERT(sizeof(struct lfnent)==32);

// vim:sw=4:ai:aw:ts=4:
#endif	/*lfnent.h*/
