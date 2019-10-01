/*
 * MSPNeighbourExplorer.h
 *
 *  Created on: 30 mar. 2019
 *      Author: chema969
 */

#ifndef MSPNEIGHBOUREXPLORER_H_
#define MSPNEIGHBOUREXPLORER_H_
#include <MSPInstance.h>
#include <MSPBooleanChangeOperation.h>

class MSPNeighbourExplorer {
public:
	virtual ~MSPNeighbourExplorer() {};
	virtual bool findOperation(MSPInstance &instance, MSPSolution &solution, MSPBooleanChangeOperation &operation) = 0;
};

#endif /* MSPNEIGHBOUREXPLORER_H_ */
