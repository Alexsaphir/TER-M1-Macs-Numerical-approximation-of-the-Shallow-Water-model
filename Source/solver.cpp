#include "solver.h"

Solver::Solver()
{
	
}

Solver::~Solver()
{
	
}

void Solver::saveGrid(QString filename, Grid *G) const
{
	//G->exportData(name);

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
		out << "# X T U" << endl;
	}

	for(int i=0; i<G->size(); ++i)
	{
		out << getX(i) << " " << m_t << " " << G->get(i);
		out << endl;
	}
	file.close();
}
