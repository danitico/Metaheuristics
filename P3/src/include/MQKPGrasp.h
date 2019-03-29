/**
 * MQKPGrasp.h
 *
 * File defining the class MQKPGrasp.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
*/

#ifndef INCLUDE_MQKPGRASP_H_
#define INCLUDE_MQKPGRASP_H_

#include <MQKPMetaheuristic.h>
#include <MQKPInstance.h>
#include <MQKPSolution.h>
#include <MQKPLocalSearch.h>
#include <MQKPSimpleFirstImprovementNO.h>
#include <MQKPObjectAssignmentOperation.h>
#include <vector>

using namespace std;

/**
 * Class implementing the GRASP metaheuristic, in the variant of constructing a greedy
 * solution by selecting the best option between a series of alternative random
 * solutions
 */
class MQKPGrasp : public MQKPMetaheuristic{

protected:

	/**
	 * Properties of the class
	 * _alpha will be a value in the range (0,1), indicating the percentage of alternatives
	 *        to evaluate to select the best option to add to the solution which is being
	 *        constructed
	 * _instance is a pointer to the instance of the problem
	 * _sol stores the solution considered by GRASP, during the constructions and the application
	 *      of the local search
	 * _ls is the internal local search used to improve the solutions generated
	 * _no is the neighborhood operator used for the internal local search
	 */
	double _alpha;
	MQKPInstance *_instance;
	MQKPSolution *_sol;
	MQKPLocalSearch _ls;
	MQKPSimpleFirstImprovementNO _no;

	/**
	 * Vector of doubles with the quality of the last solution evaluated
	 */
	vector<double> _results;

	/**
	 * Function returning the best assignment operation of a non-assigned object to a knapsack
	 * from a series of randomly selected alternatives
	 * @param[out] operation Assignment operation of an object to a knapsack
	 */
	void chooseOperation(MQKPObjectAssignmentOperation &operation);

	/**
	 * Function which creates a solution from the empty knapsack. For this, it iteratively calls to
	 * chooseOperation until it does not find any other assignment operation improving the current
	 * solution (from those randomly selected).
	 * The changes are stored in the property _sol.
	 */
	void buildInitialSolution();

public:
	/**
	 * Constructor
	 */
	MQKPGrasp(){
		_sol = NULL;
		_instance = NULL;
		_alpha = 0;
	}

	/**
	 * Destructor
	 */
	virtual ~MQKPGrasp(){

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
	 * Specifically, the properties _sol and _bestSolution and the percentage alpha
	 * @param[in] alpha Percentage between 0 and 1 of the number of random alternatives
	 *                  to evaluate each time it chooses the next assignment operation
	 *                  of an object to a knapsack to apply over _sol
	 * @param[in] instance Instance of the problem to be tackled
	 */
	void initialise(double alpha, MQKPInstance &instance);

	/**
	 * Function which runs the metaheuristic until reaching the stop condition
	 * @param[in] stopCondition Stop condition of the metaheuristic
	 */
	virtual void run(MQKPStopCondition &stopCondition);

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

#endif /* INCLUDE_MQKPGRASP_H_ */
