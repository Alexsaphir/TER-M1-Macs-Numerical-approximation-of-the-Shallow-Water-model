#include "solvercoupledlfsv2.h"

SolverCoupledLFSV2::SolverCoupledLFSV2(): SolverCoupledLFSV()
{

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
