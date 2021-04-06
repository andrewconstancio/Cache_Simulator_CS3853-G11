#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h> 

#include "ParseInput.h"


void m1(ParsedArgs *myIns) {

    int cSize = myIns->cacheSize;
    int bSize = myIns->blockSize;
    int asso = myIns->associativity;
    char rp[3] = "";
    printf("\n");


    printf("Trace File: %s\n", myIns->traceFileName);
    printf("\n");
    printf("***** Cache Input Parameters ***** \n");
    printf("Cache Size:                    %dKB\n", cSize);
    printf("Block Size:                    %d bytes\n", bSize);
    printf("Associativity:                 %d \n", asso);
    printf("Replacement Policy:            \n");

    printf("\n");

    FILE *file;
    char line[256];
    file = fopen(myIns->traceFileName, "r");

    if (file == NULL){
        printf("file does not exist?!\n");
        exit(1);
    }

    // BLOCK TOTAL
    int bit_value = cSize * 1024;
    int bit_block_value  = bSize * 8;
    int block_total = bit_value / bit_block_value;
    block_total = block_total * 8;

    //INDEX 
    double bit_block = log( bSize) / log( 2 );
    double bit_asso = log( asso ) / log( 2 );
    double bit_size = log( bit_value ) / log( 2 );

    int index  = ( int) bit_size - ( (int) bit_block + (int) bit_asso);


    //TAG SIZE
    int tag = 32 -  (int) bit_block - index;


    //NUMBER OF ROWS
    int rows = block_total / asso;

    //OVERHEAD
    int overhead = ((tag + 1) * block_total) / 8;

    //IMPLEMATION SIZE
    int overhead_convert = overhead / 1024;
    int act_size = cSize + overhead_convert;

    //COST
    double cost = act_size * 0.09; // 9 cents per KB as per instruction file

    printf("Total # Blocks:               %d\n", block_total);
    printf("Tag Size:                     %d bits\n", tag);
    printf("Index Size:                   %d bits\n", index);
    printf("Total # Rows:                 %d\n", rows);
    printf("Overhead Size:                %d bytes\n", overhead);
    printf("Implementation Memory Size:   %d\n", act_size);
    printf("Cost:                         %.2lf\n", cost);


    printf("\n");

    int count = 0;
    int line_count = 1;
    char real_size[3];

    while (fgets(line, sizeof(line), file)) {
        signed int address;
        signed int address_two;
        signed int address_three;
        char reg[20], temp[20];
        char size[5];

        
        if(line_count == 1) {
            sscanf(line, "%s %s %x", reg, size, &address);
            real_size[0] = size[1];
            real_size[1] = size[2];
            printf("0x%x: 00%s\n", address, real_size); 
            count++;
         } else if(line_count == 2) {
            sscanf(line, "%s %x %s %s %x %s", temp, &address_two, temp, temp, &address_three, temp);
            if(address_two > 0) {
                printf("0x%x: 00%s\n", address_two, real_size);
                count++;
            }
            if(address_three > 0) {
                printf("0x%x: 00%s\n", address_three, real_size);
                count++;
            }
        } else {
            line_count = 0;
        }

        line_count++;

        if(count == 20) {
            break;
        }
    }

    fclose(file);
	
}
