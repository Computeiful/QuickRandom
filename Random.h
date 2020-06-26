#ifndef RANDOM_H
#define RANDOM_H

	#include <stdint.h>
	#include <assert.h>

	union Random {
		__uint128_t seed;
	};

	static uint64_t Random(union Random *a) {
		a->seed *= 0xDA942042E4DD58B5;
		return (uint64_t) (a->seed >> 64); 
	}

	static uint64_t Random_Range(union Random *a, uint64_t max) {
		assert(max > 0);
		uint64_t n = 0;

		for(;;) { // Better than modulus
			n = Random(a);
			if(n < UINT64_MAX - (UINT64_MAX % max)) break;
		}

		return (n % max);
	}

	static uint64_t Random_Between(union Random *a, uint64_t min, uint64_t max) {
		assert(max > min);
		return Random_Range(a, max - min) + min;
	}

	static double Random_Uniform(union Random *a) { // Value between 0.0 and 1.0, mean of 0.5
		union {
			uint64_t u64;
			double f64;
		} map;
		map.u64 = 0x3FF0000000000000ULL | (Random(a) >> 12); // IEEE-754 abuse
		return (map.f64 - 1.0);
	}

	static double Random_Gaussian(union Random *a) { // Normal value, mean of 0.0, s.d. of 1.0 (values cannot exceed 6.0 or -6.0)
		double n = 0.0;

		for(char i = 0; i < 12; i++) {
			n += Random_Uniform(a);
		}
		n -= 6.0;

		return n;
	}

#endif
