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
	void exportData() const;

private:
	VectorR2 F(const VectorR2 &W) const;
	double F1(const VectorR2 &W) const;
	double F2(const VectorR2 &W) const;
	void evaluateFlux();

	void computeNext();
	double computeCFL() const;
	void swapCoupledGrid();

private:
	double m_uL;
	double m_uR;
	double m_g;

	CoupledGridPhysical *m_Current;
	CoupledGridPhysical *m_Next;
	CoupledGridFlux *m_Flux;

	GridPhysical *m_H;
};

#endif // SOLVERCOUPLEDLFSV_H
