#ifndef COUPLEDGRID2DPHYSICAL_H
#define COUPLEDGRID2DPHYSICAL_H

#include "coupledgrid2d.h"
#include "grid2dphysical.h"

class CoupledGrid2DPhysical: public CoupledGrid2D
{
public:
	CoupledGrid2DPhysical(int Nx, int Ny);
	~CoupledGrid2DPhysical();
};

#endif // COUPLEDGRID2DPHYSICAL_H
