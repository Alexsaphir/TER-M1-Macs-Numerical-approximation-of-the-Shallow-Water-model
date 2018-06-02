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
	 * @brief Solver
	 */
	Solver();
	/**
	 * @brief Solver
	 * @param N
	 */
	Solver(int N);
	virtual ~Solver();

	/**
	 * @brief initialCondition
	 */
	virtual void initialCondition() = 0;
	/**
	 * @brief solve
	 */
	virtual void solve() = 0;

protected:
	/**
	 * @brief saveGrid
	 * @param filename
	 * @param G
	 */
	void saveGrid(QString filename, Grid *G) const;
	/**
	 * @brief saveGridCSV
	 * @param filename
	 * @param G
	 */
	void saveGridCSV(QString filename, Grid *G) const;
	/**
	 * @brief saveGridCSV
	 * @param filename
	 * @param G
	 * @param offset
	 */
	void saveGridCSV(QString filename, Grid *G, Grid *offset) const;
	/**
	 * @brief saveGridPython
	 * @param filename
	 * @param G
	 */
	void saveGridPython(QString filename, Grid *G) const;
	/**
	 * @brief saveTo3d
	 * @param filename
	 * @param G
	 * @param init
	 */
	void saveTo3d(QString filename, Grid *G, bool init=false) const;
	/**
	 * @brief saveTo3d
	 * @param filename
	 * @param G
	 * @param offset
	 * @param init
	 */
	void saveTo3d(QString filename, Grid *G, Grid *offset, bool init=false) const;
	/**
	 * @brief getX
	 * @param i
	 * @return
	 */
	virtual double getX(int i) const;

	/**
	 * @brief initFunc
	 * @param G
	 * @param uL
	 * @param uR
	 */
	void initFunc(GridPhysical *G, double uL, double uR);

protected:
	/**
	 * @brief m_cache
	 */
	CacheSolver *m_cache;
	/**
	 * @brief m_cacheSpeed
	 */
	CacheSolver *m_cacheSpeed;

	/**
	 * @brief m_xmax
	 */
	double m_xmax;
	/**
	 * @brief m_xmin
	 */
	double m_xmin;
	/**
	 * @brief m_dx
	 */
	double m_dx;
	/**
	 * @brief m_N
	 */
	int m_N;

	double m_tmax;
	/**
	 * @brief m_t
	 */
	double m_t;
	/**
	 * @brief m_dt
	 */
	double m_dt;
	/**
	 * @brief m_dtmax
	 */
	double m_dtmax;

};

#endif // SOLVER_H
