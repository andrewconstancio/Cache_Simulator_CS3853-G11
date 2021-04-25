#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h> 

#include "ParseInput.h"
#include "ParseHex.h"

int fromBinary(const char *s) {
    return (int) strtol(s, NULL, 2);
 }

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
    struct cache newCache[rows][asso];
    int i, j;
    int missCount;
    int hitCount;
    int readCount;

    for(i = 0; i < rows; i++) {
        for(j = 0; j < asso; j++) {
            newCache[i][j].tag = (char *)malloc(sizeof(char)*(tag+1));
            newCache[i][j].valid = 0;
        } 
    }

    // Parse trace file
    while (fgets(line, sizeof(line), file)) {
        signed int address;
        signed int address_two;
        signed int address_three;
        char reg[20], temp[20], str[20];
        char size[5];  
        char binaryNum[100];
        char a[3][100];
        int addressArr[3];
        int cnt;
        
        //fine addresses in file
        if(line_count == 1) {
            sscanf(line, "%s %s %x", reg, size, &address);
            real_size[0] = size[1];
            real_size[1] = size[2];
            // printf("0x%x: 00%s\n", address, real_size); 
            sprintf(str, "%x", address);
            strcpy(binaryNum, "");
            HexToBin(str, binaryNum);
            strcpy(a[0], binaryNum);
            addressArr[0] = address;
            count++;
         } else if(line_count == 2) {
            addressArr[0] = -1;
            sscanf(line, "%s %x %s %s %x %s", temp, &address_two, temp, temp, &address_three, temp);
            if(address_two > 0) {
                count++;
                strcpy(binaryNum, "");
                HexToBin(str, binaryNum);
                strcpy(a[1], binaryNum);
                addressArr[1] = address_two;
            } else {
                strcpy(a[1], "");
                addressArr[1] = -1;
            }
            if(address_three > 0) {
                count++;
                strcpy(binaryNum, "");
                HexToBin(str, binaryNum);
                strcpy(a[2], binaryNum);
                addressArr[2] = address_three;
            } else {
                strcpy(a[2], "");
                addressArr[2] = -1;
            }
        } else {
            line_count = 0;
        }

        //loop through address array and add to cache
        for(cnt = 0; cnt < line_count; ++cnt) {
            if(strcmp(a[cnt], "") != 0 && addressArr[cnt] != -1) {
                int j = 0, k = 0, z = 28, l = 0;
                int oSize = log( bSize ) / log( 2 );
                char tagValue[tag];
                char indexValue[index];
                char offsetValue[oSize];
                int indexS = 32 - oSize - index;
                int tagS = 32 - oSize - index - tag;
                int iIndex;

                while (z <= 32) {
                    offsetValue[l] = a[cnt][z];
                    z++;
                    l++;
                }
    
                while(indexS < 32 - oSize) {
                    indexValue[k] = a[cnt][indexS];
                    k++;
                    indexS++;
                }
    
                while(tagS < 32 - oSize - index) {
                    tagValue[j] = a[cnt][tagS];
                    // printf("%d", tagValue[j]);
                    j++;
                    tagS++;
                }
    
                iIndex = fromBinary(indexValue);
    
                for(i = 0; i < asso; i++) {
                    if(newCache[iIndex][i].valid == 0) {
                        newCache[iIndex][i].valid = 1;
                        newCache[iIndex][i].tag = tagValue;
                        missCount += 1;
                        break;
                    } else if(newCache[iIndex][i].valid == 1) {
                        // if(strcmp(newCache[iIndex][i].tag, tagValue) == 0) {
                        //     hitCount += 1 
                        // }
                    } else {
                        // random replacement
                        int num = (rand() % (asso - 0 + 1)) + 0;
                        newCache[iIndex][num].tag = tagValue;
                    }
                }


                printf("INST: %x\n", atoi(real_size));

                // tagValue[j++] = '\0';
                indexValue[k++] = '\0';
                offsetValue[z++] = '\0';
                // printf("BLOCK: %d\n", bSize);
                // printf("SEE: %x\n", addressArr[cnt]);
                // printf("SEE2: %x\n", addressArr[cnt] + 4);
                // signed int off = binaryToHex(indexValue);
                // printf("%s\n", indexValue);
                // printf("%x\n", off);
    
            }
        }

        if(count == 20) {
            break;
        }

        line_count++;
    }

    printf("MISS: %d\n", missCount);


    fclose(file);
}


