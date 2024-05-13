#include <iostream>
#include <fstream>
using namespace std;

void swap1(int a, int b) {
	int t;
	t = a;
	a = b;
	b = t;
}

void swap2(int* a, int* b) {
	int t;
	t = *a;
	*a = *b;
	*b = t;
}
int main() {
	ofstream fout;
	ifstream fin;

	fin.open("input.txt");
	fout.open("output.txt");

	int size = 0;
	fin >> size;
	fout << size << '\n';

	int* mas;

	mas = new int[size];
	for (int i = 0; i < size; i++) {
		fin >> mas[i];
	}

	//swap2(&mas[0], &mas[size - 1]);
	//*(mas+i) = mas[i]
	for (int i = 0; i < size; ++i) {
		fout << mas[i] << ' ';
	}

	delete[] mas;

	fin.close();
	fout.close();
}