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
	 * @brief SolverBurger Create a Riemann problem for the burger's equation
	 * @param l  Left side value
	 * @param r Right  side value
	 */
	SolverBurger(double l, double r);
	/**
	 * @brief SolverBurger
	 * @param l Left  side value
	 * @param r Right side value
	 * @param N Number of point used for the physical grid
	 */
	SolverBurger(double l, double r, int N);

	/**
	 * @brief initialCondition Define the IC for a Riemann problem
	 */
	void initialCondition();
	/**
	 * @brief solve Solve the problem with the parameters define previously
	 */
	void solve();

private:
	/**
	 * @brief F Function flux of the Burger's equation
	 * @param W
	 * @return Flux evaluate at W
	 */
	double F(const double &W) const;
	/**
	 * @brief Fder derivative of the Flux
	 * @param W
	 * @return Derivative of the Flux evaluate at W
	 */
	double Fder(const double &W) const;
	/**
	 * @brief evaluateFlux Evaluate and store the Flux in the GridFlux
	 */
	void evaluateFlux();

	/**
	 * @brief computeNext Evaluate the next time step
	 */
	void computeNext();
	/**
	 * @brief computeCFL Compute the best time step
	 * @return Better time step
	 */
	double computeCFL() const;
	/**
	 * @brief swapGrid Swap the old grid with the new
	 */
	void swapGrid();

private:
	/**
	 * @brief m_uL Left side value
	 */
	double m_uL;
	/**
	 * @brief m_uR Right side value
	 */
	double m_uR;

	/**
	 * @brief m_Current Grid of the current time
	 */
	GridPhysical *m_Current;
	/**
	 * @brief m_Next Grid for the Next time
	 */
	GridPhysical *m_Next;
	/**
	 * @brief m_Flux Grid to store the flux
	 */
	GridFlux *m_Flux;
};

#endif // SOLVERBURGER_H
