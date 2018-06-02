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
	 * @brief SolverCoupledLF0
	 * @param l
	 * @param r
	 */
	SolverCoupledLF0(double l, double r);
	/**
	 * @brief SolverCoupledLF0
	 * @param l
	 * @param r
	 * @param N
	 */
	SolverCoupledLF0(double l, double r, int N);

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
	VectorR2 F(const VectorR2 &W) const;
	/**
	 * @brief F1
	 * @param W
	 * @return
	 */
	double F1(const VectorR2 &W) const;
	/**
	 * @brief F2
	 * @param W
	 * @return
	 */
	double F2(const VectorR2 &W) const;

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
	 * @brief swapCoupledGrid
	 */
	void swapCoupledGrid();

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
	 * @brief m_g
	 */
	double m_g;

	/**
	 * @brief m_Current
	 */
	CoupledGridPhysical *m_Current;
	/**
	 * @brief m_Next
	 */
	CoupledGridPhysical *m_Next;
	/**
	 * @brief m_Flux
	 */
	CoupledGridFlux *m_Flux;
};

#endif // SOLVERCOUPLEDLF0_H
