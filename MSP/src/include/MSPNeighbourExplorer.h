/*
 * MSPNeighbourExplorer.h
 *
 *  Created on: 30 mar. 2019
 *      Author: chema969
 */

#ifndef MSPNEIGHBOUREXPLORER_H_
#define MSPNEIGHBOUREXPLORER_H_
#include <MSPChangeOperation.h>
#include <MSPInstance.h>

class MSPNeighbourExplorer {
public:
//	virtual ~MSPNeighbourExplorer() = 0;
	virtual bool findOperation(MSPInstance &instance, MSPSolution &solution, MSPChangeOperation &operation) = 0;
};

#endif /* MSPNEIGHBOUREXPLORER_H_ */
