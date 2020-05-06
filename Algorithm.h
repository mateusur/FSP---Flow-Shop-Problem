#pragma once
#include <string>
#include <vector>
typedef std::vector<std::vector<unsigned>> Matrix;
class Algorithm
{	
protected:
	Matrix s, c, data;
	std::vector<unsigned> pi_order;
	std::string names[7] = {
	"data001.txt",
	"data002.txt",
	"data003.txt",
	"data004.txt",
	"data005.txt",
	"data006.txt",
	"data007.txt"
	};
	int calculate_Cmax(std::vector<unsigned> kolejnosc);
	int calculate_Cmax(const Matrix& data);
	
};

