#include "solver2d.h"

Solver2D::Solver2D()
{
	m_xmax = 0.;
	m_xmin = 0.;
	m_dx = 0.;
	m_nx = 0;

	m_ymax = 0.;
	m_ymin = 0.;
	m_dy = 0.;
	m_ny = 0;

	m_t = 0.;
	m_tmax = 0.;
	m_dt = 0.;
	m_dtmax = 0.;
}

Solver2D::~Solver2D()
{

}

double Solver2D::getX(int i) const
{
	return m_xmin + static_cast<double>(i)*m_dx;
}

double Solver2D::getY(int i) const
{
	return m_xmin + static_cast<double>(i)*m_dx;
}
