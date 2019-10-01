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

	for (unsigned i = 1; i <= numLiterals; i++) {

		int indexLiteral = i;
		if(!_sol->isTrue(i)){

			double deltaFitness = MSPEvaluator::computeDeltaFitness(*_instance, *_sol, indexLiteral);

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

	MSPBooleanChangeOperation operation;
	chooseOperation(operation);

	while (operation.getDeltaFitness() > 0) {
		operation.apply(*_sol);
		_results.push_back(_sol->getFitness());
		chooseOperation(operation);
	}
}

void MSPIteratedGreedy::destroy() {

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
