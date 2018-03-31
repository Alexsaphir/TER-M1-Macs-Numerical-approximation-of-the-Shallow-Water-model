#include <QCoreApplication>

#include "solvercoupledlf0.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	SolverCoupledLF0 S(3., 2.);
	S.solve();

	a.quit();
}
