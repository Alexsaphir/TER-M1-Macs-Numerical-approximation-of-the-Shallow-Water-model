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
	QPair<double, double> F(QPair<double, double> W) const;
	void evaluateFlux();
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

	double m_g;

	QPair<GridPhysical*, GridPhysical*> m_Current;
	QPair<GridPhysical*, GridPhysical*> m_Next;

	QPair<GridVirtual*, GridVirtual*> m_Flux;

};

QPair<double, double> operator+(const QPair<double, double> &A, const QPair<double, double> &B)
{
	QPair<double, double> tmp;
	tmp.first = A.first + B.first;
	tmp.second = A.second + B.second;
	return tmp;
}

QPair<double, double> operator-(const QPair<double, double> &A, const QPair<double, double> &B)
{
	QPair<double, double> tmp;
	tmp.first = A.first - B.first;
	tmp.second = A.second - B.second;
	return tmp;
}

QPair<double, double> operator*(double k, const QPair<double, double> &B)
{
	QPair<double, double> tmp;
	tmp.first = k * B.first;
	tmp.second = k * B.second;
	return tmp;
}

QPair<double, double> operator*(const QPair<double, double> &B, double k)
{
	return k*B;
}

#endif // SOLVERLAXFRIEDRICHS2S_H
