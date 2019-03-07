/*
 * main.cpp
 *
 * File which defines the main fucntion for running experiments over the Multiple Quadratic Knapsack Problem.
 * Specifically, these experiments apply local search over the four instances and store the best solution
 * found up to the moment.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

//Definition of some parameters of the experimentation
#define MAX_SECONS_PER_RUN 5
#define MAX_SOLUTIONS_PER_RUN 100000
#define MAX_INITIAL_SOLUTIONS 5

#include <MQKPEvaluator.h>
#include <MQKPInstance.h>
#include <MQKPSolGenerator.h>
#include <MQKPSolution.h>
#include <MQKPLocalSearch.h>
#include <MQKPSimpleFirstImprovementNO.h>
#include <MQKPSimpleBestImprovementNO.h>
#include <Timer.h>

#include <iostream>
using namespace std;

//External definition of the seeds for the random number generator (in seeds.cpp)
//extern unsigned int numSeeds;
extern unsigned int seeds[];

/**
 * Function to apply several local search processes over random solutions,
 * for a maximum of MAX_SECONS_PER_RUN seconds, a maximum of MAX_SOLUTIONS_PER_RUN
 * and a maximum of MAX_INITIAL_SOLUTIONS local search processes, for the instance provided
 * @param[out] currentResults vector where we will store the fitness of the solutions that the local search
 *                            accepts in any moment.
 * @param[out] bestSoFarResults vector where we will store the fitness of the best solutions found by the local
 *                              search up to the moment.
 * @param[in] instance Instance of the MQKP
 * @param[in] explorer Operator for exploring the neighbourhood to be used during the LS
 */
void runALSExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, MQKPInstance &instance,
		MQKPNeighExplorer &explorer) {

	//Initialization
	MQKPLocalSearch ls;
	MQKPSolution initialSolution(instance);
	Timer t;
	MQKPEvaluator::resetNumEvaluations();

	//Generate a first random solution to initialize bestFitness
	MQKPSolGenerator::genRandomSol(instance, initialSolution);
	double currentFitness = MQKPEvaluator::computeFitness(instance,
			initialSolution);
	double bestFitness = currentFitness;
	initialSolution.setFitness(currentFitness);
	currentResults.push_back(currentFitness);
	bestSoFarResults.push_back(bestFitness);
	int numInitialSolutions = 0;

	//While there is time and not too many solutions have been generated,
	//generate a random solution, apply the local search and store
	//the result
	while (t.elapsed_time(Timer::VIRTUAL) <= MAX_SECONS_PER_RUN
			&& MQKPEvaluator::getNumEvaluations() < MAX_SOLUTIONS_PER_RUN &&
			numInitialSolutions < MAX_INITIAL_SOLUTIONS) {

		/*
		 * TODO - Generate a new random solution in initialSolution
		 *      - Obtain its current fitness
		 *      - Set currentFitness to the solution
		 */

		currentResults.push_back(currentFitness);
		bestSoFarResults.push_back(
				max(bestSoFarResults.back(), currentFitness));

		//TODO Call to the method optimise of the object ls to optimise the solution


		//Store the results
		vector<double> &resultsLS = ls.getResults();

		for (auto aResult : resultsLS) {
			currentResults.push_back(aResult);
			bestSoFarResults.push_back(max(bestSoFarResults.back(), aResult));
		}

		numInitialSolutions++;
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

	MQKPSimpleFirstImprovementNO firstExplorer;
	MQKPSimpleBestImprovementNO bestExplorer;

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

		//Run the first improvement local search
		vector<double> *theseFirstResults = new vector<double>;
		vector<double> *bestFirstResults = new vector<double>;
		resultsOnThisInstance->push_back(theseFirstResults);
		resultsOnThisInstance->push_back(bestFirstResults);
		runALSExperiment(*theseFirstResults, *bestFirstResults, instance,
				firstExplorer);

		//Run the best improvement local search
		vector<double> *theseBestResults = new vector<double>;
		vector<double> *bestBestResults = new vector<double>;
		resultsOnThisInstance->push_back(theseBestResults);
		resultsOnThisInstance->push_back(bestBestResults);
		runALSExperiment(*theseBestResults, *bestBestResults, instance,
				bestExplorer);
	}
}

/**
 * Function to free the memory of a 2D vector
 * @param[in] array 2D vector whose memory is going to be freed
 */
template<typename T>
void free2Darray(vector<vector<T>*> &array) {

	int numVectors = array.size();

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

	int numArrays = array.size();

	for (int i = 0; i < numArrays; i++) {
		free2Darray(*(array.at(i)));
		delete (array.at(i));
	}

	array.clear();
}

/**
 * Main function running the experimentation. Generation of random solutions for the instances.
 *
 * Finally, the results generated in matrix form are written to the standard output. For each instance, four columns are generated.
 * 2 columns for the first improvement local search (fitness of the last solution generated by this LS
 * and fitness of the best solution found up to the moment by this LS) and other 2 columns for the best
 * improvement local search (fitness of the last solution and fitness of the best solution up to the moment).
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
		cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_currentFirst\t";
		cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_bestFirst\t";
		cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_currentBest\t";
		cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_bestBest\t";
		lastResults.push_back(allTheResults.at(iInstance)->at(0)->at(0));
		lastResults.push_back(allTheResults.at(iInstance)->at(1)->at(0));
		lastResults.push_back(allTheResults.at(iInstance)->at(2)->at(0));
		lastResults.push_back(allTheResults.at(iInstance)->at(3)->at(0));
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
