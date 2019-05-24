#include <MSPInstance.h>
#include <MSPSolution.h>
#include <MSPRandomSolution.h>
#include <MSPEvaluator.h>
#include <LocalSearch.h>
#include <FirstImprovement.h>
#include <Timer.h>
#include <cstdlib>
#include <iostream>
using namespace std;
extern unsigned int numSeeds;
extern unsigned int seeds[];
#define MAX_SECONS_PER_RUN 5
#define MAX_SOLUTIONS_PER_RUN 100000
#define MAX_INITIAL_SOLUTIONS 5

void runRandomFunction(MSPInstance instance, MSPSolution solution){
	int r=0;
	srand(seeds[r]); r++;
	MSPRandomSolution::genRandomSol(instance, solution);

	double Bestsol=instance.computeFitness(solution);
	MSPSolution bestSolution=solution;
	std::cout<<Bestsol<<" "<<Bestsol<<std::endl;
    for(int i=0;i<10000;i++){
    	srand(seeds[r]);seeds[r]+=rand()%100; r=(r+1)%numSeeds;
    	MSPRandomSolution::genRandomSol(instance, solution);
    	double currentsol=instance.computeFitness(solution);

    	if(currentsol>Bestsol){
    		bestSolution=solution;
    		Bestsol=currentsol;
    	}
    	std::cout<<currentsol<<" "<<Bestsol<<std::endl;
    }
}

void runFirstImprovement(MSPInstance instance, MSPSolution solution){
	Timer t;
	MSPEvaluator::resetNumEvaluations();
	srand(seeds[0]);
	FirstImprovement explorer;
	LocalSearch ls;
	MSPRandomSolution::genRandomSol(instance, solution);
	double currentSolution = instance.computeFitness(solution);
	double bestSolution = currentSolution;

	std::cout << currentSolution << " " << bestSolution << std::endl;
	int numInitialSolutions = 0;


	while(t.elapsed_time(Timer::VIRTUAL) <= MAX_SECONS_PER_RUN
			&& MSPEvaluator::getNumEvaluations() < MAX_SOLUTIONS_PER_RUN &&
			numInitialSolutions < MAX_INITIAL_SOLUTIONS){
		MSPRandomSolution::genRandomSol(instance, solution);
		currentSolution = instance.computeFitness(solution);

		if(currentSolution > bestSolution){
			bestSolution = currentSolution;
		}

		std::cout << currentSolution << " " << bestSolution << std::endl;

		ls.optimise(instance, explorer, solution);
		vector<double> &resultsLS = ls.getResults();

		for(auto solution : resultsLS){
			if(solution > bestSolution){
				bestSolution = solution;
			}

			std::cout << solution << " " << bestSolution << std::endl;
		}

		numInitialSolutions++;
	}
}

int main(int argc, char** argv) {
	if(argc<2){
		std::cout<<"You must include at least one instance file"<<std::endl;
		return 0;
	}
	MSPInstance instance;
	instance.readInstance(argv[1]);
	MSPSolution solution(instance.getNumberOfLiterals());

//	runRandomFunction(instance, solution);
	runFirstImprovement(instance, solution);
}
