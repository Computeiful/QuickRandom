#include <stdio.h>
#include <time.h>

#include "Lean.h"

/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/

void check(union Lean *a) { 
	// Check the header for the expected values and bounds of each call

	for(uint64_t i = 0; i < 1000; i++) {
		const uint64_t n = Lean_Range(a, i + 1);
		assert(n <= i + 1);
	}

	for(int i = 0; i < 10000; i++) {
		uint64_t n = Lean_Between(a, 10, 1000);
		assert(n >= 10 && n < 1000);
	}

	for(int i = 0; i < 1000; i++) {
		double n = Lean_Uniform(a);
		assert(n >= 0 && n <= 1);
	}

	for(int i = 0; i < 1000; i++) {
		double n = Lean_Gaussian(a);
		assert(n >= -6 && n <= 6);
	}

	// Random array test
	uint8_t temp[15];
	const int size = sizeof(temp);

	for(size_t i = 0; i < size; i++) {
		temp[i] = 0;
	}
	
	Lean_Copy(a, temp, size);
	uint8_t freq = 0;

	for(size_t i = 0; i < size; i++) {
		if(temp[i] == 0x00) {
			freq++;
		}
	}

	assert(freq <= 1); // More than 1 zero could happen, but would be very rare 
}

int main(void) {
	union Lean a;
	a.seed = 1; 
	Lean(&a); // Needed when the seed has a low value (such as above)
	assert(Lean(&a) == 0xBAA09CA73F3265B4); // Correctness check

	a.seed = (__uint128_t) time(NULL);
	Lean(&a);

	for(int i = 0; i < 10; i++) {
		printf("%08X\n", (int) Lean(&a));
	}

	check(&a);
}
