/**
 * MQKPStopCondition.h
 *
 * File defining the class MQKPStopCondition.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
*/

#ifndef INCLUDE_MQKPSTOPCONDITION_H_
#define INCLUDE_MQKPSTOPCONDITION_H_

#include "MQKPEvaluator.h"
#include <Timer.h>

/**
 * Class defining some stop conditions common in the metaheuristics and informs about the neccesity
 * of stopping the metaheuristic when some conditions are met
 */
class MQKPStopCondition{
	/**
	 * Properties of the class
	 * _maxEvaluations unsigned Maximum number of evaluations of solutions
	 * _maxIterations unsigned Maximum number of iterations of the metaheuristic
	 * _maxTime double indicating the maximum running time of the metaheuristic, measured in seconds
	 * _numIterations unsigned It counts the number of iterations considered
	 * _time Object of the Timer class which counts the running seconds of the metaheuristic
	 */
	unsigned _maxEvaluations;
	unsigned _maxIterations;
	double _maxTime;
	unsigned _numIterations;
	Timer _time;

public:
	/**
	 * Constructor
	 */
	MQKPStopCondition(){
		_maxEvaluations = 0;
		_maxIterations = 0;
		_maxTime = 0;
		_numIterations = 0;
		_time.reset(); //Reset the variable _time calling to the proper method
	}

	/**
	 * Destructor
	 */
	virtual ~MQKPStopCondition(){};

	virtual bool reached(){
		bool result = false;

		if (_maxEvaluations > 0 && MQKPEvaluator::getNumEvaluations() >= _maxEvaluations)
			result = true;

		if (_maxIterations > 0 && _numIterations >= _maxIterations)
			result = true;

		if (_maxTime > 0 && _time.elapsed_time(Timer::VIRTUAL) >= _maxTime)
			result = true;

		return result;
	}

	/**
	 * Function which initializes the properties
	 * @param[in] maxEvaluations Maximum number of evaluations of solutions
	 * @param[in] maxIterations Maximum number of iterations of the metaheuristic
	 * @param[in] maxTime Maximum running time of the metaheuristic, measured in seconds
	 */
	void setConditions(unsigned maxEvaluations, unsigned maxIterations, double maxTime){
		_maxEvaluations = maxEvaluations;
		_maxIterations = maxIterations;
		_maxTime = maxTime;
		_time.reset(); //Reset the variable _time calling to the proper method
	}

	unsigned int getIterarions(){
		return _numIterations;
	}

	/**
	 * Function which notifies the stop condition object about the execution of a new
	 * iteration of the metaheuristic
	 */
	void notifyIteration(){
		_numIterations++;
	}
};



#endif /* INCLUDE_MQKPSTOPCONDITION_H_ */
