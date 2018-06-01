#include "solvercoupledlfsv.h"

SolverCoupledLFSV::SolverCoupledLFSV()
{
	m_g = 10.;

	m_Current = new CoupledGridPhysical(m_N);
	m_Next = new CoupledGridPhysical(m_N);
	m_Flux = new CoupledGridFlux(*m_Current);
	m_Z = new GridPhysical(m_N);
}

SolverCoupledLFSV::SolverCoupledLFSV(int N): Solver(N)
{
	m_g = 10.;

	m_Current = new CoupledGridPhysical(m_N);
	m_Next = new CoupledGridPhysical(m_N);
	m_Flux = new CoupledGridFlux(*m_Current);
	m_Z = new GridPhysical(m_N);
}

void SolverCoupledLFSV::initialCondition()
{
	//initialConditionOscillating();
	//initialConditionDam();
	initAnthenden();
	/*
	m_t = 0.;
	m_tmax = 2.;
#pragma omp parallel
	for(int i=0; i<m_N; ++i)
	{
		double x = m_xmin + m_dx*static_cast<double>(i);
		if(i==0)
		{
			m_Current->setOnFirst(i, 1.);
			m_Current->setOnSecond(i, m_Current->getOnFirst(i) * 5.);
		}
		if(x<=0.)
			m_Z->set(i, 2);
		if(x>0)
			m_Current->setOnFirst(i, .5);

	}

	initFunc(dynamic_cast<GridPhysical*>(m_Current->first()), 3., .5);
	initialConditionOscillating();
	*/
}

void SolverCoupledLFSV::initialConditionOscillating()
{
	m_tmax = 27;
	m_xmax = 1.;
	m_xmin = 0.;
	m_dx = (m_xmax - m_xmin) / (m_N - 1);
#pragma omp parallel
	for(int i=0; i<m_N; ++i)
	{
		double x = m_xmin + m_dx*static_cast<double>(i);
		m_Current->setOnSecond(i, 0.);
		m_Z->set(i, .5*(1-.5*(std::cos(M_PI*(x-.5)/.5)+1)));
		m_Current->setOnFirst(i, std::max(0., .4 - m_Z->get(i) + .04*std::sin((x-.5)/.25) - std::max(0., -4.+ m_Z->get(i))));
	}
}

void SolverCoupledLFSV::initialConditionRest()
{
	m_t = 0.;
#pragma omp parallel
	for(int i=0; i<m_N; ++i)
	{
		double x = m_xmin + m_dx*static_cast<double>(i);
		if(std::abs(x) < 8)
		{
			m_Current->setOnFirst(i, 16./5. - x*x/20.);

		}
		m_Z->set(i, x*x/20);

	}
}

void SolverCoupledLFSV::initialConditionDam()
{
#pragma omp parallel
	for(int i=0; i<m_N; ++i)
	{
		double x = m_xmin + m_dx*static_cast<double>(i);
		if(x < -7.1)
		{
			m_Z->set(i,4.);
			m_Current->setOnFirst(i, 5);
		}
		else if(x <=-7.)
		{
			m_Z->set(i,5.);
			m_Current->setOnFirst(i, 4);
		}
		else
		{
			//m_Z->set(i,1./x);
			m_Current->setOnFirst(i, .5);
		}
	}
}

void SolverCoupledLFSV::initAnthenden()
{
	m_xmin = 0.;
#pragma omp parallel
	for(int i=0; i<m_N; ++i)
	{
		double x = m_xmin + m_dx*static_cast<double>(i);
		if(x < 0)
		{
			m_Z->set(i,1 + exp(-x));
			m_Current->setOnFirst(i, x*std::log(x*x+1));
		}
		else
		{
			m_Z->set(i,1.+ cos(x));
			m_Current->setOnFirst(i, 1+exp(-x*x/2.));
		}
	}
}

void SolverCoupledLFSV::solve()
{
	initialCondition();

	double t_elapsed =0.;
	m_cache->addCorrectedGrid(m_Current->first()->getRawVector(), m_Z->getRawVector());
	m_cacheSpeed->addSpeedGrid(m_Current->first()->getRawVector(), m_Current->second()->getRawVector());
	while(m_t < m_tmax)
	{
		//Compute the Next u
		m_dt = computeCFL();
		computeNext();

		t_elapsed += m_dt;
		std ::cout << "t:" << m_t << " dt:" << m_dt << std::endl;

		if(t_elapsed >= m_dtmax)
		{
			m_cache->addCorrectedGrid(m_Current->first()->getRawVector(), m_Z->getRawVector());
			m_cacheSpeed->addSpeedGrid(m_Current->first()->getRawVector(), m_Current->second()->getRawVector());
			t_elapsed =0.;
		}

	}
	if(t_elapsed != 0.)
	{
		m_cache->addCorrectedGrid(m_Current->first()->getRawVector(), m_Z->getRawVector());
		m_cacheSpeed->addSpeedGrid(m_Current->first()->getRawVector(), m_Current->second()->getRawVector());
	}
	saveGridPython("LFSV_Z.csv", m_Z);
	m_cache->save("LFSV.csv");
	m_cacheSpeed->save("LFSV_V.csv");
}


VectorR2 SolverCoupledLFSV::F(VectorR2 w) const
{
	return VectorR2(F1(w), F2(w));
}

double SolverCoupledLFSV::F1(VectorR2 w) const
{
	return w.y;//q
}

double SolverCoupledLFSV::F2(VectorR2 w) const
{
	if( w.x <= 0.)
		return 0.;
	return w.y * w.y / w.x + m_g * w.x * w.x / 2.;
}


double SolverCoupledLFSV::getZ(int i) const
{
	return m_Z->get(i);
}

double SolverCoupledLFSV::getH(int i) const
{
	return m_Current->getOnFirst(i);
}

double SolverCoupledLFSV::getV(int i) const
{
	double h = getH(i);
	if(h <= 0.)
		return 0.;
	else
		return m_Current->second()->get(i)/h;
}


double SolverCoupledLFSV::getZ_mh(int i) const
{
	return getZ_ph(i-1);
}

double SolverCoupledLFSV::getZ_ph(int i) const
{
	return std::max(getZ(i), getZ(i+1));
}


double SolverCoupledLFSV::getH_mhm(int i) const
{
	return getH_phm(i-1);
}

double SolverCoupledLFSV::getH_mhp(int i) const
{
	return getH_php(i-1);
}

double SolverCoupledLFSV::getH_phm(int i) const
{
	return std::max(0., getH(i) + getZ(i) - getZ_ph(i));
}

double SolverCoupledLFSV::getH_php(int i) const
{
	return std::max(0., getH(i+1) + getZ(i+1) - getZ_ph(i));
}


VectorR2 SolverCoupledLFSV::getU_mhm(int i) const
{
	return getU_phm(i-1);
}

VectorR2 SolverCoupledLFSV::getU_mhp(int i) const
{
	return getU_php(i-1);
}

VectorR2 SolverCoupledLFSV::getU_phm(int i) const
{
	double h = getH_phm(i);
	return VectorR2(h, h * getV(i));
}

VectorR2 SolverCoupledLFSV::getU_php(int i) const
{
	double h = getH_php(i);
	return VectorR2(h, h * getV(i+1));
}


VectorR2 SolverCoupledLFSV::getS(int i) const
{
	double h1 = getH_phm(i);
	double h2 = getH_php(i-1);

	return VectorR2(0., .5*m_g*(h1*h1 - h2*h2) );
}


VectorR2 SolverCoupledLFSV::Flux(VectorR2 wL, VectorR2 wR) const
{

	return .5*( F(wL) + F(wR) ) - .5*m_dx/m_dt *( wR - wL );
}

void SolverCoupledLFSV::evaluateFlux()
{
#pragma omp parallel
	for(int i=0; i<m_N - 1; ++i)
	{
		// Compute the flux Fi+1/2
		VectorR2 wL = getU_phm(i);
		VectorR2 wR = getU_php(i);

		m_Flux->set(i, Flux(wL, wR));
	}
}

double SolverCoupledLFSV::computeCFL() const
{
	double t = 0;
	for(int i=0; i<m_N; ++i)
	{
		//Compute u
		double u = 0.;
		double h = getH(i);
		if (h <= 0.)
		{
			u = 0.;
			h = 0.;
		}
		else
			u = m_Current->second()->get(i) / h;
		t = std::max(t, std::max(std::abs(u + sqrt(m_g * h)), std::abs(u - sqrt(m_g * h)) ));
	}

	//Max time step
	t = m_dx / 2. * 1./t;

	if(t > m_dtmax)
		t= m_dtmax;
	if(t+m_t > m_tmax)
		return m_tmax - m_t;
	return t;
}

void SolverCoupledLFSV::computeNext()
{
	evaluateFlux();
#pragma omp parallel
	for(int i=1; i<m_N-1; ++i)
	{
		VectorR2 tmp = m_Current->get(i) - m_dt/m_dx * ( m_Flux->get(i) - m_Flux->get(i-1) - getS(i) );//Be carefull '-' before ( .... )
		m_Next->set(i, tmp);
	}

	//Boundary Condition
	// Dirichlet
	m_Next->set(0, m_Current->get(0));
	m_Next->set(m_N - 1, m_Current->get(m_N-1));

	//m_Next->set(0, m_Next->get(1));
	//m_Next->set(m_N - 1, m_Next->get(m_N-2));

	swapCoupledGrid();
	m_t+=m_dt;
}

void SolverCoupledLFSV::swapCoupledGrid()
{
	std::swap(m_Current, m_Next);
}

void SolverCoupledLFSV::computeSpeed()
{
#pragma omp parallel
	for(int i=0; i<m_N; ++i)
	{
		double h = m_Current->first()->get(i);
		if(h<=0.)
			m_U->set(i, 0.);
		else
			m_U->set(i, m_Current->second()->get(i)/h);
	}
}
