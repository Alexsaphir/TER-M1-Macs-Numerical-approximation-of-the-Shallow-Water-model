#include <QCoreApplication>

#include <chrono>

#include "solverburger.h"
#include "solvercoupledlfsv.h"
#include "solvercoupledlf0.h"
#include "solvercoupledlfsv2.h"

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();


	//SolverBurger SB(3,1, 401);

	//SB.solve();

	//SolverCoupledLF0 S0(3., .5, 401);
	//S0.solve();

	SolverCoupledLFSV SSV(401);
	SSV.solve();

	SolverCoupledLFSV2 SSV2(401);
	SSV2.solve();


	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::duration<double>>( t2 - t1 ).count();

	std::cout << "Solving duration (s): " << duration << std ::endl;

	app.quit();
	return 0;
}
