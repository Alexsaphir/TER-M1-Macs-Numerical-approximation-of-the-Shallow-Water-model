#ifndef SOLVERBURGER_H
#define SOLVERBURGER_H

#include "solver.h"
#include "gridflux.h"
#include "gridphysical.h"

class SolverBurger: public Solver
{
public:
	SolverBurger(double l, double r);
	SolverBurger(double l, double r, int N);

	void initialCondition();
	void solve();

private:
	double F(const double &W) const;
	double Fder(const double &W) const;
	void evaluateFlux();

	void computeNext();
	double computeCFL() const;
	void swapGrid();

private:
	double m_uL;
	double m_uR;

	GridPhysical *m_Current;
	GridPhysical *m_Next;
	GridFlux *m_Flux;
};

#endif // SOLVERBURGER_H
