/**
 * MQKPTabuSearch.h
 *
 * File defining the class MQKPTabuSearch.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
*/

#ifndef INCLUDE_MQKPTABUSEARCH_H_
#define INCLUDE_MQKPTABUSEARCH_H_

#include <MQKPSolution.h>
#include <MQKPInstance.h>
#include <MQKPMetaheuristic.h>
#include <MQKPStopCondition.h>
#include <cstdlib>
#include <queue>
#include <set>

using namespace std;

/**
 * Class implementing the Tabu Search metaheuristic for MQKP. It uses only the short
 * term memory which avoids any operation over an object over which an operation
 * was recently applied
 */

class MQKPTabuSearch : public MQKPMetaheuristic{
protected:

	/**
	 * Properties of the class
	 * _solution MQKP solution over which the tabu search is working
	 * _instance is a pointer to the instance of the problem
	 * _shortTermMem this a queue implementing the short term memory of tabu search
	 * _shortTermMem_aux this is a auxiliary structure to make more efficient checking if
	 *                   an element is found in the tabu memory
	 * _tabuTennure Tabu tennure of the metaheuristic
	 */
	MQKPSolution *_solution;
	MQKPInstance *_instance;
	queue<unsigned> _shortTermMem;
	set<unsigned> _shortTermMem_aux;
	unsigned _tabuTennure;

	/**
	 * Vector of doubles with the quality of the last solution evaluated
	 */
	vector<double> _results;

public:
	/**
	 * Constructor
	 */
	MQKPTabuSearch(){
		_solution = NULL;
		_instance = NULL;
		_tabuTennure = 0;
	}

	/**
	 * Destructor
	 */
	virtual ~MQKPTabuSearch(){

		if (_bestSolution != NULL){
			delete _bestSolution;
			_bestSolution = NULL;
		}
	}

	/**
	 * Function which initializes some parameters of the metaheuristic.
	 * @param[in] instance Instance of the problem to be tackled
	 * @param[in] tabuTennure Tabu tennure of the metaheuristic
	 */
	void initialise(MQKPInstance * instance, unsigned tabuTennure);

	/**
	 * Function which assigns the solution over which the tabu search will work
	 * @param[in] solution Initial solution over which the tabu search is applied
	 */
	void setSolution(MQKPSolution* solution);

	/**
	 * Function which runs the metaheuristic until reaching the stop condition
	 * @param[in] stopCondition Stop condition of the metaheuristic
	 */
	virtual void run(MQKPStopCondition &stopCondition);

	/**
	 * Function returning the array with the results of the solutions accepted, in each step,
	 * by the metaheuristic
	 * @return vector with the results of the solutions accepted, in each step,
	 *         by the metaheuristic
	 */
	vector<double>& getResults() {
		return _results;
	}
};

#endif
