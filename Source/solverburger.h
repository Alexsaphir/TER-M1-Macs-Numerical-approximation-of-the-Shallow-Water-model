#ifndef SOLVERBURGER_H
#define SOLVERBURGER_H

#include "solver.h"
#include "gridflux.h"
#include "gridphysical.h"

/**
 * @brief The SolverBurger class is used for the solving of the Burger's equation
 */

class SolverBurger: public Solver
{
public:
	/**
	 * @brief SolverBurger
	 * @param l
	 * @param r
	 */
	SolverBurger(double l, double r);
	/**
	 * @brief SolverBurger
	 * @param l
	 * @param r
	 * @param N
	 */
	SolverBurger(double l, double r, int N);

	/**
	 * @brief initialCondition
	 */
	void initialCondition();
	/**
	 * @brief solve
	 */
	void solve();

private:
	/**
	 * @brief F
	 * @param W
	 * @return
	 */
	double F(const double &W) const;
	/**
	 * @brief Fder
	 * @param W
	 * @return
	 */
	double Fder(const double &W) const;
	/**
	 * @brief evaluateFlux
	 */
	void evaluateFlux();

	/**
	 * @brief computeNext
	 */
	void computeNext();
	/**
	 * @brief computeCFL
	 * @return
	 */
	double computeCFL() const;
	/**
	 * @brief swapGrid
	 */
	void swapGrid();

private:
	/**
	 * @brief m_uL
	 */
	double m_uL;
	/**
	 * @brief m_uR
	 */
	double m_uR;

	/**
	 * @brief m_Current
	 */
	GridPhysical *m_Current;
	/**
	 * @brief m_Next
	 */
	GridPhysical *m_Next;
	/**
	 * @brief m_Flux
	 */
	GridFlux *m_Flux;
};

#endif // SOLVERBURGER_H
