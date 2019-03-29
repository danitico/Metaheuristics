/*
 * MQKPSimpleBestImprovementNO.cpp
 *
 * File defining the methods of the class MQKPSimpleBestImprovementNO.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <MQKPSimpleBestImprovementNO.h>
#include <MQKPInstance.h>
#include <MQKPSolution.h>
#include <MQKPObjectAssignmentOperation.h>
#include <MQKPEvaluator.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

bool MQKPSimpleBestImprovementNO::findOperation(MQKPInstance& instance,
		MQKPSolution& solution, MQKPChangeOperation& operation) {

	MQKPObjectAssignmentOperation *oaOperation = dynamic_cast<MQKPObjectAssignmentOperation*>(&operation);
	if (oaOperation == NULL){
		cerr << "MQKPSimpleBestImprovementNO::findOperation received an operation object of a class different from MQKPObjectAssignmentOperation" << endl;
		exit(1);
	}

	//Create a permutation of the indices of the objects and initialize some variables
	vector<int> perm;
	int numObjs = instance.getNumObjs();
	MQKPInstance::randomPermutation(numObjs, perm);
	int numKnapsacks = instance.getNumKnapsacks();
	bool initialised = false;
	double bestDeltaFitness = 0;

	/*
	 * 1. For each object of the problem (iterating them in the order defined by perm)
	 *   a. For each knapsack of the problem (Note: do not forget any of them)
	 *     i. Obtain the value deltaFitness obtained from assign this object to the knapsack in the solution
	 *
	 *     ii. If deltaFitness is better than bestDeltaFitness or if bestDeltaFitness was not initialised (initialised == false)
	 *       . Set initialised to true
	 *       . Update bestDeltaFitness
	 *       . Update the values of the operation in oaOperation
	 *
	 * 2. Finally, return true if bestDeltaFitness is positive and false otherwise
	 *
	 */

	for (int i = 0; i < numObjs; i++){
		int indexObj = perm[i];

		for (int j = 0; j <= numKnapsacks; j++){
			double deltaFitness = MQKPEvaluator::computeDeltaFitness(instance, solution, indexObj, j);

			if (deltaFitness > bestDeltaFitness || initialised == false){
				initialised = true;
				bestDeltaFitness = deltaFitness;
				oaOperation->setValues(indexObj, j, deltaFitness);
			}
		}
	}

	if (bestDeltaFitness > 0)
		return true;
	else
		return false;
}
