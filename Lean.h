#ifndef LEAN_H
#define LEAN_H

	#include <stdint.h>
	#include <assert.h>

	union Lean {
		__uint128_t seed;
	};

	static uint64_t Lean(union Lean *a) {
		a->seed *= 0xDA942042E4DD58B5;
		return (uint64_t) (a->seed >> 64); 
	}

	static uint64_t Lean_Range(union Lean *a, uint64_t max) {
		assert(max > 0);
		uint64_t n = 0;

		for(;;) { // Better than modulus
			n = Lean(a);
			if(n < UINT64_MAX - (UINT64_MAX % max)) break;
		}

		return (n % max);
	}

	static uint64_t Lean_Between(union Lean *a, uint64_t min, uint64_t max) { 
		assert(max > min);
		return Lean_Range(a, max - min) + min;
	}

	static double Lean_Uniform(union Lean *a) { // Value between 0.0 and 1.0, mean of 0.5
		union {
			uint64_t u64;
			double f64;
		} map;
		map.u64 = 0x3FF0000000000000ULL | (Lean(a) >> 12); // IEEE-754 abuse
		return (map.f64 - 1.0);
	}

	static double Lean_Gaussian(union Lean *a) { // Normal value, mean of 0.0, s.d. of 1.0 (values cannot exceed 6.0 or -6.0)
		double n = 0.0;

		for(char i = 0; i < 12; i++) {
			n += Lean_Uniform(a);
		}
		n -= 6.0;

		return n;
	}

#endif