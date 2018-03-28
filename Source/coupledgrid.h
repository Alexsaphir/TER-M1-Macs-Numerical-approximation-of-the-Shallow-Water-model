#ifndef COUPLEDGRID_H
#define COUPLEDGRID_H

#include <QPair>

#include "grid.h"

typedef QPair<double, double> VectorR2;

class CoupledGrid
{
public:
	CoupledGrid();
	virtual ~CoupledGrid();

	virtual Grid* first() const;
	virtual Grid* second() const;

	virtual double get(int i, int idx_grid) const;
	virtual VectorR2 get(int i) const;
	virtual void set(int i, double value, int idx_grid);
	virtual void set(int i, VectorR2 value);

	double getOnFirst(int i) const;
	double getOnSecond(int i) const;
	void setOnFirst(int i, double value);
	void setOnSecond(int i, double value);

protected:
	Grid *m_grid1;
	Grid *m_grid2;
};

#endif // COUPLEDGRID_H
