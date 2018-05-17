#ifndef SOLVERCOUPLEDLFSV_H
#define SOLVERCOUPLEDLFSV_H

#include <QDebug>

#include "solver.h"

#include "coupledgridflux.h"
#include "coupledgridphysical.h"

class SolverCoupledLFSV : public Solver
{
public:
	SolverCoupledLFSV();

	void initialCondition();
	void solve();

protected:

	double getZ(int i) const;


	double getH(int i) const;
	VectorR2 getU(int i) const;

private:
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

	VectorR2 getS(int i) const;

protected:
	VectorR2 getFlux_mh(int i) const;
	VectorR2 getFlux_ph(int i) const;
	void evaluateFlux();

	VectorR2 F(VectorR2 w) const;
	double F1(VectorR2 w) const;
	double F2(VectorR2 w) const;
	VectorR2 Flux(VectorR2 wL, VectorR2 wR) const;

	void computeNext();
	double computeCFL() const;
	void swapCoupledGrid();

	void computeSpeed();
private:
	double m_g;

	CoupledGridPhysical *m_Current;
	CoupledGridPhysical *m_Next;
	CoupledGridFlux *m_Flux;

	GridPhysical *m_Z;
	GridPhysical *m_U;
};

#endif // SOLVERCOUPLEDLFSV_H
