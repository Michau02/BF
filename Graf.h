#pragma once
#include <string>
class Graf{

public:
	void loadFile(std::string fileName);
	void write();
	void generateRandom(int size);
	Graf();


	int vertex;
	int** table;

private:
};

