#include <QCoreApplication>

#include <QDebug>

#include "solverlaxfriedrichs.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	SolverLaxFriedrichs S(3., 2.);

	S.solve();

	a.quit();
}
