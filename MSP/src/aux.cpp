//============================================================================
// Name        : aux.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "MSPInstance.h"
#include "MSPSolution.h"
#include "MSPRandomSolution.h"
#include <cstdlib>
#include <iostream>
using namespace std;
extern unsigned int numSeeds;
extern unsigned int seeds[];

int main(int argc, char** argv) {
	if(argc<2){
		std::cout<<"You must include at least one instance file"<<std::endl;
		return 0;
	}
	MSPInstance instance;
	instance.readInstance(argv[1]);
	MSPSolution solution(instance.getNumberOfLiterals());
	int r=0;
	srand(seeds[r]); r++;
	MSPRandomSolution::genRandomSol(instance, solution);

	double sol=instance.computeFitness(solution);
	MSPSolution bestSolution=solution;
	std::cout<<sol<<" "<<sol<<std::endl;
    for(int i=0;i<10000;i++){
    	srand(seeds[r]);seeds[r]+=rand()%100; r=(r+1)%numSeeds;
    	MSPRandomSolution::genRandomSol(instance, solution);
    	double newsol=instance.computeFitness(solution);
    	if(newsol>sol){
    		bestSolution=solution;
    		sol=newsol;
    	}
    	std::cout<<newsol<<" "<<sol<<std::endl;
    }

}
