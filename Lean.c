#include "Lean.h"

inline uint64_t Lean(union Lean *a) {
    a->seed *= 0xDA942042E4DD58B5;
    return (uint64_t) (a->seed >> 64);
}

uint64_t Lean_Range(union Lean *a, const uint64_t max) {
    assert(max > 0);
    uint64_t n = 0;

    for(;;) { // Better than modulus
        n = Lean(a);
        if(n < UINT64_MAX - (UINT64_MAX % max)) break;
    }

    return (n % max);
}

uint64_t Lean_Between(union Lean *a, const uint64_t min, const uint64_t max) { 
    assert(max > min);
    return Lean_Range(a, max - min) + min;
}

void Lean_Copy(union Lean *a, void *dst, const size_t size) { // Copy random bytes onto the array
    uint64_t *body = (uint64_t *) dst;

    for(size_t i = 0; i < (size >> 3); i++) {
        *body++ = Lean(a);
    }

    uint8_t *foot = (uint8_t *) body;
    
    for(size_t i = 0; i < (size & 0x07); i++) {
        *foot++ = (uint8_t) Lean(a);
    }
}

double Lean_Uniform(union Lean *a) { // Value between 0.0 and 1.0, mean of 0.5
    static union {
        uint64_t u;
        double f;
    } map;
    map.u = UINT64_C(0x3FF0000000000000) | (Lean(a) >> 12); // IEEE-754 abuse
    return (map.f - 1.0);
}

float Lean_Uniformf(union Lean *a) { // Value between 0.0 and 1.0, mean of 0.5
    static union {
        uint32_t u;
        float f;
    } map;
    const uint32_t n = (uint32_t) Lean(a); // 64 -> 32
    map.u = UINT32_C(0x3F800000) | (n >> 9); // IEEE-754 abuse
    return (map.f - 1.0f);
}

double Lean_Gaussian(union Lean *a) { // Normal value, mean of 0.0, s.d. of 1.0 (values cannot exceed 6.0 or -6.0)
    double n = 0.0;

    for(char i = 0; i < 12; i++) {
        n += Lean_Uniform(a);
    }
    n -= 6.0;

    return n;
}

float Lean_Gaussianf(union Lean *a) { // Normal value, mean of 0.0, s.d. of 1.0 (values cannot exceed 6.0 or -6.0)
    float n = 0.0f;

    for(char i = 0; i < 12; i++) {
        n += Lean_Uniformf(a);
    }
    n -= 6.0f;

    return n;
}
