#include "MSPInstance.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include "MSPSolution.h"
#include "Clause.h"

MSPInstance::MSPInstance()
{
	nClauses_=0;
	nLiterals_=0;
	instancesVector_.resize(0);
}

MSPInstance::~MSPInstance()
{
}


void MSPInstance::readInstance(char* fileName){
	std::ifstream file(fileName);
    char aux;
    file>>aux;
    std::string dummie;

    while(aux!='p'){
      	getline(file, dummie, '\n');
      	file>>aux;
    }
    file>>dummie>>nLiterals_>>nClauses_;
    int newLiteral;
    Clause newclause;
    while(file>>newLiteral){
    	if(newLiteral==0){
    		instancesVector_.push_back(newclause);
    		newclause.clean();
    	}
    	else newclause.addLiteral(newLiteral);
    }
    if(newclause.size()!=0) instancesVector_.push_back(newclause);

}

double MSPInstance::computeFitness( MSPSolution &solucion){
	double fit=0.0;
	for(int i=0;i<nClauses_;i++){
		if(instancesVector_[i].isTrue(solucion)) fit++;
	}
	solucion.setFitness(fit);
	return fit;
}

void MSPInstance::randomPermutationOfLiterals(std::vector<int>& perm) {

	perm.clear();

	for (int i = 1; i <= getNumberOfLiterals(); i++)
		perm.push_back(i);

	for (int i = 1; i <= getNumberOfLiterals(); i++){
		int pos = rand() % getNumberOfLiterals();
		int aux = perm[i];
		perm[i] = perm[pos];
		perm[pos] = aux;
	}
}

double MSPInstance::getDeltaFitness(const MSPSolution &solucion, int pos){
	double fitnessDiference=0.0;
	if(!solucion.isTrue(pos)){
		for(int i=0;i<nClauses_;i++){
			/*If the clause has the new boolean value and that clause used to be not fulfilled, now it is*/
			if(instancesVector_[i].has(-pos)){
				if(!instancesVector_[i].isTrue(solucion)){
					fitnessDiference++;
				}
			}
			/*If the clause has the old boolean value it can change to be not fulfilled*/
			if(instancesVector_[i].has(pos)){
				if(!instancesVector_[i].isTrue(solucion)){
					fitnessDiference--;
				}
			}
		}
	}
	else{
			for(int i=0;i<nClauses_;i++){
				/*If the clause has the new boolean value and that clause used to be not fulfilled, now it is*/
				if(instancesVector_[i].has(pos)){
					if(!instancesVector_[i].isTrue(solucion)){
						fitnessDiference++;
					}
				}
				/*If the clause has the old boolean value it can change to be not fulfilled*/
				if(instancesVector_[i].has(-pos)){
					if(!instancesVector_[i].isTrue(solucion)){
						fitnessDiference--;
					}
				}
			}
		}

	return fitnessDiference;
}



