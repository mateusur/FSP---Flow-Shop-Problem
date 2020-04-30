#include "Algorithm.h"

#include <algorithm>

int Algorithm::calculate_Cmax(std::vector<unsigned> kolejnosc) {
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
				s[i][j] = std::max(c[i][j - 1], c[i - 1][j]);
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

int Algorithm::calculate_Cmax(const Matrix& data) {
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
				c[i][j] = s[i][j] + data[j][i];
			}
			else if (j == 0) {
				s[i][j] = c[i - 1][j];
				c[i][j] = s[i][j] + data[j][i];
			}
			else {
				s[i][j] = std::max(c[i][j - 1], c[i - 1][j]);
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
