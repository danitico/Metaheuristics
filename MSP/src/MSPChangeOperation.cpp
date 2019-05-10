/*
 * MSPChangeOperation.cpp
 *
 *  Created on: 30 mar. 2019
 *      Author: chema969
 */

#include <MSPChangeOperation.h>

MSPChangeOperation::MSPChangeOperation() {
	_deltaFitness = 0;
	_indexObj = 0;

}

MSPChangeOperation::~MSPChangeOperation() {
	// TODO Auto-generated destructor stub
}

void MSPChangeOperation::apply(MSPSolution &solution){
	    solution.setBool(_indexObj,!solution.isTrue(_indexObj));
		double actualFitness = solution.getFitness();
		double newFitness = actualFitness + _deltaFitness;
		solution.setFitness(newFitness);
}
