#pragma once

#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define C 86969 /* yet another prime */
#define FIRSTH 37 /* also prime */

class Hashing {
public:
	static unsigned Hash(const char* s);
};