#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
typedef vector<vector<unsigned>> Matrix;
std::string names[6] = {
	"data001.txt",
	"data002.txt",
	"data003.txt",
	"data004.txt",
	"data005.txt",
	"data006.txt",
};


class Brute_force
{
	Matrix s, c,data;
	int bestCmax = UINT16_MAX;
	vector<unsigned> pi_order;
public:
	Brute_force(unsigned nuber_of_file);
	//Matrix load_data(unsigned nuber_of_file);
	int calculate_Cmax(vector<unsigned> kolejnosc);
	int calculate_Cmax(const Matrix& data);
	int brute_force_iteration();
	int brute_force_recursion( int index);
	~Brute_force() {}
};
Brute_force::Brute_force(unsigned nuber_of_file) {
	int tasks, machines, machine_num, p_time;
	/*Matrix data;*/
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
	int Cmax = c[machines - 1][tasks - 1];
	return Cmax;
}
int Brute_force::calculate_Cmax(const Matrix& data) {
	//static short number_of_calls = 0;
	unsigned tasks = data.size();
	unsigned machines = data[1].size() - 1;

	vector<unsigned> temp(tasks, 0);
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


int main() {
	
	int n = 1;
	long long czas = 0;
	for (int i = 0; i < 6; i++) {
		//Matrix data = load_data(i);
		Brute_force obiekt(i);
		czas = 0;
		for (int i = 0; i < n; i++) {
			auto start = std::chrono::steady_clock::now();
			cout << obiekt.brute_force_iteration();
			auto end = std::chrono::steady_clock::now();
			czas += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		}
		cout << "\nCzas iteracji dla klasy n= " << i + 1 << ": " << double(czas / n) << endl;
		czas = 0;
		for (int i = 0; i < n; i++) {
			auto start = std::chrono::steady_clock::now();
			//brute_force_recursion(data, 0, data.size());
			cout << obiekt.brute_force_recursion(0);
			auto end = std::chrono::steady_clock::now();
			czas += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		}
		cout << "\nCzas iteracji2 dla n= " << i + 1 << ": " << double(czas / n) << endl ;
		//cout << "\nBest Cmax: " << bestCmax << endl;
		//bestCmax = INT16_MAX;
	}
	
	return 0;
}
Matrix load_data(unsigned nuber_of_file) {
	int tasks, machines, machine_num, p_time;
	Matrix data;
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
	return data;
}
int calculate_Cmax(const Matrix& data) {
	unsigned tasks = data.size();
	unsigned machines = data[1].size() - 1;
	//cout <<"Liczba zadan: "<< tasks << endl;
	//cout << "Liczba maszyn: " << machines << endl;
	vector<unsigned> temp(tasks, 0);
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
int calculate_Cmax(const Matrix& data, vector<unsigned> kolejnosc) {
	//static short number_of_calls = 0;
	unsigned tasks = data.size();
	unsigned machines = data[1].size() - 1;

	vector<unsigned> temp(tasks, 0);
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
				S[i][j] = max(C[i][j - 1], C[i - 1][j]);
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
bool compareID(const vector<unsigned>& v1, vector<unsigned>& v2) {
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
	vector<unsigned> pi(data.size());
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
int bestCmax = INT16_MAX;
void brute_force_recursion(Matrix& data, int index, size_t n) {
	int temp;
	if (index >= n) {
		temp = calculate_Cmax(data);
		if (temp < bestCmax) {
			bestCmax = temp;
		}
		return;
	}
	for (int i = index; i < n; i++) {
		std::swap(data[index], data[i]);
		brute_force_recursion(data, index + 1, n);
		std::swap(data[index], data[i]);
	}
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