#include "vectorr2.h"

VectorR2::VectorR2()
{
	x = 0.;
	y = 0.;
}

VectorR2::VectorR2(double a, double b)
{
	x = a;
	y = b;
}

VectorR2::VectorR2(const VectorR2 &A)
{
	x = A.x;
	y = A.y;
}

void VectorR2::abs()
{
	x = std::abs(x);
	y = std::abs(y);
}

VectorR2 operator+(const VectorR2 &A, const VectorR2 &B)
{
	return VectorR2(A.x + B.x, A.y + B.y);
}

VectorR2 operator-(const VectorR2 &A, const VectorR2 &B)
{
	return VectorR2(A.x - B.x, A.y - B.y);
}

VectorR2 operator*(double d, const VectorR2 &B)
{
	return VectorR2(d*B.x, d * B.y);
}

VectorR2 operator*(const VectorR2 &A, double d)
{
	return d*A;
}

VectorR2 operator/(const VectorR2 &A, double d)
{
	return VectorR2(A.x/d, A.y/d);
}

VectorR2 abs(const VectorR2 &A)
{
	return VectorR2(A).abs();
}
