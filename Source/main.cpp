#include <QCoreApplication>

#include "solvercoupledlf0.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	SolverCoupledLF0 S(5., 3.);
	S.solve();

	a.quit();
}
