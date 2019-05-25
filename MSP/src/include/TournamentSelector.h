/*
 * TournamentSelector.h
 *
 *  Created on: 15 may. 2019
 *      Author: chema969
 */

#ifndef INCLUDE_TOURNAMENTSELECTOR_H_
#define INCLUDE_TOURNAMENTSELECTOR_H_


#include <MSPSolution.h>
#include <SelectionOperator.h>
#include <vector>
#include <cstdlib>

using namespace std;

/**
 * Class implementing the tournament selection
 */
class TournamentSelector : public SelectionOperator{

protected:
	/**
	 * Properties of the class
	 * _k number of contestants in the tournament
	 */
	unsigned _k;

	/**
	 * Function which selects a solution from the set by applying a tournament
	 * @param[in] set Vector of solutions
	 * @result Solution selected
	 */
	MSPSolution* selectOne (vector<MSPSolution*> &set){

		/**
		 *
		 * 1. Select randomly a solution as the current winner
		 *
		 * 2. Repeat (_k-1) times: select randomly another solutions and make a tournament with the current winner (keep the best one)
		 */
		MSPSolution* best=set[rand()%set.size()];
		for(unsigned i=0;i<_k-1;i++){
			MSPSolution* aux=set[rand()%set.size()];
			if(MSPEvaluator::compare(aux->getFitness(), best->getFitness()) > 0){
				best=aux;
			}
		}
		return best;
	}

public:

	/**
	 * Constructor
	 * @param[in] k number of contestants in the tournament
	 */
	TournamentSelector(unsigned k){
		_k = k;
	}

	/**
	 * Destructor
	 */
	~TournamentSelector(){}

	/**
	 * Function which select as many pairs of parents from a vector as the number of elements
	 * in the corresponding vector
	 * @param[in] orig Vector of solutions from which apply the selection
	 * @param[out] result Vector where the pairs of parents selected will be stored
	 */
	virtual void select(vector<MSPSolution*> &orig, vector<MSPSolution*> &result){

		unsigned origSize = (unsigned) orig.size();

		for (unsigned i = 0; i < origSize; i++){
			result.push_back(selectOne(orig));
			result.push_back(selectOne(orig));
		}
	}
};



#endif /* INCLUDE_TOURNAMENTSELECTOR_H_ */
