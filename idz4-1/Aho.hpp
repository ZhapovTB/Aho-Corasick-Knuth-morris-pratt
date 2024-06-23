#pragma once
#ifndef AHO
#define AHO
#include <ctime> 
#include <iostream>
#include <String>
#include <cmath>
#include <vector>
#include <fstream>
#include <windows.h>
#include <queue>
#include "Node.hpp"
struct Vertex {
	Vertex* suflink = nullptr;
	Vertex* parent = nullptr;
	std::vector<Vertex*> children = {};
	char val = '0';
	bool terminal = false;
	bool good_link = false;
	std::string terminal_val = "";
};

void add_vertex(Vertex*& root, std::string temp) {
	Vertex* curent_vertex = root;
	bool flag = true;

	for (auto temp_sym = temp.begin(); temp_sym != temp.end(); temp_sym++) {

		if (!curent_vertex->children.empty()) {
			for (auto link = curent_vertex->children.begin(); link != curent_vertex->children.end(); link++) {
				if ((*link)->val == (*temp_sym)) {
					curent_vertex = *link;
					flag = false;
					break;
				}
			}
			if (flag) {
				Vertex* new_vertex = new Vertex;
				new_vertex->parent = curent_vertex;
				new_vertex->val = (*temp_sym);
				curent_vertex->children.push_back(new_vertex);
				curent_vertex = new_vertex;

				flag = true;
			}
		}
		else {
			Vertex* new_vertex = new Vertex;
			new_vertex->parent = curent_vertex;
			new_vertex->val = (*temp_sym);
			curent_vertex->children.push_back(new_vertex);
			curent_vertex = new_vertex;
		}
		flag = true;

	}
	curent_vertex->terminal = true;
	curent_vertex->terminal_val = temp;
}

void create_trie(Vertex*& root, std::vector<std::string> temps) {
	for (auto temp = temps.begin(); temp != temps.end(); temp++) {
		add_vertex(root, (*temp));
	}
}

void add_suf_link(Vertex*& root) {
	Vertex* cur_ver;
	Vertex* par_ver;
	bool flag = true;
	std::queue<Vertex*> queue;
	queue.push(root);

	while (!queue.empty()) {
		cur_ver = queue.front();
		queue.pop();
		par_ver = cur_ver->parent;

		if (par_ver != nullptr) {
			while (flag) {
				par_ver = par_ver->suflink;
				if (cur_ver->parent != root) {
					for (auto ver = par_ver->children.begin(); ver != par_ver->children.end(); ver++) {
						if ((*ver)->val == cur_ver->val) {
							cur_ver->suflink = (*ver);
							if ((*ver)->terminal) { cur_ver->good_link = true; }
							flag = false;
						}
					}
					if (par_ver == root && flag) {
						cur_ver->suflink = root;
						flag = false;
					}
				}
				else { cur_ver->suflink = root; flag = false; }

			}
		}
		else { cur_ver->suflink = root; }


		for (auto ver = cur_ver->children.begin(); ver != cur_ver->children.end(); ver++) {
			queue.push(*ver);
		}

		flag = true;
	}
}

Vertex* search_vertex(Vertex* vertex, char sym) {
	for (auto link = vertex->children.begin(); link != vertex->children.end(); link++) {
		if ((*link)->val == sym) { return *link; }
	}
	if (vertex->parent == nullptr) {
		return vertex;
	}
	else {
		return search_vertex(vertex->suflink, sym);
	}
}



std::vector<int> check(Vertex* root, std::string line, std::vector<std::string> temps) {
	Vertex* cur_ver = root;
	bool flag = true;
	std::vector<int> temps_count(temps.size());

	for (auto sym = line.begin(); sym != line.end(); sym++) {
		cur_ver = search_vertex(cur_ver, *sym);
		if (cur_ver->terminal) {
			for (int i = 0; i < temps.size(); i++) {
				if (cur_ver->terminal_val == temps[i]) { temps_count[i]++; }
			}
		}
		if (cur_ver->good_link) {
			for (int i = 0; i < temps.size(); i++) {
				if (cur_ver->suflink->terminal_val == temps[i]) { temps_count[i]++; }
			}
		}
	}
	return temps_count;
}




void algo_aho_korasik(std::vector<Node> people_list, std::vector<std::string> temps_for_name, std::vector<std::string> temps_for_car, int num_of_entries_name, int num_of_entries_car, std::ofstream& file) {
	bool flag = true;
	std::vector<int> count_temps_name{};
	std::vector<int> count_temps_car{};
	int tem_of_name_ent = 0;
	int tem_of_car_ent = 0;
	Vertex* root_name = new Vertex;
	Vertex* root_car = new Vertex;

	clock_t start;
	start = clock();
	create_trie(root_name, temps_for_name);
	add_suf_link(root_name);

	create_trie(root_car, temps_for_car);
	add_suf_link(root_car);

	for (auto node = people_list.begin(); node != people_list.end(); node++) {
		count_temps_name = check(root_name, (*node).fio, temps_for_name);
		for (auto tem = count_temps_name.begin(); tem != count_temps_name.end(); tem++) {
			if ((*tem) != 0) { tem_of_name_ent++; }
		}

		count_temps_car = check(root_car, (*node).car.brand, temps_for_car);
		for (auto tem = count_temps_car.begin(); tem != count_temps_car.end(); tem++) {
			if ((*tem) != 0) { tem_of_car_ent++; }
		}

		if (tem_of_name_ent >= num_of_entries_name && tem_of_car_ent >= num_of_entries_car) {
			file << (*node).fio << " " << (*node).car.brand <<" "<< (*node).car.model << " " << (*node).ch << std::endl;
		}
		tem_of_name_ent = 0;
		tem_of_car_ent = 0;
	}
	clock_t end;
	end = clock();
	int time = end - start;
	file << ((float)time) / CLOCKS_PER_SEC<<"сек.";

	file.close();
}

#endif // AHO