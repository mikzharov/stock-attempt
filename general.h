//Change for git
#pragma once
#include <iostream>
#include <string>
#include "stock.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ostream>
#include "stock.h"
#include <random>
#include <memory>
#include <assert.h>

namespace {
	bool is_double(const char* str) {
		char* endptr = 0;
		strtod(str, &endptr);

		if (*endptr != '\0' || endptr == str)
			return false;
		return true;
	}
}
//Source for random number generator was originally posted on Codereview to a question I wrote
//http://codereview.stackexchange.com/questions/101525/random-number-generation-seeding-in-c

//Looking back, the question wasn't a very good one, but the new code to the previous function was, so here it is.
class random_in_range {
	std::mt19937 rng;
public:
	random_in_range() : rng(std::random_device()()) {}
	int operator()(int low, int high) {
		std::uniform_int_distribution<int> uni(low, high);
		return uni(rng);
	}
};