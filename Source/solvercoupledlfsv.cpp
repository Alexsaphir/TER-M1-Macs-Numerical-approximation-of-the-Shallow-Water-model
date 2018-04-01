#include "solvercoupledlfsv.h"

SolverCoupledLFSV::SolverCoupledLFSV(double l, double r)
{
	m_uL = l;
	m_uR = r;

	m_g = 10.;

	m_xmin = -10.;
	m_xmax = 10.;
	m_dx = .001;
	m_N = (m_xmax - m_xmin) / m_dx + 1;

	m_tmax = 1.;
	m_t = 0.;
	m_dt = 0.;
	m_dtmax = 0.1;

	m_Current = new CoupledGridPhysical(m_N);
	m_Next = new CoupledGridPhysical(m_N);
	m_Flux = new CoupledGridFlux(*m_Current);
	m_H = new GridPhysical(m_N);
}

VectorR2 SolverCoupledLFSV::F(const VectorR2 &W) const
{
	return VectorR2(F1(W), F2(W));
}

double SolverCoupledLFSV::F1(const VectorR2 &W) const
{
	return W.y;//q
}

double SolverCoupledLFSV::F2(const VectorR2 &W) const
{
	return W.y*W.y/W.x + m_g*W.x*W.x/2.;//q*q/h + g*h*h/2
}

void SolverCoupledLFSV::initialCondition()
{
	//h = .04*x^2

#pragma omp parallel
	for(int i=0; i<m_N; ++i)
	{
		double c = 2;

		m_H->set(i, .04*getX(i)*getX(i));
		if( ( c-m_H->get(i) ) <0.)
		{
			m_Current->setOnFirst(i, 0);
		}
		else
		{
			m_Current->setOnFirst(i, c-m_H->get(i));
		}

		m_Current->setOnSecond(i, 0.);
	}
}

void SolverCoupledLFSV::exportData() const
{
	saveGridCSV("SV_ u.csv", m_Current->first());
	saveGridCSV("SV_U.csv", m_Current->first(), m_H);
	saveGridCSV("SV_Uv.csv", m_Current->second());
	saveGridCSV("SV_H.csv", m_H);
}

void SolverCoupledLFSV::evaluateFlux()
{
#pragma omp parallel
	for(int i=0; i<m_N - 1; ++i)
	{
		// Compute the flux Fi+1/2
		VectorR2 wL = m_Current->get(i);
		VectorR2 wR = m_Current->get(i+1);

		VectorR2 tmp = .5*( F(wL) + F(wR) ) - .5*m_dx/m_dt*(wR -wL);

		m_Flux->set(i, tmp);
	}
}

void SolverCoupledLFSV::solve()
{
	initialCondition();

	while(m_t < m_tmax)
	{
		//Compute the Next u
		m_dt = computeCFL();
		computeNext();
		std ::cout << "t:" << m_t << " dt:" << m_dt << std::endl;
	}
}

double SolverCoupledLFSV::computeCFL() const
{
	double t = 0;
	for(int i=1; i<m_N - 1; ++i)
	{
		VectorR2 D = ( m_Current->get(i+1) - m_Current->get(i-1) ) / (2.*m_dx);
		D.abs();

		if( t< D.x)
			t = D.x;
		if( t < D.y)
			t = D.y;
	}

	//Max time step
	t = m_dx / 2. * 1./t;

	if(t > m_dtmax)
		t= m_dtmax;
	if(t+m_t > m_tmax)
		return m_tmax - m_t;
	return t;
}

void SolverCoupledLFSV::swapCoupledGrid()
{
	std::swap(m_Current, m_Next);
}

void SolverCoupledLFSV::computeNext()
{
	evaluateFlux();

	#pragma omp parallel
	for(int i=1; i<m_N-1; ++i)
	{
		VectorR2 tmp = m_Current->get(i) - m_dt/m_dx * (m_Flux->get(i) - m_Flux->get(i-1) );
		m_Next->set(i, tmp);
	}

	//Boundary Condition
	// Dirichlet
	m_Next->set(0, m_Current->get(0));
	m_Next->set(m_N - 1, m_Current->get(m_N-1));

	swapCoupledGrid();
	m_t+=m_dt;
}
