#include "solvercoupledlfsv2.h"

SolverCoupledLFSV2::SolverCoupledLFSV2()
{
	m_g = 10.;

	m_Current = new CoupledGridPhysical(m_N);
	m_Next = new CoupledGridPhysical(m_N);
	m_Flux = new CoupledGridFlux(*m_Current);
	m_Z = new GridPhysical(m_N);
	m_U = new GridPhysical(m_N);
}

void SolverCoupledLFSV2::initialCondition()
{
	m_t = 0.;

#pragma omp parallel
	for(int i=0; i<m_N; ++i)
	{
		double x = m_xmin + m_dx*static_cast<double>(i);
		m_Current->setOnSecond(i, 0.);
		m_Z->set(i, std::sin(x));
	}

	initFunc(dynamic_cast<GridPhysical*>(m_Current->first()), 3., 10.);
}

void SolverCoupledLFSV2::solve()
{
	initialCondition();

	double t_elapsed =0.;
	m_cache->addGrid(m_Current->first()->getRawVector());
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
			m_cache->addGrid(m_Current->first()->getRawVector());
			m_cacheSpeed->addSpeedGrid(m_Current->first()->getRawVector(), m_Current->second()->getRawVector());
			t_elapsed =0.;
		}

	}
	if(t_elapsed != 0.)
	{
		m_cache->addGrid(m_Current->first()->getRawVector());
		m_cacheSpeed->addSpeedGrid(m_Current->first()->getRawVector(), m_Current->second()->getRawVector());
	}
	m_cache->save("LFSV2.csv");
	m_cacheSpeed->save("LFSV2_V.csv");
}


VectorR2 SolverCoupledLFSV2::F(VectorR2 w) const
{
	return VectorR2(F1(w), F2(w));
}

double SolverCoupledLFSV2::F1(VectorR2 w) const
{
	return w.y;//q
}

double SolverCoupledLFSV2::F2(VectorR2 w) const
{
	if( w.x <= 0.)
		return 0.;
	return w.y * w.y / w.x + m_g * w.x * w.x / 2.;
}


double SolverCoupledLFSV2::minmod(double x, double y) const
{
	if(x>=0 && y>=0)
		return std::min(x, y);
	if(x<=0 && y<=0)
		return std::max(x, y);
	return 0.;

}

double SolverCoupledLFSV2::getW_l(double wim, double wi, double wip) const
{
	return wi - .5*minmod(wi - wim, wip - wi);
}

double SolverCoupledLFSV2::getW_r(double wim, double wi, double wip) const
{
	return wi + .5*minmod(wi - wim, wip - wi);
}


double SolverCoupledLFSV2::getZ(int i) const
{
	return m_Z->get(i);
}

double SolverCoupledLFSV2::getH(int i) const
{
	return m_Current->getOnFirst(i);
}

double SolverCoupledLFSV2::getV(int i) const
{
	double h = getH(i);
	if(h <= 0.)
		return 0.;
	else
		return m_Current->second()->get(i)/h;
}


double SolverCoupledLFSV2::getZ_l(int i) const
{
	return getW_l(getZ(i-1), getZ(i), getZ(i+1));
}

double SolverCoupledLFSV2::getZ_r(int i) const
{
	return getW_r(getZ(i-1), getZ(i), getZ(i+1));
}

double SolverCoupledLFSV2::getZ_mh(int i) const
{
	return getZ_ph(i-1);
}

double SolverCoupledLFSV2::getZ_ph(int i) const
{
	if(i == 1)
		return getZ_l(i+1);
	if(i == m_N-2)
		return getZ_r(i);

	return std::max(getZ_r(i), getZ_l(i+1));
}


double SolverCoupledLFSV2::getH_l(int i) const
{
	return getW_l(getH(i-1), getH(i), getH(i+1));
}

double SolverCoupledLFSV2::getH_r(int i) const
{
	return getW_r(getH(i-1), getH(i), getH(i+1));
}

double SolverCoupledLFSV2::getH_mhm(int i) const
{
	return getH_phm(i - 1);
}

double SolverCoupledLFSV2::getH_mhp(int i) const
{
	return getH_php(i - 1);
}

double SolverCoupledLFSV2::getH_phm(int i) const
{
	return std::max(0., getH_r(i) + getZ_r(i) - getZ_ph(i));
}

double SolverCoupledLFSV2::getH_php(int i) const
{
	return std::max(0., getH_l(i+1) + getZ_l(i+1) - getZ_ph(i));
}


double SolverCoupledLFSV2::getV_l(int i) const
{
	return getW_l(getV(i-1), getV(i), getV(i+1));
}

double SolverCoupledLFSV2::getV_r(int i) const
{
	return getW_r(getV(i-1), getV(i), getV(i+1));
}


VectorR2 SolverCoupledLFSV2::getU_mhm(int i) const
{
	return getU_phm(i-1);
}

VectorR2 SolverCoupledLFSV2::getU_mhp(int i) const
{
	return getU_php(i-1);
}

VectorR2 SolverCoupledLFSV2::getU_phm(int i) const
{
	double h = getH_phm(i);
	return VectorR2(h, h*getV_r(i));
}

VectorR2 SolverCoupledLFSV2::getU_php(int i) const
{
	double h =getH_php(i);
	return VectorR2(h, h*getV_l(i+1));
}

VectorR2 SolverCoupledLFSV2::getS(int i) const
{
	return getS_phm(i) + getS_mhp(i);
}

VectorR2 SolverCoupledLFSV2::getS_mhp(int i) const
{
	double h0 = getH_l(i);
	double h1 = getH_mhp(i);

	return VectorR2(0., .5*m_g*(h0*h0 - h1*h1));
}

VectorR2 SolverCoupledLFSV2::getS_phm(int i) const
{
	double h0 = getH_phm(i);
	double h1 = getH_r(i);

	return VectorR2(0., .5*m_g*(h0*h0 - h1*h1));
}



VectorR2 SolverCoupledLFSV2::getS_ci(int i) const
{
	return VectorR2( 0., .5*m_g*(getH_l(i) + getH_r(i)) * (getZ_l(i) - getZ_r(i)) );
}

VectorR2 SolverCoupledLFSV2::Flux(VectorR2 wL, VectorR2 wR) const
{
	return .5*( F(wL) + F(wR) ) - .5*m_dx/m_dt *( wR - wL );
}





void SolverCoupledLFSV2::computeNext()
{
	evaluateFlux();
//#pragma omp parallel for simd
	int offset = 2;
	for(int i=offset; i<m_N-offset-1; ++i)
	{
		VectorR2 tmp = m_Current->get(i) - m_dt/m_dx * ( m_Flux->get(i) - m_Flux->get(i-1) - getS(i) - getS_ci(i));//Be carefull '-' before ( .... )
		m_Next->set(i, tmp);//
	}

	//Boundary Condition
	// Dirichlet
	for (int i=0; i<offset+1; ++i){
		m_Next->set(i, m_Current->get(i));
		m_Next->set(m_N-i - 1, m_Current->get(m_N-i - 1));
	}
	m_Next->set(m_N-offset, m_Current->get(m_N-offset));
	//m_Next->set(m_N - 1, m_Next->get(m_N-2));

	swapCoupledGrid();
	m_t+=m_dt;
}

void SolverCoupledLFSV2::evaluateFlux()
{
#pragma omp parallel
	for(int i=1; i<m_N - 2; ++i)
	{
		// Compute the flux Fi+1/2
		VectorR2 wL = getU_phm(i);
		VectorR2 wR = getU_php(i);

		m_Flux->set(i, Flux(wL, wR));
	}
}

double SolverCoupledLFSV2::computeCFL() const
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

void SolverCoupledLFSV2::swapCoupledGrid()
{
std::swap(m_Current, m_Next);
}

void SolverCoupledLFSV2::computeSpeed()
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
