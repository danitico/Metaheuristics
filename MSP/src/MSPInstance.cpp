#include "include/MSPInstance.h"

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

double MSPInstance::computeFitness(const MSPSolution &solucion){
	double fit=0.0;
	for(int i=0;i<nClauses_;i++){
		if(instancesVector_[i].isTrue(solucion)) fit++;
	}
	return fit;
}


