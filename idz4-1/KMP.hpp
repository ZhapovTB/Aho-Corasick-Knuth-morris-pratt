#pragma once
#ifndef KMP
#define KMP
#include"Aho.hpp"
int* pre_kmp(std::string pattern)
{
    int size = pattern.size();
    int* pie = new int[size];
    pie[0] = 0;
    int k = 0;
    for (int i = 1; i < size; i++)
    {
        while (k > 0 && pattern[k] != pattern[i])
        {
            k = pie[k - 1];
        }
        if (pattern[k] == pattern[i])
        {
            k = k + 1;
        }
        pie[i] = k;
    }

    return pie;
}

int kamp_search(std::string text, std::string pattern, int* pie)
{
    int count = 0;
    int matched_pos = 0;
    for (int current = 0; current < text.length(); current++)
    {
        while (matched_pos > 0 && pattern[matched_pos] != text[current])
            matched_pos = pie[matched_pos - 1];

        if (pattern[matched_pos] == text[current])
            matched_pos = matched_pos + 1;

        if (matched_pos == (pattern.length()))
        {
            count++;
            matched_pos = pie[matched_pos - 1];
        }
    }
    return count;
}
void algo_Knuth_Morris_Pratt(std::vector<Node> list, std::vector<std::string> temps_for_name, std::vector<std::string> temps_for_car, int num_of_entries_name, int num_of_entries_car, std::ofstream& file) {
    
    int shet = 0;

    int tem_of_name_enter = 0;
    int tem_of_car_enter = 0;

 
    clock_t start;
    start = clock();
    for (auto node = list.begin(); node != list.end(); node++) {
        for (auto temp = temps_for_name.begin(); temp != temps_for_name.end(); temp++) {
            int* pie = pre_kmp(*temp);
            int kmp = kamp_search((*node).fio, *temp, pie );
            if (kmp!=0)
            {
                tem_of_name_enter++;
            }
        }
        for (auto temp = temps_for_car.begin(); temp != temps_for_car.end(); temp++) {
            int* pie = pre_kmp(*temp);
            int kmp = kamp_search((*node).car.brand, *temp, pie);
            if (kmp != 0)
            {
                tem_of_car_enter++;
            }
        }
        if (tem_of_name_enter >= num_of_entries_name && tem_of_car_enter >= num_of_entries_car) {
            file << (*node).fio << " " << (*node).car.brand << " " << (*node).car.model << " " <<(*node).ch<< std::endl;
        }
        tem_of_name_enter = 0;
        tem_of_car_enter = 0;
    }

    clock_t end;
    end = clock();
    int time = end - start;
  
    file << "Время: " << time/ CLOCKS_PER_SEC << "сек.";
}

#endif // AHO