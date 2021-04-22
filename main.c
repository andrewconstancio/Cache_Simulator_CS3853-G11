#include <stdlib.h>
#include <stdio.h>

#include "ParseInput.h"
#include "m1.h"
#include "m2.h"

int main(int argc, char **argv){

	//print intro line
	printf("Cache Simulator CS 3853 Spring 2021 - Group #11\n"); // section 2.5 assignment sheet

	//parse command line inputs
	ParsedArgs *myIns = parseInput(argc - 1, argv+1);
	if (myIns == NULL){ 
		printf("Invalid input.\n");
		return 1;
	}

	// Make and print calculations
	m1(myIns);
	
	//TODO Cache simulation
  m2(myIns);

	//free parsed args
	free(myIns->traceFileName);
	free(myIns);
	myIns = NULL;

	return 0;
	
}
