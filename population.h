#pragma once
#include "general.h"
#include <iostream>
#include <cstdlib>
#include <random>
#include <stdio.h>
#include <string>
#include "stock.h"
#include <chrono>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <memory>
#include "gen_cont.h"
#ifdef __APPLE__
	#include "OpenCL/opencl.h"//Probably won't use an apple device for this program, but why not
#else
	#include "CL/cl.h"
#endif
class population {
public:
	population(int size, int initial_worth, string stock);
	~population();
	void next_day();
	void simulate();
	void init_opencl();
	int generations = 0;
	inline void cl_error(cl_int error, string desc) {
		if (error != CL_SUCCESS) {
			cerr << desc << endl;
			throw exception();
		}
	}
private:
	int size = 0;
	double top_percent_to_crossover = 0.1; //Top 10% crossover
	vector<gen_cont> pop;
	double mutation_rate = 0.02;
	double crossover_rate = 0.05;
	unique_ptr<stock> st;
};

