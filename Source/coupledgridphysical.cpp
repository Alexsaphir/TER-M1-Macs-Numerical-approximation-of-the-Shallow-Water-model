#include "coupledgridphysical.h"

CoupledGridPhysical::CoupledGridPhysical(int N): CoupledGrid()
{
	m_grid1 = new GridPhysical(N);
	m_grid2 = new GridPhysical(N);
}

CoupledGridPhysical::~CoupledGridPhysical()
{

}
