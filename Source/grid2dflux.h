#ifndef GRID2DFLUX_H
#define GRID2DFLUX_H

#include "grid2d.h"
#include "grid2dphysical.h"

class Grid2DFlux: public Grid2D
{
public:
	Grid2DFlux(const Grid2DPhysical &GP);
	~Grid2DFlux();
};

#endif // GRID2DFLUX_H
