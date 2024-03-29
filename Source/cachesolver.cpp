#include "cachesolver.h"

CacheSolver::CacheSolver()
{
	m_cache = new QList<QVector<double>*>;
}

CacheSolver::~CacheSolver()
{
	//while(!m_cache->isEmpty())
		//delete m_cache->last();
	delete m_cache;
}

void CacheSolver::addGrid(const QVector<double> *G)
{
	QVector<double> *tmp = new QVector<double>;
	tmp->resize(G->size());
#pragma omp parallel
	for(int i=0; i<tmp->size(); ++i)
		tmp->replace(i, G->at(i));

	m_cache->append(tmp);
}

void CacheSolver::addSpeedGrid(const QVector<double> *Vh, const QVector<double> *Vhu)
{
	QVector<double> *tmp = new QVector<double>;
	tmp->resize(Vh->size());
#pragma omp parallel
	for(int i=0; i<tmp->size(); ++i)
	{
		double h = Vh->at(i);
		if(h<=0.)
			tmp->replace(i, 0.);
		else
			tmp->replace(i, Vhu->at(i) / h);
	}

	m_cache->append(tmp);
}

void CacheSolver::addCorrectedGrid(const QVector<double> *Vh, const QVector<double> *Vz)
{
	QVector<double> *tmp = new QVector<double>;
	tmp->resize(Vh->size());
#pragma omp parallel
	for(int i=0; i<tmp->size(); ++i)
	{
		double h = Vh->at(i);
		if(h<=0.)
			tmp->replace(i, Vz->at(i));
		else
			tmp->replace(i, Vz->at(i) + h);
	}

	m_cache->append(tmp);
}

void CacheSolver::save(QString filename) const
{
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;
	QTextStream out(&file);

	for(int i=0; i<m_cache->size(); ++i)
	{
		for (int j=0; j<m_cache->at(i)->size(); ++j)
		{
			out << m_cache->at(i)->at(j);
			if(j<m_cache->at(i)->size()-1)
				out << " ";
		}
		out << endl;
	}
	file.close();
}
