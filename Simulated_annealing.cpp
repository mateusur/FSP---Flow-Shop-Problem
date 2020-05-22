#include "Simulated_annealing.h"

#include <chrono>
#include <ctime>
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

Anwser Simulated_annealing::Algorithm(const short &init_temp, const short& init_L, const short& init_x, const short& init_alfa, const double &temperature_end,const short &mode) {
	const float temperature_table[3] = { 100,1000,10000 }; //100, 1000, 10000
	int data_size = data.size();
	const int L_table[3] = { sqrt(data_size),data_size,pow(data_size,2) }; //sqrt, n, n^2
	double temperature = temperature_table[init_temp-1];
	const float x_table[3] = { temperature / 1000.0,temperature / 10000,temperature / 100000 }; // T0/1000 , T0/10000 , T0/100000
	const float alfa_table[3] = { 0.97,0.95,0.9 }; // 0.97 ; 0.95 ; 0.9 ;
	vector<unsigned> pi = pi_order;
	vector<unsigned> best_pi = pi;
	int best_cmax = calculate_Cmax(best_pi);
	//cout << "Poczatkowy cmax: " << best_cmax << endl;
	//double temperature_end = 0.1;//5.6053e-45;//1e-300;// //0; //
	
	int L = L_table[init_L-1];
	float x = x_table[init_x-1];
	float alfa = alfa_table[init_alfa-1];
	long iteration = 0;
	srand(time(NULL));
	auto start = std::chrono::steady_clock::now();
	while (temperature>temperature_end) {
		iteration++;
		for(int k=0;k<L;k++) {
			auto end = std::chrono::steady_clock::now();
			auto czas = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
			if (czas >  60000)
				return { best_cmax,best_pi };
			int i = rand() % (data_size - 1);
			int j = rand() % (data_size - 1);
			while (i==j) 
				j = rand() % data_size;
			vector<unsigned> new_pi = pi;
			swap(new_pi[i], new_pi[j]);
			int new_cmax = calculate_Cmax(new_pi);
			int pi_cmax = calculate_Cmax(pi);
			if(new_cmax>pi_cmax) {
				float r = (rand() % 100) /100.00;
				float temp = exp((pi_cmax - new_cmax) / double (temperature));
				if (r >= temp) {
					new_pi = pi;
				}
			}
			pi = new_pi;
			if(calculate_Cmax(pi)<best_cmax) {
				best_cmax = new_cmax;
				best_pi = pi;
				//cout << "Best cmax:	" << best_cmax << endl;
			}
		}
		if(mode==1)
		temperature *= alfa;
		else if(mode==2) 
			temperature -= x;
		else if(mode==3)
			temperature = temperature / log(iteration + 1);
		//cout << temperature << endl;
		
	}
	return {best_cmax,best_pi};
}

//ta1  & 1216 & 1192 & 1269 & 1277 & 1254 & 1266 & 1269 & 1192   \\
//ta11 & 1657 & 1586 & 1589 & 1734 & 1604 & 1642 & 1678 & 1545  \\
//ta21 & 2346 & 2304 & 2432 & 2443 & 2390 & 2388 & 2413 & 2249  \\
//ta31 & 2732 & 2706 & 2799 & 2890 & 2786 & 2775 & 2805 & 2706  \\
//ta41 & 3186 & 3035 & 3205 & 3399 & 3159 & 3192 & 3250 & 3027  \\
//ta51 & 4197 & 3974 & 4125 & 4376 & 4023 & 4163 & 4228 & 3928  \\
//ta61 & 5493 & 5475 & 5589 & 5589 & 5589 & 5524 & 5589 & 5427  \\
//ta71 & 6006 & 5865 & 6080 & 6270 & 5945 & 5972 & 6036 & 5771  \\
//ta81 & 6770 & 6399 & 6779 & 7031 & 6687 & 6694 & 6841 & 6858  \\
//ta91 & 11040 & 10938 & 11128 & 11507 & 11038 & 11117 & 11098 & 11341   \\
//ta101 & 12192 & 11502 & 11996 & 12564 & 11847 & 11884 & 12137 & 12661  \\
//ta111 & 28847 & 29002 & 27615 & 28541 & 27127 & 27399 & 27714 & 29037  \\






















