/*
 * MSPEvaluator.cpp
 *
 *  Created on: May 13, 2019
 *      Author:
 */

#include <MSPEvaluator.h>
#include <MSPInstance.h>
#include <MSPSolution.h>

double MSPEvaluator::_numEvaluations = 0.;

double MSPEvaluator::computeFitness(MSPInstance &instance, MSPSolution &solution){
	_numEvaluations++;
	return instance.computeFitness(solution);
}

double MSPEvaluator::computeDeltaFitness(MSPInstance& instance,
		MSPSolution& solution, int position) {

	_numEvaluations += (1. / instance.getNumberOfLiterals());//TODO Preguntar sobre esto

	double actualSumProfits = instance.computeFitness(solution);
	double deltaSumProfits = instance.getDeltaFitness(solution, position);
	double newSumProfits = actualSumProfits + deltaSumProfits;

	//TODO Preguntar :3
//	if (actualMaxViolation > 0 && newMaxViolation > 0){
//		return (-1.) * deltaMaxCapacityViolation;
//	} else if (actualMaxViolation <= 0 && newMaxViolation <= 0){
//		return deltaSumProfits;
//	} else if (actualMaxViolation > 0){
//		return (newSumProfits - deltaMaxCapacityViolation);
//	} else {
//		return (-1.) * (actualSumProfits + newMaxViolation);
//	}
	return 0.;
}

void MSPEvaluator::resetNumEvaluations() {
	_numEvaluations = 0;
}



