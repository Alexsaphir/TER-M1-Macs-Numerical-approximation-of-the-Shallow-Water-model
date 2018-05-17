#include "grid.h"

///
/// \brief Grid::Grid
/// \param N Number of element in the grid
///
Grid::Grid(int N): m_n(N)
{
	m_V.reserve(m_n);
	m_V.fill(0, m_n);
}

///
/// \brief Grid::~Grid
///
Grid::~Grid()
{
	m_V.clear();
	m_V.squeeze();
}

///
/// \brief Grid::size
/// \return Number of elements in the grid.
///
int Grid::size() const
{
	return m_n;
}

///
/// \brief Grid::get
/// \param i Position on the grid
/// \return Value of the grid at the position i.
///
double Grid::get(int i) const
{
	if(i<0 || i>=m_n)
	{
		//qDebug() << "Get Grid error";
		return 0.;
	}
	return m_V.at(i);
}

///
/// \brief Grid::set
/// \param i Position on the grid
/// \param v Value to set
///
void Grid::set(int i, double v)
{
	if(i<0 || i>=m_n)
	{
		qDebug() << "Set Grid error";
		return;
	}
	m_V.replace(i, v);
}
