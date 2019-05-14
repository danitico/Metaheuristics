/*
 * MSPEvaluator.h
 *
 *  Created on: May 13, 2019
 *      Author: daniel
 */

#ifndef INCLUDE_MSPEVALUATOR_H_
#define INCLUDE_MSPEVALUATOR_H_

#include <MSPInstance.h>
#include <MSPSolution.h>

class MSPEvaluator {

protected:
	/**
	 * Variable counting the number of solutions that have been evaluated using computeFitness or computeDeltaFitness
	 */
	static double _numEvaluations;

public:
	/**
	 * Function obtaining the fitness of a solution
	 * @param[in] instance Reference to an object with the information of the MQKP instance.
	 * @param[in] solution Reference to an object with a MQKP solution.
	 *
	 * @return Solution fitness. It will be negative if the capicity constraint is violated for a
	 *                           given knapsack and positive if the solution is feasible.
	 *                           In this case, the value is the sum of the individual and shared profits.
	 */
	static double computeFitness(MSPInstance &instance, MSPSolution &solution);

	/**
	 * Function which obtains the difference of fitness when the solution passed as an argument is modified
	 * by assigning a given object to a given knapsack.
	 * @param[in] instance Reference to an object with information about the instance of the MQKP
	 * @param[in] solution Reference to an object with the information of the current solution
	 *
	 * @return Difference of fitness after including the object indexObject in the knapsack indexKnapsack
	 */
	static double computeDeltaFitness(MSPInstance &instance, MSPSolution &solution, int position);

	/**
	 * Function which resets the internal variable storing the number of evaluations.
	 */
	static void resetNumEvaluations();

	/**
	 * Function for observing the number of times any solution has been evaluated.
	 */
	static double getNumEvaluations() {
		return _numEvaluations;
	}

	/**
	 * Function that compares two fitness values. Its purpose is to specify if the problem is a
	 * minimization problem or a maximization one.
	 * @param[in] f1 first fitness value to compare
	 * @param[in] f2 second fitness value to compare
	 * @return A positive value if the first value is better than the second, a negative if the second
	 *         is better than the first, 0 if they cannot be differentiated
	 */
	static double compare(double f1, double f2){
		return (f1 - f2);
	}

	/**
	 * Function for indicating if the problem is a minimization or a maximization problem
	 * @return true if the problem is minimization, false if it is maximization
	 */
	static bool isToBeMinimised(){
		return (compare(0,1) > 0);
	}
};




#endif /* INCLUDE_MSPEVALUATOR_H_ */
