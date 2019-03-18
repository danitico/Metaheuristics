#ifndef SRC_INCLUDE_MSPINSTANCE_H_
#define SRC_INCLUDE_MSPINSTANCE_H_

#include <vector>
#include <fstream>
#include <string>
#include "MSPSolution.h"
#include "Clause.h"

class MSPInstance
{
private:
	std::vector<Clause> instancesVector_;
	int nLiterals_;
	int nClauses_;
public:
	MSPInstance();
	virtual ~MSPInstance();
	void readInstance(char* fileName);
	int getNumberOfLiterals() const{return nLiterals_;}
	int getNumberOfClauses() const{return nClauses_;}
	double computeFitness(const MSPSolution &solucion);
};

#endif /*SRC_INCLUDE_MSPINSTANCE_H_*/
