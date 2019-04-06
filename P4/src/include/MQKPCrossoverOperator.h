/**
 * MQKPCrossoverOperator.h
 *
 * File defining the class MQKPCrossoverOperator.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_MQKPCROSSOVEROPERATOR_H_
#define INCLUDE_MQKPCROSSOVEROPERATOR_H_

#include <MQKPSolution.h>
#include <Solution.h>
#include <MQKPInstance.h>
#include <vector>

using namespace std;

/**
 * Class which implements a uniform crossover operator for the MQKP. The basic idea is similar
 * to the uniform crossover for integer coding
 */
class MQKPCrossoverOperator {

protected:
	/**
	 * Properties of the class:
	 *  - _instance Instance of the problem considered. It is used only for creating new objects MQKPSolution
	 *  - _numObjs Stores the number of objects in the instance considered to reduce the number of queries
	 *             to the instance object
	 *  - _crossProb crossover probability
	 */
	MQKPInstance *_instance;
	unsigned _numObjs;
	double _crossProb;

	/**
	 * Function which cross two solutions according to the crossover probability. In case the crossover is not
	 * considered, the solution will be the first parent
	 * @param[in] s1 first parent
	 * @param[in] s2 second parent
	 * @return New object with the solution descendant after considering the crossover of s1 and s2.
	 *         The solution is dynamically allocated in memory. It is the responsibility of the one invoking
	 *         this method to manage this memory correctly.
	 */
	MQKPSolution * cross(Solution *s1, Solution *s2) {
		MQKPSolution * sol = new MQKPSolution(*_instance);
		MQKPSolution * sol1 = (MQKPSolution *) s1;
		MQKPSolution * sol2 = (MQKPSolution *) s2;

		double randSample = (((double) rand()) / RAND_MAX);

		if (randSample < _crossProb) {

			//Uniform crossover of two parents, where the value of the parents
			//is randomly chosen for each gene
			for (unsigned i = 0; i < _numObjs; i++) {
				unsigned knapsack = sol1->whereIsObject(i);

				randSample = (((double) rand()) / RAND_MAX);

				if (randSample < 0.5)
					knapsack = sol2->whereIsObject(i);

				sol->putObjectIn(i, knapsack);
			}
		} else {
			//If there is no crossover, copy the first parent
			sol->copy(*sol1);
		}

		return sol;
	}

public:

	/**
	 * Constructor
	 * @param[in] crossProb Crossover probability
	 * @param[in] instance Instance of the problem considered
	 */
	MQKPCrossoverOperator(double crossProb, MQKPInstance &instance) {
		_instance = &instance;
		_numObjs = instance.getNumObjs();
		_crossProb = crossProb;
	}

	/**
	 * Function which applies crossover to a population of parents
	 * @param[in] parents Parent vector. The crossover is applied to every two consecutive parents (1,2), (3,4)...
	 * @param[out] offspring Vector where the descendants are stored.
	 * IMPORTANT: this function allocates memory dynamically for the new solutions in offspring,
	 * so it is the responsibility of the one invoking this method to manage this memory correctly.
	 */
	void cross(vector<Solution*> &parents, vector<Solution*> &offspring) {

		unsigned numParents = (unsigned) parents.size();

		//TODO Apply crossover considering every two consecutive pairs (1,2), (3,4)...
		for (...) {
			MQKPSolution *sol = cross(...);
			offspring.push_back(sol);
		}
	}
};

#endif /* INCLUDE_MQKPCROSSOVEROPERATOR_H_ */
