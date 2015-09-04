
#include <cstdio>
#include <cstdlib>
#include <iostream>


typedef unsigned long long int uint64_t;

using namespace std;

uint64_t lcg(uint64_t seed);
uint64_t bbs(uint64_t seed);
void printBin(uint64_t);


int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << ' ' << "<seed>" << endl;
        return 0;
    }
    for (long i = 0; i < 240000000/30; ++i) {
        printBin(lcg(atoi(argv[1])));
    }
    return 0;
}


uint64_t lcg(uint64_t seed) {
    uint64_t a = 1103515245;
    uint64_t c = 12345;
    uint64_t m = 0x80000000;
    static uint64_t x = seed;
    x = (a * x + c) % m;
    return x;		
}

void printBin(uint64_t x) {
    int bit = 0;
    for (int shift = sizeof(int) * 8 - 1 - 2; shift >= 0; --shift) {
        bit = (x >> shift) & 1;
        cout << bit;
    }
    cout << endl;
}
