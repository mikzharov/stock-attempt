#pragma once
#include <iostream>
#include <string>
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
	node(int, stock *);
	typedef std::vector<std::unique_ptr<node>> node::child_array;
	int depth;
	double result();
	
	typedef double(*action)(const child_array&, stock *);
	struct descriptor {
		action a;
		int arity;
	};
	static descriptor get_random_descriptor(unsigned int);
	static int size() {
		return (int)descriptors.size();
	}
	static void add_descriptor(action a, unsigned int arity);
private:
	static vector<vector<descriptor>> descriptors;
	child_array children;
	descriptor des;
	stock * st;
};

