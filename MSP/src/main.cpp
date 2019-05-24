#include <MSPInstance.h>
#include <MSPSolution.h>
#include <MSPRandomSolution.h>
#include <cstdlib>
#include <iostream>
using namespace std;
extern unsigned int numSeeds;
extern unsigned int seeds[];

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

int main(int argc, char** argv) {
	if(argc<2){
		std::cout<<"You must include at least one instance file"<<std::endl;
		return 0;
	}
	MSPInstance instance;
	instance.readInstance(argv[1]);
	MSPSolution solution(instance.getNumberOfLiterals());

	runRandomFunction();

}
