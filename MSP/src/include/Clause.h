/*
 * Clause.h
 *
 *  Created on: 18 mar. 2019
 *      Author: chema969
 */

#ifndef SRC_INCLUDE_CLAUSE_H_
#define SRC_INCLUDE_CLAUSE_H_
#include <vector>

#include "MSPSolution.h"

class Clause {
private:
	std::vector <int> literals_;
public:
	Clause();
	virtual ~Clause();
	void addLiteral(int literal){literals_.push_back(literal);}
	void clean(){literals_.clear();}
	int size() const{return literals_.size();}
	bool isTrue(const MSPSolution &solution)const;
};

#endif /* SRC_INCLUDE_CLAUSE_H_ */
