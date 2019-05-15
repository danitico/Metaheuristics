/*
 * MSPSolution.cpp
 *
 *  Created on: 18 mar. 2019
 *      Author: chema969
 */

#include <MSPSolution.h>
MSPSolution::MSPSolution(int numberOfLiterals) {
	solution_.resize(numberOfLiterals+1);
	numlits_=numberOfLiterals;
	fitness_=0;
	_fitnessAssigned=false; //TODO READ This variable has been included to know which individuals have a fitness assigned
	// Auto-generated constructor stub

}

MSPSolution::~MSPSolution() {
	solution_.resize(0);
	// Auto-generated destructor stub
}

 void MSPSolution::setBool(int i,bool v){
	 solution_[i]=v;
 }

 bool MSPSolution::isTrue(int pos) const{
	return solution_[pos];
}
void MSPSolution::copy(MSPSolution &solution) {
	for (int i = 0; i < numlits_; i++)
		solution_[i] = solution.solution_[i];

	fitness_ = solution.fitness_;
  }
