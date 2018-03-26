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
	m_dtmax = 0.0001;

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
	saveGridCSV("outS2.csv", m_Current.first);
	saveGridCSV("outS2_q.csv", m_Current.second);

}

double SolverLaxFriedrichs2S::getX(int i) const
{
	if (i < 0 || i>= m_N)
		return 0.;
	return m_xmin + static_cast<double>(i) * m_dx;
}

void SolverLaxFriedrichs2S::swapGrid()
{
	std::swap(m_Current.first, m_Next.first);
	std::swap(m_Current.second, m_Next.second);
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

QPair<double, double> SolverLaxFriedrichs2S::F(QPair<double, double> W) const
{
	QPair<double, double> FW;

	FW.first = F1(W);
	FW.second = F2(W);

	return FW;
}

double SolverLaxFriedrichs2S::F1(QPair<double, double> W) const
{
	return W.second;//q
}

double SolverLaxFriedrichs2S::F2(QPair<double, double> W) const
{
	return W.second*W.second/W.first + m_g*W.first*W.first/2.;//q*q/h + g*h*h/2
}

void SolverLaxFriedrichs2S::evaluateFlux()
{
#pragma omp parallel
	for(int i=0; i< m_N-1;++i)
	{
		QPair<double, double> Wr(m_Current.first->get(i + 1), m_Current.second->get(i + 1));
		QPair<double, double> Wl(m_Current.first->get(i), m_Current.second->get(i));


		QPair<double, double> tmp = .5*(F(Wl) + F(Wr)) - .5/(m_dt/m_dx)*(Wr - Wl);

		m_Flux.first->set(i, tmp.first);
		m_Flux.second->set(i, tmp.second);
	}
}


double SolverLaxFriedrichs2S::computeCFL() const
{
	double tmp(0.);

	//return m_dtmax;

	for(int i=1; i<m_Current.first->size(); ++i)
	{
		double der  = ( F1(qMakePair( m_Current.first->get(i), m_Current.second->get(i)) ) - F1( qMakePair(m_Current.first->get(i-1), m_Current.second->get(i-1)) ) ) / m_dx;
		double der2 = ( F2(qMakePair( m_Current.first->get(i), m_Current.second->get(i)) ) - F2( qMakePair(m_Current.first->get(i-1), m_Current.second->get(i-1)) ) ) / m_dx;

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
		m_Next.first->set(i, m_Current.first->get(i) - m_dt/m_dx*( m_Flux.first->get(i) - m_Flux.first->get(i - 1) ) );
		m_Next.second->set(i, m_Current.second->get(i) - m_dt/m_dx*( m_Flux.second->get(i) - m_Flux.second->get(i-1) ) );
	}

	//Apply Boundary
	m_Next.first->set(0, m_Current.first->get(0));
	m_Next.second->set(0, m_Current.second->get(0));

	m_Next.first->set(m_N-1, m_Current.first->get(m_N-1));
	m_Next.second->set(m_N-1, m_Current.second->get(m_N-1));

	//Swap the grid
	swapGrid();

	//Increase the current time by the time step
	m_t+=m_dt;
}
