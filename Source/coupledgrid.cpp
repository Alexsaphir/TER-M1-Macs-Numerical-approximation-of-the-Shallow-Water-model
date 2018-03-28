#include "coupledgrid.h"

CoupledGrid::CoupledGrid()
{
	m_grid1 = NULL;
	m_grid2 = NULL;
}

CoupledGrid::~CoupledGrid()
{
	delete m_grid1;
	delete  m_grid2;
}

Grid* CoupledGrid::first() const
{
	return m_grid1;
}

Grid* CoupledGrid::second() const
{
	return m_grid2;
}

double CoupledGrid::get(int i, int idx_grid) const
{

	if(idx_grid == 1)
		return getOnFirst(i);
	else if(idx_grid == 2)
		return getOnSecond(i);
	else return 0.;
}

QPair<double, double> CoupledGrid::get(int i) const
{
	return qMakePair(getOnFirst(i), getOnSecond(i));
}

double CoupledGrid::getOnFirst(int i) const
{
	if(m_grid1->isValidIndex(i))
		return m_grid1->get(i);
	return 0.;
}

double  CoupledGrid::getOnSecond(int i) const
{
	if(m_grid2->isValidIndex(i))
		return m_grid2->get(i);
	return 0.;
}

void CoupledGrid::set(int i, double value, int idx_grid)
{
	if(idx_grid == 1)
		setOnFirst(i, value);
	else if(idx_grid == 2)
		setOnSecond(i, value);
}

void CoupledGrid::setOnFirst(int i, double value)
{
	if(m_grid1->isValidIndex(i))
		 m_grid1->set(i, value);
}

void CoupledGrid::setOnSecond(int i, double value)
{
	if(m_grid2->isValidIndex(i))
		 m_grid2->set(i, value);
}
