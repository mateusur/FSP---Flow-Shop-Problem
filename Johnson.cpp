#include "Johnson.h"
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;
//extern string names[];

//bool compare(const vector<unsigned>& v1, vector<unsigned>& v2) {
//	short min_v1 = v1[0] > v1[1] ? 1 : 0;
//	short min_v2 = v2[0] > v2[1] ? 1 : 0;
//	return v1[min_v1] < v2[min_v2];
//}

Johnson::Johnson(unsigned nuber_of_file) {
	int tasks, machines, machine_num, p_time;
	std::vector<unsigned> v_temp;
	std::ifstream file;
	file.open("data/" + names[nuber_of_file], ios::out);
	file >> tasks >> machines;
	if(machines!=2)
		std::cerr << "Algorytm Johnsona dziala tylko dla 2 maszyn, wczytaj inny plik"<<endl;
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

int Johnson::Johnson_algorithm() {
	Matrix kopia=data;
	std::sort(kopia.begin(), kopia.end());
	vector<unsigned> order(kopia.size());
	unsigned l = 0, k = kopia.size()-1;
	for (int i = 0;i < kopia.size();i++) {
		if(kopia[i][0] < kopia[i][1]) {
			order.at(l) = kopia[i][2]-1;
			l++;
		}
		else {
			order.at(k) = kopia[i][2]-1;
			k--;
		}
	}
	int C_max= calculate_Cmax(order);
	return C_max;
}

bool operator<(const std::vector<unsigned>& v1, std::vector<unsigned>& v2) {
	short min_v1 = v1[0] > v1[1] ? 1 : 0;
	short min_v2 = v2[0] > v2[1] ? 1 : 0;
	return v1[min_v1] < v2[min_v2];
}
