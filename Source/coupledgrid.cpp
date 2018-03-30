#include "coupledgrid.h"

CoupledGrid::CoupledGrid()
{
	m_grid1 = NULL;
	m_grid2 = NULL;

}

CoupledGrid::~CoupledGrid()
{
	delete m_grid1;
	delete m_grid2;
}

Grid* CoupledGrid::first() const
{
	return m_grid1;
}

Grid* CoupledGrid::second() const
{
	return m_grid2;
}

VectorR2 CoupledGrid::get(int i) const
{
	return VectorR2(getOnFirst(i), getOnSecond(i));
}

double CoupledGrid::getOnFirst(int i) const
{
	return m_grid1->get(i);
}

double CoupledGrid::getOnSecond(int i) const
{
	return m_grid2->get(i);
}

void CoupledGrid::set(int i, VectorR2 value)
{
	setOnFirst(i, value.x);
	setOnSecond(i, value.y);
}

void CoupledGrid::setOnFirst(int i, double value)
{
	m_grid1->set(i, value);
}

void CoupledGrid::setOnSecond(int i, double value)
{
	m_grid2->set(i, value);
}
