#include "solverlaxfriedrichs.h"

SolverLaxFriedrichs::SolverLaxFriedrichs()
{
	m_xmin = -5.;
	m_xmax = 5.;

	m_dx = .01;

	m_N = (m_xmax - m_xmin) * m_dx + 1;

	m_tmax = 1.;
	m_t = 0.;
	m_dt = 0.;

	m_Current = NULL;
	m_Next = NULL;
	m_Flux = NULL;

	m_Current	= new GridPhysical(m_N);
	m_Next		= new GridPhysical(m_N);

	m_Flux		= new GridVirtual(*m_Current);

}

void SolverLaxFriedrichs::swapGrid()
{
	std::swap(m_Current, m_Next);
}

void SolverLaxFriedrichs::saveCurrentGrid() const
{

}

void SolverLaxFriedrichs::initialCondition()
{
	for(int i=0; i<m_N; ++i)
	{
		double x = m_xmin + m_dx*static_cast<double>(i);
		if(x<3.)
		{
			m_Current->set(i, 1.);
		}
		else
		{
			m_Current->set(i, 4.);
		}
	}
}

double SolverLaxFriedrichs::f(int i) const
{
	double y = m_Current->get(i);
	y *= y;
	y /=2.;
	return y;
}

void SolverLaxFriedrichs::evaluateFlux()
{
	for(int i=1; i< m_N-1;++i)
	{
		double v = ( f( m_Current->get(i) ) + f( m_Current->get(i + 1) ) )*.5 - .5*m_dx/m_dt*( m_Current->get(i) + m_Current->get(i+1));


		m_Flux->set(i, v);
	}
}

void SolverLaxFriedrichs::computeNext()
{
	for(int i=1; i< m_N-1;++i)
	{
		m_Next->set(i, m_Current->get(i) - m_dt/m_dx*( m_Flux->get(i) - m_Flux->get(i - 1) ) );
	}
}

void SolverLaxFriedrichs::solve()
{
	initialCondition();
	m_t = 0.;

	while(m_t < m_tmax)
	{
		//Find the best m_dt
		m_dt = .01;

		//Compute the Flux of u
		evaluateFlux();

		//Compute the Next u
		computeNext();

		//Apply Boundary
		m_Next->set(0, m_Current->get(0));
		m_Next->set(m_N-1, m_Current->get(m_N-1));

		m_t+=m_dt;
	}
}

SolverLaxFriedrichs::~SolverLaxFriedrichs()
{
	delete m_Current;
	delete m_Next;
	delete m_Flux;
}
