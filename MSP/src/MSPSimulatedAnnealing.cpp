#include <MSPSimulatedAnnealing.h>
#include <MSPSolution.h>
#include <MSPRandomSolution.h>
#include <MSPInstance.h>
#include <cmath>
#include <iostream>
#include <cstdlib>

using namespace std;

void MSPSimulatedAnnealing::setSolution(MSPSolution* solution) {
	if (_T <= 0 || _annealingFactor <= 0){
		cerr << "Simulated annealing has not been initialized" << endl;
		exit(-1);
	}

	if (_solution != NULL){
		cerr << "You should not call MQKPSimulatedAnnealing::setSolution more than once" << endl;
		exit(1);
	}

	this->_solution = solution;

	if (_bestSolution == NULL){
		_bestSolution = new MSPSolution(*_instance);
	}

	_bestSolution->copy(*solution);
}
