#include "BestFit2.h"

// ----- hulpfuncties -----

// Iemand levert een gebied weer in (eager version)
void	BestFit2::free(Area *ap)
{
	require(ap != 0);
    areas.sort(Area::orderByAddress());	// WARNING: expensive N*log(N) operation !
	// Find the right place to insert ap, keeping the list sorted by address
	for (ALiterator  i = areas.begin() ; i != areas.end() ; )
	{
		Area  *bp = *i;							// match new ap with existing bp ...
		if (cflag)
			check(!ap->overlaps(bp));    		// sanity check
		// Does older area bp matc  h new free area ap?
		if (bp->getBase() == (ap->getBase() + ap->getSize())) {
			// Yes, bp matches with ap ...	[ap directly before bp]
			ALiterator  next = areas.erase(i);	// remove bp from the list
			ap->join(bp);						// append area bp to ap (and destroy bp)
			++mergers;							// update statistics
			areas.insert(next, ap);				// insert ap before next
			return;
		} else
		if (ap->getBase() == (bp->getBase() + bp->getSize())) {
			// Yes, ap matches with bp ... [ap directly after bp]
			ALiterator  next = areas.erase(i);	// remove bp from the list
			bp->join(ap);						// append area ap to bp (and destroy ap)
			++mergers;							// update statistics
			ap = bp;							// now pretend this is the free'd area
				// and compare it with the new 'next item'
			i = next;							// must "revive" the 'i' iterator here
		} else
		if (ap->getBase() < bp->getBase()) {
			// To keep the list sorted by address ap should go before bp
			areas.insert(i, ap);				// insert ap before cursor
			return;
		} else {
			++i;								// move on to next area in the freelist
		}
	}

	// Found no match
	areas.push_back(ap);	// then ap goes at the end
	areas.sort(Area::orderBySizeDescending());	// WARNING: expensive N*log(N) operation !
}
