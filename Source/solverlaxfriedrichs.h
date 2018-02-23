#ifndef SOLVERLAXFRIEDRICHS_H
#define SOLVERLAXFRIEDRICHS_H

#include "gridphysical.h"
#include "gridvirtual.h"

class SolverLaxFriedrichs
{
public:
	SolverLaxFriedrichs();
	~SolverLaxFriedrichs();

	void solve();

//private:
	void initialCondition();
	double f(int i) const;
	double fDer(int i) const;

	void evaluateFlux();
	void computeNext();

	void saveCurrentGrid() const;
private:
	void swapGrid();

private:
	double m_xmax;
	double m_xmin;
	double m_dx;
	int m_N;

	double m_tmax;
	double m_t;
	double m_dt;


	GridPhysical *m_Current;
	GridPhysical *m_Next;

	GridVirtual *m_Flux;

};

#endif // SOLVERLAXFRIEDRICHS_H
