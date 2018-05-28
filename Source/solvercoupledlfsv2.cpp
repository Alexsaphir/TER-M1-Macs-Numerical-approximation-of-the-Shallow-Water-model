#include "solvercoupledlfsv2.h"

SolverCoupledLFSV2::SolverCoupledLFSV2(): SolverCoupledLFSV()
{

}

void SolverCoupledLFSV2::computeNext()
{
	evaluateFlux();
#pragma omp parallel for simd
	for(int i=1; i<m_N-1; ++i)
	{
		VectorR2 tmp = m_Current->get(i) - m_dt/m_dx * ( getF_l(i) - getF_r(i-1) - getS_ci(i) );//Be carefull '-' before ( .... )
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

void SolverCoupledLFSV2::evaluateFlux()
{
#pragma omp parallel
	for(int i=2; i<m_N - 2; ++i)
	{
		// Compute the flux Fi+1/2
		VectorR2 wL = getU_phm(i);
		VectorR2 wR = getU_php(i);

		VectorR2 tmp = .5*( F(wL) + F(wR) ) - .5*m_dx/m_dt*(wR - wL);

		m_Flux->set(i, tmp);
	}
}

double SolverCoupledLFSV2::minmod(double x, double y) const
{
	if(x>=0 && y>=0)
		return std::min(x, y);
	if(x<=0 && y<=0)
		return std::max(x, y);
	return 0.;

}

double SolverCoupledLFSV2::getV(int i) const
{
	double h = getH(i);
	if(h <= 0.)
		return 0.;// There is no water so speed of water == 0.
	else
		return m_Current->getOnSecond(i)/h;
}

double SolverCoupledLFSV2::getW_l(double wim, double wi, double wip) const
{
	return wi - .5*minmod(wi - wim, wip - wi);
}

double SolverCoupledLFSV2::getW_r(double wim, double wi, double wip) const
{
	return wi + .5*minmod(wi - wim, wip - wi);
}

double SolverCoupledLFSV2::getZ_l(int i) const
{
	return getW_l(getZ(i-1), getZ(i), getZ(i+1));
}

double SolverCoupledLFSV2::getZ_r(int i) const
{
	return getW_r(getZ(i-1), getZ(i), getZ(i+1));
}

double SolverCoupledLFSV2::getH_l(int i) const
{
	return getW_l(getH(i-1), getH(i), getH(i+1));
}

double SolverCoupledLFSV2::getH_r(int i) const
{
	return getW_r(getH(i-1), getH(i), getH(i+1));
}

double SolverCoupledLFSV2::getV_l(int i) const
{
	return getW_l(getV(i-1), getV(i), getV(i+1));
}

double SolverCoupledLFSV2::getV_r(int i) const
{
	return getW_r(getV(i-1), getV(i), getV(i+1));
}

double SolverCoupledLFSV2::getZ_mh(int i) const
{
	return getZ_ph(i-1);
}

double SolverCoupledLFSV2::getZ_ph(int i) const
{
	return std::max( getZ_r(i), getZ_l(i + 1));
}

double SolverCoupledLFSV2::getH_mhm(int i) const
{
	return getH_phm(i-1);
}

double SolverCoupledLFSV2::getH_mhp(int i) const
{
	return getH_php(i-1);
}

double SolverCoupledLFSV2::getH_phm(int i) const
{
	return std::max(0., getH_r(i) + getZ_r(i) - getZ_ph(i));
}

double SolverCoupledLFSV2::getH_php(int i) const
{
	return std::max(0., getH_l(i+1) + getZ_l(i+1) - getZ_ph(i));
}

VectorR2 SolverCoupledLFSV2::getU_mhm(int i) const
{
	return getU_phm(i - 1);
}

VectorR2 SolverCoupledLFSV2::getU_mhp(int i) const
{
	return getU_php(i - 1);
}

VectorR2 SolverCoupledLFSV2::getU_phm(int i) const
{
	double h = getH_phm(i);
	return VectorR2(h, h*getV_r(i));
}

VectorR2 SolverCoupledLFSV2::getU_php(int i) const
{
	double h = getH_php(i);
	return VectorR2(h, h*getV_l(i+1));
}

VectorR2 SolverCoupledLFSV2::getS_mhm(int i) const
{
	return getS_phm(i - 1);
}

VectorR2 SolverCoupledLFSV2::getS_mhp(int i) const
{
	return getS_php(i - 1);
}

VectorR2 SolverCoupledLFSV2::getS_phm(int i) const
{
	return VectorR2(0., .5*m_g*std::pow(getH_phm(i), 2) - .5*m_g*std::pow(getH_r(i),2) );
}

VectorR2 SolverCoupledLFSV2::getS_php(int i) const
{
	return VectorR2(0., .5*m_g*std::pow(getH_l(i), 2) - .5*m_g*std::pow(getH_mhp(i),2) );
}

VectorR2 SolverCoupledLFSV2::getS_ci(int i) const
{
	return VectorR2( 0., .5*m_g*( getH_l(i) + getH_r(i) )*( getZ_l(i) - getZ_r(i)) );
}

VectorR2 SolverCoupledLFSV2::getF_l(int i) const
{
	return getFlux_mh(i) - getS_phm(i);
}

VectorR2 SolverCoupledLFSV2::getF_r(int i) const
{
	return getFlux_ph(i) - getS_php(i);
}
