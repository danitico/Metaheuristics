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
	static unsigned _numEvaluations;
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
	double getDeltaFitness(const MSPSolution &solucion, int pos);
	static unsigned getNumEvaluations() {
			return _numEvaluations;
		}
	static double compare(double f1, double f2){
			return f1 - f2;
		}
	void resetNumEvaluations() {
		_numEvaluations = 0;
};

#endif /*SRC_INCLUDE_MSPINSTANCE_H_*/
