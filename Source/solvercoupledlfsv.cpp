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
	m_Z = new GridPhysical(m_N);
}

void SolverCoupledLFSV::initialCondition()
{

}

void SolverCoupledLFSV::solve()
{

}


double SolverCoupledLFSV::getZ(int i) const
{
	return m_Z->get(i);
}

double SolverCoupledLFSV::getZ_mh(int i) const
{
	return getZ_ph(i-1);
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

	h = getH_php(i + 1);
	if(getH(i+1) <= 0.)
		q = 0.;// There is no water so speed of water == 0.
	else
		q = h * m_Current->getOnSecond(i + 1)/getH(i + 1);

	return VectorR2(h, q);
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
	return w.y;
}

double SolverCoupledLFSV::F2(VectorR2 w) const
{
	return w.x * w.y + m_g * w.x * w.x / 2.;
}

VectorR2 SolverCoupledLFSV::Flux(VectorR2 wL, VectorR2 wR) const
{
	return .5*( ( F(wL) + F(wR) ) - m_dt/m_dx *( wR - wL ) );
}
