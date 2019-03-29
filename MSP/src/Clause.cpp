/*
 * Clause.cpp
 *
 *  Created on: 18 mar. 2019
 *      Author: chema969
 */

#include "include/Clause.h"

Clause::Clause() {
	literals_.resize(0);
	//  Auto-generated constructor stub

}

Clause::~Clause() {
	literals_.clear();
	literals_.shrink_to_fit();
	//  Auto-generated destructor stub
}

bool Clause::isTrue(const MSPSolution &solution) const{
	for(int i=0;i<literals_.size();i++){
		if(literals_[i]>0){
			if(solution.isTrue(literals_[i])) return true;
		}
		else{
			if(!solution.isTrue(-literals_[i])) return true;
		}
	}
	return false;
}

