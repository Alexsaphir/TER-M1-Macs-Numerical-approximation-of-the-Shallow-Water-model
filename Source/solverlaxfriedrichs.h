#ifndef SOLVERLAXFRIEDRICHS_H
#define SOLVERLAXFRIEDRICHS_H

#include "solver.h"
#include "gridphysical.h"
#include "gridvirtual.h"

#include <QDebug>

class SolverLaxFriedrichs : public Solver
{
public:
	SolverLaxFriedrichs(double l, double r);
	~SolverLaxFriedrichs();

	void initialCondition();
	void solve();

private:
	double f(int i) const;
	void evaluateFlux();
	void computeNext();
	double computeCFL() const;

private:
	void swapGrid();
	double getX(int i) const;

private:
	double m_dx;
	double m_dt;

	double m_uL;
	double m_uR;

	GridPhysical *m_Current;
	GridPhysical *m_Next;

	GridVirtual *m_Flux;

};

#endif // SOLVERLAXFRIEDRICHS_H
