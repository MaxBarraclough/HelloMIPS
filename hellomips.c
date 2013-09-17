#include "stdio.h"  // printf
#include "string.h" // memcpy
#include "stdlib.h" // malloc

typedef void (*takesNoneReturnsNone) ();
typedef int  (*takesIntReturnsInt)   (int);

int quadruplePlusThree(int arg) {
    return ( arg * 4 ) + 3;
}


void print80ints(const int* const ptr) {

    int newline = 0;
    int offset;
    for (offset = 0; offset != 80; ++offset) {
        newline = (newline + 1) % 8;
        // %04x means hex, length 8, filling with 0s not spaces
        printf(  newline == 0 ? "%08x,\n" : "%08x,", *(offset + (int*)ptr)  );
    }
}


// unsigned int add99(unsigned int arg) {
//     return arg + ((unsigned int)99);
// }
//
//
// void doNothing() { }


#define NOP 0x00200825

static const int doNothingArr[] = {
    0x27bdfff8,0xafbe0004,0x03a0f021,0x03c0e821,
    0x8fbe0004,0x27bd0008,0x03e00008,NOP
};

static const int add99Arr[] = {
    0x27bdfff8,0xafbe0004,0x03a0f021,0xafc40008,
    0x8fc20008,NOP       ,0x24420000,0x03c0e821, //// replace the 0000 bits. index is 6. (last 16 bits)
    0x8fbe0004,0x27bd0008,0x03e00008,NOP
};


takesIntReturnsInt generateAddXFunction(unsigned short x) {
    // assert x <= 65535;

    /* MIPS has no Data Execution Prevention,
    so we can just malloc space to fill with machine-code */
    unsigned int* const toReturn = (unsigned int*)malloc(sizeof add99Arr);
    memcpy(toReturn, add99Arr, sizeof add99Arr);

//  toReturn[6] |= x;
    ((unsigned short*)toReturn)[13] = x;

    return (takesIntReturnsInt)toReturn;
}


void runOurDoNothingMachineCode() {

    takesNoneReturnsNone toCall; // = doNothing;

    toCall = (takesNoneReturnsNone)doNothingArr;

    toCall();

//  print80ints(add99Arr);
}


int main() {
//  printf("sizeof (int) is : %d\n",   sizeof(int)   );
//  printf("sizeof (short) is : %d\n", sizeof(short) );

//  printf( "%d\n", quadruplePlusThree(10) );

    runOurDoNothingMachineCode();

    const takesIntReturnsInt add87 = generateAddXFunction(87);
    printf("%d\n",add87(1000));;

    return 0;
}

