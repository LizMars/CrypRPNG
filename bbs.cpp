
#include <cstdlib>
#include <iostream>
#include <gmp.h>
//#include <gmpxx.h>


using namespace std;


void bbsInit(unsigned int seed);
unsigned int bbs();
void printBin(unsigned int x);


void printBin(unsigned int x) {
    int bit = 0;
    for (int shift = sizeof(unsigned int) * 8 - 1; shift >= 0; --shift) {
        bit = (x >> shift) & 1;
        cout << bit;
    }
    cout << endl;
}

struct {
    mpz_t state;
    mpz_t mod;
    mpz_t output_mask;
} bbs_conf;

void bbsInit(unsigned int seed) {
    mpz_init(bbs_conf.state);
    mpz_init(bbs_conf.mod);
    mpz_init(bbs_conf.output_mask);
    mpz_set_ui(bbs_conf.state, seed);
    mpz_set_str(bbs_conf.mod, "87f8c4dccb9485c7c330b5757d2d751", 16);
    mpz_set_ui(bbs_conf.output_mask, 0xFFFFFFFF);
    for (int i = 0; i < 32; ++i) {
        bbs();
    }
}

unsigned int bbs() {
    mpz_mul(bbs_conf.state, bbs_conf.state, bbs_conf.state);
    mpz_mod(bbs_conf.state, bbs_conf.state, bbs_conf.mod);
    return mpz_get_ui(bbs_conf.state);
}

int main(int argc, char** argv) {
    bbsInit(77);
    for (int i = 0; i < 55000000/32; ++i) {
        printBin(bbs());
    }
    return 0;
}
