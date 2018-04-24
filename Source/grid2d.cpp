#include "grid2d.h"

Grid2D::Grid2D(int Nx, int Ny): m_nx(Nx), m_ny(Ny)
{
	m_V.reserve(m_nx * m_ny);
	m_V.fill(0., m_nx * m_ny);
}

Grid2D::~Grid2D()
{
	m_V.clear();
	m_V.squeeze();
}

int Grid2D::sizeX() const
{
	return m_nx;
}

int Grid2D::sizeY() const
{
	return m_ny;
}

double Grid2D::get(int i, int j) const
{
	if(i<0 || i>=m_nx)
	{
		qDebug() << "Get Grid error";
		return 0.;
	}
	if(j<0 || j>=m_ny)
	{
		qDebug() << "Get Grid error";
		return 0.;
	}
	return m_V.at(m_nx * j + i);
}

void Grid2D::set(int i, int j, double v)
{
	if(i<0 || i>=m_nx)
	{
		qDebug() << "Set Grid error";
		return;
	}
	if(j<0 || j>=m_ny)
	{
		qDebug() << "Set Grid error";
		return;
	}
	m_V.replace(m_nx * j + i, v);
}

