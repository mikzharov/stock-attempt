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
	node(int, stock *, int = 0);
	typedef std::vector<std::unique_ptr<node>> node::child_array;
	int depth;
	double result();
	
	typedef double(*action)(const child_array&, stock *);
	struct descriptor {
		action a;
		int arity;
		string symbol;
	};
	void write(vector<vector<string>>& = vector<vector<string>>());
	static descriptor get_random_descriptor(unsigned int);
	static int size() {
		return (int)descriptors.size();
	}
	static void add_descriptor(action a, unsigned int arity, const string &symbol);
	const static string delimiter;
private:
	static vector<vector<descriptor>> descriptors;
	child_array children;
	descriptor des;
	stock * st;
};
ostream& operator<<(ostream &out, node&  other);
ostream& operator<<(ostream &out, node *  other);

