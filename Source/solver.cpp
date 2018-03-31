#include "solver.h"

Solver::Solver()
{
	m_xmax = 0.;
	m_xmin = 0.;
	m_dx = 0.;
	m_N= 0;

	m_t = 0.;
	m_tmax = 0.;
	m_dt = 0.;
	m_dtmax = 0.;
}

Solver::~Solver()
{

}

double Solver::getX(int i) const
{
	return m_xmin + static_cast<double>(i)*m_dx;
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
