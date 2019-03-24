/*
 * MQKPSimulatedAnnealing.cpp
 *
 * File defining the methods of the class MQKPSimulatedAnnealing.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#include "MQKPSimulatedAnnealing.h"
#include "MQKPSolution.h"
#include "MQKPSolGenerator.h"
#include <MQKPEvaluator.h>
#include <cmath>
#include <iostream>
#include <cstdlib>

using namespace std;

void MQKPSimulatedAnnealing::setSolution(MQKPSolution* solution) {
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
		_bestSolution = new MQKPSolution(*_instance);
	}

	_bestSolution->copy(*solution);
}

void MQKPSimulatedAnnealing::run(MQKPStopCondition& stopCondition) {

	if (_T <= 0 || _annealingFactor <= 0){
		cerr << "Simulated annealing has not been initialised" << endl;
		exit(-1);
	}

	if (_solution == NULL){
		cerr << "Simulated annealing has not been given an initial solution" << endl;
		exit(-1);
	}

	_results.clear();
	unsigned numObjs = _instance->getNumObjs();
	unsigned numKnapsacks = _instance->getNumKnapsacks();
	unsigned numIterations = 0;

	/**
	 * TODO
	 * While the stop condition is not met
	 *   1. Generate random indices for an object and a knapsack (including knapsack 0)
	 *   2. Obtain the difference of fitness when applying the change over _solution
	 *   3. Check if the change is accepted
	 *   4. Update the best so-far solution.
	 *   5. If _itsPerAnnealing iterations has passed since the last temperature decrease,
	 *      then you should decrease the temperature
	 */
	while (stopCondition.r...){
		int indexObject = ...
		int indexKnapsack = ...
		double deltaFitness = MQKPEvaluator::computeDelta...;

		if (...){
			_solution->putObjectIn(indexObject, indexKnapsack);
			_solution->setFitness(_solution->getFitness() + deltaFitness);

			if (MQKPEvaluator::compare(_solution->getFitness(), _bestSolution->getFitness()) > 0){
				_bestSolution->copy(*_solution);
			}
		}
		numIterations++;
		_results.push_back(_solution->getFitness());

		if (numIterations % ...){
			_T *= _annealingFactor;
		}

		stopCondition.notifyIteration();
	}
}

bool MQKPSimulatedAnnealing::accept(double deltaFitness) {
	/**
	 * TODO
	 * Obtain the probability of accepting a change, which is the exponential of
	 * (difference of fitness divided by the temperature)
	 * Generate a random number between 0 and 1
	 * Return true if the random number is lower than the acceptance probability
	 *
	 * (Think about what happens when the difference of fitness is positive and when
	 *  the difference of fitness is negative. You should use the isToBeMinisedMethod
	 *  to interpret correctly the auxDeltaFitness, if the problem is minimization, then
	 *  a negative difference of fitness is good)
	 */
	double auxDeltaFitness = ...

	if (MQKPEvaluator::isToBeMinimised()){
		...
	}

	double prob = ...;
	double randSample = (((double)rand()) / RAND_MAX);
	return (...);
}

void MQKPSimulatedAnnealing::initialise(double initialProb, int numInitialEstimates, double annealingFactor, unsigned itsPerAnnealing, MQKPInstance &instance) {
	_initialProb = initialProb;
	_annealingFactor = annealingFactor;
	_instance = &instance;
	_itsPerAnnealing = itsPerAnnealing;
	int numObjs = instance.getNumObjs();
	int numKnapsacks = instance.getNumKnapsacks();
	double averageFDiffs = 0.;

	/**
	 * Initialize the temperature:
	 * - For this, you will have to generate some random solutions and the indices for changes to
	 *   random neighboring solutions
	 * - You will have to obtain the average difference of fitness for changes to worse solutions
	 * - Then, you will have to derive the initial temperature from the equation used for accepting
	 *   worse solutions
	 */

	for (int i = 0; i < numInitialEstimates; i++){
		MQKPSolution sol(instance);
		MQKPSolGenerator::genRandomSol(instance, sol);
		sol.setFitness(MQKPEvaluator::computeFitness(instance, sol));
		int indexObject = rand() % numObjs;
		int indexKnapsack = rand() % (numKnapsacks + 1);
		double deltaFitness = MQKPEvaluator::computeDeltaFitness(instance, sol, indexObject, indexKnapsack);
		averageFDiffs += max(fabs(deltaFitness),10.);
		//There is a minimum difference of 10 to avoid fitness changes too small
		//(for example, when a knapsack is modified and it is not the one leading to
		// maximum violation) (this method could be improved)
	}

	averageFDiffs /= numInitialEstimates;

	_T = -1. * averageFDiffs / log(initialProb);
}
