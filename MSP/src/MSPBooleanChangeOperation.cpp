/*
 * MSPBooleanChangeOperation.cpp
 *
 *  Created on: 15 may. 2019
 *      Author: chema969
 */

#include <MSPBooleanChangeOperation.h>

MSPBooleanChangeOperation::MSPBooleanChangeOperation() {
	_indexLiteral = 0;
	_deltaFitness = 0;

}

MSPBooleanChangeOperation::~MSPBooleanChangeOperation() {
	// TODO Auto-generated destructor stub
}

void MSPBooleanChangeOperation::apply(MSPSolution& solution) {
	/* 1. Assign the index _indexObj to the knapsack _indexKnapsack in solution
	 * 2. Update the fitness of the solution increasing it by _deltaFitness
	 */
	solution.setBool(_indexLiteral, !solution.isTrue(_indexLiteral));
	double actualFitness = solution.getFitness();
	double newFitness = actualFitness + _deltaFitness;
	solution.setFitness(newFitness);
}

void MSPBooleanChangeOperation::setValues(int indexLiteral, double deltaFitness) {
	/* Store the values passed as an argument in the properties of the class */
	_indexLiteral = indexLiteral;
	_deltaFitness = deltaFitness;
}
