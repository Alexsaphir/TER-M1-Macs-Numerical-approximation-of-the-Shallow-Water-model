#ifndef CACHESOLVER_H
#define CACHESOLVER_H

#include <QList>
#include <QFile>
#include <QString>
#include <QTextStream>

#include <iostream>



class CacheSolver
{
public:
	CacheSolver();
	~CacheSolver();

	void addGrid(const QVector<double> * G);
	void addSpeedGrid(const QVector<double> * Vh, const QVector<double> * Vhu);
	void addCorrectedGrid(const QVector<double> * Vh, const QVector<double> * Vz);

	void save(QString filename) const;

private:
	QList<QVector<double>*> *m_cache;
};

#endif // CACHESOLVER_H
