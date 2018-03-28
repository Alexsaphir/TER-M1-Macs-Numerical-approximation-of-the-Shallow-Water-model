#ifndef COUPLEDGRIDFLUX_H
#define COUPLEDGRIDFLUX_H

#include "coupledgrid.h"
#include "coupledgridphysical.h"
#include "gridflux.h"

class CoupledGridFlux: public CoupledGrid
{
public:
	CoupledGridFlux(const CoupledGridPhysical &CGP);
	~CoupledGridFlux();
};

#endif // COUPLEDGRIDFLUX_H
