//============================================================================
// Name        : aux.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "include/MSPInstance.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
	if(argc<2){
		std::cout<<"You must include at least one instance file"<<std::endl;
		return 0;
	}
	MSPInstance instance;
	instance.readInstance(argv[1]);
	std::cout<<instance.getNumberOfClauses()<<std::endl;
}
