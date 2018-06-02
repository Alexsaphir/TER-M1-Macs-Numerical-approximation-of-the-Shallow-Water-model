#ifndef GRIDPHYSICAL_H
#define GRIDPHYSICAL_H

#include "grid.h"

/**
 * @brief The GridPhysical class is Grid for the physical domain
 */

class GridPhysical: public Grid
{
public:
	/**
	 * @brief GridPhysical Create a GridPhysical with a given number of elements
	 * @param N Number of elements
	 */
	GridPhysical(int N);
	~GridPhysical();
};

#endif // GRIDPHYSICAL_H
