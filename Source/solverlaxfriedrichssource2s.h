#ifndef SOLVERLAXFRIEDRICHSSOURCE2S_H
#define SOLVERLAXFRIEDRICHSSOURCE2S_H

#include <QDebug>

#include "solver.h"
#include "gridphysical.h"
#include "gridvirtual.h"

#include "coupledgridflux.h"
#include "coupledgridphysical.h"

class SolverLaxFriedrichsSource2S
{
public:
	SolverLaxFriedrichsSource2S();

private:
	double m_dx;
	double m_dt;

	double m_uL;
	double m_uR;

	double m_g;

	CoupledGridPhysical *m_z;
	CoupledGridPhysical *m_Next;

	CoupledGridFlux *m_Flux;
};

#endif // SOLVERLAXFRIEDRICHSSOURCE2S_H
