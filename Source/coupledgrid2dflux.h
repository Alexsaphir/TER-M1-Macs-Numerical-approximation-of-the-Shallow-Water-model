#ifndef COUPLEDGRID2DFLUX_H
#define COUPLEDGRID2DFLUX_H

#include "coupledgrid2d.h"
#include "coupledgrid2dphysical.h"
#include "grid2dflux.h"

class CoupledGrid2DFlux: public CoupledGrid2D
{
public:
	CoupledGrid2DFlux(const CoupledGrid2DPhysical &CGP);
	~CoupledGrid2DFlux();
};

#endif // COUPLEDGRID2DFLUX_H
