#include "gridvirtual.h"

GridVirtual::GridVirtual(const GridPhysical &GP): Grid(GP.size() - 2)
{

}

double GridVirtual::get(int i) const
{
	if(i<1 || i>m_n)
		return 0.;
	return m_V.at(i-1);
}

void GridVirtual::set(int i, double v)
{
	if(i<1 || i>m_n)
		return ;
	m_V.replace(i-1, v);
}

GridVirtual::~GridVirtual()
{

}
