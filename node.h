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
#include <deque>

class node {
public:
	typedef deque<double> child_array;
	typedef double(*action)(child_array&, stock *);
	struct descriptor {
		action a;
		size_t arity;
		string symbol;
	};

	node() {};
	void init(int max_size, stock *);
	node(int max_size, stock *);
	
	double result();

	void write(ostream &out);

	void delete_mutate();
	void add_mutate();
	void all_mutate();

	static int descriptor_size() {
		return (int)descriptors.size();
	}
	static void add_descriptor(action a, unsigned int arity, const string &symbol);
	const static char delimiter;
	const static char end_node;

	static descriptor * get_random_descriptor();

	void crossover(node * other);
	vector<double> leaves;
	static vector<descriptor> descriptors;
	vector<descriptor *> children;
private:
	child_array cache;
	stock * st;
};
ostream& operator<<(ostream &out, node&  other);
ostream& operator<<(ostream &out, node *  other);

istream& operator>>(istream &out, node&  other);
istream& operator>>(istream &out, node *  other);

