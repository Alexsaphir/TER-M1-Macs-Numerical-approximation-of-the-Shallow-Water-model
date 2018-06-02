#ifndef SOLVERCOUPLEDLFSV2_H
#define SOLVERCOUPLEDLFSV2_H

#include <algorithm>

#include "solver.h"
#include "coupledgridflux.h"
#include "coupledgridphysical.h"

/**
 * @brief The SolverCoupledLFSV2 class is the implementation of the well-balanced scheme, 1st order, for the shallow water equation
 */

class SolverCoupledLFSV2 : public Solver
{
public:
	/**
	 * @brief SolverCoupledLFSV2
	 */
	SolverCoupledLFSV2();
	/**
	 * @brief SolverCoupledLFSV2
	 * @param N
	 */
	SolverCoupledLFSV2(int N);

	/**
	 * @brief initialCondition
	 */
	void initialCondition();
	/**
	 * @brief initialConditionOscillating
	 */
	void initialConditionOscillating();
	/**
	 * @brief initialConditionRest
	 */
	void initialConditionRest();
	/**
	 * @brief initialConditionDam
	 */
	void initialConditionDam();
	/**
	 * @brief solve
	 */
	void solve();


private:
	/**
	 * @brief F
	 * @param w
	 * @return
	 */
	VectorR2 F(VectorR2 w) const;
	/**
	 * @brief F1
	 * @param w
	 * @return
	 */
	double F1(VectorR2 w) const;
	/**
	 * @brief F2
	 * @param w
	 * @return
	 */
	double F2(VectorR2 w) const;

	/**
	 * @brief minmod
	 * @param x
	 * @param y
	 * @return
	 */
	double minmod(double x, double y) const;
	/**
	 * @brief getW_l
	 * @param wim
	 * @param wi
	 * @param wip
	 * @return
	 */
	double getW_l(double wim, double wi, double wip) const;
	/**
	 * @brief getW_r
	 * @param wim
	 * @param wi
	 * @param wip
	 * @return
	 */
	double getW_r(double wim, double wi, double wip) const;

	/**
	 * @brief getZ
	 * @param i
	 * @return
	 */
	double getZ(int i) const;
	/**
	 * @brief getH
	 * @param i
	 * @return
	 */
	double getH(int i) const;
	/**
	 * @brief getV
	 * @param i
	 * @return
	 */
	double getV(int i) const;

	/**
	 * @brief getZ_l
	 * @param i
	 * @return
	 */
	double getZ_l(int i) const;
	/**
	 * @brief getZ_r
	 * @param i
	 * @return
	 */
	double getZ_r(int i) const;
	/**
	 * @brief getZ_mh
	 * @param i
	 * @return
	 */
	double getZ_mh(int i) const;
	/**
	 * @brief getZ_ph
	 * @param i
	 * @return
	 */
	double getZ_ph(int i) const;

	/**
	 * @brief getH_l
	 * @param i
	 * @return
	 */
	double getH_l(int i) const;
	/**
	 * @brief getH_r
	 * @param i
	 * @return
	 */
	double getH_r(int i) const;
	/**
	 * @brief getH_mhm
	 * @param i
	 * @return
	 */
	double getH_mhm(int i) const;
	/**
	 * @brief getH_mhp
	 * @param i
	 * @return
	 */
	double getH_mhp(int i) const;
	/**
	 * @brief getH_phm
	 * @param i
	 * @return
	 */
	double getH_phm(int i) const;
	/**
	 * @brief getH_php
	 * @param i
	 * @return
	 */
	double getH_php(int i) const;

	/**
	 * @brief getV_l
	 * @param i
	 * @return
	 */
	double getV_l(int i) const;
	/**
	 * @brief getV_r
	 * @param i
	 * @return
	 */
	double getV_r(int i) const;




	/**
	 * @brief getU_mhm
	 * @param i
	 * @return
	 */
	VectorR2 getU_mhm(int i) const;
	/**
	 * @brief getU_mhp
	 * @param i
	 * @return
	 */
	VectorR2 getU_mhp(int i) const;
	/**
	 * @brief getU_phm
	 * @param i
	 * @return
	 */
	VectorR2 getU_phm(int i) const;
	/**
	 * @brief getU_php
	 * @param i
	 * @return
	 */
	VectorR2 getU_php(int i) const;

	/**
	 * @brief getS
	 * @param i
	 * @return
	 */
	VectorR2 getS(int i) const;
	/**
	 * @brief getS_mhp
	 * @param i
	 * @return
	 */
	VectorR2 getS_mhp(int i) const;
	/**
	 * @brief getS_phm
	 * @param i
	 * @return
	 */
	VectorR2 getS_phm(int i) const;
	/**
	 * @brief getS_ci
	 * @param i
	 * @return
	 */
	VectorR2 getS_ci(int i) const;

	/**
	 * @brief Flux
	 * @param wL
	 * @param wR
	 * @return
	 */
	VectorR2 Flux(VectorR2 wL, VectorR2 wR) const;

	/**
	 * @brief computeNext
	 */
	void computeNext();
	/**
	 * @brief evaluateFlux
	 */
	void evaluateFlux();
	/**
	 * @brief computeCFL
	 * @return
	 */
	double computeCFL() const;
	/**
	 * @brief swapCoupledGrid
	 */
	void swapCoupledGrid();
	/**
	 * @brief computeSpeed
	 */
	void computeSpeed();
protected:
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

	/**
	 * @brief m_Z
	 */
	GridPhysical *m_Z;
	/**
	 * @brief m_U
	 */
	GridPhysical *m_U;
};

#endif // SOLVERCOUPLEDLFSV2_H
