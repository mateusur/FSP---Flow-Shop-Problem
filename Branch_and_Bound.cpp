#include "Branch_and_Bound.h"

#include <algorithm>
#include <iostream>


#include "fstream"

int Branch_and_Bound::bound(std::vector<unsigned> pi, std::vector<unsigned> avaliable) {
	std::vector<unsigned> max;
	unsigned tasks = data.size();
	unsigned machines = data[1].size() - 1;
	for (int i = 0;i < machines;i++) {
		for(int j=0;j<tasks;j++) {
			s[i][j] = 0;
			c[i][j] = 0;
		}
	}
	calculate_Cmax(pi);
	for(int i=0;i<machines;i++) {
		int sum=0;
		sum += c[i][pi.size()-1];
		//std::cout << sum << std::endl;
		for(int k=0;k<avaliable.size();k++) {
			sum += data[avaliable[k]][i];
		}
		/*for(int d=i+1;d<machines;d++) {
			std::vector<int> min_p;
			for(int b=pi.size();b<tasks;b++) {
				min_p.push_back(data[b][d]);
			}
			sum += *min_element(min_p.begin(),min_p.end());
		}*/
		
		max.push_back(sum);
	}
	return *max_element(max.begin(),max.end());
}

Branch_and_Bound::Branch_and_Bound(int nuber_of_file) {
	int tasks, machines, machine_num, p_time;
	std::vector<unsigned> v_temp;
	std::ifstream file;
	file.open("data/data007.txt", std::ios::out);
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
	for(int i=0;i<data.size();i++) {
		for(int j=0;j<data[0].size();j++) {
			std::cout << data[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::vector<unsigned> pi_order(data.size());
	for (int i = 0; i < pi_order.size(); i++)
		pi_order[i] = i;

	
}

int Branch_and_Bound::BnB(int j, Matrix N, std::vector<unsigned> pi, std::vector<unsigned> avaliable) {
	int sizeN = N[0].size()-1;
	pi.push_back(j);
	avaliable.erase(std::remove(avaliable.begin(), avaliable.end(), j));
	if(!avaliable.empty()) {
		int LB = bound(pi,avaliable);
		if(LB<=UB) {
			for (int j = 0;j < avaliable.size();j++) {
				BnB(avaliable[j], N, pi,avaliable);
			}	
		}
	}
	else {
		Cmax = calculate_Cmax(pi);
		/*for(auto k:pi) {
			std::cout << k << " ";
		}
		std::cout << std::endl;
		std::cout << Cmax << std::endl;*/
		if(Cmax<UB) {
			UB = Cmax;
			//pi = pi_order;
		}
	}
	return Cmax;
}

void Branch_and_Bound::bnb() {
	std::vector<unsigned> pi_order2;
	std::vector<unsigned> avaliable = { 0,1,2,3 };
	for(int j=0;j<data.size();j++) {
		 BnB(j, data, pi_order2,avaliable);
		pi_order2.clear();
	}
	std::cout << UB << std::endl;
}

