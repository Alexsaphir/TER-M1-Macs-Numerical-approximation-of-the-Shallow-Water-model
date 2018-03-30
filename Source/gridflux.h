#ifndef GRIDFLUX_H
#define GRIDFLUX_H

#include "grid.h"
#include "gridphysical.h"

class GridFlux: public Grid
{
public:
	GridFlux(const GridPhysical &GP);
	~GridFlux();
};

#endif // GRIDFLUX_H
