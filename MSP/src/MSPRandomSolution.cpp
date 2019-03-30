/*
 * MSPRandomSolution.cpp
 *
 *  Created on: 30 mar. 2019
 *      Author: chema969
 */

#include "MSPRandomSolution.h"


void MSPRandomSolution::genRandomSol(MSPInstance &instance, MSPSolution &solution){
    int numLiterals=instance.getNumberOfLiterals();
	for (int i = 1; i < numLiterals+1; i++){
		bool randomSolution = (rand() % 2)==0;
		solution.setBool(i,randomSolution);
	}
}
