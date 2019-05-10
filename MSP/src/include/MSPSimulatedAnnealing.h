#ifndef SRC_INCLUDE_MSPSIMULATEDANNEALING_H_
#define SRC_INCLUDE_MSPSIMULATEDANNEALING_H_

#include <vector>
#include <MSPSolution.h>
#include <MSPInstance.h>
#include "MSPStopCondition.h"
#include <cstdlib>
class MSPSimulatedAnnealing {
private:
	double _T;
		double _initialProb;
		double _annealingFactor;
		unsigned _itsPerAnnealing;
		MSPSolution *_solution;
		MSPSolution _bestSolution;
		MSPInstance *_instance;
		std::vector<double> _results;
		bool accept(double deltafitness);
public:

			MSPSimulatedAnnealing(){
				_T = 0;
				_initialProb = 0;
				_annealingFactor = 0;
				_itsPerAnnealing = 0;
				_solution = NULL;
				_instance = NULL;
			}


			virtual ~MSPSimulatedAnnealing(){

				if (_bestSolution != NULL){
					delete _bestSolution;
					_bestSolution = NULL;
				}
			};
			void setSolution(MSPSolution* solution);
			virtual void run(MSPStopCondition &stopCondition);
			void initialise(double initialProb, int numInitialEstimates, double annealingFactor, unsigned itsPerAnnealing, MSPInstance &instance);
			std::vector<double>& getResults() {
					return _results;
				}
};

#endif /* SRC_INCLUDE_MSPSOLUTION_H_ */
