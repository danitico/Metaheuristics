/**
 * MQKPMutationOperator.h
 *
 * File defining the class MQKPMutationOperator.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_MQKPMUTATIONOPERATOR_H_
#define INCLUDE_MQKPMUTATIONOPERATOR_H_

#include <MQKPSolution.h>
#include <vector>
#include <cstdlib>

using namespace std;

/**
 * Class which defines a mutation operator for the MQKP. It is based on iterating over all the
 * genes in the solutions and changing by a value randomly generated according to a probability
 */
class MQKPMutationOperator{

protected:
	/**
	 * Properties of the class:
	 * _mutProb Mutation probability
	 * _numObjs Number of objects. It is used to reduce the number of queries to the instance
	 * _numKnapsacks Number of knapsack of the problem. It is used to reduce the number of
	 *               queries to the instance
	 */
	double _mutProb;
	unsigned _numObjs;
	unsigned _numKnapsakcs;

	/**
	 * Function which mutates a solution
	 * @param[in,out] sol Solution to be mutated
	 */
	void mutate(Solution* sol){
		MQKPSolution *s = (MQKPSolution*) sol;

		//TODO Iterate over the objects and, according to a mutation probability, assign them
		//to a random knapsack (0, 1 or more than 1 genes could be modified)
		for(int i=0;i<_numObjs;i++)
				{
					double randSample=(((double)rand())/RAND_MAX);
					if(randSample <_mutProb){
					sol[i]=rand()%(_numKnapsakcs+1);
					}
				}
	}

public:
	/**
	 * Constructor
	 * @param[in] mutProb Mutation probability
	 * @param[in] instance Instance of the problem to be considered
	 */
	MQKPMutationOperator(double mutProb, MQKPInstance &instance){
		_mutProb = mutProb;
		_numObjs = instance.getNumObjs();
		_numKnapsakcs = instance.getNumKnapsacks();
	}

	/**
	 * Function which mutates a set of solutions
	 * @param[in,out] sols Solutions to be mutated
	 */
	void mutate(vector<Solution*> &sols){

		for (Solution* sol : sols){
			mutate(sol);
		}
	}
};



#endif /* INCLUDE_MQKPMUTATIONOPERATOR_H_ */
