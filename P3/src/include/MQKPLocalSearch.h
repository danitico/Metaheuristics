/**
 * MQKPLocalSearch.h
 *
 * File defining the class MQKPLocalSearch.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_MQKPLOCALSEARCH_H_
#define INCLUDE_MQKPLOCALSEARCH_H_

#include <MQKPInstance.h>
#include <MQKPSolution.h>
#include <MQKPNeighExplorer.h>

/**
 * Class implementing an iterative local search applied to a given random solution
 */
class MQKPLocalSearch{

	/**
	 * Double vector storing the quality of the last solution accepted
	 */
	vector<double> _results;

public:
	/**
	 * Constructor
	 */
	MQKPLocalSearch();

	/**
	 * Destructor
	 */
	~MQKPLocalSearch();

	/**
	 * Function optimising the solution applying iteratively the exploration of
	 * its neighbourhood until reaching a local optimum
	 * @param[in] instance Instance of the MQKP
	 * @param[in] explorer Operator for exploring the neighbourhood. The idea is that the neighbourhood will be
	 *                     explored in two alternative ways: use the first operator which improves the current
	 *                     solution, use the operator which leads to the best possible improvement.
	 * @param[in,out] solution Initial solution, i.e. starting point from which the solution will be improved.
	 *                     The final solution will be also stored in this reference.
	 */
	void optimise(MQKPInstance &instance, MQKPNeighExplorer &explorer, MQKPSolution &solution);

	/**
	 * Function returning a vector with the results of the solutions accepted by the local search in each step.
	 *
	 * @return vector with the accepted solution in each step of the local search.
	 */
	vector<double>& getResults() {
		return _results;
	}
};



#endif /* INCLUDE_MQKPLOCALSEARCH_H_ */
