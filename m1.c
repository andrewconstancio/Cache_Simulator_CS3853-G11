#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h> 

#include "ParseInput.h"

signed int binaryToHex(char* value) {
    char *a = value;
    int num = 0;
    do {
        int b = *a=='1'?1:0;
        num = (num<<1)|b;
        a++;
    } while (*a);

    return num;
}

void HexToBin(char* hexdec, int tag, int index, char* instLength) {
 
    long int i = 0;
    char binaryNum[33] = "";

    if( strlen(hexdec) != 8) {
        strcat(binaryNum, "0000");
    }

    while (hexdec[i]) {
 
        switch (hexdec[i]) {
        case '0':
            // printf("0000");
            strcat(binaryNum, "0000");
            break;
        case '1':
            // printf("0001");
            strcat(binaryNum, "0001");
            break;
        case '2':
            // printf("0010");
            strcat(binaryNum, "0010");
            break;
        case '3':
            // printf("0011");
            strcat(binaryNum, "0011");
            break;
        case '4':
            // printf("0100");
            strcat(binaryNum, "0100");
            break;
        case '5':
            // printf("0101");
            strcat(binaryNum, "0101");
            break;
        case '6':
            // printf("0110");
            strcat(binaryNum, "0110");
            break;
        case '7':
            // printf("0111");
            strcat(binaryNum, "0111");
            break;
        case '8':
            // printf("1000");
            strcat(binaryNum, "1000");
            break;
        case '9':
            // printf("1001");
            strcat(binaryNum, "1001");
            break;
        case 'A':
        case 'a':
            // printf("1010");
            strcat(binaryNum, "1010");
            break;
        case 'B':
        case 'b':
            // printf("1011");
            strcat(binaryNum, "1011");
            break;
        case 'C':
        case 'c':
            // printf("1100");
            strcat(binaryNum, "1100");
            break;
        case 'D':
        case 'd':
            // printf("1101");
            strcat(binaryNum, "1101");
            break;
        case 'E':
        case 'e':
            // printf("1110");
            strcat(binaryNum, "1110");
            break;
        case 'F':
        case 'f':
            // printf("1111");
            strcat(binaryNum, "1111");
            break;
        default:
            printf("\nInvalid hexadecimal digit");
        }
        i++;
    }

    int j = 0, k = 0, z = 28, l = 0;

    char tagValue[tag];
    char indexValue[tag];
    char offsetValue[5];

    int indexS = 28 - index;
    int tagS = 28 - index - tag;

    while (z <= 32) {
        offsetValue[l] = binaryNum[z];
        z++;
        l++;
    }

    while(indexS < 28) {
        indexValue[k] = binaryNum[indexS];
        k++;
        indexS++;
    }

    while(tagS < 28 - index) {
        tagValue[j] = binaryNum[tagS];
        j++;
        tagS++;
    }

    tagValue[j++] = '\0';
    indexValue[k++] = '\0';
    offsetValue[z++] = '\0';

    signed int offsetHEX = binaryToHex(offsetValue);
    signed int indexHEX = binaryToHex(indexValue);
    signed int tagHEX = binaryToHex(tagValue);

    printf("HEX INSTR: 0x%s\n", hexdec);
    printf("BINARY: %s\n", binaryNum);
    printf("OFF: %X\n", offsetHEX);
    printf("IND: %X\n", indexHEX);
    printf("TAG: %X\n", tagHEX);
    printf("INSTRLENGTH: %s\n", instLength);
    printf("\n");

    // printf("instLength %d\n", atoi(instLength));
    // printf("offsetValue %s\n", offsetValue);
    // printf("tagValue %s\n", tagValue);
    // printf("indexValue %s\n", indexValue);
    // printf("binaryNum %s\n", binaryNum);
}

void m1(ParsedArgs *myIns) {

    int cSize = myIns->cacheSize;
    int bSize = myIns->blockSize;
    int asso = myIns->associativity;
    char *rp;
        if(myIns->replacementVal == 0){
            rp = "Random";
        } 
        if(myIns->replacementVal == 1){
            rp = "Round-Robin";
        }
		if(myIns->replacementVal == 2){
            rp = "Last Recently Used";
        }
    printf("\n");


    printf("Trace File: %s\n", myIns->traceFileName);
    printf("\n");
    printf("***** Cache Input Parameters ***** \n");
    printf("Cache Size:                    %dKB\n", cSize);
    printf("Block Size:                    %d bytes\n", bSize);
    printf("Associativity:                 %d \n", asso);
    printf("Replacement Policy:            %s \n", rp);

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
    int act_size_bytes = act_size * 1024;

    //COST
    double cost = act_size * 0.09; // 9 cents per KB as per instruction file
	
	  printf("***** Cache Calculated Values *****\n\n");

    printf("Total # Blocks:               %d\n", block_total);
    printf("Tag Size:                     %d bits\n", tag);
    printf("Index Size:                   %d bits\n", index);
    printf("Total # Rows:                 %d\n", rows);
    printf("Overhead Size:                %d bytes\n", overhead);
    printf("Implementation Memory Size:   %d.00 KB	(%d bytes)\n", act_size, act_size_bytes);
    printf("Cost:                         $%.2lf\n", cost);
    printf("\n");

    int count = 0;
    int line_count = 1;
    char real_size[3];

    // Parse trace file
    while (fgets(line, sizeof(line), file)) {
        signed int address;
        signed int address_two;
        signed int address_three;
        char reg[20], temp[20], str[20];
        char size[5];

        if(line_count == 1) {
            sscanf(line, "%s %s %x", reg, size, &address);
            real_size[0] = size[1];
            real_size[1] = size[2];
            // printf("0x%x: 00%s\n", address, real_size); 
            sprintf(str, "%x", address);
            HexToBin(str, tag, index, real_size);
         } else if(line_count == 2) {
            sscanf(line, "%s %x %s %s %x %s", temp, &address_two, temp, temp, &address_three, temp);
            if(address_two > 0) {
                // printf("0x%x: 00%s\n", address_two, real_size);
                count++;
            }
            if(address_three > 0) {
                // printf("0x%x: 00%s\n", address_three, real_size);
                count++;
            }
        } else {
            line_count = 0;
        }

        line_count++;

        //TODO: TAKE THIS OUT
        if(count == 20) {
            break;
        }
    }

    fclose(file);
}

