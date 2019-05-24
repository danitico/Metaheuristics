#ifndef BESTIMPROVEMENT_H_
#define BESTIMPROVEMENT_H_

#include <MSPNeighbourExplorer.h>
#include <vector>
#include <MSPChangeOperation.h>

class BestImprovement:public MSPNeighbourExplorer
{
public:
	BestImprovement(){

	}
	~BestImprovement(){

	}
	bool findOperation(MSPInstance& instance,MSPSolution& solution, MSPChangeOperation& operation);

};

#endif /*BESTIMPROVEMENT_H_*/
