#ifndef LEAN_H
#define LEAN_H

	#include <stdint.h>
	#include <assert.h>
	#include <stddef.h>

	#ifndef __SIZEOF_INT128__
	#error "Found no integer mode wide enough"
	#endif

	union Lean {
		__uint128_t seed;
	};

	uint64_t Lean(union Lean *);
	uint64_t Lean_Range(union Lean *, uint64_t max);
	uint64_t Lean_Between(union Lean *, uint64_t min, uint64_t max);
	void Lean_Copy(union Lean *, void *, size_t size); // Copy random bytes onto the array
	double Lean_Uniform(union Lean *); // Value between 0.0 and 1.0, mean of 0.5
	double Lean_Gaussian(union Lean *); // Normal value, mean of 0.0, s.d. of 1.0 (values cannot exceed 6.0 or -6.0)

#endif
