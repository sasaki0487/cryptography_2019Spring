#include <stdio.h>
#include <time.h>
#include <cstdint>
#define first 0x8000000000000000
int IP[] = 
{
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17,  9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

int E[] = 
{
	32,  1,  2,  3,  4,  5,
	 4,  5,  6,  7,  8,  9,
	 8,  9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32,  1
};

int P[] = 
{
	16,  7, 20, 21,
	29, 12, 28, 17,
	 1, 15, 23, 26,
	 5, 18, 31, 10,
	 2,  8, 24, 14,
	32, 27,  3,  9,
	19, 13, 30,  6,
	22, 11,  4, 25
};

int FP[] = 
{
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41,  9, 49, 17, 57, 25
};

int Sbox[8][4][16] = {
   {
   {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
   { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
   { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
   {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},
   },
 
   {
   {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
   { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
   { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
   {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},
   },
 
   {
   {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
   {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
   {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
   { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},
   },
 
   {
   { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
   {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
   {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
   { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},
   },
 
   {
   { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
   {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
   { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
   {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},
   },
 
   {
   {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
   {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
   { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
   { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},
   },
 
   {
   { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
   {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
   { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
   { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},
   },
 
   {
   {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
   { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
   { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
   { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11},
   },
};

int PC1[] = 
{
	57, 49, 41, 33, 25, 17,  9,
	 1, 58, 50, 42, 34, 26, 18,
	10,  2, 59, 51, 43, 35, 27,
	19, 11,  3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	 7, 62, 54, 46, 38, 30, 22,
	14,  6, 61, 53, 45, 37, 29,
	21, 13,  5, 28, 20, 12,  4
};

int PC2[] = 
{
	14, 17, 11, 24,  1,  5,
	 3, 28, 15,  6, 21, 10,
	23, 19, 12,  4, 26,  8,
	16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};

int Rotate[16] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

FILE *fout;
clock_t start, end; 
double cpu_time_used[20]; 
uint64_t subkeys[16];

uint64_t ini_permutation(uint64_t in){
    uint64_t out = 0,msk=first;
    for(int i = 0 ; i < 64 ; i++){
        if((in >> (64-IP[i])) & 1){
            out |= msk;
        }
        msk >>= 1;
    }
    return out;
}

uint64_t IIP(uint64_t in){
    uint64_t out = 0,msk=first;
    for(int i = 0 ; i < 64 ; i++){
        if((in >> (64-FP[i])) & 1){
            out |= msk;
        }
        msk >>= 1;
    }
    return out;
}

uint64_t pc1(uint64_t k){
    uint64_t out = 0,msk=first>>8;
    for(int i = 0 ; i < 56 ; i++){
        if((k >> (64 - PC1[i])) & 1){
            out |= msk;
        }
        msk >>= 1;
    }
    return out;
}

uint64_t expand(uint64_t &in){
    uint64_t out = 0,msk = first >> 16;
    for(int i = 0 ; i < 48 ; i++){
        if((in >> (32 - E[i])) & 1){
            out |= msk;
        }
        msk >>= 1;
    }
    return out;
}
uint32_t lrs(uint32_t value) {
    uint32_t overflow_mask = 0x08000000;
    uint32_t value_mask = 0x07FFFFFF;
    return ((value & value_mask) << 1) | ((value & overflow_mask) >> 27);
}

uint64_t pc2(uint64_t &key,int num){
    uint32_t left,right;
    right = key & 0xFFFFFFF;
    left = key >> 28 & 0xFFFFFFF;
    if(Rotate[num] == 1){
        left = lrs(left);
        right = lrs(right);
    }
    else{
        left = lrs(left);
        right = lrs(right);
        left = lrs(left);
        right = lrs(right);
    }
    key = left;
    key = (key << 28) + right;

    uint64_t out = 0,msk = first >> 16;
    for(int i = 0 ; i < 48 ; i++){
        if((key >> (56 - PC2[i])) & 1){
            out |= msk;
        }
        msk >>= 1;
    }
    return out;
}

uint64_t sbox(uint64_t in){
    uint64_t out = 0,msk;
    int x,y;
    for(int i = 0 ; i < 8 ; i++){
        y =  in & 1;
        in >>= 1 ;
        x = in & 0x000F;
        in >>= 4 ;
        y += ( in & 1 ) * 2;
        in >>= 1 ; 
        msk = Sbox[7-i][y][x];
        out += msk << (4 * i);
    }
    return out;
}

uint64_t pbox(uint64_t &in){
    uint64_t out = 0,msk = 0x80000000;
    for(int i = 0 ; i < 32 ; i++){
        if((in >> (32-P[i])) & 1){
            out |= msk;
        }
        msk >>= 1;
    }
    return out;
}

void keygen(uint64_t k){
    k = pc1(k);
    for(int i = 0 ; i < 16 ; i++){
        subkeys[i] = pc2(k,i);
    }
}

void crypt(uint64_t in , uint64_t k,int num,int en_de_crypt){
    uint64_t key,pckey,left,right,tmp;
    fout = fopen("out.txt","a+"); 
    start = clock();
    in = ini_permutation(in);
    keygen(k);
    for(int i = 0 ; i < 16 ; i++){
        left = in >> 32 & 0xFFFFFFFF;
        right = in & 0xFFFFFFFF;
        tmp = right;
        right = expand(right);
        if(en_de_crypt == 1)
            right = right ^ subkeys[i];
        else
            right = right ^ subkeys[15-i];
        right = sbox(right);
        right = pbox(right);
        in = (tmp << 32) + (left ^ right);
    }/*
    int l = 0;
    for(int i = 0 ; i < 10000 ; i++){
        for(int j = 0 ; j < 10000 ; j++){
            l *= 1;
        }
    }*/
    left = in >> 32 & 0xFFFFFFFF;
    right = (in & 0xFFFFFFFF) << 32;
    in = left + right;
    in = IIP(in);
    end = clock(); 
    cpu_time_used[num] = ((double) (end - start)) / (double) CLOCKS_PER_SEC;
    printf("%016llx %016llx\n" , in , k);
    fprintf(fout,"%016llx %016llx\n" , in , k);
    fclose(fout);
}

int main(){
    uint64_t input,key;
    FILE *fen,*fde;
    fout = fopen("out.txt","w");
    fclose(fout);
    /*encrypt*/
    fen = fopen("DES-Key-Plaintext.txt","r");
    if(!fen){
        printf("File \"DES-Key-Plaintext.txt\" not found");
        return 0;
    }
    printf("=== Encrypt Start ===\n");
    for(int i = 0 ; i < 10 ; i++){
        fscanf(fen,"%llx %llx", &key , &input);
        crypt(input,key,i,1);
    }
    fclose(fen);
    /*decrypt*/
    fde = fopen("DES-Key-Ciphertext.txt","r");
    if(!fde){
        printf("File \"DES-Key-Ciphertext.txt\" not found");
        return 0;
    }
    printf("=== Decrypt Start ===\n");
    for(int i = 0 ; i < 10 ; i++){
        fscanf(fen,"%llx %llx", &key , &input);
        crypt(input,key,i+10,2);
    }
    fclose(fde);
    fout = fopen("out.txt","a+");
    for(int i = 0 ; i < 20 ; i++){
        fprintf(fout,"%.0lf ",cpu_time_used[i]*1000);
    }
    fclose(fout);
    printf("===    Finish     ===\n");
    return 0;
}