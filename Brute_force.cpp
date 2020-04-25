#include "Brute_force.h"


#include <algorithm>
#include <fstream>
using namespace std;
std::string names[6] = {
	"data001.txt",
	"data002.txt",
	"data003.txt",
	"data004.txt",
	"data005.txt",
	"data006.txt",
};
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
int Brute_force::calculate_Cmax(vector<unsigned> kolejnosc) {
	unsigned tasks = data.size();
	unsigned machines = data[1].size() - 1;
	for (int i = 0; i < machines; i++) {
		for (int j = 0; j < kolejnosc.size(); j++) {
			if (i == 0 && j == 0) {
				s[i][j] = 0;
				c[i][j] = data[kolejnosc[j]][i];
			}
			else if (i == 0) {
				s[i][j] = c[i][j - 1];
				c[i][j] = s[i][j] + data[kolejnosc[j]][i];
			}
			else if (j == 0) {
				s[i][j] = c[i - 1][j];
				c[i][j] = s[i][j] + data[kolejnosc[j]][i];
			}
			else {
				s[i][j] = max(c[i][j - 1], c[i - 1][j]);
				c[i][j] = s[i][j] + data[kolejnosc[j]][i];
			}
		}
	}
//	for (int i = 0; i < machines; i++) {
//	for (int j = 0; j < tasks; j++) {
//		cout << s[i][j] << " ";
//	}
//	cout << endl;
//}
//cout << endl;
//for (int i = 0; i < c.size(); i++) {
//	for (int j = 0; j < c[0].size(); j++) {
//		cout << c[i][j] << " ";
//	}
//	cout << endl;
//}
	int Cmax = c[machines - 1][tasks - 1];
	return Cmax;
}
int Brute_force::calculate_Cmax(const Matrix& data) {
	unsigned tasks = data.size();
	unsigned machines = data[1].size() - 1;
	/*vector<unsigned> temp(tasks, 0);
	Matrix S(machines, temp);
	Matrix C(machines, temp);*/
	for (int i = 0; i < machines; i++) {
		for (int j = 0; j < tasks; j++) {
			if (i == 0 && j == 0) {
				s[i][j] = 0;
				c[i][j] = data[j][i];
			}
			else if (i == 0) {
				s[i][j] = c[i][j - 1];
				c[i][j] =s[i][j] + data[j][i];
			}
			else if (j == 0) {
				s[i][j] = c[i - 1][j];
				c[i][j] = s[i][j] + data[j][i];
			}
			else {
				s[i][j] = max(c[i][j - 1], c[i - 1][j]);
				c[i][j] = s[i][j] + data[j][i];
			}
		}
	}
	//for (int i = 0; i < machines; i++) {
	//	for (int j = 0; j < tasks; j++) {
	//		cout << S[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//for (int i = 0; i < C.size(); i++) {
	//	for (int j = 0; j < C[0].size(); j++) {
	//		cout << C[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	int Cmax = c[machines - 1][tasks - 1];
	return Cmax;
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