/*
 * MSPSolution.cpp
 *
 *  Created on: 18 mar. 2019
 *      Author: chema969
 */

#include "include/MSPSolution.h"
#include "include/MSPInstance.h"
MSPSolution::MSPSolution(const MSPInstance &instance) {
	solution_.resize(instance.getNumberOfLiterals()+1);
	// Auto-generated constructor stub

}

MSPSolution::~MSPSolution() {
	solution_.resize(0);
	solution_.shrink_to_fit();
	// Auto-generated destructor stub
}

 void MSPSolution::setBool(int i,bool v){
	 solution_[i]=v;
 }

 bool MSPSolution::isTrue(int pos) const{
	return solution_[pos];
}
