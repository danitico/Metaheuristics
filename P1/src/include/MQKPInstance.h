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

#include <time.h>
#include <stdlib.h>
#include <vector>


/**
 * Class for storing the information of an instance of the problem MQKP
 */
class MQKPInstance {
protected:
	int _numKnapsacks;
	int _numObjs;
	std::vector<std::vector<int> >* _profits;
	std::vector<int>* _weights;
	std::vector<int>* _capacities; //n + 1

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

	inline int getNumKnapsacks(){
		return _numKnapsacks;
	}

	inline int getNumObjs(){
		return _numObjs;
	}

	inline int getElementProfit(int fila, int columna){
		return _profits[0][fila][columna];
	}

	void readInstance(char *filename, int numKnapsacks);

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
};

#endif

