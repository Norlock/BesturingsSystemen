//#ident	"@(#)Area.cc	3.1	AKK	20131214"
/** @file Area.cc
 * De implementatie van Area.
 */

// Eigen includes
#include "asserts.h"	// for: require()
#include "Area.h"		// class Area


// Maak een Area ...
Area::Area(int base, int size)
	: base(base), size(size)
{
	require(base >= 0);
	require(size > 0);
	// ... en bereken meteen het laatste adres binnen dit gebied
	ends = base + size - 1;
}


// Overlappen de twee gebieden elkaar ?
bool	Area::overlaps(const Area *otherArea) const // waarom xp?
{
	require(otherArea != 0);
	return  (  ((otherArea->base <= base) && (base <= otherArea->ends))		// 'this' begint  IN xp !
	        || ((otherArea->base <= ends) && (ends <= otherArea->ends)) );	// 'this' eindigt IN xp !
}


// Splits dit gebied op in een stuk ter grote van 'gevraagd'
// en maak een nieuwe Area voor de rest.
Area	*Area::split(int wanted)
{
	require(wanted > 0);		// sanity check
	require(wanted < size);	// er moet wel iets overblijven

	Area  *requestedArea = new Area(base + wanted, size - wanted);
	size = wanted;			// pas je eigen omvang aan
	ends = base + size - 1;		// must update this too!
	return  requestedArea;
}

// Plak gebied 'xp' achter dit gebied
// en gooi daarna de 'xp' descriptor weg
void	Area::join(Area *otherArea)
{
	require(otherArea != 0);					// sanity check
	require(otherArea->base == (base + size)); // xp moet op dit gebied aansluiten
	size += otherArea->size;					// dit gebied wordt groter
	ends = base + size - 1;				// must update this too!
	delete  otherArea;							// deze descriptor kan nu weg.
}

// vim:sw=4:ai:aw:ts=4:
