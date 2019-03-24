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
#include <iostream>

using namespace std;

MQKPSolution::MQKPSolution(MQKPInstance &instance) {
	// Initializing the properties. Initially, all the objects are out of any knapsack (=0)
	_numObjs = instance.getNumObjs();
	_fitness = 0;
	_sol = new int[_numObjs];
	if (!_sol) {
		cerr << "Error allocating memory for _sol" << endl;
		exit(-1);
	}
	int i;
	for (i = 0; i < _numObjs; i++) {
		_sol[i] = 0;
	}
}

MQKPSolution::~MQKPSolution() {
	//
	_numObjs = 0;
	_fitness = 0;
	delete [] _sol;
}

void MQKPSolution::putObjectIn(int object, int knapsack) {
	_sol[object] = knapsack;
}

int MQKPSolution::whereIsObject(int object) {
	return _sol[object];
}

double MQKPSolution::getFitness() const {
	return _fitness;
}

void MQKPSolution::setFitness(double fitness) {
	_fitness = fitness;
}

void MQKPSolution::copy(MQKPSolution& solution) {

	/* 1. Copy the assignment of objects to the knapsacks
	 * 2. Copy the fitness
	 */
	for (int i = 0; i < _numObjs; i++)
		_sol[i] = solution._sol[i];

	_fitness = solution._fitness;
}
