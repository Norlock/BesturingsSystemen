#pragma once
#ifndef	TYPE_H
#define	TYPE_H 1.5

#ifndef	STATIC_ASSERT
# if __cplusplus >= 201103
#  define	STATIC_ASSERT(x) static_assert(x,#x)
# else
#  define	STATIC_ASSERT(x)
# endif
#endif


/** @file type.h
 * Convenient pseudo-types.
 */

// Warning: These psuedotypes are CPU and platform dependent!
// The comment tells what size they should be on your machine.
// If the actual sizes do not match, you may have to twiddle
// a bit with the choice of built-in types.
// For instance: "ulong" may have to be "unsigned int" on
// your machine if it has a 64 bit processor.

/// A one byte bit pattern
typedef unsigned char 		byte;
// Verify size of byte
STATIC_ASSERT(sizeof(byte)==1);

/// A two byte bit pattern
typedef	unsigned short		word;
// Verify size of word
STATIC_ASSERT(sizeof(word)==2);

/// A four byte bit pattern
typedef	unsigned int		quad;
// Verify size of quad
STATIC_ASSERT(sizeof(quad)==4);

/// A two byte unsigned number
typedef	unsigned short		ushort;
// Verify size of ushort
STATIC_ASSERT(sizeof(ushort)==2);

/// A four byte unsigned number
typedef	unsigned long		ulong;
// Verify size of ulong
STATIC_ASSERT(sizeof(ulong)==4);


// vim:sw=4:ts=4:ai:aw:
#endif	/*type.h*/
