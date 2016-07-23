#include "stdafx.h"
#include "node.h"
#include <iostream>
#include <string>
#include "stock.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ostream>
#include <random>
#include <memory>
#include <assert.h>
#include "general.h"
#include "general.cpp"
#include <algorithm>

const char node::delimiter = ',';
const char node::end_node = '`';
vector<vector<node::descriptor>> node::descriptors;
random_in_range r;
void node::init(int max_size, stock * s) {
	st = s;
	int leave_count = r(5, 10);
	for (int i = 0; i < leave_count; i++) {
		leaves.push_back(r(-100, 100));
	}
	for (int i = 0; i < max_size; i++) {
		children.push_back(std::make_unique<descriptor>(get_random_descriptor()));
	}
}

node::node(int max_depth, stock * s) {
	init(max_depth, s);
}

void node::write(ostream & out) {
	for (int i = 0; i < leaves.size(); i++) {
		out << to_string(leaves.at(i)) << delimiter;
	}
	out << endl;
	for (int i = 0; i < children.size(); i++) {
		out << children.at(i)->symbol << delimiter;
	}
	out << endl << end_node <<endl;
}

void node::delete_mutate() {
	if(children.size() != 0)
	children.erase(children.begin() + r(0, (int)children.size() - 1));
}

void node::add_mutate() {
	children.push_back(std::make_unique<descriptor>(get_random_descriptor()));
}

void node::all_mutate() {
	int a = r(0, 1);
	switch (a) {
	case 0:
		leaves.at(r(0, (int)leaves.size() - 1)) = r(-100, 100);
		break;
	case 1:
		a = r(0, 2);
		switch (a) {
		case 0:
			if(children.size() != 0)
			children.at(r(0, (int)children.size() - 1)) = make_unique<descriptor>(get_random_descriptor());
			break;
		case 1:
			add_mutate();
			break;
		case 2:
			delete_mutate();
			break;
		}
		break;
	}
}

void node::add_descriptor(string a, unsigned int arity, const string &symbol) {
	if (is_double(symbol.c_str())) {
		cerr << "add_descriptor(): symbol cannot be double";
		throw exception();
	}
	if (symbol.find(end_node) != std::string::npos) {
		cerr << "add_descriptor(): symbol cannot contain end_node delimiter";
		throw exception();
	}
	if (symbol.find(delimiter) != std::string::npos) {
		cerr << "add_descriptor(): symbol cannot contain the delimiter";
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

node::descriptor node::get_random_descriptor(size_t arity) {
	if (arity == -1) arity = r(0, (int)descriptors.size() - 1);
	if (descriptors.at(arity).size() <= 0) arity = 1;
	return descriptors.at(arity).at(r(0, (int)descriptors.at(arity).size() - 1));
}

void node::crossover(node * other) {
	int lowest_size = std::min((int)other->children.size(), (int)children.size());
	
	int start = r(0, lowest_size);
	int end = r(start, lowest_size);

	descriptor * temp;
	for (int i = start; i < end; i++) {
		temp = children.at(i).release();
		children.at(i).reset(other->children.at(i).release());
		other->children.at(i).reset(temp);
	}

	lowest_size = std::min((int)other->leaves.size(), (int)leaves.size());

	start = r(0, lowest_size);
	end = r(start, lowest_size);

	double temp_l;
	for (int i = start; i > 0 && i < end - 1; i++) {
		temp_l = leaves.at(i);
		leaves.at(i) = other->leaves.at(i);
		other->leaves.at(i) = temp_l;
	}
}

ostream& operator<<(ostream &out, node&  other) {
	other.write(out);
	return out;
}

ostream& operator<<(ostream &out, node *  other) {
	out << (*other);
	return out;
}

istream& operator>>(istream &in, node&  other) {
	return in;
}

istream& operator>>(istream &in, node *  other) {
	in >> (*other);
	return in;
}
