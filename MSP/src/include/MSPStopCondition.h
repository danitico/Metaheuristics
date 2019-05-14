#ifndef INCLUDE_MQKPSTOPCONDITION_H_
#define INCLUDE_MQKPSTOPCONDITION_H_


#include <Timer.h>
#include <MSPInstance.h>
#include <MSPEvaluator.h>

class MSPStopCondition{

	unsigned _maxEvaluations;
	unsigned _maxIterations;
	double _maxTime;
	unsigned _numIterations;
	Timer _time;

public:
	/**
	 * Constructor
	 */
	MSPStopCondition(){
		_maxEvaluations = 0;
		_maxIterations = 0;
		_maxTime = 0;
		_numIterations = 0;
		_time.reset(); //Reset the variable _time calling to the proper method
	}


	virtual ~MSPStopCondition(){};

	virtual bool reached(){
		bool result = false;

		if (_maxEvaluations > 0 && MSPEvaluator::getNumEvaluations() >= _maxEvaluations)
			result = true;

		if (_maxIterations > 0 && _numIterations >= _maxIterations)
			result = true;

		if (_maxTime > 0 && _time.elapsed_time(Timer::VIRTUAL) >= _maxTime)
			result = true;

		return result;
	}

	void setConditions(unsigned maxEvaluations, unsigned maxIterations, double maxTime){
		_maxEvaluations = maxEvaluations;
		_maxIterations = maxIterations;
		_maxTime = maxTime;
		_time.reset(); //Reset the variable _time calling to the proper method
	}

	unsigned int getIterarions(){
		return _numIterations;
	}

	void notifyIteration(){
		_numIterations++;
	}
};



#endif /* INCLUDE_MQKPSTOPCONDITION_H_ */
