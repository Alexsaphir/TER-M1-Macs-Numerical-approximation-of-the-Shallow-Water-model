#include "solvercoupledlf0.h"

SolverCoupledLF0::SolverCoupledLF0(double l, double r)
{
	m_uL = l;
	m_uR = r;

	m_g = 10.;

	m_xmin = -10.;
	m_xmax = 10.;
	m_dx = .005;
	m_N = (m_xmax - m_xmin) / m_dx + 1;

	m_tmax = 1.;
	m_t = 0.;
	m_dt = 0.;
	m_dtmax = 0.1;

	m_Current = new CoupledGridPhysical(m_N);
	m_Next = new CoupledGridPhysical(m_N);
	m_Flux = new CoupledGridFlux(*m_Current);
}

VectorR2 SolverCoupledLF0::F(const VectorR2 &W) const
{
	return VectorR2(F1(W), F2(W));
}

double SolverCoupledLF0::F1(const VectorR2 &W) const
{
	return W.first * W.first /2.;
	return W.second;//q
}

double SolverCoupledLF0::F2(const VectorR2 &W) const
{
	return 0;
	return W.second*W.second/W.first + m_g*W.first*W.first/2.;//q*q/h + g*h*h/2
}

void SolverCoupledLF0::evaluateFlux()
{

}

void SolverCoupledLF0::initialCondition()
{
#pragma omp parallel
	for(int i=0; i<m_N; ++i)
	{
		double x = m_xmin + m_dx*static_cast<double>(i);

		if(x<=0.)
		{
			m_Current->setOnFirst(i, m_uL);
		}
		else
		{
			m_Current->setOnFirst(i, m_uR);
		}

		m_Current->setOnSecond(i, 0.);
	}
}

void Solver::solve()
{
	initialCondition();
	m_t = 0.;

	while(m_t < m_tmax)
	{
		//Compute the Next u
		computeNext();
		std ::cout << m_t << std::endl;
	}
	saveGridCSV("X:\outS2.csv", m_Current->first());
}

void SolverCoupledLF0::computeNext()
{

}

double SolverCoupledLF0::computeCFL() const
{

}
