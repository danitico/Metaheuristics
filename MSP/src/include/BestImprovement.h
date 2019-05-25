#ifndef BESTIMPROVEMENT_H_
#define BESTIMPROVEMENT_H_

#include <MSPNeighbourExplorer.h>
#include <vector>
#include <MSPBooleanChangeOperation.h>

class BestImprovement:public MSPNeighbourExplorer
{
public:
	BestImprovement(){

	}
	~BestImprovement(){

	}
	bool findOperation(MSPInstance& instance,MSPSolution& solution, MSPBooleanChangeOperation& operation);

};

#endif /*BESTIMPROVEMENT_H_*/
