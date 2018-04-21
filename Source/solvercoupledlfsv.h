#ifndef SOLVERCOUPLEDLFSV_H
#define SOLVERCOUPLEDLFSV_H

#include <QDebug>

#include "solver.h"

#include "coupledgridflux.h"
#include "coupledgridphysical.h"

class SolverCoupledLFSV : public Solver
{
public:
	SolverCoupledLFSV(double l, double r);

	void initialCondition();
	void solve();

private:

	double getZ(int i) const;
	double getZ_mh(int i) const;
	double getZ_ph(int i) const;

	double getH(int i) const;
	double getH_phm(int i) const;
	double getH_php(int i) const;

	VectorR2 getU(int i) const;
	VectorR2 getU_phm(int i) const;
	VectorR2 getU_php(int i) const;


private:
	double m_uL;
	double m_uR;
	double m_g;

	CoupledGridPhysical *m_Current;
	CoupledGridPhysical *m_Next;
	CoupledGridFlux *m_Flux;

	GridPhysical *m_Z;
};

#endif // SOLVERCOUPLEDLFSV_H
