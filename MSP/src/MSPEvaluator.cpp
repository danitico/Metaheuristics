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

	_numEvaluations += (1. / instance.getNumberOfLiterals());

	return instance.getDeltaFitness(solution, position);
}

void MSPEvaluator::resetNumEvaluations() {
	_numEvaluations = 0;
}
