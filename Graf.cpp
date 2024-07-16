#include "Graf.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

Graf::Graf() {

}

void Graf::generateRandom(int size) {
	vertex = size;
	if (table != nullptr) {
		delete[] table;
	}
	table = new int* [vertex];

	for (int i = 0; i < vertex; i++) {
		table[i] = new int[vertex];
		for (int j = 0; j < vertex; j++) {
			table[i][j] = rand() % 1000;
		}
	}
}

void Graf::write() {
	for (int i = 0; i < vertex; i++) {
		for (int j = 0; j < vertex; j++) {
			cout << table[i][j] << " ";
		}
		cout << endl;
	}
}
void Graf::loadFile(std::string fileName) {
	ifstream file;
	file.open(fileName);

	if (file.good()) {
		file >> vertex; //ilosc wierzcholkow

		//stworzenie i uzupelnienie wartosciami zadania tablicy
		if (table != NULL) delete[] table;
		table = new int* [vertex];

		for (int i = 0; i < vertex; i++) {
			table[i] = new int[vertex];
			for (int j = 0; j < vertex; j++) {
				file >> table[i][j];
			}
		}
		
		file.close();
	}
}