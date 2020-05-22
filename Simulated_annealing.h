#pragma once
#include "Algorithm.h"
class Simulated_annealing :public Algorithm
{
public:
	Simulated_annealing(int number_of_file);
	Anwser Algorithm(const short& init_temp, const short& init_L, const short& init_x, const short& init_alfa, const double& temperature_end, const short& mode);
};

