#include <QCoreApplication>

#include <chrono>

#include "solvercoupledlfsv.h"
#include "solvercoupledlf0.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	//SolverCoupledLF0 S(3., 1.);
	//S.solve();

	SolverCoupledLFSV S;

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

	S.solve();

	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::duration<double>>( t2 - t1 ).count();
	std::cout << "Solving duration (s): " << duration << std ::endl;

	a.quit();
}
