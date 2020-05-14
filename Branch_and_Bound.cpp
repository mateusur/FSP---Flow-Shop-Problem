#include "Branch_and_Bound.h"
#include <algorithm>
#include <iostream>
#include "fstream"
#include "NEH.h"

int Branch_and_Bound::bound(std::vector<unsigned> pi, std::vector<unsigned> available) {
	std::vector<unsigned> max;
	unsigned tasks = data.size();
	unsigned machines = data[1].size() - 1;
	calculate_Cmax(pi);
	for (int i = 0;i < machines;i++) {
		int sum = 0;
		sum += c[i][pi.size() - 1];
		//std::cout << sum << std::endl;
		for (int k = 0;k < available.size();k++) {
			sum += data[available[k]][i];
		}
		max.push_back(sum);
	}
	return *max_element(max.begin(), max.end());
}

int Branch_and_Bound::bound2(std::vector<unsigned> pi, std::vector<unsigned> available) {
	std::vector<unsigned> max;
	unsigned tasks = data.size();
	unsigned machines = data[1].size() - 1;
	calculate_Cmax(pi);
	for (int i = 0;i < machines;i++) {
		int sum = 0;
		sum += c[i][pi.size() - 1];
		//std::cout << sum << std::endl;
		for (int k = 0;k < available.size();k++) {
			sum += data[available[k]][i];
		}
		for (int d = i + 1;d < machines;d++) {
			std::vector<int> min_p;
			for (int c = 0;c < data.size();c++)
				min_p.push_back(data[c][d]);
			//std::cout << "rozmiar min_p: " << min_p.size() << std::endl;
			sum += *min_element(min_p.begin(), min_p.end());
		}
		max.push_back(sum);
	}
	return *max_element(max.begin(), max.end());
}

int Branch_and_Bound::bound3(std::vector<unsigned> pi, std::vector<unsigned> available) {
	std::vector<unsigned> max;
	unsigned tasks = data.size();
	unsigned machines = data[1].size() - 1;
	calculate_Cmax(pi);
	for(int i=0;i<machines;i++) {
		int sum=0;
		sum += c[i][pi.size()-1];
		//std::cout << sum << std::endl;
		for(int k=0;k<available.size();k++) {
			sum += data[available[k]][i];
		}
		for(int d=i+1;d<machines;d++) {
			std::vector<int> min_p;
			for(int c=0;c<available.size();c++)
				min_p.push_back(data[available[c]][d]);
			//std::cout << "rozmiar min_p: " << min_p.size() << std::endl;
			sum += *min_element(min_p.begin(), min_p.end());
		}
		max.push_back(sum);
	}
	return *max_element(max.begin(),max.end());
}

int Branch_and_Bound::bound4(std::vector<unsigned> pi, std::vector<unsigned> available) {
	std::vector<unsigned> max;
	unsigned tasks = data.size();
	unsigned machines = data[1].size() - 1;
	for (int i = 0;i < machines;i++) {
		for (int j = 0;j < tasks;j++) {
			s[i][j] = 0;
			c[i][j] = 0;
		}
	}
	calculate_Cmax(pi);
	for (int i = 0;i < machines;i++) {
		int sum = 0;
		sum += c[i][pi.size() - 1];
		//std::cout << sum << std::endl;
		for (int k = 0;k < available.size();k++) {
			sum += data[available[k]][i];
		}
		std::vector<int> min_sum;
		for (int c = 0;c < available.size();c++) {
			int temp_sum = 0;
			for (int d = i + 1;d < machines;d++) {
				temp_sum += data[available[c]][d];
			}
			min_sum.push_back(temp_sum);
		}
		if(!min_sum.empty()) 
			sum += *min_element(min_sum.begin(), min_sum.end());
		max.push_back(sum);
	}
	return *max_element(max.begin(), max.end());
}

Branch_and_Bound::Branch_and_Bound(int nuber_of_file) {
	int tasks, machines, machine_num, p_time;
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

int Branch_and_Bound::BnB(int job, std::vector<unsigned> pi, std::vector<unsigned> available) {
	count++;
	pi.push_back(job);
	available.erase(std::remove(available.begin(), available.end(), job));
	if(!available.empty()) {
		int LB = bound(pi,available);
		if(LB<UB) {
			for (int j = 0;j < available.size();j++) 
				BnB(available[j], pi,available);	
		}
	}
	else {
		Cmax = calculate_Cmax(pi);
		if(Cmax<UB) {
			UB = Cmax;
			pi_order = pi;
		}
	}
	return Cmax;
}

void Branch_and_Bound::bnb(int i) {
	count = 0;
	std::vector<unsigned> pi_order2;
	NEH obiekt2(i);
	pi_order = obiekt2.NEH_algorithm();
	std::vector<unsigned> available=pi_order;
	for(int job=0;job<data.size();job++) {
		 BnB(job, pi_order2,available );
		pi_order2.clear();
	}
	for (int i = 0; i < pi_order.size(); i++)
		std::cout << pi_order[i] << " ";
	std::cout << UB << std::endl;
	std::cout <<"Liczba wywolan: " <<count << std::endl;
}

