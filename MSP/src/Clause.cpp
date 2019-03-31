/*
 * Clause.cpp
 *
 *  Created on: 18 mar. 2019
 *      Author: chema969
 */

#include "Clause.h"
#include <iostream>
Clause::Clause(){
	//  Auto-generated constructor stub

}

Clause::~Clause() {
	literals_.clear();
	//  Auto-generated destructor stub
}

bool Clause::isTrue(const MSPSolution &solution) const{

	for(std::set<int>::iterator i=literals_.begin();i!=literals_.end();i++){

		if(*i>0){
			if(solution.isTrue(*i)) return true;
		}

		else{
			if(!solution.isTrue(-*i)) return true;
		}
	}
	return false;
}

bool Clause::has(int literal){

	for(std::set<int>::iterator i=literals_.begin();i!=literals_.end();i++){
		if(literal==*i) return true;
		else if (literal>*i) return false;
	}
	return false;
}
