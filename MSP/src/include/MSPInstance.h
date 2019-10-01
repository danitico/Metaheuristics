#ifndef SRC_INCLUDE_MSPINSTANCE_H_
#define SRC_INCLUDE_MSPINSTANCE_H_

#include <vector>
#include <fstream>
#include <string>
#include <MSPSolution.h>
#include <Clause.h>

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
	void randomPermutationOfLiterals( std::vector<int>& perm);
	int getNumberOfLiterals() const{return nLiterals_;}
	int getNumberOfClauses() const{return nClauses_;}
	double computeFitness( MSPSolution &solucion);
	double getDeltaFitness(MSPSolution &solucion, int pos);
	static double compare(double f1, double f2){
		return f1 - f2;
	}
};

#endif /*SRC_INCLUDE_MSPINSTANCE_H_*/
