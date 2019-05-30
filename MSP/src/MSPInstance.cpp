#include <MSPInstance.h>
#include <vector>
#include <fstream>
#include <string>
#include <cassert>
#include <iostream>
#include <cstdlib>
#include <MSPSolution.h>
#include <Clause.h>

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

	if(!file.is_open()){
		std::cout << fileName << std::endl;
		std::cout << "That instance file does not exist" << std::endl;
		exit(-1);
	}

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

	for (int i = 1; i <= getNumberOfLiterals(); i++){
		perm.push_back(i);
	}
	for (unsigned int i = 1; i < perm.size(); i++){
		int pos = rand() % getNumberOfLiterals();
		int aux = perm[i];
		perm[i] = perm[pos];
		perm[pos] = aux;
	}
}

double MSPInstance::getDeltaFitness(MSPSolution &solucion, int pos){

	assert(nLiterals_+1>pos&&pos>0);
	double fitnessDifference=0.0;

	MSPSolution *a = new MSPSolution(solucion);

	bool oldValue=a->isTrue(pos);
	double fit=a->getFitness();
	//	std::cout << fit << std::endl;
	if(oldValue==false)
	{
		a->setBool(pos,true);
		double newFit=computeFitness(*a);
		fitnessDifference=newFit-fit;
	}
	else
	{
		a->setBool(pos,false);
		double newFit=computeFitness(*a);
		fitnessDifference=newFit-fit;
	}
	return fitnessDifference;
}



