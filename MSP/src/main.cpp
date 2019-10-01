#include <iostream>
#include <macros.h>

#include <MSPRandomSolution.h>
#include <MSPSimulatedAnnealing.h>
#include <MSPEvaluator.h>
#include <MSPGrasp.h>
#include <MSPTabuSearch.h>
#include <BestImprovement.h>
#include <MSPIteratedGreedy.h>
#include <MSPGeneticAlgorithm.h>

using namespace std;
extern unsigned int numSeeds;
extern unsigned int seeds[];
#define MAX_SECONS_PER_RUN 500
#define MAX_SOLUTIONS_PER_RUN 1000000
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
	sa.initialise(0.9, 10, 0.85, 50, instance);
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONS_PER_RUN);

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

void runLS(vector<double> &currentResults,
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

void runIteratedGreedy(vector<double> &currentResults,
		vector<double> &bestSoFarResults, MSPInstance &instance) {

	//Initialization
	MSPSolution initialSolution(instance.getNumberOfLiterals());
	MSPIteratedGreedy ig;
	MSPStopCondition stopCond;
	MSPEvaluator::resetNumEvaluations();
	ig.initialise(0.25, instance);
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONS_PER_RUN);

	//Generate a first random solution
	MSPRandomSolution::genRandomSol(instance, initialSolution);
	double currentFitness = MSPEvaluator::computeFitness(instance,
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

void runGeneticAlgorithm(vector<double> &currentResults,
		vector<double> &bestSoFarResults, MSPInstance &instance) {

	//Initialization
	MSPGeneticAlgorithm ga;
	MSPStopCondition stopCond;
	MSPEvaluator::resetNumEvaluations();
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
}

int main(int argc, char** argv) {
	if(argc!=3){
		std::cout << BIRED << "Bad arguments" << RESET << std::endl;
		std::cout << "HELP" << std::endl;
		std::cout << "----" << std::endl;
		std::cout << BIYELLOW << argv[0] << " <instance_file> " << "<no_algorithm>" << RESET << std::endl;
		std::cout << std::endl << "Algorithms" << std::endl;
		std::cout << "----------" << std::endl;
		std::cout << BICYAN << "1 -> Random Search" << RESET << std::endl;
		std::cout << BICYAN << "2 -> LS First Improvement" << RESET << std::endl;
		std::cout << BICYAN << "3 -> LS Best Improvement" << RESET << std::endl;
		std::cout << BICYAN << "4 -> Simulated Annealing" << RESET << std::endl;
		std::cout << BICYAN << "5 -> Tabu Search" << RESET << std::endl;
		std::cout << BICYAN << "6 -> Iterated Greedy" << RESET << std::endl;
		std::cout << BICYAN << "7 -> GRASP" << RESET << std::endl;
		std::cout << BICYAN << "8 -> Genetic Algorithm" << RESET << std::endl;
		return 0;
	}
	int opcion = stoi(argv[2]);

	vector<double> *current = new vector<double>();
	vector<double> *best = new vector<double>();

	MSPInstance *instance = new MSPInstance();
	instance->readInstance(argv[1]);

	switch (opcion) {
	case 1:{
		runRandomFunction(*current, *best, *instance);
	}
	break;

	case 2:{
		FirstImprovement firstExplorer;
		runLS(*current, *best, *instance, firstExplorer);
	}
	break;

	case 3:{
		BestImprovement bestExplorer;
		runLS(*current, *best, *instance, bestExplorer);
	}
	break;

	case 4:{
		runSimulatedAnnealing(*current, *best, *instance);
	}
	break;

	case 5:{
		runTabuSearch(*current, *best, *instance);
	}
	break;

	case 6:{
		runIteratedGreedy(*current, *best, *instance);
	}
	break;

	case 7:{
		runGrasp(*current, *best, *instance);
	}
	break;

	case 8:{
		runGeneticAlgorithm(*current, *best, *instance);
	}
	break;

	default:
		std::cout << BIRED << "That algorithm does not exist" << RESET << std::endl;
		return 0;
	}

	for(unsigned i=0; i < current->size(); i++){
		std::cout << current->at(i) << " " << best->at(i) << std::endl;
	}

	return 0;
}
