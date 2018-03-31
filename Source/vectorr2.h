#ifndef VECTORR2_H
#define VECTORR2_H

#include <cmath>

class VectorR2
{
public:
	VectorR2();
	VectorR2(double a, double b);
	VectorR2(const VectorR2 &A);

	void abs();

	double x;
	double y;
};

VectorR2 operator+(const VectorR2 &A, const VectorR2 &B);
VectorR2 operator-(const VectorR2 &A, const VectorR2 &B);
VectorR2 operator*(double d, const VectorR2 &B);
VectorR2 operator*(const VectorR2 &A, double d);
VectorR2 operator/(const VectorR2 &A, double d);
VectorR2 abs(const VectorR2 &A);


#endif // VECTORR2_H
