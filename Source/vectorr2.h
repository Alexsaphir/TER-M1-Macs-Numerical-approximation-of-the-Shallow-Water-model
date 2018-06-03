#ifndef VECTORR2_H
#define VECTORR2_H

#include <cmath>

/**
 * @brief The VectorR2 class save an element of \f$ \mathds{R}^2\f$
 */
class VectorR2
{
public:
	/**
	 * @brief VectorR2 Construct a null element
	 */
	VectorR2();
	/**
	 * @brief VectorR2 Construct an element with values given
	 * @param a x-element
	 * @param b y-element
	 */
	VectorR2(double a, double b);
	/**
	 * @brief VectorR2 Copy Constructor
	 * @param A Object to copy
	 */
	VectorR2(const VectorR2 &A);

	/**
	 * @brief abs Return the euclideann norm of the vector
	 */
	void abs();

	/**
	 * @brief x x componant
	 */
	double x;
	/**
	 * @brief y y componant
	 */
	double y;
};

VectorR2 operator+(const VectorR2 &A, const VectorR2 &B);
VectorR2 operator-(const VectorR2 &A, const VectorR2 &B);
VectorR2 operator*(double d, const VectorR2 &B);
VectorR2 operator*(const VectorR2 &A, double d);
VectorR2 operator/(const VectorR2 &A, double d);
VectorR2 abs(const VectorR2 &A);


#endif // VECTORR2_H
