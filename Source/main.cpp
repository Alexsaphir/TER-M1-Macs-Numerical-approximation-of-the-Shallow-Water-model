#include <QCoreApplication>

#include <QDebug>

#include "solverlaxfriedrichs.h"
#include "solverlaxfriedrichs2s.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	//SolverLaxFriedrichs S(2., 3.);
	//S.solve();


	SolverLaxFriedrichs2S S2(3, 2.);
	S2.solve();

	a.quit();
}
