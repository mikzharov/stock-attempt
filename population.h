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
#include "node.h"
class population {
public:
	population();
	~population();
private:
	vector<node> pop;
	double mutation_rate;
	double breed_rate;
	unique_ptr<stock> st;
};

