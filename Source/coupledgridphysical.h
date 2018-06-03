#ifndef COUPLEDGRIDPHYSICAL_H
#define COUPLEDGRIDPHYSICAL_H

#include "coupledgrid.h"
#include "gridphysical.h"

/**
 * @brief The CoupledGridPhysical class store two GridPhysical
 */

class CoupledGridPhysical: public CoupledGrid
{
public:
	/**
	 * @brief CoupledGridPhysical Create a coupled grid of N elements
	 * @param N Number of elements
	 */
	CoupledGridPhysical(int N);
	~CoupledGridPhysical();
};

#endif // COUPLEDGRIDPHYSICAL_H
