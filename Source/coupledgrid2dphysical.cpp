#include "coupledgrid2dphysical.h"

CoupledGrid2DPhysical::CoupledGrid2DPhysical(int Nx, int Ny)
{
	m_grid1 = new Grid2DPhysical(Nx, Ny);
	m_grid2 = new Grid2DPhysical(Nx, Ny);
}

CoupledGrid2DPhysical::~CoupledGrid2DPhysical()
{

}
