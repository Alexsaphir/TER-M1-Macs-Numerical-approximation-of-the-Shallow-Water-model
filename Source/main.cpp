#include <QCoreApplication>

#include <QDebug>

#include "solverlaxfriedrichs.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	SolverLaxFriedrichs S;

	S.solve();

	a.quit();
}
