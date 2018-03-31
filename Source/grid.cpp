#include "grid.h"

Grid::Grid(int N): m_n(N)
{
	m_V.reserve(m_n);
	m_V.fill(0, m_n);
}

Grid::~Grid()
{
	m_V.clear();
	m_V.squeeze();
}

int Grid::size() const
{
	return m_n;
}

double Grid::get(int i) const
{
	if(i<0 || i>=m_n)
	{
		qDebug() << "Get Grid error";
		return 0.;
	}
	return m_V.at(i);
}

void Grid::set(int i, double v)
{
	if(i<0 || i>=m_n)
	{
		qDebug() << "Set Grid error";
		return;
	}
	m_V.replace(i, v);
}
