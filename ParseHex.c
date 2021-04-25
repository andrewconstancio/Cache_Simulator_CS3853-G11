#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h> 

#include "ParseHex.h"

//Struct to hold arguments
//struct _CacheCol;
//above moved to header file

void HexToBin(char* hexdec, char *binaryNum) {
// void HexToBin(char* hexdec, int tag, int index, char* instLength, char type, int asso, int bSize, BinaryValues bin) {
 
    long int i = 0;

    if(strlen(hexdec) != 8) {
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

    binaryNum[32] = '\0';

    // int j = 0, k = 0, z = 28, l = 0;
    // int oSize = log( bSize ) / log( 2 );

    // char tagValue[tag];
    // char indexValue[tag];
    // char offsetValue[oSize];

    // int indexS = 32 - oSize - index;
    // int tagS = 32 - oSize - index - tag;

    // while (z <= 32) {
    //     offsetValue[l] = binaryNum[z];
    //     z++;
    //     l++;
    // }

    // while(indexS < 32 - oSize) {
    //     indexValue[k] = binaryNum[indexS];
    //     k++;
    //     indexS++;
    // }

    // while(tagS < 32 - oSize - index) {
    //     tagValue[j] = binaryNum[tagS];
    //     j++;
    //     tagS++;
    // }

    // tagValue[j++] = '\0';
    // indexValue[k++] = '\0';
    // offsetValue[z++] = '\0';

    // CacheRow row;

    // if(strcmp(row.index, "") == 0) {
    //     printf("it got here\n");
    // }

    // strcpy(bin.offsetValue, offsetValue);
    // strcpy(bin.tagValue, tagValue);
    // strcpy(bin.indexValue, indexValue);
    // strcpy(bin.binaryNum, binaryNum);

    // printf("instLength %d\n", atoi(instLength));
    // printf("offsetValue %s\n", offsetValue);
    // printf("tagValue %s\n", tagValue);
    // printf("indexValue %s\n", indexValue);
    // printf("binaryNum %s\n", binaryNum);
}