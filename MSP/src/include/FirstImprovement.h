#ifndef FIRSTIMPROVEMENT_H_
#define FIRSTIMPROVEMENT_H_

#include <MSPInstance.h>
#include <MSPNeighbourExplorer.h>
#include <vector>
#include <MSPChangeOperation.h>

class FirstImprovement:public MSPNeighbourExplorer
{
public:
//	FirstImprovement();
//	virtual ~FirstImprovement();
	virtual bool findOperation(MSPInstance& instance,MSPSolution& solution, MSPChangeOperation& operation);

};

#endif /*FIRSTIMPROVEMENT_H_*/
