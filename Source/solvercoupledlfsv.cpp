#include "solvercoupledlfsv.h"

SolverCoupledLFSV::SolverCoupledLFSV()
{

	m_g = 10.;

	m_xmin = -10.;
	m_xmax = 10.;
	m_dx = .05;
	m_N = (m_xmax - m_xmin) / m_dx + 1;

	m_tmax = 1.;
	m_t = 0.;
	m_dt = 0.;
	m_dtmax = 0.1;

	m_Current = new CoupledGridPhysical(m_N);
	m_Next = new CoupledGridPhysical(m_N);
	m_Flux = new CoupledGridFlux(*m_Current);
	m_Z = new GridPhysical(m_N);
	m_U = new GridPhysical(m_N);
}

void SolverCoupledLFSV::initialCondition()
{
	m_t = 0.;

#pragma omp parallel
	for(int i=0; i<m_N; ++i)
	{
		double x = m_xmin + m_dx*static_cast<double>(i);
		double z = .5*std::sin(x) + .5;
		double h = 3. - z;
		if (h<=0.)
			h = 0;
		double v = 1.;

		m_Current->setOnFirst(i, h);
		m_Z->set(i, z);
		m_Current->setOnSecond(i, v * h);
	}
}

void SolverCoupledLFSV::solve()
{
	initialCondition();

	saveGridCSV("FD0_beg.csv", m_Current->first(), m_Z);
	saveGridCSV("Z.csv", m_Z);
	computeSpeed();
	saveGridCSV("U_beg.csv", m_U);
	while(m_t < m_tmax)
	{
		//Compute the Next u
		m_dt = computeCFL();
		computeNext();
		std ::cout << "t:" << m_t << " dt:" << m_dt << std::endl;
	}
	computeSpeed();
	saveGridCSV("U.csv", m_U);
	saveGridCSV("FD0.csv", m_Current->first(), m_Z);
}


double SolverCoupledLFSV::getZ(int i) const
{
	return m_Z->get(i);
}

double SolverCoupledLFSV::getZ_mh(int i) const
{
	return std::max(getZ(i-1), getZ(i));
}

double SolverCoupledLFSV::getZ_ph(int i) const
{
	return std::max(getZ(i), getZ(i+1));
}

double SolverCoupledLFSV::getH(int i) const
{
	return m_Current->getOnFirst(i);
}

double SolverCoupledLFSV::getH_mhm(int i) const
{
	return getH_phm(i - 1);
}

double SolverCoupledLFSV::getH_mhp(int i) const
{
	return getH_php(i - 1);
}

double SolverCoupledLFSV::getH_phm(int i) const
{
	return std::max(0., getH(i) + getZ(i) - getZ_ph(i));
}

double SolverCoupledLFSV::getH_php(int i) const
{
	return std::max(0., getH(i+1) + getZ(i+1) - getZ_ph(i));
}

VectorR2 SolverCoupledLFSV::getU(int i) const
{
	return m_Current->get(i);
}

VectorR2 SolverCoupledLFSV::getU_mhm(int i) const
{
	return getU_phm(i - 1);
}

VectorR2 SolverCoupledLFSV::getU_mhp(int i) const
{
	return getU_php(i - 1);
}

VectorR2 SolverCoupledLFSV::getU_phm(int i) const
{
	double h = 0.;
	double q = 0.;

	h = getH_phm(i);
	if(getH(i) <= 0.)
		q = 0.;// There is no water so speed of water == 0.
	else
		q = h * m_Current->getOnSecond(i)/getH(i);

	return VectorR2(h, q);
}

VectorR2 SolverCoupledLFSV::getU_php(int i) const
{
	double h = 0.;
	double q = 0.;

	h = getH_php(i);
	if(getH(i+1) <= 0.)
		q = 0.;// There is no water so speed of water == 0.
	else
		q = h * m_Current->getOnSecond(i + 1)/getH(i + 1);

	return VectorR2(h, q);
}

VectorR2 SolverCoupledLFSV::getS(int i) const
{
	double q = 0.;

	q = m_g/2. * getH_phm(i) * getH_phm(i) - m_g/2. * getH_mhp(i) * getH_mhp(i);

	return VectorR2(0., q);
}

VectorR2 SolverCoupledLFSV::getFlux_mh(int i) const
{
	return Flux(getU_mhm(i), getU_mhp(i));
}

VectorR2 SolverCoupledLFSV::getFlux_ph(int i) const
{
	return Flux(getU_phm(i), getU_php(i));
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

VectorR2 SolverCoupledLFSV::Flux(VectorR2 wL, VectorR2 wR) const
{

	return .5*( F(wL) + F(wR) ) - .5*m_dt/m_dx *( wR - wL );
}

void SolverCoupledLFSV::evaluateFlux()
{
#pragma omp parallel
	for(int i=1; i<m_N - 1; ++i)
	{
		// Compute the flux Fi+1/2
		VectorR2 wL = getU_phm(i);
		VectorR2 wR = getU_php(i);

		VectorR2 tmp = .5*( F(wL) + F(wR) ) - .5*m_dx/m_dt*(wR - wL);

		m_Flux->set(i, tmp);
	}
}

double SolverCoupledLFSV::computeCFL() const
{
	double t = 0;
	for(int i=1; i<m_N - 1; ++i)
	{
		//Compute u
		double u = 0.;
		double h = getH(i);
		if (h <= 0.)
			u = 0.;
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
#pragma omp parallel for simd
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
