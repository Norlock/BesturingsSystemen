#pragma once
#ifndef	options_h
#define	options_h 1.1
/** @file options.h
 * Interface to command line options handler
 */

/// The function that decodes the options
extern void	doOptions(int argc, char *argv[]);

/// The next argv[] index after options have been handled.
extern int	optind;

/// A function to tell the known options
extern void	tellOptions(const char *progname);

// vim:sw=4:ts=4:ai:aw:
#endif	/*options_h*/
