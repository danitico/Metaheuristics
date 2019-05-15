/*
 * MSPMutationOperator.h
 *
 *  Created on: 15 may. 2019
 *      Author: chema969
 */

#ifndef INCLUDE_MSPMUTATIONOPERATOR_H_
#define INCLUDE_MSPMUTATIONOPERATOR_H_
#include <MSPSolution.h>
#include <vector>
#include <cstdlib>
#include <MSPInstance.h>

using namespace std;

/**
 * Class which defines a mutation operator for the MSP. It is based on iterating over all the
 * genes in the solutions and changing by a value randomly generated according to a probability
 */
class MSPMutationOperator{

protected:
	/**
	 * Properties of the class:
	 * _mutProb Mutation probability
	 * _numObjs Number of objects. It is used to reduce the number of queries to the instance
	 * _numKnapsacks Number of knapsack of the problem. It is used to reduce the number of
	 *               queries to the instance
	 */
	double _mutProb;
	unsigned _numliterals;


	/**
	 * Function which mutates a solution
	 * @param[in,out] sol Solution to be mutated
	 */
	void mutate(MSPSolution* s){


		//Iterate over the objects and, according to a mutation probability, assign them
		//to a random knapsack (0, 1 or more than 1 genes could be modified)
		for(unsigned i=0; i< this->_numliterals ;i++){
			double randSample=(double)rand()/RAND_MAX;
			if(randSample < _mutProb){
				s->setBool(i,!s->isTrue(i));
			}
		}
	}

public:
	/**
	 * Constructor
	 * @param[in] mutProb Mutation probability
	 * @param[in] instance Instance of the problem to be considered
	 */
	MSPMutationOperator(double mutProb, MSPInstance &instance){
		_mutProb = mutProb;
		_numliterals=instance.getNumberOfLiterals();
	}

	/**
	 * Function which mutates a set of solutions
	 * @param[in,out] sols Solutions to be mutated
	 */
	void mutate(vector<MSPSolution*> &sols){

		for (MSPSolution* sol : sols){
			mutate(sol);
		}
	}
};



#endif /* INCLUDE_MSPMUTATIONOPERATOR_H_ */
