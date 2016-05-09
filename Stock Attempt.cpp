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
double five(const node::child_array &name, stock * a) {
	return 5.0;
}
double six(const node::child_array &name, stock * a) {
	return name.at(0)->result() + 1000.0;
}

int main() {
	
	unique_ptr<stock> amd = make_unique<stock>("AMD");
	node::add_descriptor(five, 0);
	node::add_descriptor(six, 1);
	node n(1, amd.get());
	cout << n.result() << endl;
	//cout<<a.get_action()(node::child_array());
	int b;
	cin >> b;
	return 0;
}
