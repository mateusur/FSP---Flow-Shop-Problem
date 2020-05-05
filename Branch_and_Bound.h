#pragma once
#include "Algorithm.h"
class Branch_and_Bound :public Algorithm
{
	int UB = INT32_MAX;
	int bound(std::vector<unsigned> pi, std::vector<unsigned> avaliable);
	int Cmax=9999;
public:
	Branch_and_Bound(int nuber_of_file);
	
	int BnB(int j,Matrix N, std::vector<unsigned> pi, std::vector<unsigned> avaliable);
	void bnb();
	//int calculate_Cmax(std::vector<unsigned> kolejnosc);
};

