#ifndef GRID2D_H
#define GRID2D_H

#include <QVector>

#include <QDebug>

class Grid2D
{
public:
	Grid2D(int Nx, int Ny);
	virtual ~Grid2D();

	virtual double get(int i, int j) const;
	virtual void set(int i, int j, double v);

	int sizeX() const;
	int sizeY() const;

	bool isValidIndex(int i, int j) const;

private:
	int m_nx;
	int m_ny;

	QVector<double> m_V;
};

#endif // GRID2D_H
