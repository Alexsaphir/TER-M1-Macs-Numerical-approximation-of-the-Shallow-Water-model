#include "solverlaxfriedrichs2s.h"

SolverLaxFriedrichs2S::SolverLaxFriedrichs2S(double l, double r)
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

	std::cout << "m_N " << m_N << std::endl;
}

void SolverLaxFriedrichs2S::solve()
{
	initialCondition();
	m_t = 0.;

	while(m_t < m_tmax)
	{

		//Compute the Next u
		computeNext();
		std ::cout << m_t << std::endl;
	}
	saveGridCSV("outS2.csv", m_Current->first());
	saveGridCSV("outS2_q.csv", m_Current->first());

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
			m_Current->setOnFirst(i, m_uL);
		}
		else
		{
			m_Current->setOnFirst(i, m_uR);
		}

		m_Current->setOnSecond(i, 0.);
	}
}

VectorR2 SolverLaxFriedrichs2S::F(VectorR2 W) const
{
	VectorR2 FW;

	FW.first = F1(W);
	FW.second = F2(W);

	return FW;
}

double SolverLaxFriedrichs2S::F1(VectorR2 W) const
{
	return W.second;//q
}

double SolverLaxFriedrichs2S::F2(VectorR2 W) const
{
	return W.second*W.second/W.first + m_g*W.first*W.first/2.;//q*q/h + g*h*h/2
}

void SolverLaxFriedrichs2S::evaluateFlux()
{
#pragma omp parallel
	for(int i=0; i< m_N-1;++i)
	{
		VectorR2 Wr(m_Current->get(i + 1));
		VectorR2 Wl(m_Current->get(i));


		VectorR2 tmp = .5*(F(Wl) + F(Wr)) - .5/(m_dt/m_dx)*(Wr - Wl);

		m_Flux->set(i, tmp);
	}
}


double SolverLaxFriedrichs2S::computeCFL() const
{
	double tmp(0.);

	//return m_dtmax;

	for(int i=1; i<m_Current->first()->size(); ++i)
	{
		double der  = ( F1(m_Current->get(i)) - F1(m_Current->get(i-1)) ) / m_dx;
		double der2 = ( F2(m_Current->get(i)) - F2(m_Current->get(i-1)) ) / m_dx;

		if(der < der2)
			der = der2;

		if (der > tmp)
			tmp = der;
	}
	tmp = m_dx/2. * 1./tmp;

	if (tmp > m_dtmax)
		tmp = m_dtmax;
	if(tmp + m_t > m_tmax)
	{
		return m_tmax - m_t;
	}
	return tmp;
}

void SolverLaxFriedrichs2S::computeNext()
{
	//Find the best m_dt
	m_dt = computeCFL();

	//Compute the Flux of u
	evaluateFlux();
#pragma omp parallel
	for(int i=1; i< m_N-1;++i)
	{
		m_Next->set(i, m_Current->get(i) - m_dt/m_dx*( m_Flux->get(i) - m_Flux->get(i - 1) ) );
	}

	//Apply Boundary
	m_Next->setOnFirst(0, m_Current->getOnFirst(0));
	m_Next->setOnSecond(0, m_Current->getOnSecond(0));


	m_Next->setOnFirst(m_N-1, m_Current->getOnFirst(m_N-1));
	m_Next->setOnSecond(m_N-1, m_Current->getOnSecond(m_N-1));

	//Swap the grid
	swapGrid();

	//Increase the current time by the time step
	m_t+=m_dt;
}
