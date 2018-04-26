#ifndef SOLVER2DCOUPLEDLFSV_H
#define SOLVER2DCOUPLEDLFSV_H

#include "solver2d.h"

#include "coupledgrid2dflux.h"
#include "coupledgrid2dphysical.h"

class Solver2DCoupledLFSV
{
public:
	Solver2DCoupledLFSV();
	void initialCondition();
	void solve();
};

#endif // SOLVER2DCOUPLEDLFSV_H
