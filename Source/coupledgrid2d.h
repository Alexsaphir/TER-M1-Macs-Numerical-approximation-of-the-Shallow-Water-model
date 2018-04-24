#ifndef COUPLEDGRID2D_H
#define COUPLEDGRID2D_H

#include "grid2d.h"
#include "vectorr2.h"

class CoupledGrid2D
{
public:
	CoupledGrid2D();
	virtual ~CoupledGrid2D();

	virtual Grid2D* first() const;
	virtual Grid2D* second() const;

	virtual VectorR2 get(int i, int j) const;
	double getOnFirst(int i, int j) const;
	double getOnSecond(int i, int j) const;

	virtual void set(int i, int j, VectorR2 value);
	void setOnFirst(int i, int j, double value);
	void setOnSecond(int i, int j, double value);

protected:

	Grid2D *m_grid1;
	Grid2D *m_grid2;
};

#endif // COUPLEDGRID2D_H
