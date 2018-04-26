#ifndef COUPLEDGRID_H
#define COUPLEDGRID_H

#include "grid.h"
#include "vectorr2.h"

class CoupledGrid
{
public:
	CoupledGrid();
	virtual ~CoupledGrid();

	virtual Grid* first() const;
	virtual Grid* second() const;

	virtual VectorR2 get(int i) const;
	double getOnFirst(int i) const;
	double getOnSecond(int i) const;

	virtual void set(int i, VectorR2 value);
	void setOnFirst(int i, double value);
	void setOnSecond(int i, double value);

protected:

	Grid *m_grid1;
	Grid *m_grid2;

};

#endif // COUPLEDGRID_H
