#include "solverlaxfriedrichs2s.h"

SolverLaxFriedrichs2S::SolverLaxFriedrichs2S(double l, double r)
{
	m_uL = l;
	m_uR = r;

	m_xmin = -10.;
	m_xmax = 10.;

	m_dx = .005;

	m_N = (m_xmax - m_xmin) / m_dx + 1;

	m_tmax = 1.;
	m_t = 0.;
	m_dt = 0.;
	m_dtmax = 0.01;

	m_Current.first = NULL;
	m_Current.second = NULL;

	m_Next.first = NULL;
	m_Next.second = NULL;

	m_Flux.first = NULL;
	m_Flux.second = NULL;

	m_Current.first = new GridPhysical(m_N);
	m_Current.second = new GridPhysical(m_N);

	m_Next.first = new GridPhysical(m_N);
	m_Next.second = new GridPhysical(m_N);

	m_Flux.first = new GridVirtual(*m_Current.first);
	m_Flux.second = new GridVirtual(*m_Current.second);

	std::cout << "m_dx" << m_dx << std::endl;
}

double SolverLaxFriedrichs2S::getX(int i) const
{
	if (i < 0 || i>= m_N)
		return 0.;
	return m_xmin + static_cast<double>(i) * m_dx;
}

void SolverLaxFriedrichs2S::swapGrid()
{
	std::swap(m_Current, m_Next);
}

void SolverLaxFriedrichs2S::initialCondition()
{
#pragma omp parallel
	for(int i=0; i<m_N; ++i)
	{
		double x = m_xmin + m_dx*static_cast<double>(i);

		if(x<0.)
		{
			m_Current.first->set(i, m_uL);
		}
		else
		{
			m_Current.first->set(i, m_uR);
		}

		m_Current.second->set(i, 0.);
	}
}
