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
	/**
	 * @brief Grid Constructor for a Grid
	 * @param N Number of element for the Grid
	 */
	Grid(int N);
	virtual ~Grid();

	/**
	 * @brief get Access to the value of an element on the grid
	 * @param i Index of the element
	 * @return  value of the ith element
	 */
	virtual double get(int i) const;
	/**
	 * @brief set Update the value of an element on the grid
	 * @param i Index of the element
	 * @param v value to set
	 */
	virtual void set(int i, double v);
	/**
	 * @brief getRawVector Direct access to the QVector storing the data
	 * @return pointer to the Qvector storing the data
	 */
	const QVector<double> *getRawVector() const;
	/**
	 * @brief size Size of the Grid
	 * @return Number of elements of the grid
	 */
	int size() const;

	/**
	 * @brief isValidIndex Check if an index is on a grid
	 * @param i Index to test
	 * @return validity of the index
	 */
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
