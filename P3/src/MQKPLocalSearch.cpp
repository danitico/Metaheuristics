/*
 * MQKPLocalSearch.cpp
 *
 * File defining the methods of the class MQKPLocalSearch.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <MQKPLocalSearch.h>
#include <MQKPInstance.h>
#include <MQKPSolution.h>
#include <MQKPNeighExplorer.h>
#include <MQKPObjectAssignmentOperation.h>

MQKPLocalSearch::MQKPLocalSearch() {
}

MQKPLocalSearch::~MQKPLocalSearch() {
}

void MQKPLocalSearch::optimise(MQKPInstance& instance,
		MQKPNeighExplorer& explorer, MQKPSolution& solution) {

	_results.clear();
	_results.push_back(solution.getFitness());
	MQKPObjectAssignmentOperation operation;

	/**
	 * 1. Apply once the exploration of the neighbourhood and store whether you have
	 *    been able to improve the solution or not
	 *
	 * 2. While you have been able to improve the solution
	 *   a. Apply the exploration of the change found in the previous exploration
	 *   b. Store the new fitness of the solution in _results
	 *   c. Apply a new exploration of the neighbourhood
	 */

	bool gotBetter = explorer.findOperation(instance, solution, operation);

	while (gotBetter) {
		operation.apply(solution);
		_results.push_back(solution.getFitness());
		gotBetter = explorer.findOperation(instance, solution, operation);
	}
}
