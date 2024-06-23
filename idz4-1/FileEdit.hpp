#include "Node.hpp"
#include <fstream>
#include <time.h>

std::string error1 = "Файл не найден/Не удалось найти файл";
std::string error2 = "Неверный формат времени";
std::string error3 = "Неверный диапазон часов/минут/секунд ";



void fileParser(std::ifstream& file, std::vector <Node>& v) {
    TimeKey k;
    std::string fiok;
    Car carK;
    int ch = 1;
    Node node;
    std::string s;
    if (!file) {
        std::cout << error1 << "\n";
    }
    else {
        while (!file.eof()) {
            std::getline(file, s);
            int i = 0;
            while (s[i] != ' ') {
                fiok += s[i];
                i++;
            }
            fiok += ' ';
            i++;
            while (s[i] != ' ')
            {
                fiok += s[i];
                i++;
            }
            fiok += ' ';
            i++;
            while (s[i] != ' ')
            {
                fiok += s[i];
                i++;
            }
            fiok += ' ';
            i++;
            k.h = (s[i] - '0') * 10 + (s[i + 1] - '0');

            i = i + 3;
            k.m = (s[i] - '0') * 10 + (s[i + 1] - '0');
            i = i + 3;
            k.s = (s[i] - '0') * 10 + (s[i + 1] - '0');
            i = i + 3;

            while (s[i] != ' ') {
                carK.brand += s[i];
                i++;
            }

            i++;
            for(i;i<s.size();i++)
            {
                carK.model+= s[i];
            }
            

            node.time = k;
            node.fio = fiok;
            node.car = carK;
            node.ch = ch;
            ch++;
            v.push_back(node);
            fiok = "";
            carK.brand = "";
            carK.model = "";
        }
    }
}

void print(const std::vector<Node> container) {
    for (int i = 0; i < container.size(); i++) {

        std::cout << container[i].fio;
        for (int j = 0; j < (35 - container[i].fio.length()); j++) std::cout << " ";
        
       
        bool a = false, b = false, c = false;
        if (container[i].time.h < 10) a = true;
        if (container[i].time.m < 10) b = true;
        if (container[i].time.s < 10) c = true;

        std::cout << (a ? "0" : "") << container[i].time.h << ":" << (b ? "0" : "") << container[i].time.m << ":" << (c ? "0" : "") << container[i].time.s << "  ";

        std::cout << container[i].car.brand;
        for (int j = 0; j < (15 - container[i].car.brand.length()); j++) std::cout << " ";
        std::cout << container[i].car.model;
        for (int j = 0; j < (12 - container[i].car.model.length()); j++) std::cout << " ";
        std::cout << std::endl;
    }
}

void printFile(std::ofstream& file, const std::vector<Node> container) {
    for (int i = 0; i < container.size(); i++) {

        file << container[i].fio;
        for (int j = 0; j < (15 - container[i].fio.length()); j++) file << " ";
       

        bool a = false, b = false, c = false;
        if (container[i].time.h < 10) a = true;
        if (container[i].time.m < 10) b = true;
        if (container[i].time.s < 10) c = true;

        file << (a ? "0" : "") << container[i].time.h << ":" << (b ? "0" : "") << container[i].time.m << ":" << (c ? "0" : "") << container[i].time.s << "  " << container[i].ch << " " << std::endl;
    }
}


void request_temps(std::vector<std::string>& temps) {
    int count = 0;
    std::string temp;

    std::cout << "Введите количество шаблонов, которые вы хотите ввести ";
    std::cin >> count;
    for (int var = 0; var != count; var++) {
        std::cout << "Введите шаблон ";
        std::cin >> temp;
        temps.push_back(temp);
    }
}