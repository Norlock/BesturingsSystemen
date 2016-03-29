#pragma once
#ifndef BESTFIT2_H
#define BESTFIT2_H


#include "BestFit.h"

/// @class BestFit2
/// Het FirstFit algorithme gebruikt het eerste
/// gevonden bruikbare gebied in de resource map.
/// Dit is de eager versie (probeert meteen alles op
/// te ruimen en houdt daarom de gebieden gesorteerd
/// op adres)
class BestFit2 : public BestFit
{
public:

	explicit	// see: http://en.cppreference.com/w/cpp/language/explicit
	/// @param cflag	initial status of check-mode
	/// @param type		name of this algorithm (default=BestFit2)
	BestFit2(bool cflag=false, const char *type = "BestFit (eager)")
		: BestFit(cflag, type) {}

	/// The application returns an area to freespace
	/// @param ap	The area returned to free space
	virtual  void	 free(Area *ap);
};


#endif // BESTFIT2_H
