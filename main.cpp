#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>

#include "Brute_force.h"
#include "Johnson.h"
#include "Algorithm.h"
#include "BruteForce.h"
#include "Branch_and_Bound.h"
//#include "BruteForce.h"
#include "NEH.h"
#include "Simulated_annealing.h"
#include "Tabu_search.h"
using namespace std;

string names[7] = {
	"data001.txt",
	"data002.txt",
	"data003.txt",
	"data004.txt",
	"data005.txt",
	"data006.txt",
	"data007.txt"
};

int bestCmaxB = INT16_MAX;

int main() {
	//int n = 1;
	//long long czas = 0;
	//for (int i = 0; i < 6; i++) {
	//	if(i<5) {
	//		Matrix data = load_data(i);
	//		czas = 0;
	//		for (int i = 0; i < n; i++) {
	//			auto start = std::chrono::steady_clock::now();
	//			brute_force_iteration(data);
	//			auto end = std::chrono::steady_clock::now();
	//			czas += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	//		}
	//		cout << " Czas iteracji dla n= " << i + 1 << ": " << double(czas / n) << endl;
	//		czas = 0;
	//		for (int i = 0; i < n; i++) {
	//			auto start = std::chrono::steady_clock::now();
	//			brute_force_recursion(data, 0, data.size());
	//			auto end = std::chrono::steady_clock::now();
	//			czas += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	//		}
	//		cout << "Czas rekursji dla n= " << i + 1 << ": " << double(czas / n);
	//		//cout << " Best Cmax: " << bestCmax << endl;
	//	  bestCmaxB = INT16_MAX;
	//	}
	//	
	//	Brute_force obiekt(i);
	//	czas = 0;
	//	for (int i = 0; i < n; i++) {
	//		auto start = std::chrono::steady_clock::now();
	//		obiekt.brute_force_iteration();
	//		auto end = std::chrono::steady_clock::now();
	//		czas += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	//	}
	//	cout << "\nCzas iteracji dla klasy dla n= " << i + 1 << ": " << double(czas / n);
	//	czas = 0;
	//	for (int i = 0; i < n; i++) {
	//		auto start = std::chrono::steady_clock::now();
	//		obiekt.brute_force_recursion(0);
	//		auto end = std::chrono::steady_clock::now();
	//		czas += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	//	}
	//	cout << "\nCzas rekursji dla klasy dla n= " << i + 1 << ": " << double(czas / n) << endl<<endl;
	//
	//}
	//Johnson obiekt(0);
	//cout << obiekt.Johnson_algorithm();
	//obiekt.Johnson_algorithm();
	//std::ofstream file;
	//file.open("Wyniki_NEH2.txt", ios::app);
	//for(int i=41;i<=50;i+=1) {
	//	NEH obiekt2(i);
	//	file << "ta" + to_string(i) << " & ";
	//	file << obiekt2.NEH_algorithm().Cmax << " & ";
	//	file << obiekt2.job_with_longest_operation_on_critical_path().Cmax  << " & ";
	//	file << obiekt2.job_with_biggest_sum_time_on_crcital_path().Cmax << " & ";
	//	file << obiekt2.job_with_max_operations().Cmax << " & ";
	//	file << obiekt2.job_that_reduce_cmax_most().Cmax  << " \\\\ " << endl;
	//}
	//file.close();
	/*int liczba_wywolan = 10;
	long long time_sum = 0;
	std::ofstream file;
	file.open("Czasy_NEH.txt", ios::app);
	for (int i = 1;i <= 120;i += 10) {
		NEH obiekt2(i);
		file << "ta" + to_string(i) << " & ";
		time_sum = 0;
		for(int i=0;i<liczba_wywolan;i++) {
			auto start = std::chrono::steady_clock::now();
			obiekt2.NEH_algorithm().Cmax;
			auto end = std::chrono::steady_clock::now();
			auto czas = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
			time_sum += czas;
		}
		file << time_sum/liczba_wywolan << " & ";
		time_sum = 0;
		for (int i = 0;i < liczba_wywolan;i++) {
			auto start = std::chrono::steady_clock::now();
			obiekt2.job_with_longest_operation_on_critical_path().Cmax;
			auto end = std::chrono::steady_clock::now();
			auto czas = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
			time_sum += czas;
		}
		file << time_sum / liczba_wywolan << " & ";
		time_sum = 0;
		for (int i = 0;i < liczba_wywolan;i++) {
			auto start = std::chrono::steady_clock::now();
			obiekt2.job_with_biggest_sum_time_on_crcital_path().Cmax;
			auto end = std::chrono::steady_clock::now();
			auto czas = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
			time_sum += czas;
		}
		file << time_sum / liczba_wywolan << " & ";
		time_sum = 0;
		for (int i = 0;i < liczba_wywolan;i++) {
			auto start = std::chrono::steady_clock::now();
			obiekt2.job_with_max_operations().Cmax;
			auto end = std::chrono::steady_clock::now();
			auto czas = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
			time_sum += czas;
		}
		file << time_sum / liczba_wywolan << " & ";
		time_sum = 0;
		for (int i = 0;i < liczba_wywolan;i++) {
			auto start = std::chrono::steady_clock::now();
			obiekt2.job_that_reduce_cmax_most().Cmax;
			auto end = std::chrono::steady_clock::now();
			auto czas = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
			time_sum += czas;
		}
		file << time_sum / liczba_wywolan << " \\\\ " << endl;
	}
	file.close();*/
	//std::ofstream file;
	//file.open("Wyniki_SA.txt", ios::app);
	//for (int i = 1;i <= 120;i += 10) {
	//	Simulated_annealing SA(i);
	//	file << "ta" + to_string(i) << " & ";
	//	file << SA.Algorithm(1, 2, 1, 1, 0.1, 1).Cmax << " & ";
	//	file << SA.Algorithm(2, 2, 1, 1, 0.1, 1).Cmax << " & ";
	//	file << SA.Algorithm(3, 2, 1, 1, 0.1, 1).Cmax << " & ";
	//	file << SA.Algorithm(1, 2, 2, 1, 0.1, 1).Cmax << " & ";
	//	file << SA.Algorithm(2, 2, 2, 1, 0.1, 1).Cmax << " & ";
	//	file << SA.Algorithm(3, 2, 2, 1, 0.1, 1).Cmax << " & ";
	//	file << SA.Algorithm(1, 2, 3, 1, 0.1, 1).Cmax << " & ";
	//	file << SA.Algorithm(2, 2, 3, 1, 0.1, 1).Cmax << " & ";
	//	file << SA.Algorithm(3, 2, 3, 1, 0.1, 1).Cmax << " \\\\ " << endl;
	//}
	//file.close();
//	std::ofstream file;
//	file.open("Wyniki_SA.txt", ios::app);
//	for (int i = 101;i <= 120;i += 10) {
//	Simulated_annealing SA(i);
//	file << "ta" + to_string(i) << " & ";
//	file << SA.Algorithm(1, 2, 1, 1, 0.1, 2).Cmax << " & ";
//	file << SA.Algorithm(2, 2, 1, 1, 0.1, 2).Cmax << " & ";
//	file << SA.Algorithm(3, 2, 1, 1, 0.1, 2).Cmax << " & ";
//	cout << "policzone 3\n";
//	file << SA.Algorithm(1, 2, 2, 1, 0.1, 2).Cmax << " & ";
//	file << SA.Algorithm(2, 2, 2, 1, 0.1, 2).Cmax << " & ";
//	file << SA.Algorithm(3, 2, 2, 1, 0.1, 2).Cmax << " & ";
//	cout << "policzone 6\n";
//	file << SA.Algorithm(1, 2, 3, 1, 0.1, 2).Cmax << " & ";
//	file << SA.Algorithm(2, 2, 3, 1, 0.1, 2).Cmax << " & ";
//	file << SA.Algorithm(3, 2, 3, 1, 0.1, 2).Cmax << " \\\\ " << endl;
//	cout << "policzone end\n";
//}
//file.close();
//	std::ofstream file;
//	file.open("Wyniki_SA_zmienneL.txt", ios::app);
//	for (int i = ;i <= 120;i += 10) {
//	Simulated_annealing SA(i);
//	file << "ta" + to_string(i) << " & ";
//	file << SA.Algorithm(1, 1, 2, 1, 0.1, 2).Cmax << " & ";
//	file << SA.Algorithm(1, 2, 2, 1, 0.1, 2).Cmax << " & ";
//	file << SA.Algorithm(1, 3, 2, 1, 0.1, 2).Cmax << " & ";
//	cout << "policzone 3\n";
//	file << SA.Algorithm(2, 1, 2, 1, 0.1, 2).Cmax << " & ";
//	file << SA.Algorithm(2, 2, 2, 1, 0.1, 2).Cmax << " & ";
//	file << SA.Algorithm(2, 3, 2, 1, 0.1, 2).Cmax << " \\\\ " << endl;
//	//cout << "policzone 6\n";
//	//file << SA.Algorithm(3,1, 2, 1, 0.1, 2).Cmax << " & ";
//	//file << SA.Algorithm(3,2, 2, 1, 0.1, 2).Cmax << " & ";
//	//file << SA.Algorithm(3,3, 2, 1, 0.1, 2).Cmax << " \\\\ " << endl;
//	cout << "policzone end "<<i<< " \n";
//}
//file.close();
//Simulated_annealing SA(i);
//file << "ta" + to_string(i) << " & ";
//file << SA.Algorithm(1, 1, 2, 1, 0.1, 2).Cmax << " & ";
//file << SA.Algorithm(1, 2, 2, 1, 0.1, 2).Cmax << " & ";
//file << SA.Algorithm(1, 1, 2, 1, 0.1, 2).Cmax << " & ";
//cout << "policzone 3\n";
//file << SA.Algorithm(1, 1, 2, 1, 0.01, 2).Cmax << " & ";
//file << SA.Algorithm(1, 1, 2, 1, 0.01, 2).Cmax << " & ";
//file << SA.Algorithm(1, 2, 2, 1, 0.01, 2).Cmax << " & ";
//cout << "policzone 6\n";
//file << SA.Algorithm(1, 1, 2, 1, 0.001, 2).Cmax << " & ";
//file << SA.Algorithm(1,1, 2, 1, 0.001, 2).Cmax << " & ";
//file << SA.Algorithm(1, 2, 2, 1, 0.001, 2).Cmax << " \\\\ " << endl;
	//int init_temp[3]{1, 2, 3};
	//int init_L[3]{1,2,3};
	//int init_x[3]{ 1,2,3 };
	//int init_alfa[3]{ 1,2,3 };
	//double init_temEND[3]{ 0.1,0.01,0.001 };
	//int mode[3]{ 1,2,3 };
	//int temp, L, x, alfa, tempEND, mod;
	//srand(time(NULL));
	//std::ofstream file;
	//file.open("Wyniki_SA_zmienneWszystko.txt", ios::app);
	//for(int j=0;j<8;j++) {
	//	temp = rand() % 3;
	//	L = rand() % 3;
	//	x = rand() % 3;
	//	alfa = rand() % 3;
	//	tempEND = rand() % 3;
	//	mod = rand() % 3;
	//	if (mod == 0) {
	//		file << "Temp: " << temp << " L: " << L << " alfa: " << alfa << " tempEND: " << tempEND << " mod: " << mod << endl;
	//		cout << "Temp: " << temp << " L: " << L << " alfa: " << alfa << " tempEND: " << tempEND << " mod: " << mod << endl;
	//	}
	//	else if (mod == 1) {
	//		file << "Temp: " << temp << " L: " << L << " x: " << x << " tempEND: " << tempEND << " mod: " << mod << endl;
	//		cout << "Temp: " << temp << " L: " << L << " x: " << x << " tempEND: " << tempEND << " mod: " << mod << endl;
	//	}
	//	else {
	//		file << "Temp: " << temp << " L: " << L << " tempEND: " << tempEND << " mod: " << mod << endl;
	//		cout << "Temp: " << temp << " L: " << L << " tempEND: " << tempEND << " mod: " << mod << endl;
	//	}
	//	
	//	for (int i = 1;i <= 120;i += 10) {
	//	
	//		Simulated_annealing SA(i);
	//		if(j<10)
	//		file << "ta" + to_string(i) ;
	//		file <<" & " <<  SA.Algorithm(init_temp[temp], init_L[L], init_x[x], init_alfa[alfa], init_temEND[tempEND], mode[mod]).Cmax << " \\\\ " << endl;
	//		cout << "policzone end " << i << " \n";
	//		
	//	}
	//}
	//file.close();


int limit[2] = { 1000,5000 };
int cadency_nr[2] = { 0,1 };
	std::ofstream file,file2;
	file.open("Wyniki_TS_natural.txt", ios::app);
	file2.open("Czasy_TS_natural.txt", ios::app);
	for(int i=1;i<=120;i+=10) {
		cout << "NR pliku: " << i << endl;
		file << "ta" << i << "&";
		file2 << "ta" << i << "&";
		for(int j=0;j<2;j++) {
			for (int k = 0; k < 2;k++) {
				if (i < 80) {
					Tabu_search obiekt(i);
					auto start = std::chrono::steady_clock::now();
					file << obiekt.algorithm(limit[j],cadency_nr[k]).Cmax << "&" ;
					auto end = std::chrono::steady_clock::now();
					file2<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "&";
				}
				else {
					file << " &";
					file2 << " &";
				}
				Tabu_search obiekt2(i);
				auto start = std::chrono::steady_clock::now();
				file << obiekt2.algorithm_with_blocks(limit[j], cadency_nr[k]).Cmax << "&";
				auto  end = std::chrono::steady_clock::now();
				file2 << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "&";
			}
		}
		cout << "8 policzonych" << endl;
		file << "\\\\" << endl;
		file2 << "\\\\" << endl;
	}
	
	file.close();
	file2.close();
	return 0;
}
