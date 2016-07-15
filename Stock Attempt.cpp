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
using namespace std;
random_in_range b;
double rand(const node::child_array &name, stock * a) {
	return b(0,1);
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
int main() {
	
	unique_ptr<stock> amd = make_unique<stock>("AMD");
	node::add_descriptor(high, 1, string("high"));
	node::add_descriptor(low, 1, string("low"));
	node::add_descriptor(adjusted, 1, string("adjusted"));
	node::add_descriptor(open, 1, string("open"));
	node::add_descriptor(volume, 1, string("volume"));
	node::add_descriptor(close, 1, string("close"));
	node::add_descriptor(close, 1, string("close"));
	node::add_descriptor(rand, 0, string("rand0-1"));
	node::add_descriptor(add, 2, string("+"));
	node::add_descriptor(multiply, 2, string("*"));
	int b = 1;
	while(b == 1){
		
		//Loop things below
		cin >> b;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(80, '\n');
		}
	}
	return 0;
}
