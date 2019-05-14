#include <BestImprovement.h>

//BestImprovement::BestImprovement()
//{
//}
//
//BestImprovement::~BestImprovement()
//{
//}
bool BestImprovement::findOperation(MSPInstance& instance,MSPSolution& solution, MSPChangeOperation& operation) {

		//Create a permutation of the indices of the objects and initialize some variables
		std::vector<int> perm;
		int numLiterals = instance.getNumberOfLiterals();
		instance.randomPermutationOfLiterals(perm);
		bool initialised = false;
		double bestDeltaFitness = 0;


		for (int i = 0; i < numLiterals; i++){
			double deltaFitness = instance.getDeltaFitness(solution,perm[i]);

				if (deltaFitness > bestDeltaFitness|| initialised == false){
					operation.setValues(perm[i], deltaFitness);
					initialised = true;
					bestDeltaFitness = deltaFitness;
				}
		}
		if (bestDeltaFitness > 0)
			return true;
		else
			return false;
}
