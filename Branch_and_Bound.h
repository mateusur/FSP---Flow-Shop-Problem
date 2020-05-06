#pragma once
#include "Algorithm.h"
class Branch_and_Bound :public Algorithm
{
	int UB = INT32_MAX;
	int bound(std::vector<unsigned> pi, std::vector<unsigned> available);
	int bound2(std::vector<unsigned> pi, std::vector<unsigned> available);
	int bound3(std::vector<unsigned> pi, std::vector<unsigned> available);
	int bound4(std::vector<unsigned> pi, std::vector<unsigned> available);
	int Cmax=9999;
	//std::vector<unsigned> pi_order5;
	int count = 0;
public:
	Branch_and_Bound(int nuber_of_file);
	int BnB(int job, std::vector<unsigned> pi, std::vector<unsigned> available);
	void bnb();
	//int calculate_Cmax(std::vector<unsigned> kolejnosc);
};


