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

#include "genetic.h"
#include "stock.h"

#include <random>
using namespace std;
random_in_range b;
double five(const node::child_array &name) {
	return 5.0;
}

int main() {
	//stock stock("AMZN");
	descriptor_container::add_descriptor(five, 0);
	descriptor a = descriptor_container::get_random_descriptor(0);
	cout<<a.get_arity()<<endl;
	cout<<a.get_action()(node::child_array());
	int b;
	cin >> b;
	return 0;
}
