/*
 * MSPChangeOperation.h
 *
 *  Created on: 30 mar. 2019
 *      Author: chema969
 */

#ifndef MSPCHANGEOPERATION_H_
#define MSPCHANGEOPERATION_H_
#include "MSPSolution.h"
class MSPChangeOperation {
private:
	double _deltaFitness ;
	int 	_indexObj ;

public:
	MSPChangeOperation();
	virtual ~MSPChangeOperation();
	void apply(MSPSolution &solution);
};

#endif /* MSPCHANGEOPERATION_H_ */
