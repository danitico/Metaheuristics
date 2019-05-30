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
	bool _fitnessAssigned; //This variable has been included to know which individuals have a fitness assigned
public:
	MSPSolution(int numberOfLiterals);
	MSPSolution(const MSPSolution &copy);
	virtual ~MSPSolution();
	bool isTrue(int pos) const;
	void setBool(int i,bool v);
	void setFitness(double fit){fitness_=fit;}
	double getFitness(){return fitness_;}
	void copy(MSPSolution &solution);
	bool hasValidFitness(){
		return _fitnessAssigned;
	}
};

#endif /* SRC_INCLUDE_MSPSOLUTION_H_ */
