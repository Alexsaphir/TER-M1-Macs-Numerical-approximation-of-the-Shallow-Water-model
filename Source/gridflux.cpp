#include "gridflux.h"

GridFlux::GridFlux(const GridPhysical &GP): Grid(GP.size() - 1)
{
}

GridFlux::~GridFlux()
{
}

double GridFlux::get(int i) const
{
	if(i<0 || i>m_n)
		return 0.;
	return m_V.at(i);
}

void GridFlux::set(int i, double v)
{
	if(i<0 || i>m_n)
		return ;
	m_V.replace(i, v);
}
