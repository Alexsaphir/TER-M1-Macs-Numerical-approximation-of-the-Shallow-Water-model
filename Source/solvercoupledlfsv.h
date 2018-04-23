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

	inline double getZ(int i) const;
	inline double getZ_mh(int i) const;
	inline double getZ_ph(int i) const;

	inline double getH(int i) const;
	inline double getH_mhm(int i) const;
	inline double getH_mhp(int i) const;
	inline double getH_phm(int i) const;
	inline double getH_php(int i) const;

	inline VectorR2 getU(int i) const;
	inline VectorR2 getU_mhm(int i) const;
	inline VectorR2 getU_mhp(int i) const;
	inline VectorR2 getU_phm(int i) const;
	inline VectorR2 getU_php(int i) const;

	inline VectorR2 getS(int i) const;

	inline VectorR2 getFlux_mh(int i) const;
	inline VectorR2 getFlux_ph(int i) const;
	void evaluateFlux();

	inline VectorR2 F(VectorR2 w) const;
	inline double F1(VectorR2 w) const;
	inline double F2(VectorR2 w) const;
	inline VectorR2 Flux(VectorR2 wL, VectorR2 wR) const;

	void computeNext();
	double computeCFL() const;
	inline void swapCoupledGrid();


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
