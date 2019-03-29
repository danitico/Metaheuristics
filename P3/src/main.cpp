/*	main.cpp
 *
 * File which defines the main fucntion for running experiments over the Multiple Quadratic Knapsack Problem.
 * Specifically, these experiments apply simulated annealing, tabu search, GRASP and iterated greedy
 * over the four instances.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

//Definition of some parameters of the experimentation
#define MAX_SECONS_PER_RUN 5
#define MAX_SOLUTIONS_PER_RUN 100000

#include <MQKPEvaluator.h>
#include <MQKPInstance.h>
#include <MQKPSolGenerator.h>
#include <MQKPSolution.h>
#include <MQKPSimulatedAnnealing.h>
#include <MQKPTabuSearch.h>
#include <MQKPGrasp.h>
#include <MQKPIteratedGreedy.h>
#include <MQKPStopCondition.h>
#include <Timer.h>

#include <iostream>
using namespace std;

//External definition of the seeds for the random number generator (in seeds.cpp)
//extern unsigned int numSeeds;
extern unsigned int seeds[];

/**
 * Function to apply simulated annealing for a maximum of MAX_SECONS_PER_RUN seconds or a maximum of MAX_SOLUTIONS_PER_RUN
 * for the instance provided
 * @param[out] currentResults Vector where we will store the fitness of the solutions that the simulated annealing
 *                            accepts in any moment.
 * @param[out] bestSoFarResults Vector where we will store the fitness of the best solutions found by the local
 *                              search up to the moment.
 * @param[in] instance Instance of the MQKP
 */
void runASAExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, MQKPInstance &instance) {

	//Initialization
	MQKPSolution initialSolution(instance);
	MQKPSimulatedAnnealing sa;
	MQKPStopCondition stopCond;
	MQKPEvaluator::resetNumEvaluations();
	sa.initialise(0.9, 10, 0.9999, 50, instance);
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONS_PER_RUN);

	//Generate a first random solution
	MQKPSolGenerator::genRandomSol(instance, initialSolution);
	double currentFitness = MQKPEvaluator::computeFitness(instance,
			initialSolution);
	initialSolution.setFitness(currentFitness);
	double bestFitness = currentFitness;
	currentResults.push_back(currentFitness);
	bestSoFarResults.push_back(bestFitness);
	sa.setSolution(&initialSolution);

	//Apply SA
	sa.run(stopCond);

	//Store the results
	vector<double> &resultsSA = sa.getResults();

	for (auto aResult : resultsSA) {
		currentResults.push_back(aResult);
		bestSoFarResults.push_back(max(bestSoFarResults.back(), aResult));
	}
}

/**
 * Function to apply tabu search for a maximum of MAX_SECONS_PER_RUN seconds or a maximum of MAX_SOLUTIONS_PER_RUN
 * for the instance provided
 * @param[out] currentResults Vector where we will store the fitness of the solutions that the tabu search
 *                            accepts in any moment.
 * @param[out] bestSoFarResults Vector where we will store the fitness of the best solutions found by the local
 *                              search up to the moment.
 * @param[in] instance Instance of the MQKP
 */
void runATSExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, MQKPInstance &instance) {

	//Initialization
	MQKPSolution initialSolution(instance);
	MQKPTabuSearch ts;
	MQKPStopCondition stopCond;
	MQKPEvaluator::resetNumEvaluations();
	ts.initialise(&instance, ((unsigned)(instance.getNumObjs() / 2.5)));
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONS_PER_RUN);

	//Generate a first random solution
	MQKPSolGenerator::genRandomSol(instance, initialSolution);
	double currentFitness = MQKPEvaluator::computeFitness(instance,
			initialSolution);
	initialSolution.setFitness(currentFitness);
	double bestFitness = currentFitness;
	currentResults.push_back(currentFitness);
	bestSoFarResults.push_back(bestFitness);
	ts.setSolution(&initialSolution);

	//Apply TS
	ts.run(stopCond);

	//Store the results
	vector<double> &resultsTS = ts.getResults();

	for (auto aResult : resultsTS) {
		currentResults.push_back(aResult);
		bestSoFarResults.push_back(max(bestSoFarResults.back(), aResult));
	}
}

/**
 * Function to apply GRASP for a maximum of MAX_SECONS_PER_RUN seconds or a maximum of MAX_SOLUTIONS_PER_RUN
 * for the instance provided
 * @param[out] currentResults Vector where we will store the fitness of the solutions that GRASP
 *                            accepts in any moment.
 * @param[out] bestSoFarResults Vector where we will store the fitness of the best solutions found by the local
 *                              search up to the moment.
 * @param[in] instance Instance of the MQKP
 */
void runAGraspExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, MQKPInstance &instance) {

	//Initialization
	MQKPSolution initialSolution(instance);
	MQKPGrasp grasp;
	MQKPStopCondition stopCond;
	MQKPEvaluator::resetNumEvaluations();
	grasp.initialise(0.25, instance);
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONS_PER_RUN);

	//Generate a first random solution
	MQKPSolGenerator::genRandomSol(instance, initialSolution);
	double currentFitness = MQKPEvaluator::computeFitness(instance,
			initialSolution);
	initialSolution.setFitness(currentFitness);
	double bestFitness = currentFitness;
	currentResults.push_back(currentFitness);
	bestSoFarResults.push_back(bestFitness);

	//Apply GRASP
	grasp.run(stopCond);

	//Store the results
	vector<double> &resultsGRASP = grasp.getResults();

	for (auto aResult : resultsGRASP) {
		currentResults.push_back(aResult);
		bestSoFarResults.push_back(max(bestSoFarResults.back(), aResult));
	}
}

/**
 * Function to apply iterated greedy for a maximum of MAX_SECONS_PER_RUN seconds or a maximum of MAX_SOLUTIONS_PER_RUN
 * for the instance provided
 * @param[out] currentResults Vector where we will store the fitness of the solutions that iterated greedy
 *                            accepts in any moment.
 * @param[out] bestSoFarResults Vector where we will store the fitness of the best solutions found by the local
 *                              search up to the moment.
 * @param[in] instance Instance of the MQKP
 */
void runAIGExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, MQKPInstance &instance) {

	//Initialization
	MQKPSolution initialSolution(instance);
	MQKPIteratedGreedy ig;
	MQKPStopCondition stopCond;
	MQKPEvaluator::resetNumEvaluations();
	ig.initialise(0.25, instance);
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONS_PER_RUN);

	//Generate a first random solution
	MQKPSolGenerator::genRandomSol(instance, initialSolution);
	double currentFitness = MQKPEvaluator::computeFitness(instance,
			initialSolution);
	initialSolution.setFitness(currentFitness);
	double bestFitness = currentFitness;
	currentResults.push_back(currentFitness);
	bestSoFarResults.push_back(bestFitness);

	//Apply IG
	ig.run(stopCond);

	//Store the results
	vector<double> &resultsIG = ig.getResults();

	for (auto aResult : resultsIG) {
		currentResults.push_back(aResult);
		bestSoFarResults.push_back(max(bestSoFarResults.back(), aResult));
	}
}
/**
 * Function which runs all the experiments for arguments passed in the command line to the main program.
 * @param[out] results 3D matrix where the results will be saved. The first index will be the instance considered,
 *                     the second index will be the experiment and the third index will be the solution generated
 *                     in this experiment.
 * @param[in] mainArgs Arguments of the main function (argv). These arguments are organized, from the first index, as:
 *                     <filename of instance 1> <number of knapsacks> <filename of instance 2> <number of knapsacks>...
 * @param[in] numMainArgs Number of arguments of the main function (argc)
 */
void runExperiments(vector<vector<vector<double>*>*> &results, char **mainArgs,
		unsigned int numMainArgs) {

	//For each instance of the problem
	for (unsigned int iInstance = 1; iInstance < numMainArgs; iInstance += 2) {

		//Read the instance and create the data structures needed to store the results
		MQKPInstance instance;
		vector<vector<double>*>* resultsOnThisInstance = new vector<
				vector<double>*>;
		results.push_back(resultsOnThisInstance);
		char *instanceName = mainArgs[iInstance];
		unsigned int numKnapsacks = atoi(mainArgs[iInstance + 1]);
		instance.readInstance(instanceName, numKnapsacks);

		//Run the simulated annealing
		vector<double> *theseFirstResults = new vector<double>;
		vector<double> *bestFirstResults = new vector<double>;
		resultsOnThisInstance->push_back(theseFirstResults);
		resultsOnThisInstance->push_back(bestFirstResults);
		runASAExperiment(*theseFirstResults, *bestFirstResults, instance);

		//Run the tabu search
		theseFirstResults = new vector<double>;
		bestFirstResults = new vector<double>;
		resultsOnThisInstance->push_back(theseFirstResults);
		resultsOnThisInstance->push_back(bestFirstResults);
		runATSExperiment(*theseFirstResults, *bestFirstResults, instance);

		//Run GRASP
		theseFirstResults = new vector<double>;
		bestFirstResults = new vector<double>;
		resultsOnThisInstance->push_back(theseFirstResults);
		resultsOnThisInstance->push_back(bestFirstResults);
		runAGraspExperiment(*theseFirstResults, *bestFirstResults, instance);

		//Run iterated greedy
		theseFirstResults = new vector<double>;
		bestFirstResults = new vector<double>;
		resultsOnThisInstance->push_back(theseFirstResults);
		resultsOnThisInstance->push_back(bestFirstResults);
		runAIGExperiment(*theseFirstResults, *bestFirstResults, instance);
	}
}

/**
 * Function to free the memory of a 2D vector
 * @param[in] array 2D vector whose memory is going to be freed
 */
template<typename T>
void free2Darray(vector<vector<T>*> &array) {

	int numVectors = ((int)(array.size()));

	for (int i = 0; i < numVectors; i++) {
		array.at(i)->clear();
		delete (array.at(i));
	}

	array.clear();
}

/**
 * Function to free the memory of a 3D vector
 * @param[in] array 3D vector whose memory is going to be freed
 */
template<typename T>
void free3Darray(vector<vector<vector<T>*>*> &array) {

	int numArrays = (int)(array.size());

	for (int i = 0; i < numArrays; i++) {
		free2Darray(*(array.at(i)));
		delete (array.at(i));
	}

	array.clear();
}

/**
 * Main function running the experimentation. Optimization using metaheuristics
 * based on trajectories: simulated annealing, tabu search, GRASP and iterated
 * greedy.
 *
 * Finally, the results generated in matrix form are written to the standard output.
 * For each instance, eight columns are generated:
 * for each metaheuristic, one with the fitness of the last solution accepted
 * and other one with the fitness of the best solution found up to the moment.
 */
int main(int argc, char **argv) {

	if (argc < 3 || (argc % 2) != 1) {
		cout << argv[0] << " (<problem instance files> <numKnapsacks>)+"
				<< endl;
		return 0;
	}

	//////////////////////////
	//Experiment execution
	//////////////////////////
	unsigned int numInstances = (argc - 1) / 2;
	vector<vector<vector<double>*>*> allTheResults;
	srand(seeds[0]);
	//All the fitness values generated will be saved in the matrix allTheResults
	//It is a 3D matrix
	//-> First index for the instance
	//-> Second index for the runs performed over the same instance
	//-> Third index for the solutions generated during the run

	runExperiments(allTheResults, argv, argc);

	//////////////////////
	// Printing the results
	//////////////////////
	vector<double> lastResults;
	for (unsigned int iInstance = 0; iInstance < numInstances; iInstance++){
		cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_currentSA\t";
		cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_bestSA\t";
		cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_currentTS\t";
		cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_bestTS\t";
		cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_currentGrasp\t";
		cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_bestGrasp\t";
		cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_currentIG\t";
		cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_bestIG\t";
		lastResults.push_back(allTheResults.at(iInstance)->at(0)->at(0));
		lastResults.push_back(allTheResults.at(iInstance)->at(1)->at(0));
		lastResults.push_back(allTheResults.at(iInstance)->at(2)->at(0));
		lastResults.push_back(allTheResults.at(iInstance)->at(3)->at(0));
		lastResults.push_back(allTheResults.at(iInstance)->at(4)->at(0));
		lastResults.push_back(allTheResults.at(iInstance)->at(5)->at(0));
		lastResults.push_back(allTheResults.at(iInstance)->at(6)->at(0));
		lastResults.push_back(allTheResults.at(iInstance)->at(7)->at(0));
	}
	cout << endl;
	bool allResultsPrinted = false;
	unsigned int iIteration = 0;
	unsigned int indexColumn = 0;

	while (allResultsPrinted == false){
		allResultsPrinted = true;
		for (unsigned int iInstance = 0; iInstance < numInstances; iInstance++){

			if (allTheResults.at(iInstance)->at(0)->size() > iIteration){
				allResultsPrinted = false;
				cout << allTheResults.at(iInstance)->at(0)->at(iIteration) << "\t";
				lastResults[indexColumn] = allTheResults.at(iInstance)->at(0)->at(iIteration);
			} else {
				cout << lastResults[indexColumn] << "\t";
			}
			indexColumn++;

			if (allTheResults.at(iInstance)->at(0)->size() > iIteration){
				allResultsPrinted = false;
				cout << allTheResults.at(iInstance)->at(1)->at(iIteration) << "\t";
				lastResults[indexColumn] = allTheResults.at(iInstance)->at(1)->at(iIteration);
			} else {
				cout << lastResults[indexColumn] << "\t";
			}
			indexColumn++;

			if (allTheResults.at(iInstance)->at(2)->size() > iIteration){
				allResultsPrinted = false;
				cout << allTheResults.at(iInstance)->at(2)->at(iIteration) << "\t";
				lastResults[indexColumn] = allTheResults.at(iInstance)->at(2)->at(iIteration);
			} else {
				cout << lastResults[indexColumn] << "\t";
			}
			indexColumn++;

			if (allTheResults.at(iInstance)->at(3)->size() > iIteration){
				allResultsPrinted = false;
				cout << allTheResults.at(iInstance)->at(3)->at(iIteration) << "\t";
				lastResults[indexColumn] = allTheResults.at(iInstance)->at(3)->at(iIteration);
			} else {
				cout << lastResults[indexColumn] << "\t";
			}
			indexColumn++;

			if (allTheResults.at(iInstance)->at(4)->size() > iIteration){
				allResultsPrinted = false;
				cout << allTheResults.at(iInstance)->at(4)->at(iIteration) << "\t";
				lastResults[indexColumn] = allTheResults.at(iInstance)->at(4)->at(iIteration);
			} else {
				cout << lastResults[indexColumn] << "\t";
			}
			indexColumn++;

			if (allTheResults.at(iInstance)->at(5)->size() > iIteration){
				allResultsPrinted = false;
				cout << allTheResults.at(iInstance)->at(5)->at(iIteration) << "\t";
				lastResults[indexColumn] = allTheResults.at(iInstance)->at(5)->at(iIteration);
			} else {
				cout << lastResults[indexColumn] << "\t";
			}
			indexColumn++;

			if (allTheResults.at(iInstance)->at(6)->size() > iIteration){
				allResultsPrinted = false;
				cout << allTheResults.at(iInstance)->at(6)->at(iIteration) << "\t";
				lastResults[indexColumn] = allTheResults.at(iInstance)->at(6)->at(iIteration);
			} else {
				cout << lastResults[indexColumn] << "\t";
			}
			indexColumn++;

			if (allTheResults.at(iInstance)->at(7)->size() > iIteration){
				allResultsPrinted = false;
				cout << allTheResults.at(iInstance)->at(7)->at(iIteration) << "\t";
				lastResults[indexColumn] = allTheResults.at(iInstance)->at(7)->at(iIteration);
			} else {
				cout << lastResults[indexColumn] << "\t";
			}
			indexColumn++;
		}
		cout << endl;
		iIteration++;
		indexColumn = 0;
	}




	//////////////////////
	// Freeing memory
	//////////////////////
	free3Darray(allTheResults);
	return 0;
}
