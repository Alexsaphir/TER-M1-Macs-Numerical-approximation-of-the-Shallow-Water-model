#include <QCoreApplication>

#include <QDebug>

#include "solverlaxfriedrichs.h"
#include "solverlaxfriedrichs2s.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	//SolverLaxFriedrichs S(1., 2.);
	//S.solve();


	SolverLaxFriedrichs2S S2(2., 1.);
	S2.solve();

	a.quit();
}
