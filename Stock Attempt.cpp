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
double rand(node::child_array &name, stock * a) {
	return 0;
}
//__global float* adjusted_buf, __global float* close_buf, __global float* high_buf, __global float* low_buf, __global float* open_buf, __global float* open_buf, __global float* result, int buf_size,
string stock_data_function_in_opencl(string buf_prefix) {
	return 
		"if((int)leaves[b] + i < i || (int)leaves[b] + i > buf_size || leaves[b] + i < 0) "
		"{"
		"	leaves[b+1] = 0;"
		"}else{"
		"	leaves[b+1] = " + buf_prefix + "_buf[(int)leaves[b] + i];"
		"}"
		"";
}

string add =
"if(b != 0){"
"leaves[b+1] = leaves[b] + leaves [b-1];}else{leaves[b+1]=0;}";

string multiply =
"if(b != 0){"
"leaves[b+1] = leaves[b] * leaves [b-1];}else{leaves[b+1]=0;}";

string divide =
"if(b == 0 || leaves[b-1] == 0) {leaves[b+1] = 0;}else{"
"leaves[b+1] = leaves[b] / leaves [b-1];}";

string i =
"if(b < 4){leaves[b+1]=0;}else{"
"if(leaves[b]< leaves[b-1]){leaves[b+1]=leaves[b-3];}else{leaves[b+1]=leaves[b-4];}}"
""
"";


int main() {
	
	unique_ptr<stock> amd = make_unique<stock>("AMD");
	node::add_descriptor(stock_data_function_in_opencl("high"), 1, string("high"));
	node::add_descriptor(stock_data_function_in_opencl("low"), 1, string("low"));
	node::add_descriptor(stock_data_function_in_opencl("adjusted"), 1, string("adjusted"));
	node::add_descriptor(stock_data_function_in_opencl("open"), 1, string("open"));
	node::add_descriptor(stock_data_function_in_opencl("volume"), 1, string("volume"));
	node::add_descriptor(stock_data_function_in_opencl("close"), 1, string("close"));
	
	node::add_descriptor(add, 2, string("+"));
	node::add_descriptor(multiply, 2, string("*"));
	node::add_descriptor(divide, 2, string("/"));
	node::add_descriptor(i, 4, string("i"));

	int b = 1;
	while(b == 1){
		//gen_cont a(10000, amd.get());
		//cout<<a.compile();

		population a(10000, 10000, "AMD");
		a.generations = 1;
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
