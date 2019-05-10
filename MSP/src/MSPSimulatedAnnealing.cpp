#include "MSPSimulatedAnnealing.h"
#include "MSPSolution.h"
#include "MSPRandomSolution.h"
#include <MSPInstance.h>
#include <MSPStopCondition.h>
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
		cerr << "You should not call MSPSimulatedAnnealing::setSolution more than once" << endl;
		exit(1);
	}

	this->_solution = solution;

	if (_bestSolution == NULL){
		_bestSolution = new MSPSolution(*_instance);
	}

	_bestSolution->copy(*solution);
}
void MQKPSimulatedAnnealing::run(MSPStopCondition& stopCondition) {

	if (_T <= 0 || _annealingFactor <= 0){
		cerr << "Simulated annealing has not been initialised" << endl;
		exit(-1);
	}

	if (_solution == NULL){
		cerr << "Simulated annealing has not been given an initial solution" << endl;
		exit(-1);
	}

	_results.clear();
	unsigned numObjs = _instance->getNumberOfLiterals();
	unsigned numKnapsacks = _instance->getNumberOfClauses();
	unsigned numIterations = 0;

	/**
	 *
	 * While the stop condition is not met
	 *   1. Generate random indices for an object and a knapsack (including knapsack 0)
	 *   2. Obtain the difference of fitness when applying the change over _solution
	 *   3. Check if the change is accepted
	 *   4. Update the best so-far solution.
	 *   5. If _itsPerAnnealing iterations has passed since the last temperature decrease,
	 *      then you should decrease the temperature
	 */
	while (stopCondition.reached()==false){
		int indexObject = rand() % numObjs;
		int indexKnapsack = rand() % (numKnapsacks+1);
		double deltaFitness =MQKPEvaluator::computeDeltaFitness(*_instance,*_solution,indexObject,indexKnapsack);
		if (this->accept(deltaFitness) == true){
			_solution->putObjectIn(indexObject, indexKnapsack);
			_solution->setFitness(_solution->getFitness() + deltaFitness);

			if (MQKPEvaluator::compare(_solution->getFitness(), _bestSolution->getFitness()) > 0){
				_bestSolution->copy(*_solution);
			}
		}
		numIterations++;
		_results.push_back(_solution->getFitness());

		if (numIterations % _itsPerAnnealing == 0){
			_T *= _annealingFactor;
		}

		stopCondition.notifyIteration();
	}
}
