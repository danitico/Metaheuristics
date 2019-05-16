/*
 * MSPTabuSearch.cpp
 *
 *  Created on: May 16, 2019
 *      Author:
 */

#include <MSPEvaluator.h>
#include <MSPBooleanChangeOperation.h>
#include <MSPTabuSearch.h>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>

using namespace std;

void MSPTabuSearch::initialise(MSPInstance* instance, unsigned tabuTennure) {
	_instance = instance;
	_tabuTennure = tabuTennure;
}

void MSPTabuSearch::setSolution(MSPSolution* solution) {

	if (_solution != NULL){
		cerr << "You should not call MSPTabuSearch::setSolution more than once" << endl;
		exit(1);
	}

	this->_solution = solution;

	if (_bestSolution == NULL) {
		_bestSolution = new MSPSolution(_instance->getNumberOfLiterals());
	}

	_bestSolution->copy(*solution);
}

void MSPTabuSearch::run(MSPStopCondition& stopCondition) {
	if (_solution == NULL) {
		cerr << "Tabu search has not been given an initial solution" << endl;
		exit(-1);
	}

	_results.clear();
	unsigned numLiteral = _instance->getNumberOfLiterals();
	unsigned numIterations = 0;

	/**
	 *
	 * While the stop condition is not met
	 *   1. Generate a permutation of the objects
	 *   2. Search for the best non tabu operation assigning an object to a knapsack (0 included)
	 *   3. Apply the operation
	 *   4. Insert the index of the object used in the tabu memory
	 *   4. Update the best so-far solution
	 */

	while (!stopCondition.reached()) {

		vector<int> perm;
		_instance->randomPermutationOfLiterals(perm);
		double bestDeltaFitness = 0;
		bool initialisedDeltaFitness = false;
		MSPBooleanChangeOperation bestOperation;

		//Obtain the best non-tabu operation
		for (unsigned i = 0; i < numLiteral; i++) {
			unsigned indexObj = perm[i];

			//If the object is not tabu (use _shortTermMem_aux.find)
			if (_shortTermMem_aux.find(indexObj) == _shortTermMem_aux.end()) {
				//Obtain the difference of fitness of applying the operation
				double deltaFitness = MSPEvaluator::computeDeltaFitness(*_instance, *_solution, indexObj);

				//If the difference of fitness is the best up to this moment,
				//store it to apply it later
				if (deltaFitness > bestDeltaFitness
						|| initialisedDeltaFitness == false) {
					initialisedDeltaFitness = true;
					bestDeltaFitness = deltaFitness;
					bestOperation.setValues(indexObj, bestDeltaFitness);
				}
			}
		}

		//Apply the operation and store it in the short term memory
		bestOperation.apply(*_solution);
		_shortTermMem.push(bestOperation.getLiteral());
		_shortTermMem_aux.insert(bestOperation.getLiteral());

		//If there are too many elements in the memory, according to the tabu tennure,
		//delete the eldest one (i.e. obtain the first element of the queue and eliminate it
		//from the queue and from the set)
		if (_shortTermMem.size() > _tabuTennure) {
			unsigned value = _shortTermMem.front();
			_shortTermMem.pop();
			_shortTermMem_aux.erase(value);
		}

		//Update the best solution
		if (MSPEvaluator::compare(_solution->getFitness(),
				_bestSolution->getFitness()) > 0) {
			_bestSolution->copy(*_solution);
		}

		numIterations++;
		_results.push_back(_solution->getFitness());

		stopCondition.notifyIteration();
	}
}


