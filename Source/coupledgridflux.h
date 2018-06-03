#ifndef COUPLEDGRIDFLUX_H
#define COUPLEDGRIDFLUX_H

#include "coupledgrid.h"
#include "coupledgridphysical.h"
#include "gridflux.h"

/**
 * @brief The CoupledGridFlux class store two GridFlux
 */

class CoupledGridFlux: public CoupledGrid
{
public:
	/**
	 * @brief CoupledGridFlux Create a coupled Grid for the flux
	 * @param CGP coupled grid physical
	 */
	CoupledGridFlux(const CoupledGridPhysical &CGP);
	~CoupledGridFlux();
};

#endif // COUPLEDGRIDFLUX_H
