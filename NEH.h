#pragma once
#include "Algorithm.h"
struct machine_job
{
	unsigned job_number, machine, time;
};
class NEH :public Algorithm
{
	std::vector<unsigned> calculate_weights();
	struct weights
	{
		unsigned position, sum;
	};
	int calculate_Cmax(std::vector<unsigned> kolejnosc);
	
	std::vector<unsigned> helper( std::vector<unsigned> pi_vector);
	std::vector<unsigned> biggest_Cmax_diffrence(std::vector<unsigned> pi_vector, int forbidden_job);
	std::vector<machine_job> critical_path( std::vector<unsigned> pi_order);
	

public:
	NEH(int nuber_of_file);
	std::vector<unsigned> NEH_algorithm(); // return int if you want bestCmax or vector<unsigned> if you want pi_order
	int job_that_reduce_cmax_most();
	int job_with_longest_operation_on_critical_path();
	int job_with_biggest_sum_time_on_crcital_path();
	int job_with_max_operations();
	friend bool operator==(const machine_job& j1, const int& j2);
};

std::ostream& operator<<(std::ostream& os, const std::vector<unsigned>& vector);
