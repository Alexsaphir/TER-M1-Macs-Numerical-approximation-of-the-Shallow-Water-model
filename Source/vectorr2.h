#ifndef VECTORR2_H
#define VECTORR2_H

class VectorR2
{
public:
	VectorR2();
	VectorR2(double a, double b);

	double x;
	double y;
};

VectorR2 operator+(VectorR2 A, VectorR2 B);
VectorR2 operator-(VectorR2 A, VectorR2 B);
VectorR2 operator*(double d, VectorR2 B);
VectorR2 operator*(VectorR2 A, double d);


#endif // VECTORR2_H
