/*
 * MQKPSolution.cpp
 *
 * File defining the methods of the class MQKPSolution.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#include "MQKPSolution.h"
#include "MQKPInstance.h"

MQKPSolution::MQKPSolution(MQKPInstance &instance) {
	_numObjs = instance.getNumObjs();
	_sol.resize(_numObjs, 0);
	_fitness = 0.0;
	//Complete initializing the properties. Initially, all the objects are out of any knapsack (=0)
}

MQKPSolution::~MQKPSolution() {
	_sol.resize(0);
	//complete
}

void MQKPSolution::putObjectIn(int object, int knapsack){
	_sol[object] = knapsack;
	//complete the function
}

int MQKPSolution::whereIsObject(int object){
	return _sol[object];
	//complete the function
}

