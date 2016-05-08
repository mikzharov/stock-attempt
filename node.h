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

class node {
public:
	typedef vector<unique_ptr<node>> child_array;
	typedef double(*action)(const child_array&);
	node(int);
	int depth;
	double result();
	struct descriptor {
		action a;
		int arity;
	};
	static descriptor get_random_descriptor(unsigned int);
	static int size() {
		return descriptors.size();
	}
	static void add_descriptor(action a, unsigned int arity);
private:
	static vector<vector<descriptor>> descriptors;
	child_array children;
	descriptor des;
};

