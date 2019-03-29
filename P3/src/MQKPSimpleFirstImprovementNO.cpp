/*
 * MQKPSimpleFirstImprovementNO.cpp
 *
 * File defining the methods of the class MQKPSimpleFirstImprovementNO.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <MQKPSimpleFirstImprovementNO.h>
#include <MQKPInstance.h>
#include <MQKPEvaluator.h>
#include <MQKPObjectAssignmentOperation.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

bool MQKPSimpleFirstImprovementNO::findOperation(MQKPInstance &instance, MQKPSolution &solution, MQKPChangeOperation &operation) {

	MQKPObjectAssignmentOperation *oaOperation = dynamic_cast<MQKPObjectAssignmentOperation*>(&operation);
	if (oaOperation == NULL){
		cerr << "MQKPSimpleFirstImprovementNO::findOperation received an operation object of a class different from MQKPObjectAssignmentOperation" << endl;
		exit(1);
	}

	//Create a permutation of the indices of the objects and initialize some variables
	vector<int> perm;
	int numObjs = instance.getNumObjs();
	int numKnapsacks = instance.getNumKnapsacks();
	MQKPInstance::randomPermutation(numObjs, perm);

	/*
	 * 1. For each object of the problem (iterating them in the order defined by perm)
	 *   a. For each knapsack of the problem (Note: do not forget any of them)
	 *     i. Obtain the value deltaFitness obtained from assign this object to the knapsack in the solution
	 *
	 *     ii. If deltaFitness is positive
	 *       . Update the values of the operation in oaOperatio
	 *       . Exit returning true
	 *
	 * 2. If you reach this point, no positive deltaFitness was found so you return false
	 *
	 */

	for (int i = 0; i < numObjs; i++){
		int indexObj = perm[i];

		for (int j = 0; j <= numKnapsacks; j++){
			double deltaFitness = MQKPEvaluator::computeDeltaFitness(instance, solution, indexObj, j);

			if (deltaFitness > 0){
				oaOperation->setValues(indexObj, j, deltaFitness);
				return true;
			}
		}
	}

	return false;
}



