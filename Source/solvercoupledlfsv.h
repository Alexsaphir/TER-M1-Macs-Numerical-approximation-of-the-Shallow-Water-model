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

	double getCorrected_Z_half(int i) const;

	double getCorrected_H_half_pos(int i) const;
	double getCorrected_H_half_min(int i) const;

	VectorR2 S(int i) const;

	VectorR2 getCorrected_U_half_pos(int i) const;
	VectorR2 getCorrected_U_half_min(int i) const;


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

	GridPhysical *m_Z;
};

#endif // SOLVERCOUPLEDLFSV_H
