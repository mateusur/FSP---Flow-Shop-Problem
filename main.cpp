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

using namespace std;

string names[6] = {
"data001.txt",
"data002.txt",
"data003.txt",
"data004.txt",
"data005.txt",
"data006.txt",
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
	///*cout << obiekt.Johnson_algorithm();*/
	//obiekt.Johnson_algorithm();
	Branch_and_Bound obiekt(0);
	obiekt.bnb();
	Algorithm obiekt2();
	//obiekt.calculate_Cmax({ 0,1,2,3,4,5,6,7 });
	return 0;
}

