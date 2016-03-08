//#ident	"@(#)BestFit.cc	2.2	AKK	20140130"
/** @file BestFit.cc
 * De implementatie van BestFit.
 */

#include "BestFit.h"
#include "ansi.h"
#include <iostream>

using namespace std;

// Clean up dead stuff
BestFit::~BestFit()
{
	while (!areas.empty()) {
		Area  *ap = areas.back();
		areas.pop_back();
		delete ap;
	}
}

// Initializes how much memory we own
void  BestFit::setSize(int new_size)
{
	require(areas.empty());					// prevent changing the size when the freelist is nonempty
	Fitter::setSize(new_size);
	areas.push_back(new Area(0, new_size));	// and create the first free area (i.e. "all")
}

// Print the current freelist for debugging
void	BestFit::dump()
{
	std::cerr << AC_BLUE << type << "::areas";
	for (ALiterator  i = areas.begin() ; i != areas.end() ; ++i) {
		std::cerr << ' ' << **i;
	}
	std::cerr << AA_RESET << std::endl;
}


// Geeft een gebied terug met een bepaalde grote
Area  *BestFit::alloc(int wanted)
{
	require(wanted > 0);		// mag geen null zijn
	require(wanted <= size);	// kan niet groter zijn dan de maximale geheugen beschikbaar

	updateStats();				// update resource map statistics

	if(areas.empty()) {		// geef null terug als gebied leeg is
		return 0;
	}

	// Search thru all available free areas
	Area  *areaWanted = 0;
	areaWanted = searcher(wanted);		// first attempt
	if(areaWanted) {					// success ?
		return areaWanted;
	}

	if(reclaim()) {			// could we reclaim fragmented freespace ?
		areaWanted = searcher(wanted);	// then make a second attempt
		if(areaWanted) {				// success ?
			return areaWanted;
		}
	}

	// Alas, failed to allocate anything
	//dump();//DEBUG
	return 0;					// inform caller we failed
}


// Application returns an area no longer needed
void	BestFit::free(Area *area)
{
	require(area != 0);
	if (cflag) {
		// EXPENSIVE: check for overlap with all registered free areas
		for(ALiterator  i = areas.begin() ; i != areas.end() ; ++i) {
			check(!area->overlaps(*i));    // the sanity check
		}
	}
	areas.push_back(area);	// add discarded "old" object to the end of free list
}


// ----- internal utilities -----

// Zoekt voor een gebied met die groter is dan wanted
Area  *BestFit::searcher(int wanted)
{
	require(wanted > 0);		// has to be "something",
	require(wanted <= size);	// but not more than can exist,
	require(!areas.empty());	// provided we do have something to give

	// Search thru all available areas
	for(ALiterator  i = areas.begin() ; i != areas.end() ; ++i)
	{
		Area  *areaWanted = *i;					// Candidate item
		if(areaWanted->getSize() < wanted)
		{
            Area *previousArea = 0;
            ALiterator  next = null;
            if(it == areas.begin())//eerste element
            {
                previousArea = *i;
                next =  areas.erase(i);
            }
            else
            {
              ALiterator _copy = i;
              --_copy;
               previousArea = *_copy;
               next =  areas.erase(_copy);
            }

           // Remove this element from the freelist
            if(previousArea->getSize() != wanted)
            {
                Area  *restArea = previousArea->split(wanted);	// Split into two parts (updating sizes)
                areas.insert(next, restArea);
                cout << "Wanted is: " << wanted << endl;
                cout << "Size of area used is: " << previousArea->getSize()<< endl;
                cout << "Size of rest area is: " << restArea->getSize()<< endl;
            }
            return previousArea;
		}
	}
	return 0;

}


// We have run out of usefull areas;
// Try to reclaim space by joining fragmented freespace
bool	BestFit::reclaim()
{
	require(!areas.empty());		// sanity check

	// Sort resource map by area address
	areas.sort(Area::orderByAddress());	// WARNING: expensive N*log(N) operation !

	// Search thru all free areas for matches between successive elements
	bool  changed = false;
	ALiterator  i = areas.begin();
	Area  *area = *i;					// The current candidate ...
	for(++i ; i != areas.end() ;)
	{
		Area  *otherArea = *i;				// ... match it with.
		if(otherArea->getBase() == (area->getBase() + area->getSize()))
		{
			// Oke; bp matches ap ... [i.e. bp follows ap]
			ALiterator  next = areas.erase(i);	// remove bp from the list
			area->join(otherArea);			// append area bp to ap (and destroy bp)
			++mergers;				// update statistics
			changed = true;			// we changed something
			i = next;				// revive the 'i' iterator
			// and now try match ap with whatever followed bp
		}
		else
		{
			area = otherArea;				// move on to next free area
			++i;
		}
	}
	++reclaims;	// update statistics ("reclaims attempted")
	return changed;
}

// Update statistics
void	BestFit::updateStats()
{
	++numberOfAllocsTried;									// number of 'alloc's
	qsum  += areas.size();					// length of resource map
	qsum2 += (areas.size() * areas.size());	// same: squared wordt gebruikt voor standaard deviaties
}

// vim:sw=4:ai:aw:ts=4:
