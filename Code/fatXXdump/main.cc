/** @file main.cc
 * A program to dump a FAT12/FAT16 image.
 */

#include <fcntl.h>		// for: option flags voor 'open()' (O_RDONLY, O_BINARY)
#include <unistd.h>		// for: lseek(), read(), close()
#include <cstddef>		// for: offsetof(type,member)
#include <cstring>		// for: memset()
#include <cstdlib>		// for: atexit(), exit(), system()
#include <cstdio>		// for: printf() etc (or use iostream instead)
#include <iostream>		// for: std::cin, std::cout, std::cerr, std::endl

#include "main.h"		// common includes
#include "ansi.h"		// ansi color code strings
#include "asserts.h"	// require(), check(), ensure(), notreached()
#include "options.h"	// getOptions en optind
#include "fatal.h"		// fatal(...)

// DOS/FAT specs
#include "type.h"		// defines our own pseudo-types
#include "dosboot.h"	// the bootsector description
#include "dirent.h"		// a directory entry description
#include "lfnent.h"		// a long-file-name directory entry description

// TODO add other includes as needed


// === MAGIC FUNCTION ===
#ifndef	__unix__
// Various IDE's on non-unix platforms create a window
// that will disappear when the program terminates.
// Not needed for: CodeBlocks, Eclipse
// Needed for: DevCpp
void	dowait()
{
#if	__DEVCPP__			// DevCpp on windows
	system("PAUSE");	// "Hit RETURN to continue"
#endif
}
#endif
// === end MAGIC ===


// The flags that (should) change the program's behaviour
// These are changed by doOptions()
bool	bflag(true);	// dump the bootsector info,	default true
bool	fflag;			// dump the entire fat,			default false
bool	rflag(true);	// dump the rootdirectory,		default true



// The fuction that dumps the contents of given the image file
void	dumpimage(const char *image)
{
	std::cout << "Dumping contents of "<<image<<std::endl;

	// TODO this is your assignment

}


// The main function
int  main(int argc, char *argv[])
{
#ifndef	__unix__
	atexit( dowait );	// make sure 'dowait' is called on exit
#endif
	try {
		// Check that your compiler did honour the "packed" attribute (see dosboot.h).
		//printf("sizeof bootsector is %d\n", sizeof(dosboot));//DEBUG
		check(sizeof(dosboot) == 512);	// sanity check

		// Make some preparations
		doOptions(argc, argv);			// inspect the argv and handle options
		if (argv[optind] == 0) {		// no further arguments?
			tellOptions( argv[0] );		// then tell the user we expect a file name
			exit(EXIT_FAILURE);			// and stop
		}

		// Do the real work
		dumpimage( argv[optind] );	// dump the contents of this file
		exit(EXIT_SUCCESS);
	} catch(const assert_error& e) {
		std::cerr << AC_RED "Assertion: "<< e.what() << AA_RESET << std::endl;
		exit(EXIT_FAILURE);
	} catch(const std::exception& e) {
		std::cerr << AC_RED "Exception: "<< e.what() << AA_RESET << std::endl;
		exit(EXIT_FAILURE);
	} catch(...) {
		std::cerr << AC_RED "OOPS: something went wrong" AA_RESET << std::endl;
		return EXIT_FAILURE;
	}
}

// vim:sw=4:ai:aw:ts=4:
