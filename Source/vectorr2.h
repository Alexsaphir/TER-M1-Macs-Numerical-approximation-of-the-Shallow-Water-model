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
	 * @brief VectorR2
	 */
	VectorR2();
	/**
	 * @brief VectorR2
	 * @param a
	 * @param b
	 */
	VectorR2(double a, double b);
	/**
	 * @brief VectorR2
	 * @param A
	 */
	VectorR2(const VectorR2 &A);

	/**
	 * @brief abs
	 */
	void abs();

	/**
	 * @brief x
	 */
	double x;
	/**
	 * @brief y
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
