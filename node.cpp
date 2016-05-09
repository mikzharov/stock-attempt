#include "node.h"
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
#include "general.h"

random_in_range r;

vector<vector<node::descriptor>> node::descriptors;
node::node(int depth, stock * s) {
	st = s;
	this->depth = depth;
	if (depth > 0) {
		des = get_random_descriptor(r(0, size() - 1));
		for (int i = 0; i < des.arity; i++) {
			children.push_back(make_unique<node>(depth - 1, s));
		}
	} else {
		des = get_random_descriptor(0);
	}
}
double node::result() {
	return des.a(children, st);
}

node::descriptor node::get_random_descriptor(unsigned int arity) {
	if (descriptors.size() > arity) {
		return descriptors.at(arity).at(r(0, descriptors.at(arity).size() - 1));
	}
	cout << arity << endl;
	throw exception();
}

void node::add_descriptor(action a, unsigned int arity) {
	struct node::descriptor d;
	d.a = a;
	d.arity = arity;
	while (descriptors.size() <= arity || descriptors.size() == 0) {
		descriptors.push_back(vector<descriptor>());
	}
	descriptors.at(arity).push_back(d);
}
