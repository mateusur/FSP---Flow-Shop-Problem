#include "BruteForce.h"

#include <algorithm>
#include <fstream>

int calculate_Cmax(const Matrix& data, std::vector<unsigned> kolejnosc) {
	//static short number_of_calls = 0;
	unsigned tasks = data.size();
	unsigned machines = data[1].size() - 1;

	std::vector<unsigned> temp(tasks, 0);
	Matrix S(machines, temp);
	Matrix C(machines, temp);
	for (int i = 0; i < machines; i++) {
		for (int j = 0; j < kolejnosc.size(); j++) {
			if (i == 0 && j == 0) {
				S[i][j] = 0;
				C[i][j] = data[kolejnosc[j]][i];
			}
			else if (i == 0) {
				S[i][j] = C[i][j - 1];
				C[i][j] = S[i][j] + data[kolejnosc[j]][i];
			}
			else if (j == 0) {
				S[i][j] = C[i - 1][j];
				C[i][j] = S[i][j] + data[kolejnosc[j]][i];
			}
			else {
				S[i][j] = std::max(C[i][j - 1], C[i - 1][j]);
				C[i][j] = S[i][j] + data[kolejnosc[j]][i];
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
	int Cmax = C[machines - 1][tasks - 1];
	//cout << Cmax << endl;
	return Cmax;
}

bool compareID(const std::vector<unsigned>& v1, std::vector<unsigned>& v2) {
	size_t size = v1.size() - 2;
	return v1[size] < v2[size];
}

//int brute_force_iteration(Matrix& data) {
//	int bestCmax = UINT16_MAX;
//	int temp = 0;
//	do {
//		temp = calculate_Cmax(data);
//		if (temp < bestCmax) bestCmax = temp;
//	} while (next_permutation(data.begin(), data.end(), [&](const vector<unsigned>& v1, vector<unsigned>& v2)
//	{
//			size_t size = v1.size() - 1;
//			return v1[size] < v2[size];
//	}));
//	return bestCmax;
//}
int calculate_Cmax(const Matrix& data) {
	unsigned tasks = data.size();
	unsigned machines = data[1].size() - 1;
	//cout <<"Liczba zadan: "<< tasks << endl;
	//cout << "Liczba maszyn: " << machines << endl;
	std::vector<unsigned> temp(tasks, 0);
	Matrix S(machines, temp);
	Matrix C(machines, temp);
	for (int i = 0; i < machines; i++) {
		for (int j = 0; j < tasks; j++) {
			if (i == 0 && j == 0) {
				S[i][j] = 0;
				C[i][j] = data[j][i];
			}
			else if (i == 0) {
				S[i][j] = C[i][j - 1];
				C[i][j] = S[i][j] + data[j][i];
			}
			else if (j == 0) {
				S[i][j] = C[i - 1][j];
				C[i][j] = S[i][j] + data[j][i];
			}
			else {
				S[i][j] = std::max(C[i][j - 1], C[i - 1][j]);
				C[i][j] = S[i][j] + data[j][i];
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
	int Cmax = C[machines - 1][tasks - 1];
	//cout << Cmax << endl;
	return Cmax;
}

int brute_force_iteration(Matrix& data) {
	int bestCmax = UINT16_MAX;
	int temp = 0;
	do {
		temp = calculate_Cmax(data);
		if (temp < bestCmax) bestCmax = temp;
	} while (next_permutation(data.begin(), data.end(), compareID));
	return bestCmax;
}

int brute_force_iteration2(Matrix& data) {
	std::vector<unsigned> pi(data.size());
	for (int i = 0; i < pi.size(); i++)
		pi[i] = i;
	int bestCmax = UINT16_MAX;
	int temp = 0;
	do {
		temp = calculate_Cmax(data, pi);
		if (temp < bestCmax) bestCmax = temp;
	} while (next_permutation(pi.begin(), pi.end()));
	return bestCmax;
}

void brute_force_recursion(Matrix& data, int index, size_t n) {
	int temp;
	if (index >= n) {
		temp = calculate_Cmax(data);
		if (temp < bestCmaxB) {
			bestCmaxB = temp;
		}
		return;
	}
	for (int i = index; i < n; i++) {
		std::swap(data[index], data[i]);
		brute_force_recursion(data, index + 1, n);
		std::swap(data[index], data[i]);
	}
}

Matrix load_data(unsigned nuber_of_file) {
	int tasks, machines, machine_num, p_time;
	Matrix data;
	std::vector<unsigned> v_temp;
	std::ifstream file;
	file.open("data/" + names[nuber_of_file], std::ios::out);
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
	return data;
}

//auto akceleration(Matrix data) {
//	Matrix copy = data;
//	size_t tasks = copy.size();
//	size_t machines = copy[0].size() - 1;
//	for(int i =0;i<tasks;i++) {
//		int sum = 0;
//		for(int j=0;j<machines;j++) {
//			sum += copy[i][j];
//		}
//		copy[i].push_back(sum);
//	}
//
//	//for(int i=0;i<tasks;i++) {
//	//for (int j = 0; j < data[0].size();j++) {
//	//	cout << data[i][j] << " " ;
//	//}
//	//cout << endl;
//	//}
//	//cout << endl;
//	sort(copy.begin(), copy.end(), [&](const vector<unsigned>& v1, const vector<unsigned>& v2)
//		{
//			size_t s = v1.size()-1;
//			return v1[s] > v2[s];
//		});
//	for (int i = 0; i < tasks; i++) {
//		for (int j = 0; j < copy[0].size(); j++) {
//			cout << copy[i][j] << " ";
//		}
//		cout << endl;
//	}
//	cout << endl;
//
//	Matrix anwser;
//	unsigned temp = 0,temp2=0;
//	anwser.push_back(copy[0]);
//	copy.erase(copy.begin());
//	anwser.push_back(copy[0]);
//	copy.erase(copy.begin());
//	for(int i =0;i< anwser.size();i++) {
//		
//	}
//
//
//
//	
//	temp = calculate_Cmax(anwser);
//	swap(anwser[0], anwser[1]);
//	temp2 = calculate_Cmax(anwser);
//	cout << temp << endl << temp2 << endl;
//
//	for (int i = 0; i < anwser.size(); i++) {
//		for (int j = 0; j < anwser[0].size(); j++) {
//			cout << anwser[i][j] << " ";
//		}
//		cout << endl;
//	}
//	cout << endl;
//
//	for (int i = 0; i < copy.size(); i++) {
//		for (int j = 0; j < copy[0].size(); j++) {
//			cout << copy[i][j] << " ";
//		}
//		cout << endl;
//	}
//	cout << endl;
//}
bool comp(const std::vector<unsigned>& v1, std::vector<unsigned>& v2) {
	short min_v1 = v1[0] > v1[1] ? 1 : 0;
	short min_v2 = v2[0] > v2[1] ? 1 : 0;
	return v1[min_v1] < v2[min_v2];
}