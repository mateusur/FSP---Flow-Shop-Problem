#pragma once
#include <vector>
#include "Algorithm.h"
typedef std::vector<std::vector<unsigned>> Matrix;
class Brute_force : public Algorithm
{
	int bestCmax = UINT16_MAX;
public:
	Brute_force(unsigned nuber_of_file);
	int brute_force_iteration();
	int brute_force_recursion(int index);
	~Brute_force() {}
};
