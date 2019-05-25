#ifndef FIRSTIMPROVEMENT_H_
#define FIRSTIMPROVEMENT_H_

#include <MSPInstance.h>
#include <MSPNeighbourExplorer.h>
#include <vector>
#include <MSPBooleanChangeOperation.h>

class FirstImprovement:public MSPNeighbourExplorer
{
public:
	~FirstImprovement(){

	}
	bool findOperation(MSPInstance& instance,MSPSolution& solution, MSPBooleanChangeOperation& operation);

};

#endif /*FIRSTIMPROVEMENT_H_*/
