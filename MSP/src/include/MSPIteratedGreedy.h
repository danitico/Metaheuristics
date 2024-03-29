/*
 * MSPIteratedGreedy.h
 *
 *  Created on: 15 may. 2019
 *      Author: chema969
 */

#ifndef INCLUDE_MSPITERATEDGREEDY_H_
#define INCLUDE_MSPITERATEDGREEDY_H_

#include <MSPMetaheuristic.h>
#include <MSPSolution.h>
#include <MSPInstance.h>
#include <MSPBooleanChangeOperation.h>
#include <vector>
using namespace std;

/**
 * Class implementing the Iterated Greedy metaheuristic for MQKP, in the variant that the
 * destruction is always applies to the best solution and local search is not considered
 */
class MSPIteratedGreedy : public MSPMetaheuristic{

protected:

	/**
	 * Properties of the class
	 * _alpha stores the probability that the objects are removed from their corresponding knapsacks
	 * _instance is a pointer to the instance of the problem
	 * _sol stores the solution considered by Iterated Greedy, during the destructions and constructions
	 */
	double _alpha;
	MSPInstance *_instance;
	MSPSolution *_sol;

	/**
	 * Vector of doubles with the quality of the last solution evaluated
	 */
	vector<double> _results;

	/**
	 * Function returning the best assignment operation of a non-assigned object to a knapsack
	 * from a series of randomly selected alternatives
	 * @param[out] operation Assignment operation of an object to a knapsack
	 */
	void chooseOperation(MSPBooleanChangeOperation &operation);

	/**
	 * Function which rebuilds the solution _sol. For this, it iteratively calls to the
	 * function chooseOperation until it does not find any other assignment
	 * operation improving the current solution. The changes are stored in the property
	 * _sol
	 */
	void rebuild();

	/**
	 * Function which partially destroys the solution _sol. For this, it removes objects
	 * from their knapsacks with probability _alpha
	 */
	void destroy();

public:
	/**
	 * Constructor
	 */
	MSPIteratedGreedy(){
		_alpha = 0.;
		_instance = NULL;
		_sol = NULL;
	}

	/**
	 * Destructor
	 */
	virtual ~MSPIteratedGreedy(){

		if (_bestSolution != NULL){
			delete _bestSolution;
			_bestSolution = NULL;
		}

		if (_sol != NULL){
			delete _sol;
			_sol = NULL;
		}
	}

	/**
	 * Function which initializes some parameters of the metaheuristic.
	 * Specifically, the properties _sol and _bestSolution and the probability  alpha
	 * @param[in] alpha Probability of removing an object from its knapsack during the destruction phase
	 * @param[in] instance Instance of the problem to be tackled
	 */
	void initialise(double alpha, MSPInstance &instance);

	/**
	 * Function which runs the metaheuristic until reaching the stop condition
	 * @param[in] stopCondition Stop condition of the metaheuristic
	 */
	virtual void run(MSPStopCondition &stopCondition);

	/**
	 * Function returning the array with the results of the solutions accepted, in each step,
	 * by the metaheuristic
	 * @return vector with the results of the solutions accepted, in each step,
	 *         by the metaheuristic
	 */
	vector<double>& getResults() {
		return _results;
	}
};

#endif /* INCLUDE_MSPITERATEDGREEDY_H_ */
