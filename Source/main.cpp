#include <QCoreApplication>

#include "solvercoupledlfsv.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	//SolverCoupledLF0 S(5., 3.);
	//S.solve();

	SolverCoupledLFSV S(5., 3.);
	S.initialCondition();

	S.solve();
	S.exportData();

	a.quit();
}
