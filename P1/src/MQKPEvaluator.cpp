/*
 * MQKPEvaluator.cpp
 *
 * File defining the methods of the class MQKPEvaluator.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#include "MQKPSolution.h"
#include "MQKPInstance.h"
#include "MQKPEvaluator.h"

double MQKPEvaluator::computeFitness(MQKPInstance &instance, MQKPSolution &solution){

	double fitness = 0;
	fitness = instance.getMaxCapacityViolation(solution);

	if(fitness > 0){
		fitness*=-1;
	}
	else{
		fitness = instance.getSumProfits(solution);
	}
	/*
	 *  Calculate the fitness of the solution in the following way:
	 *   1. Obtain the maximum violation of the knapsack capacities, by using the corresponding function.
	 *   2. If it is higher than 0, then return the maximum violation multiplied by -1.
	 *   3. If not, the return the sum of the individual and share profits using the corresponding function.
	 */

	return fitness;
}



