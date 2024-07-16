#include "TSP.h"
#include "Graf.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <fstream>
     
using namespace std;
      
Graf g;
double t = 0;
int n, k;

std::chrono::high_resolution_clock::time_point start;
std::chrono::duration<double, std::milli> timePassed;

ofstream results;

int calculateCost(int* order, Graf& g) {
	//obliczamy koszt drogi w podanej kolejnoœci
	int cost = 0;
	for (int i = 0; i < g.vertex - 1; i++) {
		cost += g.table[order[i]][order[i + 1]]; // dodajemy wszystkie drogi oprócz ostatniej - robimy to po wykonaniu siê pêtli (powrót do pocz¹tku)
	}
	cost += g.table[order[g.vertex - 1]][order[0]]; // Powrót do punktu pocz¹tkowego
	return cost;
}

void recursiveBruteForce(int* order, int depth, int& minCost, int* finalOrder, Graf& g) {
	if (depth == g.vertex) {
		int tempCost = calculateCost(order, g);
		if (tempCost < minCost) {
			minCost = tempCost;
			copy(order, order + g.vertex, finalOrder);
		}
		return;
	}

	for (int i = depth; i < g.vertex; i++) {
		swap(order[depth], order[i]);
		recursiveBruteForce(order, depth + 1, minCost, finalOrder, g);
		swap(order[depth], order[i]); // Przywracamy pierwotny stan tablicy
	}
	return;
}

void bruteForce(Graf g) {

	start = std::chrono::high_resolution_clock::now();

	int minCost = INT_MAX;
	int* finalOrder = new int[g.vertex];
	int* order = new int[g.vertex];

	for (int i = 0; i < g.vertex; i++) {
		finalOrder[i] = i;
		order[i] = i;
	}

	recursiveBruteForce(order, 0, minCost, finalOrder, g);	//dopoki wszystkie kombinacje wierzcholkow nie beda sprawdzone, wywolujemy ta funkcje 
												// rekurencyjnie zmieniajac wartosc depth oraz kolejnosc wierzcholkow (order)


	// Wyœwietlenie znalezionej trasy dla danych testowych dra Mierzwy
	cout << "Najkrotsza trasa: ";
	for (int i = 0; i < g.vertex; i++) {
		std::cout << finalOrder[i] << " -> ";
	}
	cout << finalOrder[0] << endl << "Koszt trasy: " << minCost << endl << "czas: " << timePassed.count() << "ms" << endl;

	delete[] finalOrder;
	delete[] order;
}

int main() {

	srand(time(NULL));

	cout << "tsp_6_1.txt" << endl;
	g.loadFile("tsp_6_1.txt");
	bruteForce(g);
	
	cout << endl << "tsp_6_2.txt" << endl;
	g.loadFile("tsp_6_2.txt");
	bruteForce(g);

	cout << endl << "tsp_10.txt" << endl;
	g.loadFile("tsp_10.txt");
	bruteForce(g);
	
	cout << endl << "tsp_12.txt" << endl;
	g.loadFile("tsp_12.txt");
	bruteForce(g);

	cout << endl << "tsp_13.txt" << endl;
	g.loadFile("tsp_13.txt");
	bruteForce(g);

	/*cout << endl << "tsp_14.txt" << endl; // to sie robi dluzej niz 2h
	g.loadFile("tsp_14.txt");
	bruteForce(g);*/

	//TESTY Z LOSOWO WYGENEROWANYM GRAFEM O n WIERZCHOLKACH
	
	//n = 100000; // ilosc badan
	//k = 5; // ilosc wierzcholkow

	//g.generateRandom(k);

	//for (int i = 0; i < n; i++) {
	//	bruteForce(g);
	//}
	//if (results.good()) {
	//	results.open("wyniki.txt", std::ios::app);
	//}
	//results << n << ";" << k << ";" << timePassed.count()/n << endl;
	//results.close();

	return 0;
}