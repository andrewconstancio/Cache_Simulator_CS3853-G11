#include <stdlib.h>
#include <string.h>

#include "ParseInput.h"

//Struct to hold arguments
//struct _ParsedArgs;
//above moved to header file

//returns null on error
ParsedArgs *parseInput(int argc, char **argv)
{
    //5 bit number with each bit representing 
    int validCounter = 0;
    int i, j, k;
    ParsedArgs *myIns = (ParsedArgs *) malloc(sizeof(ParsedArgs));
    if(argc != 10){
       return NULL;
    }   
    else{
        //create ParsedArgs struct
//        ParsedArgs myIns;
        for( i = 0; i <= 10; i+=2 )
        {   
            if(strcmp(argv[i], "-f") == 0){ 
                //trace file name

                //get file name
                for(j = 0; argv[i+1][j] != '\0'; ++j){}
                char *traceName = (char *) malloc(sizeof(char)*j+2);
                
                //copy file name
                for(k = 0; k < j+2; k++){
                    traceName[k] = argv[i+1][k];
                }
                //add file name to myIns struct                    
                myIns->traceFileName = traceName;
                
                //set first bit of validCounter to 1
                validCounter = validCounter | 1;
            }   
            if(strcmp(argv[i], "-s") == 0){ 
                //get cache size
                myIns->cacheSize = -1;
                myIns->cacheSize = atoi(argv[i+1]);
                if(myIns->cacheSize > 8 || myIns->cacheSize < 1){
                    break;
                }
                validCounter = validCounter | 2; 
            }   
            if(strcmp(argv[i], "-b") == 0){ 
                //get block size
                myIns->blockSize = -1;
                myIns->blockSize = atoi(argv[i+1]);
                if(myIns->blockSize < 4 || myIns->blockSize > 64){
                    break;
                }
                validCounter = validCounter | 4;
            }   
            if(strcmp(argv[i], "-a") == 0){ 
                //get associativeity
                myIns->associativity = -1;
                myIns->associativity = atoi(argv[i+1]);
                if(myIns->associativity == 1 || myIns->associativity == 2 || myIns->associativity == 4 || myIns->associativity == 8 || myIns->associativity == 16){
                    validCounter = validCounter | 8;
                }
                else{
                    break;
                }

            }   
            if(strcmp(argv[i], "-r") == 0){ 
                //get replacement policy
                myIns->replacementVal = -1;
                if(strcmp(argv[i+1], "RND") == 0)
                {
                    myIns->replacementVal=0;
                    validCounter = validCounter | 16;
                }
                else if(strcmp(argv[i+1], "RR") == 0){
                    myIns->replacementVal = 1;
                }
                else{
                    break;
                }
                validCounter = validCounter | 16;
            }   
        }   
        //check if valid bit true
        if(validCounter != 31){
            return NULL;
        }
        return myIns;
    }   

}

