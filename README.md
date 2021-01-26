# Lean - QuickRandom

This is a Lehmer PRNG in C which passes TestU01's BigCrunch. For more info see [here](https://lemire.me/blog/2019/03/19/the-fastest-conventional-random-number-generator-that-can-pass-big-crush/).

This generator focuses on speed and thus has some operating constraints. See `Main.c` for usage examples.

---

I've found speeds of ~5 GB/s can be achieved on modern hardware, though YMMV. 