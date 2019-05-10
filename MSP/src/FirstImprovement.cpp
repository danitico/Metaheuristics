#include <FirstImprovement.h>
#include <MSPNeighbourExplorer.h>
FirstImprovement::FirstImprovement()
{
}

FirstImprovement::~FirstImprovement()
{
}

bool FirstImprovement::findOperation(MSPInstance& instance,MSPSolution& solution, MSPChangeOperation& operation) {

		//Create a permutation of the indices of the objects and initialize some variables
		std::vector<int> perm;
		int numLiterals = instance.getNumberOfLiterals();
		instance.randomPermutationOfLiterals(perm);



		for (int i = 0; i < numLiterals; i++){
			double deltaFitness = instance.getDeltaFitness(solution,perm[i]);

				if (deltaFitness > 0){
					operation.setValues(perm[i], deltaFitness);
					return true;
				}
			}
		

	return false;
}
