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
class population {
public:
	population(int size, int initial_worth, string stock);
	~population();
	void next_day();
	void simulate();
	int generations = 0;
private:
	int size = 0;
	double top_percent_to_crossover = 0.1; //Top 10% crossover
	vector<gen_cont> pop;
	double mutation_rate = 0.02;
	double crossover_rate = 0.05;
	unique_ptr<stock> st;
};

