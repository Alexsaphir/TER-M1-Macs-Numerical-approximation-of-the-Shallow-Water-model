#include "solverburger.h"

SolverBurger::SolverBurger(double l, double r)
{
	m_uL = l;
	m_uR = r;

	m_Current = new GridPhysical(m_N);
	m_Next = new GridPhysical(m_N);
	m_Flux = new GridFlux(*m_Current);
}

void SolverBurger::initialCondition()
{
	m_t = 0.;

	initFunc(m_Current, m_uL, m_uR);
}

void SolverBurger::solve()
{
	initialCondition();

	double t_elapsed =0.;

	m_cache->addGrid(m_Current->getRawVector());

	while(m_t < m_tmax)
	{
		//Compute the Next u
		m_dt = computeCFL();
		computeNext();

		//Stats and saving stuff
		t_elapsed += m_dt;
		std ::cout << "t:" << m_t << " dt:" << m_dt << std::endl;

		if(t_elapsed >= m_dtmax)
		{
			m_cache->addGrid(m_Current->getRawVector());
			t_elapsed =0.;
		}

	}
	if(t_elapsed != 0.)
		m_cache->addGrid(m_Current->getRawVector());

	m_cache->save("Burgers.csv");
}

double SolverBurger::F(const double &W) const
{
	return W*W/2.;
}

double SolverBurger::Fder(const double &W) const
{
	return W;
}

void SolverBurger::evaluateFlux()
{
#pragma omp parallel
	for(int i=0; i<m_N - 1; ++i)
	{
		// Compute the flux Fi+1/2
		double wL = m_Current->get(i);
		double wR = m_Current->get(i+1);

		double tmp = .5*( F(wL) + F(wR) ) - .5*m_dx/m_dt*(wR - wL);

		m_Flux->set(i, tmp);
	}
}

void SolverBurger::computeNext()
{
	evaluateFlux();

#pragma omp parallel
	for(int i=1; i<m_N-1; ++i)
	{
		double tmp = m_Current->get(i) - m_dt/m_dx * (m_Flux->get(i) - m_Flux->get(i-1) );
		m_Next->set(i, tmp);
	}

	//Boundary Condition
	// Dirichlet
	m_Next->set(0, m_Current->get(0));
	m_Next->set(m_N - 1, m_Current->get(m_N-1));

	swapGrid();
	m_t+=m_dt;
}

double SolverBurger::computeCFL() const
{
	double t = 0;
	for(int i=0; i<m_N; ++i)
	{
		double D = std::abs(Fder(m_Current->get(i)));

		if( t< D)
			t = D;
	}

	//Max time step
	t = m_dx / 2. * 1./t;

	if(t > m_dtmax)
		t= m_dtmax;
	if(t+m_t > m_tmax)
		return m_tmax - m_t;
	return t;
}

void SolverBurger::swapGrid()
{
	std::swap(m_Current, m_Next);
}
