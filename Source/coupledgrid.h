#ifndef COUPLEDGRID_H
#define COUPLEDGRID_H

#include "grid.h"
#include "vectorr2.h"

/**
 * @brief The CoupledGrid class store two Grid object
 */

class CoupledGrid
{
public:
	/**
	 * @brief CoupledGrid Create two grid
	 */
	CoupledGrid();
	virtual ~CoupledGrid();

	/**
	 * @brief first
	 * @return pointer to the first grid
	 */
	virtual Grid* first() const;
	/**
	 * @brief second
	 * @return pointer to the second grid
	 */
	virtual Grid* second() const;

	/**
	 * @brief get Access to an element of both grid in one time
	 * @param i Index
	 * @return ith element on both grid
	 */
	virtual VectorR2 get(int i) const;
	/**
	 * @brief getOnFirst Access to an element of the first grid
	 * @param i Index
	 * @return ith element on the first grid
	 */
	double getOnFirst(int i) const;
	/**
	 * @brief getOnSecond Access to an element of the second grid
	 * @param i Index
	 * @return ith element on the second grid
	 */
	double getOnSecond(int i) const;

	/**
	 * @brief set Set an element of both grid in one time
	 * @param i Index
	 * @param value value to set
	 */
	virtual void set(int i, VectorR2 value);
	/**
	 * @brief setOnFirst Set an element of the first grid
	 * @param i Index
	 * @param value value to set
	 */
	void setOnFirst(int i, double value);
	/**
	 * @brief setOnSecond Set an element of the second grid
	 * @param i Index
	 * @param value value to set
	 */
	void setOnSecond(int i, double value);

protected:

	/**
	 * @brief m_grid1 First grid
	 */
	Grid *m_grid1;
	/**
	 * @brief m_grid2 Second grid
	 */
	Grid *m_grid2;

};

#endif // COUPLEDGRID_H
