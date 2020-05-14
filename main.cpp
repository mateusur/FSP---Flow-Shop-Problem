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
	//file.open("Wyniki.txt", ios::app);
	//cout << "----Czasy dla wersji bound 3 ----" <<endl;
	/*file << "\nBnB LB1 & ";*/
	//for (int i = 0;i < 6;i++) {
	//	Branch_and_Bound obiekt(i);
	////	long long sredni_czas = 0;
	////	for(int j=0;j<1;j++) {
	////		auto start = std::chrono::steady_clock::now();
	//		obiekt.bnb(i);
	//		auto end = std::chrono::steady_clock::now();
	//		auto czas = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	//		sredni_czas += czas;
	//	}
	//	sredni_czas /= 1;
	//	if(i<5)
	//	file << sredni_czas << " & ";
	//	else {
	//		file << sredni_czas << " \\\\";
	//	}
	//}

	
	////}
	////for (int i = 0; i < 6; i++) {
	//	NEH obiekt2(6);
	//	cout << "Cmax dla podstawowego NEH: " << obiekt2.NEH_algorithm() << endl;
	//	cout << "------------------------------------------------" << endl;
	//	cout << "Cmax dla NEH+: " << obiekt2.job_with_max_operations() << endl;
	//	cout << "------------------------------------------------" << endl;
	////}

	Simulated_annealing SA(1);
	return 0;
}
