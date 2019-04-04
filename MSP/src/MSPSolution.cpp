/*
 * MSPSolution.cpp
 *
 *  Created on: 18 mar. 2019
 *      Author: chema969
 */

#include "include/MSPSolution.h"
#include "include/MSPInstance.h"
MSPSolution::MSPSolution(int numberOfLiterals) {
	solution_.resize(numberOfLiterals+1);
	fitness_=0;
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
