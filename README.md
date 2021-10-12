# Lean - QuickRandom

This is a Lehmer PRNG in C which passes TestU01's BigCrunch. For more info see [here](https://lemire.me/blog/2019/03/19/the-fastest-conventional-random-number-generator-that-can-pass-big-crush/).

This generator focuses on speed and thus has some operating constraints. See `Main.c` for usage examples.

---

This PRNG is zero-sensitive (though the chance of hitting a zero is around 1 in 340 undecillion). I have tested this PRNG using a seed of `1` up to 21,520,000,000,000 iterations (~156.6 TB) without encountering a zero, so a seed of `1` is safe for most use cases. 

There are no guarantees as to the PRNG period. 

I've found speeds of ~5 GB/s can be achieved on modern hardware, though YMMV. 