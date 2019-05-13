/*
 * MSPSolution.h
 *
 *  Created on: 18 mar. 2019
 *      Author: chema969
 */

#ifndef SRC_INCLUDE_MSPSOLUTION_H_
#define SRC_INCLUDE_MSPSOLUTION_H_

#include <vector>

class MSPSolution {
private:
	std::vector<bool> solution_;
	int numlits_;
	double fitness_;
public:
	MSPSolution(int numberOfLiterals);
	virtual ~MSPSolution();
	bool isTrue(int pos) const;
	void setBool(int i,bool v);
	void setFitness(double fit){fitness_=fit;}
	double getFitness(){return fitness_;}
	void copy(MSPSolution &solution);
};

#endif /* SRC_INCLUDE_MSPSOLUTION_H_ */
