/**
 * MQKPSolGenerator.h
 * 
 * File defining the class MQKPSolGenerator.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */


#ifndef __MQKPSOLGENERATOR_H__
#define __MQKPSOLGENERATOR_H__

#include "MQKPInstance.h"
#include "MQKPSolution.h"

/**
 * Class for generating a random solution of the MQKP
 *
 * About the representation of the solutions:
 * The representation will be a vector of integer values: from 1 to M for the objects which are allocated
 * in one of the M knapsacks and 0 for those non included in any knapsack.
 */
class MQKPSolGenerator {

public:

	/**
	 * Function which generates a random solution for the MQKP
	 * @param[in] instance Reference to an object with the information of the MQKP instance.
	 * @param[out] solution Reference to an object representing a solution to the problem.
     *             IMPORTANT NOTE: it has to be correctly initialize. Specifically, its internal
     *             vector has to be previously reserved.
	 */
	static void genRandomSol(MQKPInstance &instance, MQKPSolution &solution);
};

#endif
