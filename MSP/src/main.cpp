#include <MSPInstance.h>
#include <MSPSolution.h>
#include <LocalSearch.h>
#include <MSPRandomSolution.h>
#include <MSPSimulatedAnnealing.h>
#include <MSPStopCondition.h>
#include <MSPEvaluator.h>
#include <MSPGrasp.h>
#include <MSPTabuSearch.h>
#include <cstdlib>
#include <iostream>
#include <LocalSearch.h>
#include <FirstImprovement.h>
using namespace std;
extern unsigned int numSeeds;
extern unsigned int seeds[];
#define MAX_SECONS_PER_RUN 5
#define MAX_SOLUTIONS_PER_RUN 100000
#define MAX_INITIAL_SOLUTIONS 5

void runRandomFunction(vector<double> &currentResults,
		vector<double> &bestSoFarResults, MSPInstance &instance){
	int r=0;
	srand(seeds[r]); r++;
	Timer t;
	MSPSolution solution(instance.getNumberOfLiterals());
	MSPEvaluator::resetNumEvaluations();

	MSPRandomSolution::genRandomSol(instance, solution);
	double currentFitness = MSPEvaluator::computeFitness(instance, solution);
	solution.setFitness(currentFitness);
	double bestFitness = currentFitness;
	currentResults.push_back(currentFitness);
	bestSoFarResults.push_back(bestFitness);


	while(t.elapsed_time(Timer::VIRTUAL) <= MAX_SECONS_PER_RUN
			&& MSPEvaluator::getNumEvaluations() < MAX_SOLUTIONS_PER_RUN){

		srand(seeds[r]);seeds[r]+=rand()%100; r=(r+1)%numSeeds;
    	MSPRandomSolution::genRandomSol(instance, solution);
    	double currentsol=MSPEvaluator::computeFitness(instance, solution);

		currentResults.push_back(currentsol);
		bestSoFarResults.push_back(max(bestSoFarResults.back(), currentsol));
    }
}
void runSimulatedAnnealing(vector<double> &currentResults,
		vector<double> &bestSoFarResults, MSPInstance &instance) {

	//Initialization
	MSPSolution initialSolution(instance.getNumberOfLiterals());
	MSPSimulatedAnnealing sa;
	MSPStopCondition stopCond;
	MSPEvaluator::resetNumEvaluations();
	sa.initialise(0.9, 10, 0.8000, 50, instance);
	stopCond.setConditions(100000, 0, 5);

	//Generate a first random solution
	MSPRandomSolution::genRandomSol(instance, initialSolution);
	double currentFitness = MSPEvaluator::computeFitness(instance,
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

void runFirstImprovement(vector<double> &currentResults,
		vector<double> &bestSoFarResults, MSPInstance &instance,
		MSPNeighbourExplorer &explorer) {

	srand(seeds[0]);
	//Initialization
	LocalSearch ls;
	MSPSolution initialSolution(instance.getNumberOfLiterals());
	Timer t;
	MSPEvaluator::resetNumEvaluations();

	//Generate a first random solution to initialize bestFitness
	MSPRandomSolution::genRandomSol(instance, initialSolution);
	double currentFitness = MSPEvaluator::computeFitness(instance,
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
			&& MSPEvaluator::getNumEvaluations() < MAX_SOLUTIONS_PER_RUN &&
			numInitialSolutions < MAX_INITIAL_SOLUTIONS) {

		MSPRandomSolution::genRandomSol(instance, initialSolution);

		currentFitness = MSPEvaluator::computeFitness(instance, initialSolution);

		currentResults.push_back(currentFitness);
		bestSoFarResults.push_back(
				max(bestSoFarResults.back(), currentFitness));

		ls.optimise(instance, explorer, initialSolution);

		//Store the results
		vector<double> &resultsLS = ls.getResults();

		for (auto aResult : resultsLS) {
			currentResults.push_back(aResult);
			bestSoFarResults.push_back(max(bestSoFarResults.back(), aResult));
		}

		numInitialSolutions++;
	}

}
void runTabuSearch(vector<double> &currentResults,
		vector<double> &bestSoFarResults, MSPInstance &instance) {

	//Initialization
	MSPSolution initialSolution(instance.getNumberOfLiterals());
	MSPTabuSearch ts;
	MSPStopCondition stopCond;
	MSPEvaluator::resetNumEvaluations();
	ts.initialise(&instance, ((unsigned)(instance.getNumberOfLiterals() / 2.5)));
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONS_PER_RUN);

	//Generate a first random solution
	MSPRandomSolution::genRandomSol(instance, initialSolution);
	double currentFitness = MSPEvaluator::computeFitness(instance,
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

void runGrasp(vector<double> &currentResults,
		vector<double> &bestSoFarResults, MSPInstance &instance) {

	//Initialization
	MSPSolution initialSolution(instance.getNumberOfLiterals());
	MSPGrasp grasp;
	MSPStopCondition stopCond;
	MSPEvaluator::resetNumEvaluations();
	grasp.initialise(0.25, instance);
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONS_PER_RUN);

	//Generate a first random solution
	MSPRandomSolution::genRandomSol(instance, initialSolution);
	double currentFitness = MSPEvaluator::computeFitness(instance,
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

int main(int argc, char** argv) {
	if(argc<2){
		std::cout<<"You must include at least one instance file"<<std::endl;
		return 0;
	}
	vector<double> *current = new vector<double>();
	vector<double> *best = new vector<double>();

	MSPInstance instance;
	instance.readInstance(argv[1]);

//	runRandomFunction(*current, *best, instance);

//	runTabuSearch(*current, *best, instance);

//	runGrasp(*current, *best, instance);

//	runSimulatedAnnealing(*current, *best, instance);
	FirstImprovement firstExplorer;
	runFirstImprovement(*current, *best, instance, firstExplorer);

//
	for(unsigned i=0; i < current->size(); i++){
		std::cout << current->at(i) << " " << best->at(i) << std::endl;
	}

}
