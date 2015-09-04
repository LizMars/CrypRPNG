
#include <cstdlib>
#include <iostream>
#include <gmp.h>
#include <gmpxx.h>


using namespace std;

typedef unsigned int uint;


void printBin(unsigned int x);

void printBin(unsigned int x) {
    int bit = 0;
    for (int shift = sizeof(unsigned int) * 8 - 1; shift >= 0; --shift) {
        bit = (x >> shift) & 1;
        cout << bit;
    }
    cout << endl;
}

class LFSR {
 private:
    uint tap1;
    uint tap2;
    uint tap3;
    uint tap4;
    mpz_class reg;
 public:
    LFSR(uint e1, uint e2, uint e3, uint e4);

    void init_seed(const char* value);
    int tick();
    unsigned int rand();
};

LFSR::LFSR(uint e1, uint e2, uint e3, uint e4) {
    tap1 = e1;
    tap2 = e2;
    tap3 = e3;
    tap4 = e4;
};

void LFSR::init_seed(const char* value) {
    reg = mpz_class(value, 16);
    // Make sure the init value will not make the register longer.
    mpz_class mask(1);
    mask = (mask << tap1) - 1;
    reg = reg & mask;

    for (int i = 0; i < 1024; ++i) {
        tick();
    }
}

int LFSR::tick() {
    mpz_t temp;
    mpz_init(temp);

    int rand_bit = reg.get_ui() & 1;

    int xorbit = 1;
    mpz_set(temp, reg.get_mpz_t());
    xorbit ^= mpz_tstbit(temp, tap1);
    xorbit ^= mpz_tstbit(temp, tap2);
    xorbit ^= mpz_tstbit(temp, tap3);
    xorbit ^= mpz_tstbit(temp, tap4);

    reg = reg >> 1;
    mpz_set(temp, reg.get_mpz_t());
    if (xorbit == 1) {
        mpz_setbit(temp, tap1);
    }
    reg = mpz_class(temp);

    mpz_clear(temp);
    return rand_bit;
}

unsigned int LFSR::rand() {
    unsigned int result = 0;
    for (int i = 0; i < sizeof(unsigned int) * 8; ++i) {
        result |= tick() << i;
    }
    return result;
}

int main(int argc, char** argv) {
    LFSR test(133, 9, 8, 2);

    test.init_seed("0123456789abcdef");
    for (int i = 0; i < 55000000/32; ++i) {
        printBin(test.rand());
    }
    return 0;
}
