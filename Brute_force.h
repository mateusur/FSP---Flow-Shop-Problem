#pragma once
#include <vector>
typedef std::vector<std::vector<unsigned>> Matrix;
class Brute_force
{
	Matrix s, c, data;
	int bestCmax = UINT16_MAX;
	std::vector<unsigned> pi_order;
	int calculate_Cmax(std::vector<unsigned> kolejnosc);
	int calculate_Cmax(const Matrix& data);
public:
	Brute_force(unsigned nuber_of_file);
	int brute_force_iteration();
	int brute_force_recursion(int index);
	~Brute_force() {}
};
