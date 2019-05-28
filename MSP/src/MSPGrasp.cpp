#include <MSPGrasp.h>
#include <vector>
#include <FirstImprovement.h>
#include <LocalSearch.h>
#include <iostream>
using namespace std;

void MSPGrasp::chooseOperation(MSPBooleanChangeOperation& operation) {

	int bestLiteral = 0;
	double bestDeltaFitness = 0;
	bool initialisedBestDeltaFitness = false;
	unsigned numLiterals = _instance->getNumberOfLiterals();


	for (unsigned i = 1; i <=numLiterals; i++) {

		int indexLiteral = rand()%(numLiterals+1);
		        if(!_sol->isTrue(indexLiteral)&&indexLiteral>0){
			//Obtain delta fitness
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

void MSPGrasp::buildInitialSolution() {

	/**
	 * Empty the solution _sol assigning a 0 fitness to it and establishing a 0
	 * for the knapsacks of all objects
	 */
	unsigned numLiterals = _instance->getNumberOfLiterals();

	_sol->setFitness(0.);
	for (unsigned i = 0; i < numLiterals; i++) {
		_sol->setBool(i,false);
	}

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

void MSPGrasp::initialise(double alpha, MSPInstance& instance) {

	unsigned i=instance.getNumberOfLiterals();
	_sol = new MSPSolution(i);
	_bestSolution = new MSPSolution(i);
	_bestSolution->copy(*_sol);
	_instance = &instance;
	_alpha = alpha;
}

void MSPGrasp::run(MSPStopCondition& stopCondition) {

	if (_sol == NULL) {
		cerr << "GRASP was not initialised" << endl;
		exit(-1);
	}

	/**
	 *
	 * While the stop condition is not met
	 *   1. Generate a random solution calling the corresponding method (buildInitialSolution)
	 *   2. Store the fitness of the solution in _results
	 *   3. Optimize _sol using a local search and the neighbourhood operator of the metaheuristic
	 *   4. Update the best so-far solution
	 */
	while (! stopCondition.reached()) {
		buildInitialSolution();
		_results.push_back(_sol->getFitness());
		_ls.optimise(*_instance, _no, *_sol);

		vector<double> &auxResults = _ls.getResults();

		for (auto result : auxResults){
			_results.push_back(result);
		}

		if (MSPEvaluator::compare(_sol->getFitness(), _bestSolution->getFitness()) > 0)
			_bestSolution->copy(*_sol);

		stopCondition.notifyIteration();
	}
}
