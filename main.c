#include <stdlib.h>
#include <stdio.h>

#include "ParseInput.h"

int main(int argc, char **argv){

//parse command line inputs
ParsedArgs *myIns = parseInput(argc - 1, argv+1);
if (myIns == NULL){ 
    printf("Invalid input.\n");
    return 1;
}

//TODO Cache simulation

return 0;
}
