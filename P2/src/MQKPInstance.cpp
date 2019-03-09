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
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

MQKPInstance::MQKPInstance() {
	// initializing the properties
	_numKnapsacks = 0;
	_numObjs = 0;
	this->_capacities = NULL;
	this->_profits = NULL;
	this->_weights = NULL;
}

MQKPInstance::~MQKPInstance() {
	//
	int i;
	for (i = 0; i < getNumObjs(); i++) {
		delete[] _profits[i];
	}
	delete[] _profits;
	delete[] _weights;
	delete[] _capacities;
	_numKnapsacks = _numObjs = 0;
}

double MQKPInstance::getMaxCapacityViolation(MQKPSolution &solution) {

	double *sumWeights = new double[this->_numKnapsacks + 1];

	for (int j = 1; j <= this->_numKnapsacks; j++) {
		sumWeights[j] = 0;
	}

	for (int i = 0; i < this->_numObjs; i++) {

		/*
		 * 1. Obtain the knapsack where we can find the i-th object.
		 * 2. If it is a valid knapsack (higher than 0), increment sumWeights by the weight of the object.
		 */
		if (solution.whereIsObject(i) > 0) {
			sumWeights[solution.whereIsObject(i)] =
					sumWeights[solution.whereIsObject(i)] + getWeight(i);

		}
	}

	double maxCapacityViolation = 0; //We initialize maximum violation to 0, meaning that there are no violations.

	for (int j = 1; j <= this->_numKnapsacks; j++) {

		/*
		 * 1. Obtain the violation for the j-th knapsack
		 * 2. Update maxCapacityViolation if needed
		 */
		if ((sumWeights[j] - getCapacity(j)) > maxCapacityViolation) {
			maxCapacityViolation = sumWeights[j] - getCapacity(j);
		}
	}

	delete[] sumWeights;
	return maxCapacityViolation;
}

double MQKPInstance::getSumProfits(MQKPSolution &solution) {

	double sumProfits = 0.;

	/*
	 * Double loop for each pair of objects
	 * object included in any knapsack (> 0) must sum its individual profit.
	 * pair of objects included in the same knapsack (and with value > 0) must sum its shared profit.
	 * IMPORTANT NOTE, sum the pair (i,j) only once, that is, if you sum (i, j), you should not sum (j, i)
	 */
	int i, j;
	for(i=0; i<getNumObjs(); i++)
	{
		if (solution.whereIsObject(i) > 0)
		{
			sumProfits = sumProfits + getProfit(i);
			for (j=i+1; j < getNumObjs(); j++)
			{
				if(solution.whereIsObject(i) == solution.whereIsObject(j))
				{
					sumProfits = sumProfits + getProfit(i,j);
				}
			}
		}
	}

	return sumProfits;
}

void MQKPInstance::readInstance(char *filename, int numKnapsacks) {

	/*
	 *   1. read the number of objects
	 *   2. allocate matrix and vector memory
	 *   3. read profits and object weights, according to what has been previously discussed
	 *   4. Obtain the capacities of the knapsacks:
	 *      . Sum all the object weights
	 *      . Multiply by 0.8
	 *      . Divide the previous results by the number of knapsacks. This will be the capacity of each knapsack
	 */
	_numKnapsacks = numKnapsacks;

	ifstream fe;
	fe.open(filename,ifstream::in);
	if(!fe){
		cerr << "Error when opening the file: " << filename << endl;
		exit(-1);
	}
	string trush;
	fe >> trush;
	fe >> _numObjs;

	_profits = new double * [getNumObjs()];
	if(!_profits)
	{
		cerr << "Error when allocating memory for profits" << endl;
		exit(-1);
	}
	int i;
	for(i=0; i<getNumObjs(); i++){
		_profits[i] = new double[getNumObjs()];
		if(!_profits[i])
		{
			cerr << "Error when allocating memory for profits [i]" << endl;
			exit(-1);
		}
	}

	for(i=0; i<getNumObjs(); i++)
	{
		fe >> _profits[i][i];
	}
	int j;
	for(i=0; i<getNumObjs(); i++)
	{
		for (j=i+1; j<getNumObjs(); j++)
		{
			fe >> _profits[i][j];
			_profits[j][i] = _profits[i][j];
		}
	}

	fe >> trush;
	fe >> trush;

	_weights = new double[getNumObjs()];
	if(!_weights)
	{
		cout << "Error when allocating memory for weights" << endl;
		exit(-1);
	}

	double suma=0;

	for(i=0; i<getNumObjs(); i++)
	{
		fe >> _weights[i];
		suma = suma + _weights[i];
	}

	_capacities = new double[getNumKnapsacks()+1];
	if(!_capacities)
	{
		cout << "Error when allocating memory for capacities" << endl;
		exit(-1);
	}

	double capacity = suma * 0.8 / getNumKnapsacks();
	for(i=1; i<=getNumKnapsacks(); i++)
	{
		_capacities[i] = capacity;
	}
	fe.close();
}

int MQKPInstance::getNumObjs() {
	return _numObjs;
}

int MQKPInstance::getNumKnapsacks() {
	return _numKnapsacks;
}

double MQKPInstance::getWeight(int object) {
	return _weights[object];
}

double MQKPInstance::getCapacity(int knapsack){
	return _capacities[knapsack];
}

double MQKPInstance::getProfit(int object){
	return _profits[object][object];
}

double MQKPInstance::getProfit(int o1, int o2){
	return _profits[o1][o2];
}

void MQKPInstance::randomPermutation(int size, vector<int>& perm) {
	/*
	 * clear the vector,
	 * fill it with the initial indices and interchange them
	 */
	perm.clear();
	for( int i=0;i<size;i++)
		{
		perm[i]=i;
		}
	for( int i=0;i<size;i++)
		{
			int num = rand()%(size-1);
			int tmp= perm[i];
			perm[i]=perm[num];
			perm[num]=tmp;
		}
	return;

}

double MQKPInstance::getDeltaSumProfits(MQKPSolution& solution, int indexObject,
		int indexKnapsack) {

	double deltaSumProfits = 0;
	int oldKnapsack=solution.whereIsObject(indexObject);
	if(oldKnapsack!=0){
		deltaSumProfits-=this->getProfit(indexObject);
		for(int i=0;i<this->getNumObjs();i++){
			if( (i!=indexObject)  &&  (oldKnapsack==solution.whereIsObject(i)) ){
				deltaSumProfits-=this->getProfit(i,indexObject);
			}
		}
	}
	/*
	 * If the object was in a knapsack, substract its individual profit from deltaSumProfits and
	 * substract the profit shared with any other object allocated in the same knapsack
	 */
	if(indexKnapsack!=0){
		deltaSumProfits+=this->getProfit(indexObject);
		for(int i=0; i<this->getNumObjs(); i++){
			if( (i!=indexObject)  &&  (indexKnapsack==solution.whereIsObject(i)) ){
				deltaSumProfits+=this->getProfit(i,indexObject);
			}
		}
	}

	/*
	 * If the object is going to be included in a knapsack, sum its individual profit to
	 * deltaSumProfits and also sum the profit shared with any other object in the same knapsack
	 */

	return deltaSumProfits;
}

double MQKPInstance::getDeltaMaxCapacityViolation(MQKPSolution& solution,
		int indexObject, int indexKnapsack) {
	/*
	 * find the knapsack where the object currently is
	 */
	int knapsack=solution.whereIsObject(indexObject);
	/*
	 * calculate the current capacity violation
	 */
	double curMaxCapacityViolation=this->getMaxCapacityViolation(solution);
	/*
	 * put the object into a given knapsack
	 */
	solution.putObjectIn(indexObject,indexKnapsack);
	/*
		 * calculate the new capacity violation
		 */
	double newMaxCapacityViolation=this->getMaxCapacityViolation(solution);
	/*
	 * return to the original solution
	 */
	solution.putObjectIn(indexObject,knapsack);
	/*
	 * calculate the difference between the current and the new solution
	 */
	double deltaMaxCapacityViolation=newMaxCapacityViolation - curMaxCapacityViolation;
	return deltaMaxCapacityViolation;

}
