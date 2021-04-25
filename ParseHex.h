//header file for ParseHex.c

typedef struct _CacheCol {
    short int valid;
    char* tag;
    char* offset;
    char* colNum;
    struct CacheCol* next;
} CacheCol;

struct cache {
    short int valid;
    char* tag;
};

signed int binaryToHex(char* value);
void HexToBin(char* hexdec, char *binaryNum);