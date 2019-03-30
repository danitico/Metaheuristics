/*
 * MSPRandomSolution.h
 *
 *  Created on: 30 mar. 2019
 *      Author: chema969
 */

#ifndef MSPRANDOMSOLUTION_H_
#define MSPRANDOMSOLUTION_H_

#include "MSPInstance.h"
#include "MSPSolution.h"
class MSPRandomSolution {
public:
	MSPRandomSolution();
	virtual ~MSPRandomSolution();
	static void genRandomSol(MSPInstance &instance, MSPSolution &solution);

};

#endif /* MSPRANDOMSOLUTION_H_ */
