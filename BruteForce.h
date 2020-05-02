#pragma once
#include <string>
#include <vector>
extern std::string names[6];
typedef std::vector<std::vector<unsigned>> Matrix;
int calculate_Cmax(const Matrix& data, std::vector<unsigned> kolejnosc);
bool compareID(const std::vector<unsigned>& v1, std::vector<unsigned>& v2);
int calculate_Cmax(const Matrix& data);
int brute_force_iteration(Matrix& data);
int brute_force_iteration2(Matrix& data);
extern int bestCmaxB;
void brute_force_recursion(Matrix& data, int index, size_t n);
Matrix load_data(unsigned nuber_of_file);
bool comp(const std::vector<unsigned>& v1, std::vector<unsigned>& v2);