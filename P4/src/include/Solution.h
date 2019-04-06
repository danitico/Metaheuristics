/**
 * Solution.h
 *
 * File defining the class Solution.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_SOLUTION_H_
#define INCLUDE_SOLUTION_H_

class Solution {
public:
	virtual ~Solution(){};

	virtual double getFitness() const = 0;

	virtual void copy(Solution&) = 0;
};



#endif /* INCLUDE_SOLUTION_H_ */
