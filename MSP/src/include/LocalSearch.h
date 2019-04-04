/*
 * LocalSearch.h
 *
 *  Created on: 30 mar. 2019
 *      Author: chema969
 */

#ifndef LOCALSEARCH_H_
#define LOCALSEARCH_H_
#include "MSPInstance.h"
#include "MSPSolution.h"
#include <vector>
#include "MSPNeighbourExplorer.h"
#include "MSPChangeOperation.h"

class LocalSearch {
private:
	std::vector<double> _results;

public:
	LocalSearch();
	virtual ~LocalSearch();
	void optimise(MSPInstance &instance, MSPNeighbourExplorer &explorer, MSPSolution &solution);
};

#endif /* LOCALSEARCH_H_ */
