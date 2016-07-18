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
	void init(int max_depth, stock *, int current = 0, int arity = -1);
	node(int max_depth, stock *, int current = 0, int arity = -1);
	node(vector<vector<string>>& tree, int depth);
	typedef std::vector<std::unique_ptr<node>> node::child_array;
	double result();
	
	typedef double(*action)(const child_array&, stock *);
	struct descriptor {
		action a;
		size_t arity;
		string symbol;
	};
	void write(vector<vector<string>>& = vector<vector<string>>());
	
	size_t arity();//Returns the arity of the node
	int get_depth();//Returns the depth of the node
	void release(size_t index);
	void make_value();
	int count();

	size_t get_index_in_parent_children_array();
	void set_index_in_parent_children_array(size_t i);
	void set_tree_depth(int depth = 0);//Sets the deoth of the node and it's children correctly (where each child it 1 deeper than the parent)
	void set_tree_stock(stock * s);
	void set_parent(node *);
	void revalidate();
	void revalidate_tree();
	void add_to_children(node * n, bool revalidate = true);
	void replace_child_with(size_t index_in_child_array, node * n);

	void shrink_mutate();//These methods mutate the tree. They apply to the whole tree
	void subtree_mutate();
	void point_mutate();

	void all_mutate();

	void crossover(node * n);

	void change_action();
	static int descriptor_size() {
		return (int)descriptors.size();
	}
	static void add_descriptor(action a, unsigned int arity, const string &symbol);
	static vector<vector<string>> node_graph_from_stream(istream &in);
	node * get_random_node_in_tree(node * current = nullptr);
	node * get_parent();
	const static char delimiter;
	const static char end_node;
	string created_by = "1|";

	void set_depth(int depth) { this->depth = depth; };

	int max_depth();
private:
	void set_random_descriptor(size_t);
	node * parent = nullptr;
	size_t index_in_parent_children_array = 0;
	int depth;
	double value;
	bool value_flag = false;//This flag decides whether this node is a value node
	static vector<vector<descriptor>> descriptors;
	child_array children;
	descriptor des;
	stock * st;
};
ostream& operator<<(ostream &out, node&  other);
ostream& operator<<(ostream &out, node *  other);

istream& operator>>(istream &out, node&  other);
istream& operator>>(istream &out, node *  other);

