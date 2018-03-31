#ifndef SOLVER_H
#define SOLVER_H

#include <QFile>
#include <QString>
#include <QTextStream>

#include <iostream>

#include "grid.h"

class Solver
{
public:
	Solver();
	virtual ~Solver();

	virtual void initialCondition() = 0;
	virtual void solve() = 0;

protected:
	void saveGrid(QString filename, Grid *G) const;
	void saveGridCSV(QString filename, Grid *G) const;
	void saveTo3d(QString filename, Grid *G, bool init=false) const;
	virtual double getX(int i) const;

protected:
	double m_xmax;
	double m_xmin;
	double m_dx;
	int m_N;

	double m_tmax;
	double m_t;
	double m_dt;
	double m_dtmax;
};

#endif // SOLVER_H
