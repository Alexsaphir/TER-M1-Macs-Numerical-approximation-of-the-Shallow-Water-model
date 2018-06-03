#ifndef SOLVERCOUPLEDLF0_H
#define SOLVERCOUPLEDLF0_H

#include <QDebug>
#include "solver.h"

#include "coupledgridflux.h"
#include "coupledgridphysical.h"

/**
 * @brief The SolverCoupledLF0 class is used for the solving of a coupled equation
 */

class SolverCoupledLF0: public Solver
{
public:
	/**
	 * @brief SolverCoupledLF0 Default constructor for a Riemann equation and a coupled equation
	 * @param l Left side value
	 * @param r Right side value
	 */
	SolverCoupledLF0(double l, double r);
	/**
	 * @brief SolverCoupledLF0  constructor for a Riemann equation and a coupled equation and a given number of points
	 * @param l Left side value
	 * @param r Right side  value
	 * @param N Number of points
	 */
	SolverCoupledLF0(double l, double r, int N);

	/**
	 * @brief initialCondition Initialize the IC of the problem
	 */
	void initialCondition();
	/**
	 * @brief solve Solve the problem with the current parameters
	 */
	void solve();

private:
	/**
	 * @brief F Function of the Flux
	 * @param W
	 * @return Evaluation of the Flux at W
	 */
	VectorR2 F(const VectorR2 &W) const;
	/**
	 * @brief F1 Partial Flux
	 * @param W
	 * @return
	 */
	double F1(const VectorR2 &W) const;
	/**
	 * @brief F2 Partial Flux
	 * @param W
	 * @return
	 */
	double F2(const VectorR2 &W) const;

	/**
	 * @brief evaluateFlux Evaluate and store the flux
	 */
	void evaluateFlux();

	/**
	 * @brief computeNext Compute next iteration
	 */
	void computeNext();
	/**
	 * @brief computeCFL Compute the best time step
	 * @return Time step
	 */
	double computeCFL() const;
	/**
	 * @brief swapCoupledGrid Swap the current grid with the next
	 */
	void swapCoupledGrid();

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
	 * @brief m_g Gravity
	 */
	double m_g;

	/**
	 * @brief m_Current Current grid
	 */
	CoupledGridPhysical *m_Current;
	/**
	 * @brief m_Next Next Grid
	 */
	CoupledGridPhysical *m_Next;
	/**
	 * @brief m_Flux GridFlux associate to the Current
	 */
	CoupledGridFlux *m_Flux;
};

#endif // SOLVERCOUPLEDLF0_H
