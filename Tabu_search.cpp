#include "Tabu_search.h"

#include <algorithm>
#include <fstream>
#include <iostream>

#include "NEH.h"

using namespace std;

int Tabu_search::calculate_Cmax(const std::vector<unsigned>& kolejnosc) {
	unsigned tasks = data.size();
	unsigned machines = data[1].size();

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
	//std::cout << "Wartosci S: " << std::endl;
	//	for (int i = 0; i < machines; i++) {
	//	for (int j = 0; j < tasks; j++) {
	//		cout << s[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	//std::cout <<"Wartosci C: "<< std::endl;
	//for (int i = 0; i < c.size(); i++) {
	//	for (int j = 0; j < c[0].size(); j++) {
	//		std::cout << c[i][j] << " ";
	//	}
	//	std::cout << std::endl;
	//}
	int Cmax = c[machines - 1][kolejnosc.size() - 1];
	return Cmax;
}

vector<unsigned> Tabu_search::cricital_path(const std::vector<unsigned> &pi_order) {
	calculate_Cmax(pi_order);
	unsigned tasks = pi_order.size();
	unsigned machines = data[1].size();
	vector<machine_job> V_cricital_path;
	machine_job temp{ pi_order[tasks - 1],machines - 1,data[pi_order[tasks - 1]][machines - 1] };
	V_cricital_path.push_back(temp);
	int i = tasks - 1;
	int j = machines - 1;
	int current_length;
	int currentC;
	while (i != 0 || j != 0) {
		currentC = c[j][i];
		current_length = data[pi_order[i]][j];
		if (j != 0) {
			int C_over_current = c[j - 1][i];
			if (currentC - current_length == C_over_current) {
				j--;
				machine_job temp{ pi_order[i],j,data[pi_order[i]][j] };
				V_cricital_path.push_back(temp);
			}
			else {
				i--;
				machine_job temp{ pi_order[i],j,data[pi_order[i]][j] };
				V_cricital_path.push_back(temp);
			}
		}
		else {
			int C_left_current = c[j][i - 1];
			if (currentC - current_length == C_left_current) {
				i--;
				machine_job temp{ pi_order[i],j,data[pi_order[i]][j] };
				V_cricital_path.push_back(temp);
			}
			else {
				j--;
				machine_job temp{ pi_order[i],j,data[pi_order[i]][j] };
				V_cricital_path.push_back(temp);
			}
		}
	}
	
	return blocks(V_cricital_path);
}

void Tabu_search::remove(std::vector<unsigned>& v) {
	auto end = v.end();
	for (auto it = v.begin(); it != end; ++it) {
		end = std::remove(it + 1, end, *it);
	}

	v.erase(end, v.end());
}

std::vector<unsigned> Tabu_search::blocks(const std::vector<machine_job>& cricital_path) {
	vector<unsigned> anwser{};
	//vector<unsigned> test;
	for(int i=0;i<cricital_path.size()-1;++i) {
		//test.push_back(cricital_path[i].job_number);
		if(cricital_path[i].machine != cricital_path[i+1].machine) {
			anwser.push_back(cricital_path[i].job_number);
		}
	}
	//test.push_back(cricital_path[cricital_path.size() - 1].job_number);
	//remove(test);
	remove(anwser);
	return anwser;
}

Tabu_search::Tabu_search(const int& number_of_file) {
	nr_of_file = number_of_file;
	int tasks, machines, machine_num, p_time;
	std::vector<unsigned> v_temp;
	std::ifstream file;
	std::string name;
	if (number_of_file < 10)
		name = "ta00" + std::to_string(number_of_file) + ".txt";
	else if (number_of_file < 100)
		name = "ta0" + std::to_string(number_of_file) + ".txt";
	else
		name = "ta" + std::to_string(number_of_file) + ".txt";
	file.open("data/fspB/" + name, std::ios::in);
	std::string file_name;
	file >> file_name >> tasks >> machines;
	for (int i = 0; i < tasks; i++) {
		for (int j = 0; j < machines; j++) {
			file >> machine_num >> p_time;
			//file  >> p_time;
			v_temp.push_back(p_time);
		}
		//v_temp.push_back(i + 1); // Adding id at last column
		data.push_back(v_temp);
		v_temp.clear();
	}
	file.close();
	std::vector<unsigned> temp(tasks, 0);
	for (int i = 0; i < machines; i++) {
		s.push_back(temp);
		c.push_back(temp);
	}
	for (int i = 0; i < data.size(); i++)
		pi_order.push_back(i);
	std::vector<int> temp2(tasks, 0);
	for (int i = 0; i < tasks; i++)
		tabu_matrix.push_back(temp2);

	for (int i = 0; i < tasks; i++) {
		for (int j = 0; j < tasks; j++) {
			if (i == j) {
				tabu_matrix[i][j] = -1;
				break;
			}

		}
	}
}

Anwser Tabu_search::algorithm() {
	//NEH obiekt(nr_of_file);
	vector<unsigned> pi = pi_order;
	vector<unsigned> pi_new =pi;
	vector<unsigned> best_pi = pi;
	auto pi_size = pi.size();
	int it_limit = 1000;
	int iteration = 1;
	int j2=0, k2=0;
	int square = sqrt(pi_size);
	int C_best=0;
	int bestCmax = calculate_Cmax(pi);
	for(int i=0;i<it_limit;i++,++iteration) {
		 C_best = INT16_MAX;
		for(auto j=0;j<pi_size;j++) {
			for(auto k=j+1;k<pi_size-1;k++) {
				if(tabu_matrix[j][k]<iteration) {
					//move(pi.begin() + j, pi.begin() + j+1, pi_new.begin() + k);
					pi_new = pi;
					swap(pi_new[j], pi_new[k]);
					int calculate_new = calculate_Cmax(pi_new);
					if(calculate_new < C_best) {
						C_best = calculate_new;
						j2 = j;
						k2 = k;
					}
				}
			}
		}
		//move(pi.begin() + j2, pi.begin() + j2 + 1, pi.begin() + k2);
		swap(pi[j2], pi[k2]);
		tabu_matrix[j2][k2] = iteration + square;
		int calculate_pi = calculate_Cmax(pi);
		int tempCmax = calculate_Cmax(best_pi);
		if (calculate_pi < tempCmax) {
			best_pi = pi;
			bestCmax = tempCmax;
		}
	}
	//cout << best_pi;
	//cout << calculate_Cmax(best_pi) << endl;
	return { bestCmax, best_pi};
}

Anwser Tabu_search::algorithm_with_blocks()
{
	//NEH obiekt(nr_of_file);
	vector<unsigned> pi = pi_order;
	vector<unsigned> pi_new = pi;
	vector<unsigned> best_pi = pi;
	auto pi_size = pi.size();
	int it_limit = 1000;
	int iteration = 1;
	int j2 = 0, k2 = 0;
	int square = sqrt(pi_size);
	int C_best = 0;
	int bestCmax = calculate_Cmax(pi);
	for (int i = 0; i < it_limit; i++, ++iteration) {
		C_best = INT16_MAX;
		vector<unsigned> jobs_in_blocks = cricital_path(pi);
		for (int d = 0;d < jobs_in_blocks.size();d++) {
			vector<unsigned>::iterator it = std::find(pi.begin(), pi.end(), jobs_in_blocks[d]);
			int j  = it - pi.begin();
			for(int l=0;l<2;l++) {
				int k=j;
				if(l==0) {
					k--;
					if(j==0)
						break;
				}
				else {
					k++;
					if(j==pi_size-1)
						break;;
				}
				if (tabu_matrix[j][k] < iteration) {
					pi_new = pi;
					swap(pi_new[j], pi_new[k]);
					int calculate_new = calculate_Cmax(pi_new);
					if (calculate_new < C_best) {
						C_best = calculate_new;
						j2 = j;
						k2 = k;
					}
				}
			}

		}

		swap(pi[j2], pi[k2]);
		tabu_matrix[j2][k2] = iteration + square;
		int calculate_pi = calculate_Cmax(pi);
		int tempCmax = calculate_Cmax(best_pi);
		if (calculate_pi < tempCmax) {
			best_pi = pi;
			bestCmax = tempCmax;
		}
	}
	return {bestCmax, best_pi};
}
