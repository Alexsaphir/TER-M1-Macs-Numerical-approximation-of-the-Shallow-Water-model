#ifndef SOLVERCOUPLEDLFSV2_H
#define SOLVERCOUPLEDLFSV2_H

#include <algorithm>

#include "solvercoupledlfsv.h"

class SolverCoupledLFSV2 : public SolverCoupledLFSV
{
public:
	SolverCoupledLFSV2();

private:
	double minmod(double x, double y) const;

	double getW_l(double wim, double wi, double wip) const;
	double getW_r(double wim, double wi, double wip) const;

	double getZ_l(int i) const;
	double getZ_r(int i) const;

	double getH_l(int i) const;
	double getH_r(int i) const;
};

#endif // SOLVERCOUPLEDLFSV2_H
