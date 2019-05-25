/*
 * MSPBooleanChangeOperation.h
 *
 *  Created on: 15 may. 2019
 *      Author: chema969
 */

#ifndef INCLUDE_MSPBOOLEANCHANGEOPERATION_H_
#define INCLUDE_MSPBOOLEANCHANGEOPERATION_H_
#include <MSPChangeOperation.h>
#include <MSPSolution.h>
class MSPBooleanChangeOperation: public MSPChangeOperation{
	protected:
	/*
	 * Properties of this class
	 */
	int _indexLiteral;
	double _deltaFitness;
public:
	MSPBooleanChangeOperation();
	virtual ~MSPBooleanChangeOperation();
	/**
	 * Function which applies the change defined by this object to the solution
	 * received as an argument
	 * @param[in, out] solution Solution over which the change will be applied
	 */
	virtual void apply(MSPSolution &solution);

	/**
	 * Function for assigning the values of the operation
	 * @param[in] indexLiteral Index of the literal which is going to be changed.
	 * @param[in] deltaFitness Difference in fitness of the solution after applying the change,
	 *                         provided that the solution has not changed since the object
	 *                         of this class was created
	 */
	virtual void setValues(int indexLiteral, double deltaFitness);

	/**
	 * Function which returns the object considered by the operation
	 * @return Index of the object considered by the operation
	 */
	unsigned getLiteral(){
		return _indexLiteral;
	}

	/**
	 * Function which returns the difference of fitness by the operation
	 * @return Difference of fitness of the operation (if the current solution has not changed
	 *         when the difference was calculated)
	 */
	double getDeltaFitness(){
		return _deltaFitness;
	}

};

#endif /* INCLUDE_MSPBOOLEANCHANGEOPERATION_H_ */
