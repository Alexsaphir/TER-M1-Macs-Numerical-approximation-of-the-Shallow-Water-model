#ifndef SOLVERCOUPLEDLFSV2_H
#define SOLVERCOUPLEDLFSV2_H

#include <algorithm>

#include "solver.h"
#include "coupledgridflux.h"
#include "coupledgridphysical.h"

class SolverCoupledLFSV2 : public Solver
{
public:
	SolverCoupledLFSV2();
	SolverCoupledLFSV2(int N);

	void initialCondition();
	void initialConditionOscillating();
	void initialConditionRest();

	void solve();

private:
	VectorR2 F(VectorR2 w) const;
	double F1(VectorR2 w) const;
	double F2(VectorR2 w) const;

	double minmod(double x, double y) const;
	double getW_l(double wim, double wi, double wip) const;
	double getW_r(double wim, double wi, double wip) const;

	double getZ(int i) const;
	double getH(int i) const;
	double getV(int i) const;

	double getZ_l(int i) const;
	double getZ_r(int i) const;
	double getZ_mh(int i) const;
	double getZ_ph(int i) const;

	double getH_l(int i) const;
	double getH_r(int i) const;
	double getH_mhm(int i) const;
	double getH_mhp(int i) const;
	double getH_phm(int i) const;
	double getH_php(int i) const;

	double getV_l(int i) const;
	double getV_r(int i) const;





	VectorR2 getU_mhm(int i) const;
	VectorR2 getU_mhp(int i) const;
	VectorR2 getU_phm(int i) const;
	VectorR2 getU_php(int i) const;

	VectorR2 getS(int i) const;
	VectorR2 getS_mhp(int i) const;
	VectorR2 getS_phm(int i) const;
	VectorR2 getS_ci(int i) const;

	VectorR2 Flux(VectorR2 wL, VectorR2 wR) const;

	void computeNext();
	void evaluateFlux();
	double computeCFL() const;
	void swapCoupledGrid();
	void computeSpeed();
protected:
	double m_g;

	CoupledGridPhysical *m_Current;
	CoupledGridPhysical *m_Next;
	CoupledGridFlux *m_Flux;

	GridPhysical *m_Z;
	GridPhysical *m_U;
};

#endif // SOLVERCOUPLEDLFSV2_H
