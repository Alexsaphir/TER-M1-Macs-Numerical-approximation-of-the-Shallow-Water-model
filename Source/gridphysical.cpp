#include "gridphysical.h"

GridPhysical::GridPhysical(int N): Grid(N)
{
}

double GridPhysical::get(int i) const
{
	if(i<0 || i>=m_n)
		return 0.;
	return m_V.at(i);
}

void GridPhysical::set(int i, double v)
{
	if(i<0 || i>=m_n)
		return ;
	m_V.replace(i, v);
}

GridPhysical::~GridPhysical()
{
}
