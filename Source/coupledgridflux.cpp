#include "coupledgridflux.h"

CoupledGridFlux::CoupledGridFlux(const CoupledGridPhysical &CGP): CoupledGrid()
{
	m_grid1 = new GridFlux( *static_cast<GridPhysical*>(CGP.first()) );
	m_grid2 = new GridFlux(*static_cast<GridPhysical*>(CGP.second()));
}

CoupledGridFlux::~CoupledGridFlux()
{

}
