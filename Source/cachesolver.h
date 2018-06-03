#ifndef CACHESOLVER_H
#define CACHESOLVER_H

#include <QList>
#include <QFile>
#include <QString>
#include <QTextStream>

#include <iostream>

/**
 * @brief The CacheSolver class store a collection of data to save them on disk later
 */

class CacheSolver
{
public:
	/**
	 * @brief CacheSolver Create a cach for Grid
	 */
	CacheSolver();
	~CacheSolver();

	/**
	 * @brief addGrid Copy a grid in memory
	 * @param G QVector of data to store
	 */
	void addGrid(const QVector<double> * G);
	/**
	 * @brief addSpeedGrid Add a grid where the value need to be compute to obtain the speed
	 * @param Vh h
	 * @param Vhu hu
	 */
	void addSpeedGrid(const QVector<double> * Vh, const QVector<double> * Vhu);
	/**
	 * @brief addCorrectedGrid Add a Grid where the value to store need to be the sum of two Grid
	 * @param Vh Heigh
	 * @param Vz Ground
	 */
	void addCorrectedGrid(const QVector<double> * Vh, const QVector<double> * Vz);

	/**
	 * @brief save Write the integrality of the cache on the disk
	 * @param filename File where to write the data
	 */
	void save(QString filename) const;

private:
	/**
	 * @brief m_cache List of Data to store
	 */
	QList<QVector<double>*> *m_cache;
};

#endif // CACHESOLVER_H
