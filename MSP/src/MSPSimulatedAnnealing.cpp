#include <MSPSimulatedAnnealing.h>
#include <MSPSolution.h>
#include <MSPRandomSolution.h>
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
		_bestSolution = new MSPSolution(_instance->getNumberOfLiterals());
	}

	_bestSolution->copy(*solution);
}
void MSPSimulatedAnnealing::run(MSPStopCondition& stopCondition) {

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
		int indexLiteral = (rand() % (numObjs-1))+1;
		bool oldValue=_solution->isTrue(indexLiteral);

		double deltaFitness =_instance->getDeltaFitness(*_solution,indexLiteral);
		if (this->accept(deltaFitness) == true){
			if(oldValue==false){
				_solution->setBool(indexLiteral, true);
				_solution->setFitness(_solution->getFitness() + deltaFitness);
			}
			if(oldValue==true)
			{
				_solution->setBool(indexLiteral, false);
				_solution->setFitness(_solution->getFitness() + deltaFitness);
			}

			if (_solution->getFitness() > _bestSolution->getFitness()){
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
bool MSPSimulatedAnnealing::accept(double deltaFitness) {
	/**
	 *
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
	double auxDeltaFitness = deltaFitness;

	double prob = exp(auxDeltaFitness/_T);
	double randSample = (((double)rand()) /RAND_MAX);

	if(randSample<prob){
		return true;
	}
	else{
		return false;
	}

}
void MSPSimulatedAnnealing::initialise(double initialProb, int numInitialEstimates, double annealingFactor, unsigned itsPerAnnealing, MSPInstance &instance) {
	_initialProb = initialProb;
	_annealingFactor = annealingFactor;
	_instance = &instance;
	_itsPerAnnealing = itsPerAnnealing;
	unsigned numObjs = _instance->getNumberOfLiterals();
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
		MSPSolution sol(instance.getNumberOfLiterals());
		MSPRandomSolution::genRandomSol(instance, sol);
		sol.setFitness(_instance->computeFitness(sol));
		int indexObject = rand() % numObjs;
		double deltaFitness =_instance->getDeltaFitness(sol, indexObject);
		averageFDiffs += max(fabs(deltaFitness),10.);
		//There is a minimum difference of 10 to avoid fitness changes too small
		//(for example, when a knapsack is modified and it is not the one leading to
		// maximum violation) (this method could be improved)
	}

	averageFDiffs /= numInitialEstimates;

	_T = -1. * averageFDiffs / log(initialProb);
}
