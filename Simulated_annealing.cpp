#include "Simulated_annealing.h"
#include <iostream>
#include "fstream"
#include "cmath"
using namespace std;

Simulated_annealing::Simulated_annealing(int number_of_file) {
	int tasks, machines, machine_num, p_time;
	std::vector<unsigned> v_temp;
	std::ifstream file;
	std::string name;
	if (number_of_file < 10)
		name = "ta00" + std::to_string(number_of_file)+".txt";
	else if( number_of_file <100)
		name= "ta0" + std::to_string(number_of_file) + ".txt";
	else
		name = "ta" + std::to_string(number_of_file) + ".txt";
	file.open("data/fspB/" + name, std::ios::in);
	string file_name;
	file >>file_name>> tasks >> machines;
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

int Simulated_annealing::Algorithm() {
	int temperature = 100;
	vector<unsigned> pi = pi_order;
	int temperature_end = 90;
	int data_size = data.size();
	int L = sqrt(data_size);
	int x = temperature / 1000;
	float alfa = 0.97;
	while (temperature>temperature_end) {
		for(int k=0;k<L;k++) {
			int i = rand() % data_size;
			int j = rand() % data_size;
		}
	}
}
