compile:
	clang -Ofast -std=c17 -Wall -Wextra -Wpedantic -Weverything -DNDEBUG *.c

debug:
	clang -Og -g -std=c17 -Wall -Wextra -Wpedantic -Weverything *.c 
