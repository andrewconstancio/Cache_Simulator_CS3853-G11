//header file for ParseInput.c

//Struct to hold arguments
typedef struct{
    char **traceFileName;
    int cacheSize;
    int blockSize;
    int associativity;
    // '0' for random, '1' for Round Robin, '2' for LRU 
    int replacementVal;
}ParsedArgs;



//parseInput takes input args, populates struct
ParsedArgs *parseInput(int, char **);

