/*
 * MSPSolution.h
 *
 *  Created on: 18 mar. 2019
 *      Author: chema969
 */

#ifndef SRC_INCLUDE_MSPSOLUTION_H_
#define SRC_INCLUDE_MSPSOLUTION_H_

#include <vector>
#include "MSPInstance.h"
class MSPSolution {
private:
	std::vector<bool> solution_;
public:
	MSPSolution(const MSPInstance &instance);
	virtual ~MSPSolution();
	bool isTrue(int pos) const;
	void setBool(int i,bool v);
};

#endif /* SRC_INCLUDE_MSPSOLUTION_H_ */
