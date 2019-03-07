/**
 * MQKPNeighExplorer.h
 *
 * File defining the class MQKPNeighExplorer.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_MQKPNEIGHEXPLORER_H_
#define INCLUDE_MQKPNEIGHEXPLORER_H_

#include <MQKPSolution.h>
#include <MQKPInstance.h>
#include <MQKPChangeOperation.h>

/**
 * Abstract class defining the operation of any operator which explores the neighbourhood of a given solution
 */
class MQKPNeighExplorer {
public:

	/**
	 * Destructor
	 */
	virtual ~MQKPNeighExplorer(){}

	/**
	 * Function for searching an operation which, applied to the solution, returns other neighbour solution.
	 * It will be used to search one neighbour solution which improves the current solution or to search
	 * the best of all the possible neighbour solutions.
	 *
	 * @param[in] instance Instance of the MQKP
	 * @param[in] solution Reference to an object with a MQKP solution, whose neighbourhood is going to be explored.
	 * @param[out] operation Operator selected after exploring the neighbourhood.
	 *
	 * @return It returns true if a valid operation is found, improving the current solution. False in the opposite case.
	 */
	virtual bool findOperation(MQKPInstance &instance, MQKPSolution &solution, MQKPChangeOperation &operation) = 0;
};



#endif /* INCLUDE_MQKPNEIGHEXPLORER_H_ */
