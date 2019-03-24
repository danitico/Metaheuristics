/**
 * MQKPSolution.h
 * 
 * File defining the class MQKPSolution.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef __MQKPSOLUTION_H__
#define __MQKPSOLUTION_H__

#ifndef __MQKPINSTANCE_H__
#include "MQKPInstance.h"
#else
class MQKPInstance;
#endif

/**
 * Class representing a solution of the problem.
 *
 * About the encoding:
 * The representation will be a vector of integer values: from 1 to M for the objects which are allocated
 * in one of the M knapsacks and 0 for those non included in any knapsack.
 */
class MQKPSolution {
protected:
	/*Properties of the class
	 * _sol Integer vector, which will be the internal representation of the solution.
	 * _numObjs Integer with the number of objects of the problem.
	 * _fitness double value with quality of the solution.
	 */
	int * _sol;
	int _numObjs;
	double _fitness;

public:
	/**
	 * Constructor
	 * @param[in] instance Reference to an object with the information of the MQKP instance.
	 */
	MQKPSolution(MQKPInstance &instance);

	/**
	 * Destructor
	 */
	~MQKPSolution();

	/**
	 * Function which assigns and object to the specified knapsack
	 * @param[in] object Index of the object to include in the specified knapsack
	 * @param[in] knapsack Index of the knapsack where the object is going to be included
	 */
	void putObjectIn(int object, int knapsack);

	/**
	 * Function returning the knapsack where an object is included
	 * @param[in] object Index of the object to be consulted
	 * @return Index of the knapsack where the object is included
	 */
	int whereIsObject(int object);

	/**
	 * Function for obtaining the fitness of the solution
	 *
	 * @return fitness of the solution
	 */
	double getFitness() const;

	/**
	 * Function for assigning the fitness of the solution
	 * @param[in] fitness New fitness
	 */
	void setFitness(double fitness);

	/**
	 * Function for copying the information of the solution from another
	 * @param[in] solution Solution from which the information is taken
	 */
	void copy(MQKPSolution &solution);
};

#endif
