#ifndef SOLVERCOUPLEDLFSV2_H
#define SOLVERCOUPLEDLFSV2_H

#include <algorithm>

#include "solvercoupledlfsv.h"

class SolverCoupledLFSV2 : public SolverCoupledLFSV
{
public:
	SolverCoupledLFSV2();
	void solve();

protected:
	void computeNext();
	void evaluateFlux();

private:
	double minmod(double x, double y) const;

	double getV(int i) const;

	double getW_l(double wim, double wi, double wip) const;
	double getW_r(double wim, double wi, double wip) const;

	double getZ_l(int i) const;
	double getZ_r(int i) const;

	double getH_l(int i) const;
	double getH_r(int i) const;

	double getV_l(int i) const;
	double getV_r(int i) const;

	double getZ_mh(int i) const;
	double getZ_ph(int i) const;

	double getH_mhm(int i) const;
	double getH_mhp(int i) const;
	double getH_phm(int i) const;
	double getH_php(int i) const;

	VectorR2 getU_mhm(int i) const;
	VectorR2 getU_mhp(int i) const;
	VectorR2 getU_phm(int i) const;
	VectorR2 getU_php(int i) const;

	VectorR2 getS_mhm(int i) const;
	VectorR2 getS_mhp(int i) const;
	VectorR2 getS_phm(int i) const;
	VectorR2 getS_php(int i) const;
	VectorR2 getS_ci(int i) const;

	VectorR2 getF_l(int i) const;
	VectorR2 getF_r(int i) const;
};

#endif // SOLVERCOUPLEDLFSV2_H
