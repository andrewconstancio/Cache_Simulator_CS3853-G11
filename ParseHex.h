

struct CacheCol {
    short int valid;
    char* tag;
    char* offset;
    char* colNum;
    struct CacheCol* next;
} typedef CacheCol;

struct cache {
    short int valid;
    char* tag;
};

signed int binaryToHex(char* value);
void HexToBin(char* hexdec, char *binaryNum);