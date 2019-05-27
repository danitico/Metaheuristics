/*
 * MSPIteratedGreedy.cpp
 *
 *  Created on: 15 may. 2019
 *      Author: chema969
 */

#include <MSPIteratedGreedy.h>
#include <MSPSolution.h>
#include <iostream>

using namespace std;

void MSPIteratedGreedy::chooseOperation(
		MSPBooleanChangeOperation& operation) {

	int bestLiteral = 0;
	double bestDeltaFitness = 0;
	bool initialisedBestDeltaFitness = false;
	unsigned numLiterals = _instance->getNumberOfLiterals();

	/**
	 *
	 * Iterate over the objects which are not in any knapsack (0)
	 *   Iterate over all the knapsacks
	 *     Obtain difference of fitness of assigning the object to the knapsack and the density
	 *     Store the assignment as the best if it is the one resulting in the highest density
	 */

	for (unsigned i = 1; i <= numLiterals; i++) {

		int indexLiteral = i;
        if(!_sol->isTrue(i)){
			//Obtain delta fitness and density (deltaFitness divided by weight)
			double deltaFitness = MSPEvaluator::computeDeltaFitness(*_instance, *_sol, indexLiteral);
			//update the best values if they are improved
			if (deltaFitness > bestDeltaFitness || initialisedBestDeltaFitness == false) {
				initialisedBestDeltaFitness = true;
				bestLiteral = indexLiteral;
				bestDeltaFitness = deltaFitness;
			}
        }
	}

	operation.setValues(bestLiteral, bestDeltaFitness);
}

void MSPIteratedGreedy::rebuild() {

	/** Choose the first operation */
	MSPBooleanChangeOperation operation;
	chooseOperation(operation);

	/**
	 * While the operation has a positive increase of fitness, operation.getDeltaFitness(),
	 *  1. Apply the operation in _sol
	 *  2. Store the fitness of the solution in _result (for the plots)
	 *  3. Select a new operation
	 */
	while (operation.getDeltaFitness() > 0) {
		operation.apply(*_sol);
		_results.push_back(_sol->getFitness());
		chooseOperation(operation);
	}
}

void MSPIteratedGreedy::destroy() {

	/**
	 *
	 * Iterate over all the objects and take them out from
	 * their knapsack with a probability _alpha
	 */

	unsigned numLiterals = _instance->getNumberOfLiterals();

	for (unsigned i = 0; i < numLiterals; i++){

		double randSample = ((double)(rand())) / RAND_MAX;

		if (randSample < _alpha){
			_sol->setBool(i, false);
		}
	}

	double fitness = MSPEvaluator::computeFitness(*_instance, *_sol);
	_sol->setFitness(fitness);
	_results.push_back(_sol->getFitness());
}

void MSPIteratedGreedy::initialise(double alpha, MSPInstance& instance) {
	_sol = new MSPSolution(instance.getNumberOfLiterals());
	_bestSolution = new MSPSolution(instance.getNumberOfLiterals());
	_bestSolution->copy(*_sol);
	_instance = &instance;
	_alpha = alpha;
}

void MSPIteratedGreedy::run(MSPStopCondition& stopCondition) {

	if (_sol == NULL) {
		cerr << "IG was not initialised" << endl;
		exit(-1);
	}

	/** Obtain the first solution */
	rebuild();

	if (MSPEvaluator::compare(_sol->getFitness(), _bestSolution->getFitness()) > 0)
		_bestSolution->copy(*_sol);

	/**
	 *
	 * While the stop condition is not met
	 *  1. Partially destroy the solution
	 *  2. Rebuild the solution
	 *  3. Store the new fitness of the solution in _results
	 *  4. Update the best solution and use it again if the new
	 *     one is worse
	 */

	while (stopCondition.reached() == false) {
		destroy();
		rebuild();
		_results.push_back(_sol->getFitness());

		if (MSPEvaluator::compare(_sol->getFitness(), _bestSolution->getFitness()) > 0){
			_bestSolution->copy(*_sol);
		}
		else{
			_sol->copy(*_bestSolution);
		}

		stopCondition.notifyIteration();
	}
}
