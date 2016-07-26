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
vector<node::descriptor> node::descriptors;
random_in_range r;
void node::init(int max_size, stock * s) {
	st = s;
	int leave_count = r(5, 10);
	for (int i = 0; i < leave_count; i++) {
		leaves.push_back(r(-100, 100));
	}
	for (int i = 0; i < max_size; i++) {
		children.push_back(get_random_descriptor());
	}
}

node::node(int max_depth, stock * s) {
	init(max_depth, s);
}

double node::result() {
	cache.clear();
	cache.insert(cache.end(), leaves.begin(), leaves.end());
	if (children.size() != 0) {
		for (size_t i = children.size() - 1; i > 0; i--) {
			double res = children.at(i)->a(cache, st);
			cache.push_front(res);
		}
	}
	return cache.at(0);
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
	children.push_back(get_random_descriptor());
}

void node::all_mutate() {
	int a = r(0, 4);
	switch (a) {
	case 0:
		if (children.size() != 0)
			children.at(r(0, (int)children.size() - 1)) = get_random_descriptor();
		if(leaves.size() != 0)
			leaves.at(r(0, (int)leaves.size() - 1)) = r(-100, 100);
		break;
	case 1:
	case 2:
		add_mutate();
		break;
	case 3:
		delete_mutate();
		break;
	case 4:
		int begin = (int) r(0, (int)children.size() - 1);
		int end = (int) r(begin, (int)children.size());
		for (int i = begin; i < end; i++) {
			children.at(i) = get_random_descriptor();
		}
		begin = (int) r(0, (int)leaves.size() - 1);
		end = (int) r(begin, (int)leaves.size());
		for (int i = begin; i < end; i++) {
			leaves.at(i) = r(-1000, 1000);
		}
	}

}

void node::add_descriptor(action a, unsigned int arity, const string &symbol) {
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
	descriptors.push_back(d);
}

node::descriptor * node::get_random_descriptor() {
	return &descriptors.at(r(0, (int)descriptors.size() - 1));
}

void node::crossover(node * other) {
	int lowest_size = std::min((int)other->children.size(), (int)children.size());
	
	int start = r(0, lowest_size);
	int end = r(start, lowest_size);

	descriptor * temp;
	for (int i = start; i < end; i++) {
		temp = children.at(i);
		children.at(i) = (other->children.at(i));
		other->children.at(i) = (temp);
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
	string s;
	while (!in.eof()) {
		std::getline(in, s, node::delimiter);
		if (is_double(s.c_str())) {
			other.leaves.push_back(stod(s.c_str()));
		} else {
			for (size_t i = 0; i < node::descriptors.size(); i++) {
				if (s == node::descriptors.at(i).symbol) {
					other.children.push_back(&node::descriptors.at(i));
				}
			}
		}
	}
	
	return in;
}

istream& operator>>(istream &in, node *  other) {
	in >> (*other);
	return in;
}
