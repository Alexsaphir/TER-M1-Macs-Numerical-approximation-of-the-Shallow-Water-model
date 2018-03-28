#ifndef GRIDFLUX_H
#define GRIDFLUX_H

#include "grid.h"
#include "gridphysical.h"

class GridFlux: public Grid
{
public:
	GridFlux(const GridPhysical &GP);
	~GridFlux();

	double get(int i) const;
	void set(int i, double v);
};

#endif // GRIDFLUX_H
