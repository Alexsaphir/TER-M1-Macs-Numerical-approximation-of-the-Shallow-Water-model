#ifndef SOLVER2D_H
#define SOLVER2D_H

#include <QFile>
#include <QString>
#include <QTextStream>

#include <iostream>

#include "grid2d.h"

class Solver2D
{
public:
	Solver2D();
	virtual ~Solver2D();

	virtual void initialCondition() = 0;
	virtual void solve() = 0;

protected:
	virtual double getX(int i) const;
	virtual double getY(int j) const;

protected:
	double m_xmax;
	double m_xmin;
	double m_dx;
	int m_nx;

	double m_ymax;
	double m_ymin;
	double m_dy;
	int m_ny;

	double m_tmax;
	double m_t;
	double m_dt;
	double m_dtmax;
};

#endif // SOLVER2D_H
