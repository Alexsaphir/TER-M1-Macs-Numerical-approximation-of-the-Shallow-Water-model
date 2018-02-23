#ifndef GRIDVIRTUAL_H
#define GRIDVIRTUAL_H

#include "grid.h"
#include "gridphysical.h"

class GridVirtual: public Grid
{
public:
	GridVirtual(const GridPhysical &GP);
	~GridVirtual();

	double get(int i) const;
	void set(int i, double v);
};

#endif // GRIDVIRTUAL_H
