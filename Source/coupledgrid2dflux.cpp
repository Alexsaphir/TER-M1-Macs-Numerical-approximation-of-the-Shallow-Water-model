#include "coupledgrid2dflux.h"

CoupledGrid2DFlux::CoupledGrid2DFlux(const CoupledGrid2DPhysical &CGP)
{
	m_grid1 = new Grid2DFlux( *static_cast<Grid2DPhysical*>(CGP.first()) );
	m_grid2 = new Grid2DFlux(*static_cast<Grid2DPhysical*>(CGP.second()));
}

CoupledGrid2DFlux::~CoupledGrid2DFlux()
{

}
