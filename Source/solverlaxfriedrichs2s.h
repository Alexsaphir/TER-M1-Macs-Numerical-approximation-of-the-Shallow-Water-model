#ifndef SOLVERLAXFRIEDRICHS2S_H
#define SOLVERLAXFRIEDRICHS2S_H

#include <QPair>

#include <QDebug>

#include "solver.h"
#include "gridphysical.h"
#include "gridvirtual.h"



class SolverLaxFriedrichs2S : public Solver
{
public:
	SolverLaxFriedrichs2S(double l, double r);


	void initialCondition();
	//void solve();

private:
	//double F(double u) const;
	//void evaluateFlux();
	//void computeNext();
	//double computeCFL() const;

private:
	void swapGrid();
	double getX(int i) const;

private:
	double m_dx;
	double m_dt;

	double m_uL;
	double m_uR;

	QPair<GridPhysical*, GridPhysical*> m_Current;
	QPair<GridPhysical*, GridPhysical*> m_Next;

	QPair<GridVirtual*, GridVirtual*> m_Flux;

};

#endif // SOLVERLAXFRIEDRICHS2S_H
