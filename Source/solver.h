#ifndef SOLVER_H
#define SOLVER_H

#include <QFile>
#include <QString>
#include <QTextStream>

#include <iostream>

#include "grid.h"
#include "gridphysical.h"
#include "cachesolver.h"

/**
 * @brief The Solver class is a pure virtual class designed for the solver
 */

class Solver
{
public:
	/**
	 * @brief Solver Base constructor for a solver based class
	 */
	Solver();
	/**
	 * @brief Solver Constructor for a solver based class with a given Number of point
	 * @param N Number of points used for the physical grid
	 */
	Solver(int N);
	virtual ~Solver();

	/**
	 * @brief initialCondition Initialize the initial condition
	 */
	virtual void initialCondition() = 0;
	/**
	 * @brief solve Solve the problem
	 */
	virtual void solve() = 0;

protected:
	/**
	 * @brief saveGrid Save the grid
	 * @param filename Name of the file
	 * @param G Grid to save
	 */
	void saveGrid(QString filename, Grid *G) const;
	/**
	 * @brief saveGridCSV Save a grid to a csv file for paraview
	 * @param filename Name of the file
	 * @param G Grid to save
	 */
	void saveGridCSV(QString filename, Grid *G) const;
	/**
	 * @brief saveGridCSV Save a grid to a csv file for paraview
	 * @param filename  Name of the file
	 * @param G Grid to save
	 * @param offset offset of the data to save
	 */
	void saveGridCSV(QString filename, Grid *G, Grid *offset) const;
	/**
	 * @brief saveGridPython Save a grid to be open with python
	 * @param filename Name of the file
	 * @param G Grid to save
	 */
	void saveGridPython(QString filename, Grid *G) const;
	/**
	 * @brief saveTo3d Save a collection of instant of a grid
	 * @param filename Name of the file
	 * @param G Grid to save
	 * @param init True if it's the fitst grid to be added or false else
	 */
	void saveTo3d(QString filename, Grid *G, bool init=false) const;
	/**
	 * @brief saveTo3d  Save a collection of instant of a grid
	 * @param filename Name of the file
	 * @param G Grid to save
	 * @param offset Grid with the offset
	 * @param init True if it's the fitst grid to be added or false else
	 */
	void saveTo3d(QString filename, Grid *G, Grid *offset, bool init=false) const;
	/**
	 * @brief getX position on the axis of the ith element
	 * @param i Index
	 * @return Value on the axis [Xmin, Xmax]
	 */
	virtual double getX(int i) const;

	/**
	 * @brief initFunc Basic initialization function
	 * @param G Grid to initalize
	 * @param uL left side value
	 * @param uR right side value
	 */
	void initFunc(GridPhysical *G, double uL, double uR);

protected:
	/**
	 * @brief m_cache Cache for the Height
	 */
	CacheSolver *m_cache;
	/**
	 * @brief m_cacheSpeed Cache for the speed
	 */
	CacheSolver *m_cacheSpeed;

	/**
	 * @brief m_xmax Xmax
	 */
	double m_xmax;
	/**
	 * @brief m_xmin Xmin
	 */
	double m_xmin;
	/**
	 * @brief m_dx dx
	 */
	double m_dx;
	/**
	 * @brief m_N Number of elements
	 */
	int m_N;

	double m_tmax;
	/**
	 * @brief m_t time where the computation need to stop
	 */
	double m_t;
	/**
	 * @brief m_dt dt used
	 */
	double m_dt;
	/**
	 * @brief m_dtmax maximum dt that can be used
	 */
	double m_dtmax;

};

#endif // SOLVER_H
