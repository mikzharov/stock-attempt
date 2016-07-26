// Stock Attempt.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <vector>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <cstdlib>

#include "general.h"
#include "stock.h"
#include "node.h"

#include "gen_cont.h"
#include <random>

#include "population.h"

#include <ctgmath>

random_in_range b;
double rand(node::child_array &name, stock * a) {
	return 0;
}
double high(node::child_array &name, stock * a) {
	if (a == nullptr)return 1;
	return a->get_high((int) name.at(0));
}
double adjusted(node::child_array &name, stock * a) {
	if (a == nullptr)return 1;
	return a->get_adjusted((int) name.at(0));
}
double low(node::child_array &name, stock * a) {
	if (a == nullptr)return 1;
	return a->get_low((int) name.at(0));
}
double volume(node::child_array &name, stock * a) {
	if (a == nullptr)return 1;
	return (double) a->get_volume((int) name.at(0));
}
double open(node::child_array &name, stock * a) {
	if (a == nullptr)return 1;
	return (double)a->get_open((int) name.at(0));
}
double close(node::child_array &name, stock * a) {
	if (a == nullptr)return 1;
	return (double)a->get_close((int) name.at(0));
}
double add(node::child_array &name, stock * a) {
	if (name.size() < 2) {
		return 1;
	}
	return name.at(0) + name.at(1);
}
double multiply(node::child_array &name, stock * a) {
	if (name.size() < 2) {
		return 1;
	}
	return name.at(0) * name.at(1);
}
double divide(node::child_array &name, stock * a) {
	if (name.size() < 2) {
		return 1;
	}
	if (name.at(1) == 0) return 1;
	return name.at(0) / name.at(1);
}
double i(node::child_array &name, stock * a) {
	if (name.size() < 4) {
		return 1;
	}
	if (name.at(0) < name.at(1)) return name.at(3);
	return name.at(4);
}
double negative(node::child_array &name, stock * a) {
	if (name.size() < 1) {
		return 1;
	}
	return - name.at(0);
}
double subtract(node::child_array &name, stock * a) {
	if (name.size() < 2) {
		return 1;
	}
	return name.at(0) - name.at(1);
}
int main() {
	
	unique_ptr<stock> amd = make_unique<stock>("AMD");
	node::add_descriptor(high, 1, string("high"));
	node::add_descriptor(low, 1, string("low"));
	node::add_descriptor(adjusted, 1, string("adjusted"));
	node::add_descriptor(open, 1, string("open"));
	node::add_descriptor(volume, 1, string("volume"));
	node::add_descriptor(close, 1, string("close"));
	//node::add_descriptor(rand, 0, string("c0"));
	node::add_descriptor(add, 2, string("+"));
	node::add_descriptor(multiply, 2, string("*"));
	node::add_descriptor(divide, 2, string("/"));
	node::add_descriptor(i, 4, string("i"));
	node::add_descriptor(negative, 1, string("n"));
	node::add_descriptor(subtract, 2, string("-"));
	int b = 1;
	while(b == 1){
		//gen_cont a(10000, amd.get());
		//a.evaluate();
		//a.update_fitness();
		//cout << "Fitness: " << a.get_fitness() << endl;
		//if (a.get_fitness() == 0) throw exception();

		//cout << "Money: " << a.get_money() << endl;
		//cout << "Stock Owned: " << a.get_stock_owned() << endl;


		population a(10000, 10000, "TEAM");
		a.generations = 2500;
		a.simulate();

		//node a;
		//ifstream myfile;
		//myfile.open("NODE.txt");
		//myfile >> a;
		//myfile.close();




		//Loop things below
		cin >> b;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(80, '\n');
		}
	}
	return 0;
}
