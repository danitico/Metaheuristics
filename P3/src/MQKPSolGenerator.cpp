/*
 * MQKPSolGenerator.cpp
 *
 * File defining the methods of the class MQKPSolGenerator.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#include "MQKPSolGenerator.h"
#include "MQKPInstance.h"
#include "MQKPSolution.h"
#include <stdlib.h>

void MQKPSolGenerator::genRandomSol(MQKPInstance &instance, MQKPSolution &solution){

	int numObjs = instance.getNumObjs();
	int numKnapsacks = instance.getNumKnapsacks();

	for (int i = 0; i < numObjs; i++){
		int randomKnapsack = rand() % (numKnapsacks + 1);
		solution.putObjectIn(i, randomKnapsack);
	}
}

