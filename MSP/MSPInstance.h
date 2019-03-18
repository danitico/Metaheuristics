#ifndef MSPINSTANCE_H_
#define MSPINSTANCE_H_

#include <vector>
#include <fstream>
class MSPInstance
{
private:
	std::vector<bool> maxSatVector_;
	
public:
	MSPInstance();
	virtual ~MSPInstance();
	void readInstance(char* fileName);
};

#endif /*MSPINSTANCE_H_*/
