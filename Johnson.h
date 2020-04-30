#pragma once
#include <vector>
#include "Algorithm.h"
typedef std::vector<std::vector<unsigned>> Matrix;
class Johnson :public Algorithm
{
public:
	Johnson(unsigned nuber_of_file);
	int Johnson_algorithm();
	friend bool operator<(const std::vector<unsigned>& v1, std::vector<unsigned>& v2);
	
};

