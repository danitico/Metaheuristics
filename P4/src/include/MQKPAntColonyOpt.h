/**
 * MQKPAntColonyOpt.h
 *
 * File defining the class MQKPAntColonyOpt.
 *
 * It is a part of the skeleton code provided for the MQKP, as a part of the module Metaheuristics of the
 * "Grado de Ingeniería Informática" of the University of Córdoba (Spain).
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_MQKPANTCOLONYOPT_H_
#define INCLUDE_MQKPANTCOLONYOPT_H_

#include <MQKPMetaheuristic.h>
#include <MQKPInstance.h>
#include <MQKPSolution.h>
#include <MQKPObjectAssignmentOperation.h>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <cmath>

using namespace std;

/**
 * Class implementing an ant colony system for the MQKP.
 */

class MQKPAntColonyOpt: public MQKPMetaheuristic {

	/**
	 * Class which internally implements an ant for the MQKP
	 */
	class MQKPAnt {
	protected:

		/**
		 * Properties of the class
		 * Basic:
		 *  _colony pointer to the class which includes it (its colony)
		 *  _sol solution for which the ant is working
		 *
		 * Additional:
		 *  _objectsLeft Set of objects which have not been included in any knapsack
         *               This variable is used for accelerating the process of construction
         *               of solutions. Its objective is making the process more efficient
		 *  _candidateListSize Number of options to consider when including a new component in
		 *                     the solution. This variable also accelerate the construction process
		 *                     avoiding the consideration of all possible solutions.
		 */
		MQKPAntColonyOpt *_colony;
		MQKPSolution *_sol;
		unordered_set<unsigned> _objectsLeft;
		double _candidateListSize;

		/**
		 * Function which sums the values of a vector. It will be used to know the sum of the values
		 * of relevance from the different options the ant has
		 * @param[in] significances Vector with the relevance of the options of the ant
		 * @return sum of the values of the relevance vector
		 */
		double sumSignificances(vector<double> &significances) {

			int sum= std:: accumulate(significances.begin(), significances.end(), 0);

			return sum;
		}

		/**
		 * Functions which returns the set of alternatives that an ant has when adding a new component
		 * to its solution.
		 * @param[out] alternatives Vector where the different alternative are stored
		 * @param[out] significances Vector with the relevance of the different alternatives created
		 */
		void createAlternatives(
				vector<MQKPObjectAssignmentOperation*> &alternatives,
				vector<double> &significances) {

			//Obtain the information of the ant
			MQKPInstance *instance = _colony->_instance;
			double alpha = _colony->_alpha;
			double beta = _colony->_beta;
			vector<vector<double>*> &phMatrix = _colony->_phMatrix;

			unsigned numKnapsacks = instance->getNumKnapsacks();
			unsigned numTries = 0;

			//For each object which is not in a knapsack
			for (auto indexObj : _objectsLeft) {

				//For each possible knapsack and without reaching the maximum number of tries
				for (unsigned j = 1;
						j <= numKnapsacks && numTries < _candidateListSize;
						j++) {

					//If the movement violates the capacity of the knapsack, discard it
					double maxViolation =
							instance->getDeltaMaxCapacityViolation(*_sol,
									indexObj, j);

					if (maxViolation > 0)
						continue;

					//Obtain the deltaFitness and count this as a try (given that we have previously checked
					//that there is no violation, the deltaFitness will be DeltaSumProfits)
					double deltaFitness = instance->getDeltaSumProfits(*_sol,
							indexObj, j);
					numTries++;

					//Ignore those options with worse fitness or the same fitness
					//(they should not happen if the profits are always positive, but
					// just in case...)
					if (deltaFitness <= 0)
						continue;

					/**
					 * 1. Create the operation
					 * 2. Obtain its relevance as densityOfTheObject^beta * amountOfPheromona^alpha
					 * 3. Include the operation in the alternatives and the relevance in significances
					 */
					MQKPObjectAssignmentOperation *al =
							new MQKPObjectAssignmentOperation();
					double density = deltaFitness
							/ instance->getWeight(indexObj);
					al->setValues(indexObj, j, deltaFitness);
					alternatives.push_back(al);
					double significance = pow(density, beta)
							* pow(phMatrix.at(indexObj)->at(j), alpha);
					significances.push_back(significance);
				}
			}
		}

		/**
		 * Function returning the best alternative of the ant when including a new component
		 * in the considered solution, from a set of alternatives randomly evaluated.
		 * @param[out] op Alternative selected as the best one for the ant
		 */
		void selectBestAlternative(MQKPObjectAssignmentOperation &op) {

			//Obtain the information of the colony
			MQKPInstance *instance = _colony->_instance;
			vector<vector<double>*> &phMatrix = _colony->_phMatrix;
			double beta = _colony->_beta;
			double alpha = _colony->_alpha;

			unsigned numKnapsacks = instance->getNumKnapsacks();
			double bestSignificance = -1;
			unsigned numTries = 0;

			//For each object which is not in the any knapsack
			for (auto indexObj : _objectsLeft) {

				//For each possible knapsack and without reaching the maximum number of tries
				for (unsigned j = 1;
						j <= numKnapsacks && numTries < _candidateListSize;
						j++) {
					// Obtain deltaMaxCapacityViolation and, if the movement violates
					// the capacity of the knapsack, discard it
					double deltaMaxCapacityViolation =instance->getDeltaMaxCapacityViolation(*_sol,
														indexObj, j);
					if (deltaMaxCapacityViolation > 0)
											continue;
					//Obtain the deltaFitness and count this as a try (given that we have previously checked
					//that there is no violation, the deltaFitness will be DeltaSumProfits)
					double deltaFitness = instance->getDeltaSumProfits(*_sol,indexObj, j);
										numTries++;
					// Ignore those options with worse fitness or the same fitness
					// by using a "continue"
					//(they should not happen if the profits are always positive, but
					// just in case...)
					if (deltaFitness <= 0)continue;

					/**
					 * 1. Obtain its relevance as densityOfTheObject^beta * amountOfPheromone^alpha
					 * 2. If it is better than the best-so-far solution, store it in op
					 */
					double density = deltaFitness/ instance->getWeight(indexObj);
					double significance = pow(density, beta)* pow(phMatrix.at(indexObj)->at(j), alpha);
					if (significance>bestSignificance)
					{
						bestSignificance=significance;
						op->setValues(indexObj,j,deltaFitness);
					}
				}
			}
		}

		/**
		 * Function which frees the memory of the alternatives created by the ant
		 * @param[in,out] alt Vector with the alternatives to be freed
		 */
		void freeAlternatives(vector<MQKPObjectAssignmentOperation*> &alt) {

			for (auto altOp : alt) {
				delete altOp;
			}

			alt.clear();
		}

	public:

		/**
		 * Constructor of an ant
		 * @param[in] candidateListSize Number of solutions to be evaluated in each step
		 * @param[in] colony Pointer to the colony which includes this ant
		 */
		MQKPAnt(unsigned candidateListSize, MQKPAntColonyOpt *colony) {
			_colony = colony;
			_sol = new MQKPSolution(*(colony->_instance));
			_candidateListSize = candidateListSize;
		}

		/**
		 * Destructor
		 */
		~MQKPAnt() {
			delete _sol;
			_sol = NULL;
		}

		/**
		 * Function which rests the memory of the ant so that it can start generating
		 * a solution from the beginning
		 */
		void resetSolution() {

			/**
			 *
			 * 1. Assign all the objects to the knapsack 0 and insert them in the memory _objectsLeft
			 * 2. Assign a zero fitness
			 */
			int numObjs=instance->getNumObjs();
			_sol.assign(numObjs,0);
			for(int i=0;i<=numObjs;i++)
			{
				_objectsLeft.insert(i);
			}
			_sol->MQKPSolution::setFitness(0);
		}

		/**
		 * Function which makes the ant select an alternative and include it in its solution.
		 * It also returns the option selected
		 * @param[out] operation Assignment operation of an object to a knapsack selected by the ant
		 */
		void chooseOperation(MQKPObjectAssignmentOperation &operation) {

			//Decide between using the best alternative or selecting the alternative according to probabilities
			double randSample = (((double) rand()) / RAND_MAX);

			if (randSample < _colony->_q0) {
				selectBestAlternative(operation);
			} else {

				//Create the alternatives
				vector<MQKPObjectAssignmentOperation*> alternatives;
				vector<double> significances;
				createAlternatives(alternatives, significances);

				//If the ant did not find alternatives, exit
				if (significances.size() <= 0) {
					return;
				}

				//Select one of the alternatives according to some probabilities which
				//are proportional to the relevances
				double v_sumSignificances = sumSignificances(significances);
				double randSample = (((double) rand()) / RAND_MAX)
						* v_sumSignificances;
				randSample -= significances.at(0);
				unsigned opSelected = 0;

				while (randSample>0) {
					opSelected+=1;
					randSample-=significances(opSelected);
				}

				//Assign the alternative selected in opSelected
				unsigned indexObj = alternatives.at(opSelected)->getObj();
				unsigned indexKnapsack =
						alternatives.at(opSelected)->getKnapsack();
				double deltaFitness =
						alternatives.at(opSelected)->getDeltaFitness();
				operation.setValues(indexObj, indexKnapsack, deltaFitness);

				//Free the memory of the alternatives
				freeAlternatives(alternatives);
			}

			//If an alternative was selected, apply it to the solution
            //and delete the corresponding object from _objectsLeft
			if (int obj=operation.getObj() >= 0) {
				operation.apply(_sol);
				auto pos= _objectsLeft.find(obj);
				_objectsLeft.erase(pos);
			}
		}

		/**
		 * Function which returns the solution constructed by the ant
		 * @return Solution constructed by the ant
		 */
		MQKPSolution & getSolution() {
			return *_sol;
		}
	};

protected:

	/**
	 * Properties of the ant colony
	 *  _q0 Probability that an ant select the best alternative instead of a random one
	 *  _alpha Importance of the amount of pheromone when calculating the relevance of each alternative
	 *  _beta Importance of the heuristic information when obtaining the relevance of each alternative
	 *  _initTau Amount of initial pheromone in the surrounding (it should not be 0)
	 *  _evaporation Percentage of pheromone which evaporates
	 *  _phMatrix 2D pheromone matrix. The first index is for the objects of the problems. The second
	 *            index is for the knapsacks
	 *  _ants Vector with the ants of the colony
	 *  _instance Instance of the problem considered
	 */
	double _q0;
	double _alpha;
	double _beta;
	double _initTau;
	double _evaporation;
	vector<vector<double>*> _phMatrix;
	vector<MQKPAnt*> _ants;
	MQKPInstance *_instance;

	/**
	 * Vectors where the results will be stored
	 *  _results Fitness values of the solutions generated
	 *  _bestPerIteration Best fitness obtained in each iteration
	 *  _currentItMeans Average fitness value of the solutions generated in each iteration
	 */
	vector<double> _results;
	vector<double> _bestPerIteration;
	vector<double> _currentItMeans;

	/**
	 * Function which performs a local update of the pheromone (when an ant walks, it takes
	 * part of the pheromone)
	 * @param[in] op Option which the ant selected, for which the update is going to be applied
	 */
	void localUpdate(MQKPObjectAssignmentOperation &op) {
		// TODO
		// New pheremone value has to be stored in the matrix _phMatrix
		// The new value will be equal to ((1-_evaporation)*oldValue)+(evaporation*_initTau)
		...
	}

	/**
	 * Function which releases ants for constructing their solutions
	 */
	void releaseAnts() {

		unordered_set<unsigned> movingAnts;
		unordered_set<unsigned> stoppedAnts;
		int i = 0;

		//TODO Reset the solutions of each ant (using the corresponding method)
		// and insert the index in moving ants
		for (auto ant : _ants) {
			...
			i++;
		}

		//While there are ants which are moving
		while (movingAnts.size() > 0) {
			stoppedAnts.clear();

			//TODO Move each ant
			for (auto iAnt : movingAnts) {
				MQKPAnt *ant = _ants[iAnt];
				MQKPObjectAssignmentOperation op;
				op.setValues(-1, -1, 0);
				... // Choose the operation calling to the method

				//TODO If the ant has moved, then apply the local update of the pheromone.
				//If not, insert it in stoppedAnts to be removed from from movingAnts
				if (...) {
					...
				} else {
					...
				}
			}

			for (auto iAnt : stoppedAnts) {
				movingAnts.erase(iAnt);
			}
		}

		//Update the best solution
		double bestFitness = _bestSolution->getFitness();

		for (auto ant : _ants) {
			MQKPSolution &sol = ant->getSolution();
			double currentFitness = ant->getSolution().getFitness();

			if (MQKPEvaluator::compare(currentFitness, bestFitness) > 0) {
				_bestSolution->copy(sol);
				bestFitness = currentFitness;
			}
		}
	}

	/**
	 * Function which stores statistics about the solutions generated in the property vectors
	 */
	void saveStatistics() {

		MQKPSolution &firstSol = _ants.at(0)->getSolution();
		double bestFitness = firstSol.getFitness();
		double meanFitness = 0.;
		unsigned numAnts = (unsigned) _ants.size();
		double inverseNumAnts = 1. / numAnts;

		for (auto ant : _ants) {
			MQKPSolution &sol = ant->getSolution();
			double currentFitness = sol.getFitness();
			_results.push_back(currentFitness);
			meanFitness += (currentFitness * inverseNumAnts);

			if (MQKPEvaluator::compare(currentFitness, bestFitness) > 0) {
				bestFitness = currentFitness;
			}
		}

		_bestPerIteration.push_back(bestFitness);
		_currentItMeans.push_back(meanFitness);
	}

	/**
	 * Function which runs a iteration of the ACO algorithm, that is:
	 * 1. Release the ants to construct their solutions.
     * 2. Update the pheromone matrix based on the best solution.
	 */
	void iterate() {

		//TODO Release the ants
		...
		saveStatistics();

		//Apply pheromone with the best solution
		unsigned numObjs = _instance->getNumObjs();
		double fitness = _bestSolution->getFitness();

		//TODO For each object, deposit the pheromone of the best solution
		// in the pair (object,knapsack) where the object is positioned.
		// The new value is equal to (1-_evaporation) * oldValue + (_evaporation * fitness)
		// The new value is assigned only if it is higher than _initTau
		for (unsigned i = 0; i < numObjs; i++) {
			...
		}
	}

public:
	/**
	 * Constructor
	 */
	MQKPAntColonyOpt() {
		_bestSolution = NULL;
		_q0 = 0.8;
		_alpha = 1;
		_beta = 1;
		_initTau = 0.1;
		_evaporation = 0.1;
		_instance = NULL;
	}

	/**
	 * Destructor
	 */
	~MQKPAntColonyOpt() {

		if (_bestSolution != NULL) {
			delete _bestSolution;
			_bestSolution = NULL;
		}

		for (auto ant : _ants) {
			delete ant;
		}
		_ants.clear();

		for (auto vector : _phMatrix) {
			vector->clear();
			delete vector;
		}

		_phMatrix.clear();
	}

	/**
	 * Function which initializes the algorithm
	 * @param[in] numAnts Number of ants in the colony
	 * @param[in] q0 Probability that an ant select the best alternative instead of a random one
	 * @param[in] alpha Importance of the amount of pheromone when calculating the relevance of each alternative
	 * @param[in] beta Importance of the heuristic information when obtaining the relevance of each alternative
	 * @param[in] initTau Amount of initial pheromone in the surrounding (it should not be 0)
	 * @param[in] evaporation Percentage of pheromone which evaporates
	 * @param[in] candidateListSize Number of alternative that each ant evaluates when selecting one option to
	 *                              be included in the solution
	 * @param[in] instance Instance of the problem considered
	 */
	void initialise(unsigned numAnts, double q0, double alpha, double beta,
			double initTau, double evaporation, unsigned candidateListSize,
			MQKPInstance &instance) {
		_instance = &instance;
		_q0 = q0;
		_alpha = alpha;
		_beta = beta;
		_initTau = initTau;
		_evaporation = evaporation;

		if (numAnts <= 0) {
			cerr << "The number of ants must be greater than 0" << endl;
			exit(1);
		}

		if (_bestSolution != NULL) {
			delete _bestSolution;
			_bestSolution = NULL;
		}

		//Generation of an initial solution for _bestSolution
		_bestSolution = new MQKPSolution(*_instance);
		MQKPSolGenerator::genRandomSol(*_instance, *_bestSolution);
		double fitness = MQKPEvaluator::computeFitness(*_instance,
				*_bestSolution);
		_bestSolution->setFitness(fitness);


		//TODO Generation of the ants: create empty ants (using the constructor) and include them in _ants
		for (unsigned i = 0; i < numAnts; i++) {
			...
		}


		//TODO Initialization of the pheromone matrix by using _initTau
		unsigned numObjs = _instance->getNumObjs();
		unsigned numKnapsacks = _instance->getNumKnapsacks() + 1;

		for (unsigned i = 0; i < numObjs; i++) {
			vector<double> *aVector = new vector<double>;
			_phMatrix.push_back(aVector);

			for (unsigned j = 0; j < numKnapsacks; j++) {
				aVector->push_back(...); //Use _initTau
			}
		}
	}

	/**
	 * Function which runs the ACO algorithm
	 * @param[in] stopCondition Object which defines when the stop condition is reached
	 */
	virtual void run(MQKPStopCondition &stopCondition) {

		if (_instance == NULL) {
			cerr << "The ACO algorithm has not been initialised" << endl;
			exit(1);
		}

		//TODO While the stop condition is not met, call to the iterate method
		while (stopCondition.reached() == false) {
			...
			stopCondition.notifyIteration();
		}
	}

	/**
	 * Function which returns the vector with the fitness of the best solutions generated per iteration
	 * @return Fitness of the best solutions generated per iteration
	 */
	const vector<double>& getBestPerIteration() const {
		return _bestPerIteration;
	}

	/**
	 * Function which returns the vector with the average fitness value of the solutions generated per iteration
	 * @return Average fitness value of the solutions generated per iteration
	 */
	const vector<double>& getAntsMeanResults() const {
		return _currentItMeans;
	}

	/**
	 * Function which returns the fitness of the solutions generated in each moment
	 * @return Fitness of the solutions generated in each moment
	 */
	vector<double>& getResults() {
		return _results;
	}
};

#endif /* INCLUDE_MQKPANTCOLONYOPT_H_ */
