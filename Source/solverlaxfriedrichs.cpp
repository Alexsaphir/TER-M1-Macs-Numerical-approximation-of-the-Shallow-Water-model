#include "solverlaxfriedrichs.h"

SolverLaxFriedrichs::SolverLaxFriedrichs(double l, double r): Solver()
{
	m_uL = l;
	m_uR = r;

	m_xmin = -5.;
	m_xmax = 5.;

	m_dx = .01;

	m_N = (m_xmax - m_xmin) / m_dx + 1;

	m_tmax = 10.;
	m_t = 0.;
	m_dt = 0.;
	m_dtmax = 0.01;

	m_Current = NULL;
	m_Next = NULL;
	m_Flux = NULL;

	m_Current	= new GridPhysical(m_N);
	m_Next		= new GridPhysical(m_N);

	m_Flux		= new GridVirtual(*m_Current);

}

double SolverLaxFriedrichs::getX(int i) const
{
	if (i < 0 || i>= m_N)
		return 0.;
	return m_xmin + static_cast<double>(i) * m_dx;
}

void SolverLaxFriedrichs::swapGrid()
{
	std::swap(m_Current, m_Next);
}


void SolverLaxFriedrichs::initialCondition()
{
	for(int i=0; i<m_N; ++i)
	{
		double x = m_xmin + m_dx*static_cast<double>(i);
		if(x<0.)
		{
			m_Current->set(i, m_uL);
		}
		else
		{
			m_Current->set(i, m_uR);
		}
	}
}

void SolverLaxFriedrichs::solve()
{
	initialCondition();
	m_t = 0.;

	int k=0;
	saveTo3d("Output/3D_out", m_Current, true);

	while(m_t < m_tmax)
	{
		//saveGrid("Output/out-" + QString::number(k), m_Current);
		//Compute the Next u
		computeNext();
		saveTo3d("Output/3D_out", m_Current);
		++k;
	}
	//Save the last time
	//saveGrid("Output/out-" + QString::number(m_t), m_Current);
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
		double v = ( f( m_Current->get(i) ) + f( m_Current->get(i + 1) ) )*.5 - .5/(m_dt/m_dx)*( m_Current->get(i+1) - m_Current->get(i));


		m_Flux->set(i, v);
	}
}

void SolverLaxFriedrichs::computeNext()
{
	//Compute the Flux of u
	evaluateFlux();

	//Find the best m_dt
	m_dt = computeCFL();

	for(int i=1; i< m_N-1;++i)
	{
		//m_Next->set(i, m_Current->get(i) - m_dt/m_dx*( m_Flux->get(i) - m_Flux->get(i - 1) ) );

		double v = .5*( m_Current->get(i+1) + m_Current->get(i-1) ) - .5/(m_dt/m_dx)*( f( m_Current->get(i+1) ) - f( m_Current->get(i-1) ) );
		m_Next->set(i, v);
	}

	//Apply Boundary
	m_Next->set(0, m_Current->get(0));
	m_Next->set(m_N-1, m_Current->get(m_N-1));

	//Swap the grid
	swapGrid();

	//Increase the current time by the time step
	m_t+=m_dt;
}

double SolverLaxFriedrichs::computeCFL() const
{
	double tmp(0.);

	for(int i=1; i<m_Current->size(); ++i)
	{
		double der = (f(i) - f(i-1)) / m_dx;
		if (der > tmp)
			tmp =der;
	}
	tmp = m_dx/2. * 1./tmp;
	if (tmp > m_dtmax)
		return m_dtmax;
	return tmp;
}

SolverLaxFriedrichs::~SolverLaxFriedrichs()
{
	delete m_Current;
	delete m_Next;
	delete m_Flux;
}
