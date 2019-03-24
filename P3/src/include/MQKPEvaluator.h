/**
 * MQKPEvaluator.h
 * 
 * File defining the class MQKPEvaluator.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
*/

#ifndef __MQKPEvaluator_H__
#define __MQKPEvaluator_H__

#include "MQKPInstance.h"
#include "MQKPSolution.h"

/**
 * Class for obtaining the fitness of a solution of the MQKP
 */

class MQKPEvaluator {

protected:
	/**
	 * Variable counting the number of solutions that have been evaluated using computeFitness or computeDeltaFitness
	 */
	static unsigned _numEvaluations;

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
	static double computeFitness(MQKPInstance &instance, MQKPSolution &solution);

	/**
	 * Function which obtains the difference of fitness when the solution passed as an argument is modified
	 * by assigning a given object to a given knapsack.
	 * @param[in] instance Reference to an object with information about the instance of the MQKP
	 * @param[in] solution Reference to an object with the information of the current solution
	 * @param[in] indexObject Index of the object which would be included in other knapsack
	 * @param[in] indexKnapsack Index of the knapsack in which the object would be included.
	 *                          It can be 0 (the object is taken out from the current knapsack and
	 *                          not included in any other one
	 *
	 * @return Difference of fitness after including the object indexObject in the knapsack indexKnapsack
	 */
	static double computeDeltaFitness(MQKPInstance &instance, MQKPSolution &solution, int indexObject, int indexKnapsack);

	/**
	 * Function which resets the internal variable storing the number of evaluations.
	 */
	static void resetNumEvaluations();

	/**
	 * Function for observing the number of times any solution has been evaluated.
	 */
	static unsigned getNumEvaluations() {
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
		return (0); //TODO correct the value that has to be returned
	}

	/**
	 * Function for indicating if the problem is a minimization or a maximization problem
	 * @return true if the problem is minimization, false if it is maximization
	 */
	static bool isToBeMinimised(){
		return (compare(0,1) > 0);
	}
};

#endif
