/*
 * MQKPGrasp.cpp
 *
 * File defining the methods of the class MQKPGrasp.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <MQKPGrasp.h>
#include <vector>
#include <MQKPSimpleFirstImprovementNO.h>
#include <MQKPLocalSearch.h>
#include <iostream>

using namespace std;

void MQKPGrasp::chooseOperation(MQKPObjectAssignmentOperation& operation) {

	int bestObj = 0;
	int bestKnapsack = 0;
	double bestDensity = 0;
	double bestDeltaFitness = 0;
	bool initialisedBestDensity = false;
	unsigned numObjs = _instance->getNumObjs();
	unsigned numKnapsacks = _instance->getNumKnapsacks();

	/**
	 * Obtain the number of tries as the percentage alpha_ of the number of possibilities,
	 * which is the number of objects multiplied by the number of knapsacks.
	 *
	 * You will not count the fact that the objects are already assigned to
	 * a knapsack, you will not count knapsack 0 (objects without a knapsack assigned), and
	 * you will not not count the fact that some knapsacks are already full.
	 */
	unsigned numTries = ((unsigned)(numObjs * numKnapsacks * _alpha));

	/**
	 * TODO
	 * Generate random alternatives of object and knapsack (without knapsack 0) and choose
	 * the alternative leading to better density.
	 */
	for (unsigned i = 0; i < numTries; i++) {
		int indexObj = ...;
		int indexKnapsack = ...;

		double deltaFitness = MQKPEvaluator::computeDel...; //TODO obtain the fitness improvement
		double density = ...; //TODO obtain the density of the operation (difference of fitness divided by the weight)

		//TODO update the best values if they are improved
		if (... > ... || initialisedBestDensity == false) {
			initialisedBestDensity = true;
			bestDensity = ...
			bestObj = ...
			bestKnapsack = ...
			bestDeltaFitness = ...
		}
	}

	operation.setValues(bestObj, bestKnapsack,
			bestDeltaFitness);
}

void MQKPGrasp::buildInitialSolution() {

	/**
	 * Empty the solution _sol assigning a 0 fitness to it and establishing a 0
	 * for the knapsacks of all objects
	 */
	unsigned numObjs = _instance->getNumObjs();

	_sol->setFitness(0.);
	for (unsigned i = 0; i < numObjs; i++) {
		_sol->putObjectIn(i, 0);
	}

	/** Choose the first operation */
	MQKPObjectAssignmentOperation operation;
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

void MQKPGrasp::initialise(double alpha, MQKPInstance& instance) {

	_sol = new MQKPSolution(instance);
	_bestSolution = new MQKPSolution(instance);
	_bestSolution->copy(*_sol);
	_instance = &instance;
	_alpha = alpha;
}

void MQKPGrasp::run(MQKPStopCondition& stopCondition) {

	if (_sol == NULL) {
		cerr << "GRASP was not initialised" << endl;
		exit(-1);
	}

	/**
	 * TODO
	 * While the stop condition is not met
	 *   1. Generate a random solution calling the corresponding method (buildInitialSolution)
	 *   2. Store the fitness of the solution in _results
	 *   3. Optimize _sol using a local search and the neighbourhood operator of the metaheuristic
	 *   4. Update the best so-far solution
	 */
	while (...) {
		bui...
		_results.push_back(_sol->getFitness());
		_ls.optimise...

		vector<double> &auxResults = _ls.getResults();

		for (auto result : auxResults){
			_results.push_back(result);
		}

		if (MQKPEvaluator::compare(_sol->getFitness(), _bestSolution->getFitness()) > 0)
			_bestSolution->copy(*_sol);

		stopCondition.notifyIteration();
	}
}
