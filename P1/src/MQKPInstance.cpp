/*
 * MQKPInstance.cpp
 *
 * File defining the methods of the class MQKPInstance.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#include "MQKPInstance.h"
#include "MQKPSolution.h"

MQKPInstance::MQKPInstance() {
	//TODO complete initializing the properties
}

MQKPInstance::~MQKPInstance() {
	//TODO complete
}

double MQKPInstance::getMaxCapacityViolation(MQKPSolution &solution) {

	double *sumWeights = new double[this->_numKnapsacks + 1];

	for (int j = 1; j <= this->_numKnapsacks; j++) {
		sumWeights[j] = 0;
	}

	for (int i = 0; i < this->_numObjs; i++) {

		/*TODO Complete
		 * 1. Obtain the knapsack where we can find the i-th object.
		 * 2. If it is a valid knapsack (higher than 0), increment sumWeights by the weight of the object.
		 */
	}

	double maxCapacityViolation = 0; //We initialize maximum violation to 0, meaning that there are no violations.

	for (int j = 1; j <= this->_numKnapsacks; j++) {

		/*TODO Complete
		 * 1. Obtain the violation for the j-th knapsack
		 * 2. Update maxCapacityViolation if needed
		 */
	}

	delete[] sumWeights;
	return maxCapacityViolation;
}

double MQKPInstance::getSumProfits(MQKPSolution &solution) {

	double sumProfits = 0.;

	/*TODO Complete
	 * Double loop for each pair of objects
	 * Todo object included in any knapsack (> 0) must sum its individual profit.
	 * Todo pair of objects included in the same knapsack (and with value > 0) must sum its shared profit.
	 *      IMPORTANT NOTE, sum the pair (i,j) only once, that is, if you sum (i, j), you should not sum (j, i)
	 */

	return sumProfits;
}

void MQKPInstance::readInstance(char *filename, int numKnapsacks) {

	/*
	 * TODO Complete this function:
	 *   1. read the number of objects
	 *   2. allocate matrix and vector memory
	 *   3. read profits and object weights, according to what has been previously discussed
	 *   4. Obtain the capacities of the knapsacks:
	 *      . Sum all the object weights
	 *      . Multiply by 0.8
	 *      . Divide the previous results by the number of knapsacks. This will be the capacity of each knapsack
	 */
}
