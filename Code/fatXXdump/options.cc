// vim:sw=4:ai:aw:ts=4:
/** @file options.cc
 * Afhandeling van opties.
 */
#include <cstdio>		// fprintf
#include <cstdlib>		// EXIT_FAILURE
#include <getopt.h>     // getopt(...)
// Voor meer informatie: zie man 3 getopt

// global flags
extern	bool	bflag;	// dump bootsector,	default true
extern	bool	fflag;	// dump fat tables,	default false
extern	bool	rflag;	// dump rootdir,	default true


// Function to convert 'bool' value to text
static inline
const char *tellBool(bool x) { return x?"true":"false"; }


// Tell about the known options
void	tellOptions(const char *progname)
{
	fprintf(stderr, "Usage: %s [options] imagefile\n", progname);
	fprintf(stderr, "Known options are:\n");
	fprintf(stderr, "  -b = toggle dump bootsector contents (%s)\n", tellBool(bflag));
	fprintf(stderr, "  -f = toggle dump full FAT table (%s)\n", tellBool(fflag));
	fprintf(stderr, "  -r = toggle dump rootdirectory (%s)\n", tellBool(rflag));
}


// Scan for options
void	doOptions(int argc, char *argv[])
{
	char  options[] = "bfr";	// de opties die we willen herkennen
	// Voor meer informatie: zie man 3 getopt

	int  opt = 0;	// "huidige" optie character
	do {
		opt = getopt(argc, argv, options);	// de uitpluizer
		switch(opt)		// welke optie hebben we gezien ...
		{
			case 'b':	// -b = toggle dump bootsector params
				bflag = !bflag;
				break;
			case 'f':	// -f = toggle dump FAT table
				fflag = !fflag;
				break;
			case 'r':	// -r = toggle dump rootdirectory
				rflag = !rflag;
				break;

			case -1:	// = einde opties
				break;

			default:	// eh? iets onbekends gevonden
				// Foutmelding geven ...
				tellOptions( argv[0] );
				// ... en eindigen
				exit(EXIT_FAILURE);
		}
	} while(opt != -1);  // tot einde opties
}
