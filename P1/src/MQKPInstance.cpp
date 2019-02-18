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
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>

MQKPInstance::MQKPInstance() {
	_numKnapsacks=0;
	_numObjs=0;
	_profits = new std::vector<std::vector<int> >;
	_profits->resize(0, std::vector<int>(0));

	_capacities = new std::vector<int>;
	_capacities->resize(0, 0);
	_weights = new std::vector<int>;
	_weights->resize(0, 0);
}

MQKPInstance::~MQKPInstance() {
	delete _profits;
	delete _capacities;
	delete _weights;
}

double MQKPInstance::getMaxCapacityViolation(MQKPSolution &solution) {

	double *sumWeights = new double[this->_numKnapsacks + 1];

	for (int j = 1; j <= this->_numKnapsacks; j++) {
		sumWeights[j] = 0;
	}

	for (int i = 0; i < this->_numObjs; i++) {
		int whichknapsack = solution.whereIsObject(i);
		if(whichknapsack > 0){
			sumWeights[whichknapsack] += _weights[0][i];
		}
		/*Complete
		 * 1. Obtain the knapsack where we can find the i-th object.
		 * 2. If it is a valid knapsack (higher than 0), increment sumWeights by the weight of the object.
		 */
	}

	double maxCapacityViolation = 0; //We initialize maximum violation to 0, meaning that there are no violations.

	for (int j = 1; j <= this->_numKnapsacks; j++) {
		if(sumWeights[j] - _capacities[0][j] > maxCapacityViolation){
			maxCapacityViolation = sumWeights[j] - _capacities[0][j];
		}
		/*Complete
		 * 1. Obtain the violation for the j-th knapsack
		 * 2. Update maxCapacityViolation if needed
		 */
	}

	delete[] sumWeights;
	return maxCapacityViolation;
}

double MQKPInstance::getSumProfits(MQKPSolution &solution) {

	double sumProfits = 0.;
	std::vector<std::vector <int> > matrixAux(getNumKnapsacks(), std::vector<int>(0,0));

	for(int i=0; i<getNumObjs(); i++){
		if(solution.whereIsObject(i) > 0){
			matrixAux[solution.whereIsObject(i)].push_back(i);
		}
	}

	for(int j=0; j<getNumKnapsacks(); j++){
		for(unsigned int k=0; k<matrixAux[j].size(); k++){
			sumProfits += this->getElementProfit(k, k);
			for(unsigned int k1=k+1; k1<matrixAux[j].size(); k1++){
				sumProfits += this->getElementProfit(k, k1);
			}
		}
	}

	/* Complete
	 * Double loop for each pair of objects
	 * object included in any knapsack (> 0) must sum its individual profit.
	 * pair of objects included in the same knapsack (and with value > 0) must sum its shared profit.
	 *      IMPORTANT NOTE, sum the pair (i,j) only once, that is, if you sum (i, j), you should not sum (j, i)
	 */

	return sumProfits;
}

void MQKPInstance::readInstance(char *filename, int numKnapsacks) {

	std::ifstream file(filename);
	if(! file.is_open()){
		std::cout << "The file does not exist" << std::endl;
		exit(-1);
	}

	std::string dummie;
	getline(file, dummie, '\n');

	getline(file, dummie, '\n');
	_numObjs = stoi(dummie);

	_profits->resize(getNumObjs(), std::vector<int>(getNumObjs(), 0));
	_weights->resize(getNumObjs());

	for (int i = 0; i < getNumObjs() - 1; ++i) {
		getline(file, dummie, ' ');
		_profits[0][i][i]= stoi(dummie);
	}

	getline(file, dummie, '\n');
	_profits[0][getNumObjs() - 1][getNumObjs() - 1]= stoi(dummie);

	int i, j;
	for(i=0; i<getNumObjs(); i++){
		for(j=i+1; j < getNumObjs(); j++){
			getline(file, dummie, ' ');
			_profits[0][i][j]= _profits[0][j][i] = stoi(dummie);
		}
		getline(file, dummie, '\n');
		_profits[0][i][j]= _profits[0][j][i] = stoi(dummie);
	}

	getline(file, dummie, '\n');
	getline(file, dummie, '\n');
	getline(file, dummie, '\n');

	int k, sumWeights=0;
	for(k=0; k < getNumObjs() - 1; k++){
		getline(file, dummie, ' ');
		sumWeights += (_weights[0][k] = stoi(dummie));

	}
	getline(file, dummie, '\n');
	sumWeights += (_weights[0][k] = stoi(dummie));

	int capacity = (0.8*sumWeights)/numKnapsacks;
	_capacities->resize(numKnapsacks + 1, capacity);

	/*
	 * Complete this function:
	 *   1. read
	 *   the number of objects
	 *   2. allocate matrix and vector getNumObjs() - 1memory
	 *   3. read profits and object weights, according to what has been previously discussed
	 *   4. Obtain the capacities of the knapsacks:
	 *      . Sum all the object weights
	 *      . Multiply by 0.8
	 *      . Divide the previous results by the number of knapsacks. This will be the capacity of each knapsack
	 */
}
