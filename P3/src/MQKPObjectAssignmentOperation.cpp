/*
 * MQKPObjectAssignmentOperation.cpp
 *
 * File defining the methods of the class MQKPObjectAssignmentOperation.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <MQKPObjectAssignmentOperation.h>

MQKPObjectAssignmentOperation::MQKPObjectAssignmentOperation(){
	_indexKnapsack = 0;
	_indexObj = 0;
	_deltaFitness = 0;
}

MQKPObjectAssignmentOperation::~MQKPObjectAssignmentOperation() {
}

void MQKPObjectAssignmentOperation::apply(MQKPSolution& solution) {
	/* 1. Assign the index _indexObj to the knapsack _indexKnapsack in solution
	 * 2. Update the fitness of the solution increasing it by _deltaFitness
	 */
	solution.putObjectIn(_indexObj, _indexKnapsack);
	double actualFitness = solution.getFitness();
	double newFitness = actualFitness + _deltaFitness;
	solution.setFitness(newFitness);
}

void MQKPObjectAssignmentOperation::setValues(int indexObject,
		int indexKnapsack, double deltaFitness) {
	/* Store the values passed as an argument in the properties of the class */
	_indexKnapsack = indexKnapsack;
	_indexObj = indexObject;
	_deltaFitness = deltaFitness;
}
