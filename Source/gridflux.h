#ifndef GRIDFLUX_H
#define GRIDFLUX_H

#include "grid.h"
#include "gridphysical.h"

/**
 * @brief The GridFlux class is a grid designed to store a flux
 */
class GridFlux: public Grid
{
public:
	/**
	 * @brief GridFlux Create the GridFlux of a GridPhysical
	 * @param GP GridPhysical associated with this GridFlux
	 */
	GridFlux(const GridPhysical &GP);
	~GridFlux();
};

#endif // GRIDFLUX_H
