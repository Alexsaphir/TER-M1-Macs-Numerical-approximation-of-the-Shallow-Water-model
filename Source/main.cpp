#include <QCoreApplication>

#include <chrono>

#include "solvercoupledlfsv.h"
#include "solvercoupledlf0.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	//SolverCoupledLF0 S(3., 1.);
	//S.solve();

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

	SolverCoupledLFSV S(3., 1.);

	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
	std::cout << "Init duration (ms): " << duration << std ::endl;


	t1 = std::chrono::high_resolution_clock::now();

	S.solve();

	t2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
	std::cout << "Solving duration (ms): " << duration << std ::endl;

	a.quit();
}
