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

random_in_range b;
double rand(const node::child_array &name, stock * a) {
	return 0;
}
double high(const node::child_array &name, stock * a) {
	if (a == nullptr)return 0.0;
	return a->get_high((int) name.at(0)->result());
}
double adjusted(const node::child_array &name, stock * a) {
	if (a == nullptr)return 0.0;
	return a->get_adjusted((int) name.at(0)->result());
}
double low(const node::child_array &name, stock * a) {
	if (a == nullptr)return 0.0;
	return a->get_low((int) name.at(0)->result());
}
double volume(const node::child_array &name, stock * a) {
	if (a == nullptr)return 0.0;
	return (double) a->get_volume((int) name.at(0)->result());
}
double open(const node::child_array &name, stock * a) {
	if (a == nullptr)return 0.0;
	return (double)a->get_open((int) name.at(0)->result());
}
double close(const node::child_array &name, stock * a) {
	if (a == nullptr)return 0.0;
	return (double)a->get_close((int) name.at(0)->result());
}
double add(const node::child_array &name, stock * a) {
	if (name.size() < 2) {
		return 0.0;
	}
	return name.at(0)->result() + name.at(1)->result();
}
double multiply(const node::child_array &name, stock * a) {
	if (name.size() < 2) {
		return 0.0;
	}
	return name.at(0)->result() * name.at(1)->result();
}
double divide(const node::child_array &name, stock * a) {
	if (name.size() < 2) {
		return 0.0;
	}
	if (name.at(1)->result() == 0) return 0;
	return name.at(0)->result() / name.at(1)->result();
}
double i(const node::child_array &name, stock * a) {
	if (name.size() < 4) {
		return 0.0;
	}
	if (name.at(0)->result() < name.at(1)->result()) return name.at(3)->result();
	return name.at(4)->result();
}
int main() {
	
	unique_ptr<stock> amd = make_unique<stock>("AMD");
	node::add_descriptor(high, 1, string("high"));
	node::add_descriptor(low, 1, string("low"));
	node::add_descriptor(adjusted, 1, string("adjusted"));
	node::add_descriptor(open, 1, string("open"));
	node::add_descriptor(volume, 1, string("volume"));
	node::add_descriptor(close, 1, string("close"));
	node::add_descriptor(close, 1, string("close"));
	node::add_descriptor(rand, 0, string("c0"));
	node::add_descriptor(add, 2, string("+"));
	node::add_descriptor(multiply, 2, string("*"));
	node::add_descriptor(divide, 2, string("/"));
	node::add_descriptor(divide, 4, string("i"));
	int b = 1;
	while(b == 1){
		//unique_ptr<node> a(new node(10, amd.get()));
		//node * c = a.get();
		//a.release();
		//a.reset();
		//cout << c;
		//cout << a.get();

		population a(10000, 10000, "AMD");
		a.generations = 1000;
		a.simulate();



		//Loop things below
		cin >> b;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(80, '\n');
		}
	}
	return 0;
}
