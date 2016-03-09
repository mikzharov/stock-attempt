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
using namespace std;
class random_in_range {
	std::mt19937 rng;
public:
	random_in_range() : rng(std::random_device()()) {}
	int operator()(int low, int high) {
		std::uniform_int_distribution<int> uni(low, high);
		return uni(rng);
	}
};

class node {
public:
	typedef vector<unique_ptr<node>> child_array;
	typedef double(*action)(child_array);
	node(int depth);
private:
	action a;
	int arity;
	child_array children;
};

class descriptor {
private:
	node::action a;
	int arity;
public:
	descriptor(node::action a, int arity) {
		this->a = a;
		this->arity = arity;
	}
	double get_arity() {
		return arity;
	}
	node::action get_action() {
		return a;
	}
};
