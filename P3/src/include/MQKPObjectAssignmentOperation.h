/**
 * MQKPObjectAssignmentOperation.h
 *
 * File defining the class MQKPObjectAssignmentOperation.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef __MQKPOBJECTASSIGNMENTOPERATION_H__
#define __MQKPOBJECTASSIGNMENTOPERATION_H__

#include <MQKPChangeOperation.h>
#include <MQKPSolution.h>

/**
 * Class that codifies an operation of assigning an object to a knapsack.
 * The knapsack can be 0, that is, the object is removed from the knapsack
 * in which it is currently stored.
 */
class MQKPObjectAssignmentOperation : public MQKPChangeOperation {

protected:
	/*
	 * Properties of this class, according to the indications in the
	 * lab assignment (_indexObj, _indexKnapsack, _deltaFitness)
	 */
	int _indexObj;
	int _indexKnapsack;
	double _deltaFitness;

public:

	/**
	 * Constructor
	 */
	MQKPObjectAssignmentOperation();

	/**
	 * Destructor
	 */
	virtual ~MQKPObjectAssignmentOperation();

	/**
	 * Function which applies the change defined by this object to the solution
	 * received as an argument
	 * @param[in, out] solution Solution over which the change will be applied
	 */
	virtual void apply(MQKPSolution &solution);

	/**
	 * Function for assigning the values of the operation
	 * @param[in] indexObject Index of the object which is going to be changed
	 * @param[in] indexKnapsack Index of the knapsack where the object will be introduced.
	 * @param[in] deltaFitness Difference in fitness of the solution after applying the change,
	 *                         provided that the solution has not changed since the object
	 *                         of this class was created
	 */
	void setValues(int indexObject, int indexKnapsack, double deltaFitness);

	/**
	 * Function which returns the object considered by the operation
	 * @return Index of the object considered by the operation
	 */
	unsigned getObj(){
		return _indexObj;
	}

	/**
	 * Function which returns the difference of fitness by the operation
	 * @return Difference of fitness of the operation (if the current solution has not changed
	 *         when the difference was calculated)
	 */
	double getDeltaFitness(){
		return _deltaFitness;
	}

	/**
	 * Function returning the knapsack considered by the operation
	 * @return Index of the knapsack considered by the operation
	 */
	unsigned getKnapsack(){
		return _indexKnapsack;
	}
};

#endif
