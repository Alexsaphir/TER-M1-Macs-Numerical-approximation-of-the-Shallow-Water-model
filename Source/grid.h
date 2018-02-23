#ifndef GRID_H
#define GRID_H

#include <QVector>

class Grid
{
public:
	Grid(int N);
	~Grid();

	virtual double get(int i) const = 0;
	virtual void set(int i, double v) = 0;

	int size() const;

protected:
	int m_n;
	QVector<double> m_V;
};

#endif // GRID_H
