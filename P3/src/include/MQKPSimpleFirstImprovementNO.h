/**
 * MQKPSimpleFirstImprovementNO.h
 *
 * File defining the class MQKPSimpleFirstImprovementNO.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_MQKPSIMPLEFIRSTIMPROVEMENTNO_H_
#define INCLUDE_MQKPSIMPLEFIRSTIMPROVEMENTNO_H_

#include <MQKPNeighExplorer.h>
#include <MQKPSolution.h>
#include <MQKPChangeOperation.h>
/**
 * Class which explores the neighbourhood of a given solution, returning the first assignment operation of an
 * object to a knapsack which improves the current solution. It returns FALSE if there is not assignment
 * improving the solution.
 */
class MQKPSimpleFirstImprovementNO : public MQKPNeighExplorer{

public:

	/**
	 * Destructor
	 */
	virtual ~MQKPSimpleFirstImprovementNO(){

	}

	/**
	 * Function exploring the neighbourhood of a given solution, returning the first assignment operation of an object
	 * to a knapsack which improves the current solution. It returns FALSE if there is not assignment
	 * improving the solution.
	 * @param[in] instance Instance of the problem
	 * @param[in] solution Solution whose neighbourhood is going to be explored
	 * @param[out] operation Operation which, after being applied to the solution, obtains the first improvement.
	 *
	 * @return true if there is an operation which improves the solution; false otherwise
	 */
	virtual bool findOperation(MQKPInstance &instance, MQKPSolution &solution, MQKPChangeOperation &operation);
};


#endif /* INCLUDE_MQKPSIMPLEFIRSTIMPROVEMENTNO_H_ */
