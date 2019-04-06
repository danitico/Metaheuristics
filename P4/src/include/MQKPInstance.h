/**
 * MQKPInstance.h
 * 
 * File defining the class MQKPInstance.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef __MQKPINSTANCE_H__
#define __MQKPINSTANCE_H__

#ifndef __MQKPSOLUTION_H__
#include "MQKPSolution.h"
#else
class MQKPSolution;
#endif

#include <vector>
using namespace std;

/**
 * Class for storing the information of an instance of the problem MQKP
 */
class MQKPInstance {
protected:
	/*Properties of the class:
	 * _numKnapsacks Integer with number of knapsacks to consider. This is not read from the file, but established by the user.
	 * _numObjs Integer with the number of objects of the problem.
	 * _profits Matrix where the profits of the objects are stored. YOU HAVE TO ALLOCATE ITS MEMORY.
	 * _weights Vector with the weights of the objects. YOU HAVE TO ALLOCATE ITS MEMORY.
	 * _capacities Vector with the capacities of the knapsacks. YOU HAVE TO ALLOCATE ITS MEMORY. To avoid problems, store the vector
	 *             for (1 + numKnapsacks) elements and use the indices from index 1
	 */
	int _numKnapsacks;
	int _numObjs;
	double ** _profits;
	double * _weights;
	double * _capacities;

public:
	/**
	 * Default constructor
	 */
	MQKPInstance();

	/**
	 * Destructor
	 */
	~MQKPInstance();

	/**
	 * Function for reading an input file.
	 * @param[in] filename Name of the file where the data of the instance can be found.
	 * @param[in] numKnapsacks Integer with the number of knapsacks to be considered. This is not read from the file,
	 *                         but established by the user.
	 */
	void readInstance(char *filename, int numKnapsacks);

	/**
	 * Getter function for obtaining information about the instance of the MQKP
	 */
	int getNumObjs();
	int getNumKnapsacks();
	double getWeight(int object);
	double getCapacity(int knapsack);
	double getProfit(int object);
	double getProfit(int o1, int o2);

	/**
	 * Function returning how much the capacity constraint is is violated for the most over-weighted knapsack.
	 * @param[in] solution Reference to an object representing a solution to the problem.
	 * @return Maximum violation of the knapsack capacities.
	 */
	double getMaxCapacityViolation(MQKPSolution &solution);

	/**
	 * Function obtaining the sum of the individual and shared profits of the objects in the knapsacks.
	 * @param[in] solution Reference to an object representing a solution to the problem.
	 * @return Sum of the individual and shared profits of the objects in the knapsacks.
	 */
	double getSumProfits(MQKPSolution &solution);

	/**
	 * Function for generating a random permutation of integer values from 0 to (size-1) (where size is an argument of this function).
	 * @param[in] size Size of the permutation
	 * @param[out] perm Output vector where the permutation will be stored
	 */
	static void randomPermutation(int size, vector<int> &perm);

	/**
	 * Function for obtaining the difference of the sum of profits if the object indexObject to the knapsack indexKnapsack
	 * @param[in] solution Reference to an object with a MQKP solution.
	 * @param[in] indexObject Index of the object which would be included in other knapsack
	 * @param[in] indexKnapsack Index of the knapsack in which the object would be included.
	 *                          It can be 0 (the object is taken out from the current knapsack and
	 *                          not included in any other one
	 *
	 * @return Difference of sum of profits after including the object indexObject in the knapsack indexKnapsack
	 */
	double getDeltaSumProfits(MQKPSolution &solution, int indexObject, int indexKnapsack);

	/**
	 * Function for obtaining the difference in maximum violation of any knapsack capacity when, for a given solution,
	 * the object indexObject is assigned to the knapsack indexKnapsack
	 * @param[in] solution Reference to an object with a MQKP solution.
	 * @param[in] indexObject Index of the object which would be included in other knapsack
	 * @param[in] indexKnapsack Index of the knapsack in which the object would be included.
	 *                          It can be 0 (the object is taken out from the current knapsack and
	 *                          not included in any other one
	 *
	 * @return Difference of maximum capacity violation after including the object indexObject in the knapsack indexKnapsack
	 */
	double getDeltaMaxCapacityViolation(MQKPSolution &solution, int indexObject, int indexKnapsack);
};

#endif

