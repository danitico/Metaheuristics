/**
 * MQKPMetaheuristic.h
 *
 * File defining the class MQKPMetaheuristic.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
*/

#ifndef INCLUDE_MQKPMETAHEURISTIC_H_
#define INCLUDE_MQKPMETAHEURISTIC_H_

#include <MQKPSolution.h>
#include <MQKPStopCondition.h>
#include <cstdlib>

/**
 * Abstract class defining the common methods for metaheuristics for the MQKP.
 */
class MQKPMetaheuristic {

protected:
	MQKPSolution *_bestSolution;

public:
	/**
	 * Constructor
	 */
	MQKPMetaheuristic(){
		_bestSolution = NULL;
	}

	/**
	 * Destructor
	 */
	virtual ~MQKPMetaheuristic(){

		if (_bestSolution != NULL){
			delete _bestSolution;
			_bestSolution = NULL;
		}
	};

	/**
	 * Function which runs the metaheuristic until reaching the stop condition
	 * @param[in] stopCondition Stop condition of the metaheuristic
	 */
	virtual void run (MQKPStopCondition &stopCondition) = 0;


	/**
	 * Function which returns the best solution found up to the moment.
	 * It is the responsability of each metaheuristic to keep udpate the
	 * property _bestSolution
	 * @return Best solution found up the moment
	 */
	MQKPSolution*& getBestSolution(){
		return _bestSolution;
	}
};



#endif /* INCLUDE_MQKPMETAHEURISTIC_H_ */
