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
int main() {
	
	unique_ptr<stock> amd = make_unique<stock>("AMD");
	node::add_descriptor(high, 1, string("high"));
	node::add_descriptor(low, 1, string("low"));
	node::add_descriptor(adjusted, 1, string("adjusted"));
	node::add_descriptor(open, 1, string("open"));
	node::add_descriptor(volume, 1, string("volume"));
	node::add_descriptor(close, 1, string("close"));
	node::add_descriptor(rand, 0, string("rand0-1"));
	node n(2, amd.get());
	cout << n.result() << endl;
	//cout<<a.get_action()(node::child_array());
	int b;
	cin >> b;
	return 0;
}
