#ifndef MSPCHANGEOPERATION_H_
#define MSPCHANGEOPERATION_H_
#include <MSPSolution.h>
class MSPChangeOperation {
public:
	virtual ~MSPChangeOperation() {};
	virtual void apply(MSPSolution &solution) = 0;
};

#endif /* MSPCHANGEOPERATION_H_ */
