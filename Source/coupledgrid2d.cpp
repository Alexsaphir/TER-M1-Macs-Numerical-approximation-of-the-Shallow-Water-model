#include "coupledgrid2d.h"

CoupledGrid2D::CoupledGrid2D()
{
	m_grid1 = NULL;
	m_grid2 = NULL;
}

CoupledGrid2D::~CoupledGrid2D()
{
	delete m_grid1;
	delete m_grid2;
}

Grid2D *CoupledGrid2D::first() const
{
	return m_grid1;
}

Grid2D *CoupledGrid2D::second() const
{
	return m_grid2;
}

VectorR2 CoupledGrid2D::get(int i, int j) const
{
	return VectorR2(getOnFirst(i, j), getOnSecond(i, j));
}

double CoupledGrid2D::getOnFirst(int i, int j) const
{
	return m_grid1->get(i, j);
}

double CoupledGrid2D::getOnSecond(int i, int j) const
{
	return m_grid2->get(i, j);
}

void CoupledGrid2D::set(int i, int j, VectorR2 value)
{
	setOnFirst(i, j, value.x);
	setOnSecond(i, j, value.y);
}

void CoupledGrid2D::setOnFirst(int i, int j, double value)
{
	m_grid1->set(i, j, value);
}

void CoupledGrid2D::setOnSecond(int i, int j, double value)
{
	m_grid2->set(i, j, value);
}
