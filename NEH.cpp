#include "NEH.h"

#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;
vector<unsigned> NEH::calculate_weights() {
	vector<weights> anwser;
	unsigned tasks = data.size();
	unsigned machines = data[1].size();
	vector<unsigned> anwser_order;

	for(int i=0;i<tasks;i++) {
		int temp_sum = 0;
		for(int j=0;j<machines;j++) {
			temp_sum += data[i][j];
			//cout << data[i][j] << " ";
		}
		//cout << endl;
		weights temp{ i,temp_sum };
		anwser.push_back(temp);
	}

	sort(anwser.begin(), anwser.end(),[](const weights &w1, const weights& w2)
	{
			return w1.sum > w2.sum;
	});
	//for (auto k : anwser)
	//	cout << k.position << " " << k.sum << endl;
	//cout << endl;
	for (auto k : anwser)
		anwser_order.push_back(k.position);

	/*for (auto k : anwser_order)
		cout << k+1 << " ";
	cout << endl;*/
	return anwser_order;
}

int NEH::calculate_Cmax(std::vector<unsigned> kolejnosc) {
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

std::vector<machine_job> NEH::critical_path( std::vector<unsigned> pi_order) {
	calculate_Cmax(pi_order);
	unsigned tasks = pi_order.size();
	unsigned machines = data[1].size();
	vector<machine_job> V_cricital_path;
	machine_job temp{ pi_order[tasks - 1],machines - 1,data[pi_order[tasks - 1]][machines - 1] };
	V_cricital_path.push_back(temp);
	int i = tasks-1;
	int j = machines-1;
	int current_length;
	int currentC;
	while (i !=0 || j!=0) {
		currentC = c[j][i];
		current_length = data[pi_order[i]][j];
		if(j != 0) {
			int C_over_current = c[j - 1][i];
			if(currentC-current_length==C_over_current) {
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
			int C_left_current = c[j][i-1];
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
	return V_cricital_path;
}

std::vector<unsigned> NEH::helper( std::vector<unsigned> pi_vector) {
	int temp_sum = 0;
	vector<unsigned> pi_anwser;
	int bestCmax = INT16_MAX;
	unsigned tasks = data.size();
	unsigned machines = data[1].size() - 1;
	for (int i = 0;i < machines;i++) {
		for (int j = 0;j < tasks;j++) {
			s[i][j] = 0;
			c[i][j] = 0;
		}
	}
	temp_sum = calculate_Cmax(pi_vector);
	/*cout << "Wartosc cmax: " << temp_sum << endl;
	cout << "Dla vectora: ";
	for (auto k : pi_vector)
		cout << k + 1 << " ";
	cout << endl;*/
	if (temp_sum <= bestCmax) {
		bestCmax = temp_sum;
		pi_anwser = pi_vector;
		/*cout << "Best cmax: " << bestCmax << endl;*/
	}
	for (int i = pi_vector.size() - 1; i > 0; i--) {
		/*cout << "Pi vector: ";
		for (auto k : pi_vector)
			cout << k << " ";
		cout << endl;*/
		std::swap(pi_vector[i], pi_vector[i - 1]);
		unsigned tasks = data.size();
		unsigned machines = data[1].size() - 1;
		for (int i = 0;i < machines;i++) {
			for (int j = 0;j < tasks;j++) {
				s[i][j] = 0;
				c[i][j] = 0;
			}
		}
		
		temp_sum = calculate_Cmax(pi_vector);
		critical_path(pi_vector);
		/*cout << "Wartosc cmax: " << temp_sum << endl;
		cout << "Dla vectora: ";
		for (auto k : pi_vector)
			cout << k + 1 << " ";
		cout << endl;*/
		if (temp_sum <= bestCmax) {
			bestCmax = temp_sum;
			pi_anwser = pi_vector;
			/*cout << "Pi anwser: ";
			for (auto k : pi_anwser)
				cout << k << " ";
			cout << endl;*/
			/*cout << "Best cmax: " << bestCmax << endl;*/
		}

	}
	return  pi_anwser;
}

std::vector<unsigned> NEH::biggest_Cmax_diffrence(std::vector<unsigned> pi_vector, int forbidden_job) {
	int temp_Cmax;
	int job_number;
	int diffrence;
	int bestCmax = calculate_Cmax(pi_vector);
	vector<unsigned> best_pi;
	for (int i = 0; i < pi_vector.size();i++) {
		diffrence = INT16_MIN;
		if (pi_vector[i] != forbidden_job) {
			int deleted_job = pi_vector[i];
			cout << "Przed erase: ";
			for (auto element : pi_vector) {
				cout << element + 1 << " ";
			}
			vector<unsigned> copy = pi_vector;
			pi_vector.erase(std::remove(pi_vector.begin(), pi_vector.end(), deleted_job));
			cout << "Po erase: ";
			for (auto element : pi_vector) {
				cout << element+1 << " ";
			}
			cout << endl;
			temp_Cmax = calculate_Cmax(pi_vector);
			cout << "best cmax -temp wynosi: " << bestCmax - temp_Cmax << endl;
			if (diffrence < bestCmax - temp_Cmax) {
				diffrence = bestCmax - temp_Cmax;
				job_number = deleted_job;
				best_pi = pi_vector;
				cout << "Roznica wynosi: " << diffrence << endl;
				cout << "Usunelismy zadanie: " << job_number+1 << endl;
			}
			pi_vector = copy;
			cout << "I cofamy do : ";
			for (auto element : pi_vector) {
				cout << element+1 << " ";
			}
			cout << endl;
		}
	}

	cout << "A wiec ostateczny vektor : ";
	for (auto element : best_pi) {
		cout << element + 1 << " ";
	}
	cout << endl;
	return best_pi;
}

NEH::NEH(int nuber_of_file) {
	int tasks, machines, machine_num, p_time;
	std::vector<unsigned> v_temp;
	std::ifstream file;
	file.open("data/" + names[nuber_of_file], std::ios::in);
	file >> tasks >> machines;
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
	//for(int i=0;i<data.size();i++) {
	//	for(int j=0;j<data[0].size();j++) {
	//		std::cout << data[i][j] << " ";
	//	}
	//	std::cout << std::endl;
	//}
	//std::cout << std::endl;

	for (int i = 0; i < data.size(); i++)
		pi_order.push_back(i);

}

vector<unsigned> NEH::NEH_algorithm() {
	vector<unsigned> weight_vector= calculate_weights();
	vector<unsigned> pi_vector;
	while (!weight_vector.empty()) {
		pi_vector.push_back(weight_vector[0]);
		weight_vector.erase(weight_vector.begin());
		pi_vector = helper(pi_vector);
	}
	
	cout << "Wynik: ";
	for (auto k : pi_vector)
		cout << k << " ";
	cout << endl;
	//cout << "Cmax: " << bestCmax;
	//return calculate_Cmax(pi_vector);
	return pi_vector;
}

int NEH::job_that_reduce_cmax_most() {
	vector<unsigned> weight_vector = calculate_weights();
	vector<unsigned> pi_vector;
	vector<unsigned> copy;
	while (!weight_vector.empty()) {
		pi_vector.push_back(weight_vector[0]);
		//weight_vector.erase(weight_vector.begin());
		pi_vector = helper(pi_vector);
		//acceleration // NEH+
		if (pi_vector.size() > 2) {
			pi_vector = biggest_Cmax_diffrence(pi_vector, weight_vector[0]);
		}
		
		/*cout << "KONIEC JEDNEGO OBROTU, NASTEPNE ZADANIE " << endl;*/
		weight_vector.erase(weight_vector.begin());
	}
	cout << "Wynik: ";
	for (auto k : pi_vector)
		cout << k << " ";
	cout << endl;
	//cout << "Cmax: " << bestCmax;
	return calculate_Cmax(pi_vector);
}

int NEH::job_with_longest_operation_on_critical_path() {
	vector<unsigned> weight_vector = calculate_weights();
	vector<unsigned> pi_vector;
	unsigned machines = data[1].size();
	int longest_job;
	int job_number = 0;
	while (!weight_vector.empty()) {
		pi_vector.push_back(weight_vector[0]);
		int forbidden_job = weight_vector[0];
		weight_vector.erase(weight_vector.begin());
		pi_vector = helper(pi_vector);

		if(pi_vector.size()>2) {
			vector<machine_job> critic_path = critical_path(pi_vector);
			sort(critic_path.begin(), critic_path.end(), [&](const machine_job& j1, const machine_job& j2)
				{
					return j1.time > j2.time;
				});
			int temp = 0;
			while (forbidden_job == critic_path[temp].job_number)
				temp++;
			job_number = critic_path[temp].job_number;
			
			pi_vector.erase(std::remove(pi_vector.begin(), pi_vector.end(), job_number));
			pi_vector.push_back(job_number);
			pi_vector = helper(pi_vector);
		}
	}//koniec while
	
	cout << "Wynik: ";
	cout << pi_vector;
	//cout << "Cmax: " << bestCmax;
	return calculate_Cmax(pi_vector);
}

int NEH::job_with_biggest_sum_time_on_crcital_path() {
	vector<unsigned> weight_vector = calculate_weights();
	vector<unsigned> pi_vector;
	unsigned machines = data[1].size();
	while (!weight_vector.empty()) {
		pi_vector.push_back(weight_vector[0]);
		int forbidden_job = weight_vector[0];
		weight_vector.erase(weight_vector.begin());
		pi_vector = helper(pi_vector);

		if (pi_vector.size() > 2) {
			vector<machine_job> critic_path = critical_path(pi_vector);
			
			int temp_job;
			int job_with_biggest_sum;
			int biggest_sum = INT16_MIN;
			for (int i = 0;i < pi_vector.size();i++) {
				int temp_sum=0;
				temp_job = pi_vector[i];
				for (auto element : critic_path) {
					if(temp_job==element.job_number)
						temp_sum += element.time;
				}
				if (temp_sum > biggest_sum && temp_job != forbidden_job) {
					job_with_biggest_sum = pi_vector[i];
					biggest_sum = temp_sum;
				}
			}

			pi_vector.erase(std::remove(pi_vector.begin(), pi_vector.end(), job_with_biggest_sum));
			pi_vector.push_back(job_with_biggest_sum);
			pi_vector = helper(pi_vector);


		}
	}//koniec while

	cout << "Wynik: ";
	for (auto k : pi_vector)
		cout << k << " ";
	cout << endl;
	//cout << "Cmax: " << bestCmax;
	return calculate_Cmax(pi_vector);
}

int NEH::job_with_max_operations() {
	vector<unsigned> weight_vector = calculate_weights();
	vector<unsigned> pi_vector;
	unsigned machines = data[1].size();
	while (!weight_vector.empty()) {
		pi_vector.push_back(weight_vector[0]);
		int forbidden_job = weight_vector[0];
		weight_vector.erase(weight_vector.begin());
		pi_vector = helper(pi_vector);

		if (pi_vector.size() > 1) {
			vector<machine_job> critic_path = critical_path(pi_vector);
			int temp;
			int temp_job;
			int job_with_max;
			int length_job_with_max= INT16_MIN;
			for (int i = 0;i < pi_vector.size();i++) {
				int temp =count(critic_path.begin(), critic_path.end(), pi_vector[i]);
				temp_job = pi_vector[i];
				if (temp > length_job_with_max && temp_job != forbidden_job) {
					job_with_max = pi_vector[i];
					length_job_with_max = temp;
				}
			}

			pi_vector.erase(std::remove(pi_vector.begin(), pi_vector.end(), job_with_max));
			pi_vector.push_back(job_with_max);
			pi_vector = helper(pi_vector);

		}
	}//koniec while

	cout << "Wynik: ";
	cout << pi_vector;
	return calculate_Cmax(pi_vector);
}

std::ostream& operator<<(std::ostream& os, const std::vector<unsigned>& vector) {
	for (auto element : vector) {
		os << element + 1 << " ";
	}
	os << endl;
	return os;
}

bool operator==(const machine_job& j1, const int& j2) {
	return j1.job_number == j2;
}
