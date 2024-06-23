#include <iostream>
#include "FileEdit.hpp"
#include "Aho.hpp"

int main() {
	std::vector <Node> container;
	std::ifstream test("test1.txt");
	std::ofstream kmpfile("outKMP.txt");
	std::ofstream akfile("outAK.txt");

	std::vector<std::string> temps_name;
	std::vector<std::string> temps_car;

	int num_of_entries_name = 0;
	int num_of_entries_car = 0;

	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	fileParser(test, container);

	std::cout << "������� �����" << std::endl;
	request_temps(temps_name);
	std::cout << "������� �� ��� ������ ����������� ? " << std::endl;
	std::cin >> num_of_entries_name;

	std::cout << "������� �����" << std::endl;
	request_temps(temps_car);
	std::cout << "������� �� ��� ������ ����������� ? " << std::endl;
	std::cin >> num_of_entries_car;

	algo_aho_korasik(container, temps_name, temps_car, num_of_entries_name, num_of_entries_car, akfile);


	print(container);


	int numName = 0;
	int numCar = 0;
	

	
	return 0;
}