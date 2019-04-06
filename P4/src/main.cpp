/*	main.cpp
 *
 * File which defines the main function for running experiments over the Multiple Quadratic Knapsack Problem.
 * Specifically, these experiments apply many searches of an evolutionary algorithm and an ant colony optimization algorithm
 * over the four instances.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 *
 * TODO READ: The ACO algorithm requires several operations for each step and it could demand the 5 seconds after generating too few solutions. This would avoid observing its generic behaviour. To avoid this limitation, the program should be compiled using a optimization flag, such as -O3
 */

//Definition of some parameters of the experimentation
#define MAX_SECONS_PER_RUN 5
#define MAX_SOLUTIONS_PER_RUN 100000

#include <MQKPEvaluator.h>
#include <MQKPInstance.h>
#include <MQKPSolGenerator.h>
#include <MQKPSolution.h>
#include <MQKPGeneticAlgorithm.h>
#include <MQKPAntColonyOpt.h>
#include <MQKPStopCondition.h>
#include <Timer.h>

#include <iostream>
using namespace std;

//External definition of the seeds for the random number generator (in seeds.cpp)
//extern unsigned int numSeeds;
extern unsigned int seeds[];

/**
Function to apply the evolutionary algorithm for a maximum of MAX_SECONS_PER_RUN seconds or a maximum of MAX_SOLUTIONS_PER_RUN
 * for the instance provided
 * @param[out] currentResults Vector where we will store the fitness of the solutions generated
 * @param[out] bestSoFarResults Vector where we will store the fitness of the best solutions found up to the moment
 * @param[out] bestPerIterations Vector where we will store the best fitness values of each generation
 * @param[out] popMean Vector where we will store the average fitness values of the population of each generation
 * @param[out] offMean Vector where we will store the average fitness values of the offspring population of each generation
 * @param[in] instance Instance of the MQKP
 */
void runAGAExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, vector<double> &bestPerIterations,
		vector<double> &popMean, vector<double> &offMean,
		MQKPInstance &instance) {

	//Initialization
	MQKPGeneticAlgorithm ga;
	MQKPStopCondition stopCond;
	MQKPEvaluator::resetNumEvaluations();
	ga.initialise(60, instance);
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONS_PER_RUN);

	//Apply the GA
	ga.run(stopCond);

	//Store the results
	vector<double> &resultsGA = ga.getResults();

	for (double aResult : resultsGA) {
		currentResults.push_back(aResult);

		if (bestSoFarResults.size() > 0)
			bestSoFarResults.push_back(max(bestSoFarResults.back(), aResult));
		else
			bestSoFarResults.push_back(aResult);
	}

	bestPerIterations = ga.getBestsPerIterations();
	popMean = ga.getPopMeanResults();
	offMean = ga.getOffMeanResults();
}

/**
Function to apply the ACO algorithm for a maximum of MAX_SECONS_PER_RUN seconds or a maximum of MAX_SOLUTIONS_PER_RUN
 * for the instance provided
 * @param[out] currentResults Vector where we will store the fitness of the solutions generated
 * @param[out] bestSoFarResults Vector where we will store the fitness of the best solutions found up to the moment
 * @param[out] bestPerIterations Vector where we will store the best fitness values of each generation
 * @param[out] antsMean Vector where we will store the average fitness values of the solutions of each iteration
 * @param[in] instance Instance of the MQKP
 */
void runAnACOExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, vector<double> &bestPerIterations,
		vector<double> &antsMean, MQKPInstance &instance) {

	//Initialization
	MQKPAntColonyOpt aco;
	MQKPStopCondition stopCond;
	MQKPEvaluator::resetNumEvaluations();
	aco.initialise(5, 0.1, 1, 0.5, 0.1, 0.1, 20, instance);
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONS_PER_RUN);

	//Run the ACO
	aco.run(stopCond);

	//Store the results
	vector<double> &resultsACO = aco.getResults();

	for (double aResult : resultsACO) {
		currentResults.push_back(aResult);

		if (bestSoFarResults.size() > 0)
			bestSoFarResults.push_back(max(bestSoFarResults.back(), aResult));
		else
			bestSoFarResults.push_back(aResult);
	}

	bestPerIterations = aco.getBestPerIteration();
	antsMean = aco.getAntsMeanResults();
}

/**
 * Function which runs all the experiments for the command line arguments of the main program
 * @param[out] results 3D matrix where the results will be saved. The first index will be the instance considered. The second index will be the experiment over this instance (and the possible subcategories: current result, best so far results...). The third index will be the solution generated in the experiment.
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

		//Run the evolutionary algorithm
		vector<double> *theseResults = new vector<double>;
		vector<double> *bestResults = new vector<double>;
		vector<double> *bestPerIterations = new vector<double>;
		vector<double> *popMeanResults = new vector<double>;
		vector<double> *offMeanResults = new vector<double>;
		resultsOnThisInstance->push_back(theseResults);
		resultsOnThisInstance->push_back(bestResults);
		resultsOnThisInstance->push_back(bestPerIterations);
		resultsOnThisInstance->push_back(popMeanResults);
		resultsOnThisInstance->push_back(offMeanResults);
		runAGAExperiment(*theseResults, *bestResults, *bestPerIterations,
				*popMeanResults, *offMeanResults, instance);

		//Run the ant colony optimization algorithm
		theseResults = new vector<double>;
		bestResults = new vector<double>;
		bestPerIterations = new vector<double>;
		vector<double> *antsMean = new vector<double>;
		resultsOnThisInstance->push_back(theseResults);
		resultsOnThisInstance->push_back(bestResults);
		resultsOnThisInstance->push_back(bestPerIterations);
		resultsOnThisInstance->push_back(antsMean);
		runAnACOExperiment(*theseResults, *bestResults, *bestPerIterations,
				*antsMean, instance);
	}
}

/**
 * Function to free the memory of a 2D vector
 * @param[in] array 2D vector whose memory is going to be freed
 */
template<typename T>
void free2Darray(vector<vector<T>*> &array) {

	int numVectors = ((int) (array.size()));

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

	int numArrays = (int) (array.size());

	for (int i = 0; i < numArrays; i++) {
		free2Darray(*(array.at(i)));
		delete (array.at(i));
	}

	array.clear();
}





/**
 * Main function running the experimentation. Optimization using metaheuristics
 * based on populations: GA and ACO.
 * Finally, the results generated in matrix form are written to the standard output in the form of a matrix.
 *
 * TODO READ: In this case, the output can be configured according to your needs (see variable printColumns).
 * Currently, you can print up to 9 columns for each instance:
 *  0. The fitness of the last solution generated by the GA (currentGA),
 *  1. The best so far fitness value obtained by the GA (bestGA),
 *  2. The fitness value of the best solution of the population per iteration (bestGAPerIt),
 *  3. The average value of the fitness of the population of the GA per iteration (popMeanGA),
 *  4. The average value of the offspring generated by the GA per iteration (offMeanGA),
 *  5. The fitness value of the last solution generated by ACO (currentACO),
 *  6. The best so far fitness generated by ACO (bestACO),
 *  7. The fitness value of the best solution of the population per iteration (bestACOPerIt),
 *  8. The average value of the fitness of the solutions generated by the ants per iteration (antsMeanACO)
 *
 * It is not advisable to print all the columns at the same time. If you want all the columns in a single
 * run, you should edit the source code to have two different output files. The problem is that the number
 * of points in the columns "by iterations" is lower than the number of points in the rest of columns,
 * and, given that the program balance the number of points repeating the last one, a single representation
 * of all data in the same plot can be uninformative about the behaviour of the algorithms.
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
	//-> Second index for the runs performed over the same instance (and possible subcategories: current result, best-so-far result)
	//-> Third index for each result

	runExperiments(allTheResults, argv, argc);




	//////////////////////
	// Printing the results
	//////////////////////
	vector<double> lastResults;
//	vector<unsigned> printColumns = { 2, 3, 4, 7, 8};
	vector<unsigned> printColumns = { 0, 1, 5, 6 };
	vector<string> titles =
			{ "currentGA", "bestGA", "bestGAPerIt", "popMeanGA", "offMeanGA",
					"currentACO", "bestACO", "bestACOPerIt", "antsMeanACO" };
	for (unsigned int iInstance = 0; iInstance < numInstances; iInstance++) {

		for (auto indexColumnPerInstance : printColumns) {
			cout << argv[iInstance * 2 + 1] << "_" << argv[iInstance * 2 + 2]
					<< "_" << titles[indexColumnPerInstance] << "\t";
			lastResults.push_back(
					allTheResults.at(iInstance)->at(indexColumnPerInstance)->at(
							0));
		}
	}
	cout << endl;
	bool allResultsPrinted = false;
	unsigned int iIteration = 0;
	unsigned int indexColumn = 0;

	while (allResultsPrinted == false) {
		allResultsPrinted = true;
		for (unsigned int iInstance = 0; iInstance < numInstances;
				iInstance++) {

			for (auto indexColumnPerInstance : printColumns) {

				if (allTheResults.at(iInstance)->at(indexColumnPerInstance)->size()
						> iIteration) {
					allResultsPrinted = false;
					cout
							<< allTheResults.at(iInstance)->at(
									indexColumnPerInstance)->at(iIteration)
							<< "\t";
					lastResults[indexColumn] = allTheResults.at(iInstance)->at(
							indexColumnPerInstance)->at(iIteration);
				} else {
					cout << lastResults[indexColumn] << "\t";
				}
				indexColumn++;
			}
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
