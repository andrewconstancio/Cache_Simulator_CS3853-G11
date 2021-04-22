#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h> 

#include "ParseInput.h"

void m2(ParsedArgs *myIns) {

  // Parse the file (do we want to move this to parse input.c???)

  FILE *file;
  char line[256];
  file = fopen(myIns->traceFileName, "r");
   
  if (file == NULL){
        printf("file does not exist?!\n");
        exit(1);
  }
  
  fclose(file);
  
  // BEGIN CALCULATION "Cache Simulation Results"
  
  // BEGIN CALCULATION "CACHE HIT & MISS RATE"
  
  double hitRate = 0;
  double missRate = 0;
  double cpi = 0;
  double usedCacheSpaceKB = 0;
  double totalCacheSpaceKB = 0;
  double cacheSpacePercentUsage = 0;
  double cacheSpaceWasteDollars = 0;
  int unusedCacheBlocks = 0;
  int totalCacheBlocks = 0;
  
  printf("***** ***** CACHE HIT & MISS RATE: ***** *****\n\n");
  
  printf("Hit Rate:            %.4lf%\n", hitRate);
  printf("Miss Rate:           %.4lf%\n", missRate);
  printf("CPI:                 %.2lf Cycles/Instruction\n", cpi);
  printf("Unused Cache Space:  %.2lf KB / %.2lf KB = %.2lf% Waste: $%.2lf\n", usedCacheSpaceKB, totalCacheSpaceKB, cacheSpacePercentUsage, cacheSpaceWasteDollars);
  printf("Unused Cache Blocks: %d / %d\n", unusedCacheBlocks, totalCacheBlocks);

}