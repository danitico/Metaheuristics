/**
 * MQKPSimpleBestImprovementNO.h
 *
 * File defining the class MQKPSimpleBestImprovementNO.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_MQKPSIMPLEBESTIMPROVEMENTNO_H_
#define INCLUDE_MQKPSIMPLEBESTIMPROVEMENTNO_H_

#include <MQKPNeighExplorer.h>
#include <MQKPSolution.h>
#include <MQKPChangeOperation.h>
/**
 * Class which explores the neighbourhood of a given solution, returning the best assignment operation of an
 * object to a knapsack from all possible assignments. It returns FALSE if the assignment found does not
 * improve current solution.
 */
class MQKPSimpleBestImprovementNO : public MQKPNeighExplorer{

public:

	/**
	 * Destructor
	 */
	virtual ~MQKPSimpleBestImprovementNO(){

	}

	/**
	 * Function exploring the neighbourhood of a given solution, returning the best assignment operation of an object
	 * to a knapsack from all possible assignments. It returns FALSE if the assignment found does not
	 * improve current solution.
	 * @param[in] instance Instance of the problem
	 * @param[in] solution Solution whose neighbourhood is going to be explored
	 * @param[out] operation Operation which, after being applied to the solution, obtains the maximum improvement.
	 *
	 * @return true if the operation improves the solution; false, if there is no operation which improves the solution
	 */
	virtual bool findOperation(MQKPInstance &instance, MQKPSolution &solution, MQKPChangeOperation &operation);

};


#endif /* INCLUDE_MQKPSIMPLEBESTIMPROVEMENTNO_H_ */
