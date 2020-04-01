#include "Random.h"
#include <stdio.h>
#include <time.h>

int main(void) {
	union Random a;
	a.seed = (__uint128_t) time(NULL);
	Random_Consume(&a); // Needed when the seed has a low value (such as above)

	printf("%08X\n", (int) Random_Consume(&a));
}
