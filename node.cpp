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
const string node::delimiter = ",";
vector<vector<node::descriptor>> node::descriptors;
node::node(int max_depth, stock * s, int current) {
	st = s;
	this->depth = current;
	if (max_depth > 0 && current < max_depth) {
		des = get_random_descriptor(r(0, size() - 1));
		for (int i = 0; i < des.arity; i++) {
			children.push_back(make_unique<node>(max_depth, s, current + 1));
		}
	} else {
		des = get_random_descriptor(0);
	}
}
double node::result() {
	return des.a(children, st);
}

void node::write(vector<vector<string>>& to_write) {
	while (to_write.size() <= depth) {
		to_write.push_back(vector<string>());
	}
	to_write.at(this->depth).push_back(des.symbol);
	for (int i = 0; i < des.arity; i++) {
		children.at(i).get()->write(to_write);
	}
}

node::descriptor node::get_random_descriptor(unsigned int arity) {
	if (descriptors.size() > arity) {
		return descriptors.at(arity).at(r(0, (int)descriptors.at(arity).size() - 1));
	}
	cout << arity << endl;
	throw exception();
}

void node::add_descriptor(action a, unsigned int arity, const string &symbol) {
	if (symbol == delimiter) {
		cerr << "add_descriptor(): symbol cannot be the delimiter";
		throw exception();
	}
	struct node::descriptor d;
	d.a = a;
	d.arity = arity;
	d.symbol = symbol;
	while (descriptors.size() <= arity || descriptors.size() == 0) {
		descriptors.push_back(vector<descriptor>());
	}
	descriptors.at(arity).push_back(d);
}
ostream& operator<<(ostream &out, node&  other) {
	vector<vector<string>> a;
	other.write(a);
	for (unsigned int i =  0; i < a.size(); i++) {
		for (unsigned int b = 0; b < a.at(i).size(); b++) {
			cout << a.at(i).at(b) << node::delimiter;
		}
		cout << endl;
	}
	return out;
}
ostream& operator<<(ostream &out, node *  other) {
	out << (*other);
	return out;
}
