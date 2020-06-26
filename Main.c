#include <stdio.h>
#include <time.h>

#include "Random.h"

int main(void) {
	union Random a;
	a.seed = (__uint128_t) time(NULL);
	Random(&a); // Needed when the seed has a low value (such as above)

	printf("%08X\n", (int) Random(&a));

	for(int i = 0; i < 1000; i++) {
		double n = Random_Uniform(&a);
		assert(n >= 0 && n <= 1);
	}
}
