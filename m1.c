#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h> 


int main() {

    int cSize = 128;
    int bSize = 16;
    int asso = 2;
    char rp[3] = "r";
    
    // BLOCK TOTAL
    int bit_value = cSize * 1024;
    int bit_block_value  = bSize * 8;
    int block_total = bit_value / bit_block_value;
    block_total = block_total * 8;

    printf("BLOCKS TOTAL: %d\n", block_total);

    //INDEX 
    double bit_block = log( bSize) / log( 2 );
    double bit_asso = log( asso ) / log( 2 );
    double bit_size = log( bit_value ) / log( 2 );

    int index  = ( int) bit_size - ( (int) bit_block + (int) bit_asso);

    printf("INDEX: %d\n", index);

    //TAG SIZE
    int tag = 32 -  (int) bit_block - index;
    printf("TAG: %d\n", tag);

    //NUMBER OF ROWS
    int rows = block_total / asso;
    printf("ROWS: %d\n", rows);

    //OVERHEAD
    int overhead = ((tag + 1) * block_total) / 8;
    printf("OVERHEAD: %d\n", overhead);

    //IMPLEMATION SIZE
    int overhead_convert = overhead / 1024;
    int act_size = cSize + overhead_convert;
    printf("IMPLEMATION SIZE: %dKB\n", act_size);

    //COST
    double cost = act_size * 0.09;
    printf("COST: $%.2lf\n", cost);


    FILE *file;
    char line[256];
    file = fopen("TestTrace.trc", "r+");

    int count = 0;
    int line_count = 1;

    while (fgets(line, sizeof(line), file)) {
        signed int address;
        signed int address_two;
        char reg[20];
        int size;


        // if(line_count == 1) {
            sscanf(line, "%s %d %x", reg, &size, &address);
        // } else if(line_count == 2) {
        //     // sscanf(line, "%s %x %s %s %x %s", reg, &size, &address, &address_two);
        // }
        if(strcmp(reg, "EIP") == 0) {
            printf("0x%x: %d\n", address, size);   
            count++;
            line_count  = 0;
            if(count == 20) {
                break;
            }
        }
    }

    fclose(file);

    return 0;
}
