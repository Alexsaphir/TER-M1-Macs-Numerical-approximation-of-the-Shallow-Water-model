#ifndef COUPLEDGRIDPHYSICAL_H
#define COUPLEDGRIDPHYSICAL_H

#include "coupledgrid.h"
#include "gridphysical.h"

class CoupledGridPhysical: public CoupledGrid
{
public:
	CoupledGridPhysical(int N);
	~CoupledGridPhysical();
};

#endif // COUPLEDGRIDPHYSICAL_H
