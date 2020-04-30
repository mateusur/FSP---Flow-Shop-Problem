#include "Brute_force.h"


#include <algorithm>
#include <fstream>
#include "Algorithm.h"
using namespace std;

Brute_force::Brute_force(unsigned nuber_of_file) {
	int tasks, machines, machine_num, p_time;
	vector<unsigned> v_temp;
	std::ifstream file;
	file.open("data/" + names[nuber_of_file], ios::out);
	file >> tasks >> machines;
	for (int i = 0; i < tasks; i++) {
		for (int j = 0; j < machines; j++) {
			file >> machine_num >> p_time;
			v_temp.push_back(p_time);
		}
		v_temp.push_back(i + 1); // Adding id at last column
		data.push_back(v_temp);
		v_temp.clear();
	}
	file.close();
	vector<unsigned> temp(tasks, 0);
	for (int i = 0; i < machines; i++) {
		s.push_back(temp);
		c.push_back(temp);
	}

	vector<unsigned> pi_order(data.size());
	for (int i = 0; i < pi_order.size(); i++)
		pi_order[i] = i;
}

int Brute_force::brute_force_iteration() {
	vector<unsigned> pi(data.size());
	for (int i = 0; i < pi.size(); i++)
		pi[i] = i;
	int bestCmax = UINT16_MAX;
	int temp = 0;
	do {
		temp = calculate_Cmax(pi);
		if (temp < bestCmax) bestCmax = temp;
	} while (next_permutation(pi.begin(), pi.end()));
	return bestCmax;
}
int Brute_force::brute_force_recursion( int index)
{	
	size_t n = data.size();
	int temp;
	if (index >= n) {
		temp = calculate_Cmax(data);
		if (temp < bestCmax) {
			bestCmax = temp;
		}
		return bestCmax;
	}
	for (int i = index; i < n; i++) {
		std::swap(data[index], data[i]);
		brute_force_recursion(index + 1);
		std::swap(data[index], data[i]);
	}
	return bestCmax;
}