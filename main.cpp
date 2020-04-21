#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
static long liczba_wywolan = 0;
typedef vector<vector<unsigned>> matrix;

struct task
{
	unsigned p;
	unsigned ID;
};
//typedef vector<vector<task>> matrix;
matrix load_data(unsigned nuber_of_file) {
	int tasks, machines, temp, temp2, id = 1;
	matrix data;
	//vector<unsigned> vtemp;
	vector<unsigned> vtemp;
	std::ifstream file;
	file.open("data/data005.txt", ios::out);
	//file.open("data/" + names[nuber_of_file], std::ios::out);
	file >> tasks >> machines;
	for (int i = 0; i < tasks; i++) {
		for (int j = 0; j < machines; j++) {
			//task temp3; 
			file >> temp >> temp2;
			//temp3.p = temp2;
			/*temp3.ID = j;*/
			vtemp.push_back(temp2);
			//vtemp.push_back(temp3);
		}
		vtemp.push_back(i+1);
		data.push_back(vtemp);
		vtemp.clear();
	}
	//cout << dane.size();
	for(int i=0;i<tasks;i++) {
		for (int j = 0; j < machines+1;j++) {
			cout << data[i][j] << " " ;
		}
		cout << endl;
	}

	//wypisanie podzadan dla zad 1
	//for(int i=0;)
	file.close();
	return data;
}

int calculate_F(const matrix& data) {
	liczba_wywolan++;
	unsigned tasks = data.size();
	unsigned machines = data[1].size()-1;
	//cout <<"Liczba zadan: "<< tasks << endl;
	//cout << "Liczba maszyn: " << machines << endl;
	vector<unsigned> temp(tasks, 0);
	//vector<task> temp(tasks,0);
	matrix S(machines, temp);
	matrix C(machines, temp);
	for (int i = 0; i < machines; i++) {
		//kolumna
		for (int j = 0; j < tasks; j++) {
			//wiersz
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
				S[i][j] = max(C[i][j - 1], C[i - 1][j]);
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
bool compareID(const vector<unsigned> v1, vector<unsigned> v2) {
	size_t size = v1.size()-1;
	return v1[size] < v2[size];
}

int brute_force_iteration(matrix data) {
	int bestCmax = UINT16_MAX;
	int temp = 0;
	do {
		temp = calculate_F(data);
		if (temp < bestCmax) bestCmax = temp;
	} while (next_permutation(data.begin(),data.end(),compareID));
	return bestCmax;
}


int bestCmax = INT16_MAX;
int temp;
void findPermutations(matrix str, int index, size_t n) {
	if (index >= n) {
		temp = calculate_F(str);
		if (temp < bestCmax) {
			bestCmax = temp;
		}
		return;
	}
	for (int i = index; i < n; i++) {
		std::swap(str[index], str[i]);
		findPermutations(str, index + 1, n);
		std::swap(str[index], str[i]);
	}
}
int main() {
	matrix data = load_data(2);
	//cout << calculate_F(data);
	cout << brute_force_iteration(data)<<endl;
	//cout << "liczba wywolan: " << liczba_wywolan << endl;
	//findPermutations(data, 0, data.size());
	//cout << bestCmax << endl;
	return 0;
}
