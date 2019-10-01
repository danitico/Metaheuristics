/*
 * SelectionOperator.h
 *
 *  Created on: 15 may. 2019
 *      Author: chema969
 */

#ifndef INCLUDE_SELECTIONOPERATOR_H_
#define INCLUDE_SELECTIONOPERATOR_H_

#include <vector>
#include <MSPSolution.h>

using namespace std;
class SelectionOperator {
public:

	virtual ~SelectionOperator(){};
	virtual void select(vector<MSPSolution*> &orig, vector<MSPSolution*> &result) = 0;
};

#endif /* INCLUDE_SELECTIONOPERATOR_H_ */
