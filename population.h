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
	void next_generation();
private:
	int size = 0;
	vector<gen_cont> pop;
	double mutation_rate = 0.02;
	double crossover_rate = 0.05;
	unique_ptr<stock> st;
};

