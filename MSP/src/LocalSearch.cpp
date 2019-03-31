/*
 * LocalSearch.cpp
 *
 *  Created on: 30 mar. 2019
 *      Author: chema969
 */

#include "LocalSearch.h"

LocalSearch::LocalSearch() {
	// TODO Auto-generated constructor stub

}

LocalSearch::~LocalSearch() {
	// TODO Auto-generated destructor stub
}

void LocalSearch::optimise(MSPInstance &instance, MSPNeighbourExplorer &explorer, MSPSolution &solution){
	_results.clear();
	_results.push_back(solution.getFitness());
	MSPChangeOperation operation;

	while(explorer.findOperation(instance, solution, operation)){
		operation.apply(solution);
		_results.push_back(solution.getFitness());
	}

}
