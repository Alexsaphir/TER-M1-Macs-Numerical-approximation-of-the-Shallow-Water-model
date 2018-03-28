#ifndef GRID_H
#define GRID_H

#include <QVector>

#include <QDebug>

class Grid
{
public:
	Grid(int N);
	virtual ~Grid();

	virtual double get(int i) const = 0;
	virtual void set(int i, double v) = 0;

	int size() const;

	bool isValidIndex(int i) const;

protected:
	int m_n;
	QVector<double> m_V;
};

#endif // GRID_H
