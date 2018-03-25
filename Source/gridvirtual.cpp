#include "gridvirtual.h"

GridVirtual::GridVirtual(const GridPhysical &GP): Grid(GP.size())
{

}

double GridVirtual::get(int i) const
{
	if(i<0 || i>m_n)
		return 0.;
	return m_V.at(i);
}

void GridVirtual::set(int i, double v)
{
	if(i<0 || i>m_n)
		return ;
	m_V.replace(i, v);
}

GridVirtual::~GridVirtual()
{

}
