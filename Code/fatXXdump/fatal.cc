/** @file fatal.cc
 * A printf style function to print a fatal error message and then quit.
 */
#include <cstdio>
#include <cstdarg>
#include <cstdlib>

// A printf style function to print a fatal error message and then quit
void	fatal(const char *format, ...)
{
	va_list alist;
	va_start(alist, format);

	fprintf(stderr, "Oops, ");
	vfprintf(stderr, format, alist);
	va_end(alist);
	fprintf(stderr, "\n");

	exit(EXIT_FAILURE);
}
