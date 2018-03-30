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

VectorR2 operator+(VectorR2 A, VectorR2 B)
{
	return VectorR2(A.x + B.x, A.y + B.y);
}

VectorR2 operator-(VectorR2 A, VectorR2 B)
{
	return VectorR2(A.x - B.x, A.y - B.y);
}

VectorR2 operator*(double d, VectorR2 B)
{
	return VectorR2(d*B.x, d * B.y);
}

VectorR2 operator*(VectorR2 A, double d)
{
	return d*A;
}
