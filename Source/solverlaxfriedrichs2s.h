#ifndef SOLVERLAXFRIEDRICHS2S_H
#define SOLVERLAXFRIEDRICHS2S_H

#include <QPair>

#include <QDebug>

#include "solver.h"
#include "gridphysical.h"
#include "gridvirtual.h"

#include "coupledgridflux.h"
#include "coupledgridphysical.h"



class SolverLaxFriedrichs2S : public Solver
{
public:
	SolverLaxFriedrichs2S(double l, double r);


	void initialCondition();
	void solve();

private:
	VectorR2 F(VectorR2 W) const;
	double F1(VectorR2 W) const;
	double F2(VectorR2 W) const;
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

	double m_g;

	CoupledGridPhysical *m_Current;
	CoupledGridPhysical *m_Next;

	CoupledGridFlux *m_Flux;

};

inline VectorR2 operator+(const VectorR2 &A, const VectorR2 &B)
{
	VectorR2 tmp;
	tmp.first = A.first + B.first;
	tmp.second = A.second + B.second;
	return tmp;
}

inline VectorR2 operator-(const VectorR2 &A, const VectorR2 &B)
{
	VectorR2 tmp;
	tmp.first = A.first - B.first;
	tmp.second = A.second - B.second;
	return tmp;
}

inline VectorR2 operator*(double k, const VectorR2 &B)
{
	VectorR2 tmp;
	tmp.first = k * B.first;
	tmp.second = k * B.second;
	return tmp;
}

inline VectorR2 operator*(const VectorR2 &B, double k)
{
	return k*B;
}

#endif // SOLVERLAXFRIEDRICHS2S_H
