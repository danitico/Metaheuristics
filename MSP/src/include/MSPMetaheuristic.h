/*
 * MSPMetaheuristic.h
 *
 *  Created on: May 12, 2019
 *
 */

#ifndef INCLUDE_MSPMETAHEURISTIC_H_
#define INCLUDE_MSPMETAHEURISTIC_H_

#include <MSPSolution.h>
#include <MSPStopCondition.h>
#include <cstdlib>

/**
 * Abstract class defining the common methods for metaheuristics for the MSP
 */
class MSPMetaheuristic {

protected:
	MSPSolution *_bestSolution;

public:
	/**
	 * Constructor
	 */
	MSPMetaheuristic(){
		_bestSolution = NULL;
	}

	/**
	 * Destructor
	 */
	virtual ~MSPMetaheuristic(){

		if (_bestSolution != NULL){
			delete _bestSolution;
			_bestSolution = NULL;
		}
	};

	/**
	 * Function which runs the metaheuristic until reaching the stop condition
	 * @param[in] stopCondition Stop condition of the metaheuristic
	 */
	virtual void run (MSPStopCondition &stopCondition) = 0;


	/**
	 * Function which returns the best solution found up to the moment.
	 * It is the responsability of each metaheuristic to keep udpate the
	 * property _bestSolution
	 * @return Best solution found up the moment
	 */
	MSPSolution*& getBestSolution(){
		return _bestSolution;
	}
};



#endif /* INCLUDE_MSPMETAHEURISTIC_H_ */
