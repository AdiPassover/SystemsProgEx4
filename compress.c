#include <stdio.h>
#include <stdlib.h>
#include "compress.h"

char encode(char c1, char c2);
void decode(char code, char nums[2]);

void compress(const char* path) {
    FILE* text = fopen(path,"r");
    if (text == NULL) { perror("error opening file"); exit(1); }
    FILE* binary = fopen("C:\\Users\\adipe\\CLionProjects\\SystemsProgEx4\\text.bin","wb");
    if (binary == NULL) { perror("error opening file"); fclose(text); exit(1); }

    int finished = 0;
    while (!finished) {
        char c1 = fgetc(text);
        if (c1 == EOF) { break; }
        char c2 = fgetc(text);
        if (c2 == EOF) { finished = 1; }
        char num = encode(c1,c2);
        if (fwrite(&num, sizeof(char), 1, binary) == EOF) { perror("error writing to file"); exit(1); }
    }

    fclose(text);
    fclose(binary);
}

void decompress(const char* path) {
    FILE* binary = fopen(path,"rb");
    if (binary == NULL) { perror("error opening file"); exit(1); }

    for (int i = 1; 1; i++) {
        char code;
        if (fread(&code,sizeof(char),1,binary) <= 0) { break; }
        char nums[2];
        decode(code,nums);
        printf("num %d: %d\n",i,nums[0]);
        if (nums[1] == EOF) { break; }
        i++;
        printf("num %d: %d\n",i,nums[1]);
    }

    fclose(binary);
}

char encode(char c1, char c2) {
    c1 -= '0';
    if (c2 == EOF) { c2 = 15; }
    else { c2 -= '0'; }

    c1 <<= 4;
    c1 += c2;

    char res = 0;
    for (char mask = 1; mask != 0; mask <<= 1) {
        char digit = (c1 & mask);
        if (digit == 0) { digit = mask; }
        else { digit = 0; }
        res += digit;
    }

    return res;
}

void decode(char code, char nums[2]) {
    nums[0] = 0;
    nums[1] = 0;
    for (char mask = 1; mask != 16; mask <<= 1) {
        int digit = (mask & code);
        if (digit == 0) { digit = mask; }
        else { digit = 0; }
        nums[1] += digit;
    }
    for (char mask = 16; mask != 0; mask <<= 1) {
        int digit = (mask & code);
        if (digit == 0) { digit = abs(mask >> 4); }
        else { digit = 0; }
        nums[0] += digit;
    }
    if (nums[1] == 15) { nums[1] = EOF; }
}