#include "grid.h"

Grid::Grid(int N): m_n(N)
{
	m_V.reserve(m_n);
	m_V.fill(0.,m_n);
}

int Grid::size() const
{
	return m_n;
}

Grid::~Grid()
{
	m_V.clear();
	m_V.squeeze();
}
