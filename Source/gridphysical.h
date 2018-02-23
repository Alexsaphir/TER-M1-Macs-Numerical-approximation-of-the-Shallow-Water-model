#ifndef GRIDPHYSICAL_H
#define GRIDPHYSICAL_H

#include "grid.h"

class GridPhysical: public Grid
{
public:
	GridPhysical(int N);
	~GridPhysical();

	double get(int i) const;
	void set(int i, double v);
};

#endif // GRIDPHYSICAL_H
