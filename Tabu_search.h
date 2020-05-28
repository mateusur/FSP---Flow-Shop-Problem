#pragma once
#include "Algorithm.h"
#include "NEH.h"
class Tabu_search : public Algorithm
{
	int nr_of_file;
	std::vector<std::vector<int>> tabu_matrix;
	int calculate_Cmax(const std::vector<unsigned>& kolejnosc);
	std::vector<unsigned> cricital_path(const std::vector<unsigned> &pi_order);
	void remove(std::vector<unsigned>& v);
	std::vector<unsigned> blocks(const std::vector<machine_job>& cricital_path);
public:
	Tabu_search(const int& number_of_file);
	Anwser algorithm();
	Anwser algorithm_with_blocks();
	
};

