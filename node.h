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
	node() {};
	node(int, stock *, int = 0);
	node(vector<vector<string>>& tree, int depth);
	typedef std::vector<std::unique_ptr<node>> node::child_array;
	double result();
	
	typedef double(*action)(const child_array&, stock *);
	struct descriptor {
		action a;
		int arity;
		string symbol;
	};
	void write(vector<vector<string>>& = vector<vector<string>>());
	descriptor get_random_descriptor(unsigned int);
	int arity();//Returns the arity of the node
	int get_depth();//Returns the depth of the node
	size_t get_index_in_parent_children_array();
	void set_index_in_parent_children_array(size_t i);
	void set_tree_depth(int depth = 0);//Sets the deoth of the node and it's children correctly (where each child it 1 deeper than the parent)
	void set_tree_stock(stock * s);
	void set_parent(node *);
	void revalidate();
	void revalidate_tree();
	void add_to_children(node * n, bool revalidate = true);
	void replace_child_with(size_t index_in_child_array, node * n);
	static int descriptor_size() {
		return (int)descriptors.size();
	}
	static void add_descriptor(action a, unsigned int arity, const string &symbol);
	static vector<vector<string>> node_graph_from_stream(istream &in);
	node * get_random_node_in_tree(node * current = nullptr);
	node * get_parent();
	const static char delimiter;
	const static char end_node;
private:
	node * parent = nullptr;
	size_t index_in_parent_children_array = 0;
	int depth;
	double value;
	bool value_flag = false;//This flag decides whether this node is a value node
	descriptor return_value_descriptor;
	static vector<vector<descriptor>> descriptors;
	child_array children;
	descriptor des;
	stock * st;
};
ostream& operator<<(ostream &out, node&  other);
ostream& operator<<(ostream &out, node *  other);

istream& operator>>(istream &out, node&  other);
istream& operator>>(istream &out, node *  other);

