/*
 * MQKPIteratedGreedy.cpp
 *
 * File defining the methods of the class MQKPIteratedGreedy.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <MQKPIteratedGreedy.h>
#include <MQKPObjectAssignmentOperation.h>
#include <MQKPSolution.h>
#include <iostream>

using namespace std;

void MQKPIteratedGreedy::chooseOperation(
		MQKPObjectAssignmentOperation& operation) {

	int bestObj = 0;
	int bestKnapsack = 0;
	double bestDensity = 0;
	double bestDeltaFitness = 0;
	bool initialisedBestDensity = false;
	unsigned numObjs = _instance->getNumObjs();
	unsigned numKnapsacks = _instance->getNumKnapsacks();

	/**
	 * TODO
	 * Iterate over the objects which are not in any knapsack (0)
	 *   Iterate over all the knapsacks
	 *     Obtain difference of fitness of assigning the object to the knapsack and the density
	 *     Store the assignment as the best if it is the one resulting in the highest density
	 */

	for (unsigned i = 0; i < numObjs; i++) {

		int indexObj = i;

		if (_sol->w...) { //TODO check that it is not in a knapsack

			for (unsigned j = ...) { //TODO for all the available knapsacks (do not consider 0) 

				//TODO Obtain delta fitness and density (deltaFitness divided by weight)
				int indexKnapsack = j;

				double deltaFitness = MQKPEvaluator::computeDel...;
				double density = ...;

				//update the best values if they are improved
				if (... || initialisedBestDensity == false) {
					initialisedBestDensity = true;
					bestDensity = ...;
					bestObj = ...;
					bestKnapsack = ...;
					bestDeltaFitness = ...;
				}
			}
		}
	}

	operation.setValues(bestObj, bestKnapsack, bestDeltaFitness);
}

void MQKPIteratedGreedy::rebuild() {

	/** Choose the first operation */
	MQKPObjectAssignmentOperation operation;
	chooseOperation(operation);

	/** TODO
	 * While the operation has a positive increase of fitness, operation.getDeltaFitness(),
	 *  1. Apply the operation in _sol
	 *  2. Store the fitness of the solution in _result (for the plots)
	 *  3. Select a new operation
	 */
	while (operation.getDeltaFitness() > 0) {
		...
	}
}

void MQKPIteratedGreedy::destroy() {

	/**
	 * TODO
	 * Iterate over all the objects and take them out from
	 * their knapsack with a probability _alpha
	 */

	unsigned numObjs = _instance->getNumObjs();

	for (unsigned i = 0; i < numObjs; i++){

		double randSample = ((double)(rand())) / RAND_MAX;

		if (...){
			_sol->putObjectIn(i, 0);
		}
	}

	double fitness = MQKPEvaluator::computeFitness(*_instance, *_sol);
	_sol->setFitness(fitness);
	_results.push_back(_sol->getFitness());
}

void MQKPIteratedGreedy::initialise(double alpha, MQKPInstance& instance) {
	_sol = new MQKPSolution(instance);
	_bestSolution = new MQKPSolution(instance);
	_bestSolution->copy(*_sol);
	_instance = &instance;
	_alpha = alpha;
}

void MQKPIteratedGreedy::run(MQKPStopCondition& stopCondition) {

	if (_sol == NULL) {
		cerr << "IG was not initialised" << endl;
		exit(-1);
	}

	/** Obtain the first solution */
	rebuild();

	if (MQKPEvaluator::compare(_sol->getFitness(), _bestSolution->getFitness()) > 0)
		_bestSolution->copy(*_sol);

	/**
	 * TODO
	 * While the stop condition is not met
	 *  1. Partially destroy the solution
	 *  2. Rebuild the solution
	 *  3. Store the new fitness of the solution in _results
	 *  4. Update the best solution and use it again if the new
	 *     one is worse
	 */

	while (stopCondition.reached() == false) {
		...
		...
		_results.push_back(_sol->getFitness());

		if (MQKPEvaluator::compare(_sol->getFitness(), _bestSolution->getFitness()) > 0)
			...
		else
			...

		stopCondition.notifyIteration();
	}
}


