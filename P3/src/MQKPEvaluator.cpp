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

#include <MQKPEvaluator.h>
#include <MQKPInstance.h>
#include <MQKPSolution.h>

unsigned MQKPEvaluator::_numEvaluations = 0;

double MQKPEvaluator::computeFitness(MQKPInstance &instance, MQKPSolution &solution){

	double fitness = 0;

	/*
	 * Calculate the fitness of the solution in the following way:
	 *   1. Obtain the maximum violation of the knapsack capacities, by using the corresponding function.
	 *   2. If it is higher than 0, then return the maximum violation multiplied by -1.
	 *   3. If not, the return the sum of the individual and share profits using the corresponding function.
	 */
	 if(instance.getMaxCapacityViolation(solution) > 0)
	 {
	 	fitness = instance.getMaxCapacityViolation(solution) * (-1);
	 }
	 else
	 {
	 	fitness = instance.getSumProfits(solution);
	 }

	 _numEvaluations++;
	return fitness;
}

double MQKPEvaluator::computeDeltaFitness(MQKPInstance& instance,
		MQKPSolution& solution, int indexObject, int indexKnapsack) {

	_numEvaluations++;

	/**
	 * Given that the fitness depends on the violation of the capacities of the knapsack,
	 * you should obtain current (maximum) violation and the possible new violation, together
	 * with the possible change in the sum of profits.
	 *
	 * 1. Obtain maximum current violation
	 * 2. Call to MQKPInstance.getDeltaMaxCapacityViolation to return how the maximum violation is modified
	 *    after the operation
	 * 3. Sum the two previous quantities to obtain maximum violation after applying the operation
	 * 4. Obtain the current sum of profits
	 * 5. Call to MQKPInstance.getDeltaSumProfits to know how the sum of profits is going to change if the
	 *    operation is performed.
	 * 6. Sum the two previous quantities to obtain the sum of profits if the operation is performed.
	 *
	 * Finally
	 * - If current and new violations are positive, return the negative of deltaMaxCapacityViolation
	 * - If both violations are 0, return deltaSumProfits
	 * - If only current violation is positive and the new one is 0, return the sum of newSumProfits
	 *   plus the negative of deltaMaxCapacityViolation
	 * - If only the new violation is positive, return the negative of
	 *    (the sum of current profits + the new violation of capacities)
	 */
	double actualMaxViolation = instance.getMaxCapacityViolation(solution);
	double deltaMaxCapacityViolation = instance.getDeltaMaxCapacityViolation(solution, indexObject, indexKnapsack);
	double newMaxViolation = actualMaxViolation + deltaMaxCapacityViolation;
	double actualSumProfits = instance.getSumProfits(solution);
	double deltaSumProfits = instance.getDeltaSumProfits(solution, indexObject, indexKnapsack);
	double newSumProfits = actualSumProfits + deltaSumProfits;

	if (actualMaxViolation > 0 && newMaxViolation > 0){
		return (-1.) * deltaMaxCapacityViolation;
	} else if (actualMaxViolation <= 0 && newMaxViolation <= 0){
		return deltaSumProfits;
	} else if (actualMaxViolation > 0){
		return (newSumProfits - deltaMaxCapacityViolation);
	} else {
		return (-1.) * (actualSumProfits + newMaxViolation);
	}
}

void MQKPEvaluator::resetNumEvaluations() {
	_numEvaluations = 0;
}
