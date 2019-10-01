#ifndef MSPCROSSOVEROPERATOR_H_
#define MSPCROSSOVEROPERATOR_H_
#include <vector>

#include <MSPInstance.h>
#include <MSPSolution.h>

class MSPCrossoverOperator
{
protected:
	/**
	 * Properties of the class:
	 *  - _instance Instance of the problem considered. It is used only for creating new objects MQKPSolution
	 *  - _numObjs Stores the number of objects in the instance considered to reduce the number of queries
	 *             to the instance object
	 *  - _crossProb crossover probability
	 */
	MSPInstance *_instance;
	unsigned _numliterals;
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
	MSPSolution * cross(MSPSolution *s1, MSPSolution *s2) {
		MSPSolution * sol = new MSPSolution(_instance->getNumberOfLiterals());
		MSPSolution * sol1 = (MSPSolution *) s1;
		MSPSolution * sol2 = (MSPSolution *) s2;

		double randSample = (((double) rand()) / RAND_MAX);

		if (randSample < _crossProb) {

			//Uniform crossover of two parents, where the value of the parents
			//is randomly chosen for each gene
			for (unsigned i = 0; i < _numliterals; i++) {
				bool s=sol1->isTrue(i);

				randSample = (((double) rand()) / RAND_MAX);

				if (randSample < 0.5)
					s = sol2->isTrue(i);

				sol->setBool(i, s);
			}
		} else {
			//If there is no crossover, copy the first parent
			sol->copy(*sol1);
		}

		return sol;
	}

public:
	MSPCrossoverOperator(double crossProb,MSPInstance instance){
		_instance = &instance;
		_numliterals=instance.getNumberOfLiterals();
		_crossProb = crossProb;
	}

	~MSPCrossoverOperator(){

	}
	void cross(std::vector<MSPSolution*> &parents, std::vector<MSPSolution*> &offspring) {

		unsigned numParents = (unsigned) parents.size();

		//Apply crossover considering every two consecutive pairs (1,2), (3,4)...
		for (unsigned i=0; i < numParents; i+=2) {
			MSPSolution *sol = cross(parents[i], parents[i+1]);
			offspring.push_back(sol);
		}
	}	
};

#endif /*MSPCROSSOVEROPERATOR_H_*/
