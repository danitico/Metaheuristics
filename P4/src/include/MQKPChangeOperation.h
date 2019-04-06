/**
 * MQKPChangeOperation.h
 *
 * File defining the class MQKPChangeOperation.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
*/

#ifndef __MQKPCHANGEOPERATION_H__
#define __MQKPCHANGEOPERATION_H__

#include <MQKPSolution.h>

/**
 * Abstract class for representing any operation modifying a solution
 */
class MQKPChangeOperation{
public:

	/**
	 * Destructor
	 */
	virtual ~MQKPChangeOperation(){
	}

	/**
	 * Function applying the change defined by the object over the solution received
	 * as a parameter.
	 * @param[in,out] solution Solution objection over which the change will be applied
	 */
	virtual void apply(MQKPSolution &solution) = 0;
};

#endif
