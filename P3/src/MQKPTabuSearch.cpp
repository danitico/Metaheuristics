/*
 * MQKPTabuSearch.cpp
 *
 * File defining the methods of the class MQKPTabuSearch.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <MQKPEvaluator.h>
#include <MQKPObjectAssignmentOperation.h>
#include <MQKPTabuSearch.h>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>

using namespace std;

void MQKPTabuSearch::initialise(MQKPInstance* instance, unsigned tabuTennure) {
	_instance = instance;
	_tabuTennure = tabuTennure;
}

void MQKPTabuSearch::setSolution(MQKPSolution* solution) {

	if (_solution != NULL){
		cerr << "You should not call MQKPTabuSearch::setSolution more than once" << endl;
		exit(1);
	}

	this->_solution = solution;

	if (_bestSolution == NULL) {
		_bestSolution = new MQKPSolution(*_instance);
	}

	_bestSolution->copy(*solution);
}

void MQKPTabuSearch::run(MQKPStopCondition& stopCondition) {
	if (_solution == NULL) {
		cerr << "Tabu search has not been given an initial solution" << endl;
		exit(-1);
	}

	_results.clear();
	unsigned numObjs = _instance->getNumObjs();
	unsigned numKnapsacks = _instance->getNumKnapsacks();
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
		MQKPInstance::randomPermutation(numObjs, perm);
		double bestDeltaFitness = 0;
		bool initialisedDeltaFitness = false;
		MQKPObjectAssignmentOperation bestOperation;

		//Obtain the best non-tabu operation
		for (unsigned i = 0; i < numObjs; i++) {
			unsigned indexObj = perm[i];

			//If the object is not tabu (use _shortTermMem_aux.find)
			if (_shortTermMem_aux.find(indexObj) == _shortTermMem_aux.end()) {

				//Try all the knapsacks (including 0) and choose the best option
				for (unsigned j = 0; j <= numKnapsacks; j++) {

					//Ignore the change which does not modify the object
					if (_solution->whereIsObject(indexObj) == ((int)j))
						continue;

					//Obtain the difference of fitness of applying the operation
					double deltaFitness = MQKPEvaluator::computeDeltaFitness(*_instance, *_solution, indexObj, j);

					//If the difference of fitness is the best up to this moment,
					//store it to apply it later
					if (deltaFitness > bestDeltaFitness
							|| initialisedDeltaFitness == false) {
						initialisedDeltaFitness = true;
						bestDeltaFitness = deltaFitness;
						bestOperation.setValues(indexObj, j, bestDeltaFitness);
					}
				}
			}
		}

		//Apply the operation and store it in the short term memory
		bestOperation.apply(*_solution);
		_shortTermMem.push(bestOperation.getObj());
		_shortTermMem_aux.insert(bestOperation.getObj());

		//If there are too many elements in the memory, according to the tabu tennure,
		//delete the eldest one (i.e. obtain the first element of the queue and eliminate it
		//from the queue and from the set)
		if (_shortTermMem.size() > _tabuTennure) {
			unsigned value = _shortTermMem.front();
			_shortTermMem.pop();
			_shortTermMem_aux.erase(value);
		}

		//Update the best solution
		if (MQKPEvaluator::compare(_solution->getFitness(),
				_bestSolution->getFitness()) > 0) {
			_bestSolution->copy(*_solution);
		}

		numIterations++;
		_results.push_back(_solution->getFitness());

		stopCondition.notifyIteration();
	}
}
