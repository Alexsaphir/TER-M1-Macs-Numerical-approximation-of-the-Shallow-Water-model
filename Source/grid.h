#ifndef GRID_H
#define GRID_H

#include <QVector>

#include <QDebug>

///
/// \brief The Grid class
/// describe a 1D-Grid who store value of N elements.
class Grid
{
public:
	Grid(int N);
	virtual ~Grid();

	virtual double get(int i) const;
	virtual void set(int i, double v);

	int size() const;

	bool isValidIndex(int i) const;

protected:
	///
	/// \brief m_n
	/// Number of element in the grid.
	int m_n;
	///
	/// \brief m_V
	/// Store value of the elements in the grid.
	QVector<double> m_V;
};
#endif // GRID_H
