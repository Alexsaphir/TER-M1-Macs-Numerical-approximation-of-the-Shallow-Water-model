#include "solver.h"

Solver::Solver()
{
	m_xmin = -10.;
	m_xmax = 10.;
	m_dx = .05;
	m_N = (m_xmax - m_xmin) / m_dx + 1;

	m_tmax = 1.;
	m_t = 0.;
	m_dt = 0.;
	m_dtmax = 0.01;

	m_cache = new CacheSolver;
	m_cacheSpeed = new CacheSolver;

	std::cout << " dx step : " << m_dx << "N : " << m_N << std::endl;
}

Solver::Solver(int N)
{
	m_xmin = -10.;
	m_xmax = 10.;
	m_N = N;
	m_dx = (m_xmax - m_xmin) / (m_N - 1);

	m_tmax = 1.;
	m_t = 0.;
	m_dt = 0.;
	m_dtmax = 0.01;

	m_cache = new CacheSolver;
	m_cacheSpeed = new CacheSolver;
	std::cout << " dx step : " << m_dx << "N : " << m_N << std::endl;
}

Solver::~Solver()
{
	delete m_cache;
	delete m_cacheSpeed;
}

double Solver::getX(int i) const
{
	return m_xmin + static_cast<double>(i)*m_dx;
}

void Solver::initFunc(GridPhysical *G, double uL, double uR)
{
#pragma omp parallel
	for(int i=0; i<m_N; ++i)
	{
		double x = m_xmin + m_dx*static_cast<double>(i);

		if(x<=0.)
		{
			G->set(i, uL);
		}
		else
		{
			G->set(i, uR);
		}
	}
}

void Solver::saveGrid(QString filename, Grid *G) const
{
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;
	QTextStream out(&file);

	//Set column title
	out << "# X U" << endl;

	for(int i=0; i<G->size(); ++i)
	{
		out << getX(i) << " " << G->get(i);
		if(i != (G->size()-1))
			out << endl;
	}
	file.close();
}

void Solver::saveGridCSV(QString filename, Grid *G) const
{
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;

	QTextStream out(&file);

	out << "\"x\",\"y\"" << endl;

	for(int i=0; i<G->size(); ++i)
	{
		out << getX(i) << "," << G->get(i);
		out << endl;
	}
	file.close();
}

void Solver::saveGridCSV(QString filename, Grid *G, Grid *offset) const
{
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;

	QTextStream out(&file);

	out << "\"x\",\"y\"" << endl;

	for(int i=0; i<G->size(); ++i)
	{
		out << getX(i) << "," << G->get(i)+offset->get(i);
		out << endl;
	}
	file.close();
}

void Solver::saveGridPython(QString filename, Grid *G) const
{
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;

	QTextStream out(&file);

	for(int i=0; i<G->size(); ++i)
	{
		out <<G->get(i);
		if(i<G->size() - 1)
			out << " ";
	}
	out << endl;
	file.close();
}

void Solver::saveTo3d(QString filename, Grid *G, bool init) const
{
	QFile file(filename);

	if(init)
	{
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
			return;
	}
	else
	{
		if (!file.open(QIODevice::Append | QIODevice::Text))
			return;
	}

	QTextStream out(&file);
	if(init)
	{
		//out << "# X T U U" << endl;
		out << "\"x\",\"y\",\"z\"" << endl;
	}

	for(int i=0; i<G->size(); ++i)
	{
		out << getX(i) << "," << m_t << "," << G->get(i);
		out << endl;
	}
	file.close();
}

void Solver::saveTo3d(QString filename, Grid *G, Grid *offset, bool init) const
{
	QFile file(filename);

	if(init)
	{
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
			return;
	}
	else
	{
		if (!file.open(QIODevice::Append | QIODevice::Text))
			return;
	}

	QTextStream out(&file);
	if(init)
	{
		//out << "# X T U U" << endl;
		out << "\"x\",\"y\",\"z\"" << endl;
	}

	for(int i=0; i<G->size(); ++i)
	{
		out << getX(i)  << "," << G->get(i)+ offset->get(i)<< "," << m_t;
		out << endl;
	}
	file.close();
}
