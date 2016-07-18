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

const char node::delimiter = ',';
const char node::end_node = '`';
vector<vector<node::descriptor>> node::descriptors;
random_in_range r;
void node::init(int max_depth, stock * s, int current, int arity) {
	value = r(-100, 100);
	des.arity = 0;
	st = s;
	this->depth = current;
	if ((max_depth > 0 && current < max_depth) && arity != 0) {
		//Prevents from running and producing a leaf when the depth is 0, can make leaves when the depth is not 0
		if (r(0, descriptor_size() - 1) == 0 && (descriptors.at(0).size() == 0 || r(0, (int)descriptors.at(0).size() - 1) == 0)) {
			value_flag = true;
			des.arity = 0;//Made for the special case of a value node
			des.symbol = to_string(value);
			created_by += "init,value|";
			return;
		}
		if (arity == -1) {
			int selection = r(0, descriptor_size() - 1);
			if (depth == 0 && selection == 0)selection = 2;
			set_random_descriptor(selection);
		} else {
			set_random_descriptor(arity);
		}
	} else {
		set_random_descriptor(0);
	}
	for (int i = 0; i < des.arity; i++) {
		add_to_children(new node(max_depth, s, current + 1), false);
	}
	if (current == 0)
		revalidate_tree();
}

node::node(int max_depth, stock * s, int current, int arity) {
	init(max_depth, s, current, arity);
}

node::node(vector<vector<string>> &n, int depth) {
	if (n.size() == 0) {
		throw exception("Vector of vectors is 0");
	}
	string op = n[depth][0];
	if (is_double(op.c_str())) {
		value = std::stod(op);
		des.arity = 0;
		des.symbol = to_string(value);
		value_flag = true;
	}
	for (vector<descriptor> temp_ : descriptors) {
		for (descriptor temp : temp_) {
			if (temp.symbol == op) {
				des = temp;
				break;
			}
		}
	}
	
	n[depth].erase(n[depth].begin());
	for (int i = 0; i < des.arity; i++) {
		add_to_children(new node(n, depth + 1), false);
	}
}
double node::result() {
	if (value_flag)return value;
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

int node::max_depth() {
	int b = depth;
	for (int i = 0; i < children.size(); i++) {
		b = children.at(i)->count();
	}
	return b;
}

void node::set_random_descriptor(size_t arity) {
	value_flag = false;
	if (descriptors.size() > arity && descriptors.at(arity).size() != 0) {//Makes sure that the descriptor exists
		des = descriptors.at(arity).at(r(0, (int)descriptors.at(arity).size() - 1));
		created_by += "srd1|";
		return;
	}
	if (descriptors.size() > arity && descriptors.at(arity).size() != 0) {//Tries again to make sure no leaves are make at depth 0
		created_by += "srd2|";
		des = descriptors.at(arity).at(r(0, (int)descriptors.at(arity).size() - 1));
		return;
	}
	make_value();
}

size_t node::arity() {
	if (des.arity != children.size()) {
		des.arity = children.size();
	}
	return des.arity;
}

int node::get_depth() {
	return depth;
}

void node::release(size_t index) {
	children.at(index).release();
}

void node::make_value() {
	value = r(-100, 100);
	value_flag = true;
	des.arity = 0;//Made for the special case of a value node
	des.symbol = to_string(value);
	created_by += "mkv|";
	return;
}

int node::count() {
	int b = 0;
	for (int i = 0; i < children.size(); i++) {
		b += children.at(i)->count();
	}
	return b;
}

size_t node::get_index_in_parent_children_array() {
	return index_in_parent_children_array;
}

void node::set_index_in_parent_children_array(size_t i) {
	index_in_parent_children_array = i;
}

void node::set_tree_depth(int depth) {
	this->depth = depth;//Sets it's own depth
	if (depth > 1000)parent->shrink_mutate();
	for (int i = 0; i < children.size(); i++) {//Cycles through the children array and sets their depth
		children.at(i)->set_tree_depth(depth + 1);//The child's depth is 1 deeper than the parents depth
	}
}

void node::set_tree_stock(stock * s) {
	this->st = s;
	for (size_t i = 0; i < children.size(); i++) {
		children.at(i)->set_tree_stock(s);
	}
}

void node::set_parent(node * p) {
	this->parent = p;
}

void node::revalidate() {
	for (size_t i = 0; i < children.size(); i++) {
		children.at(i)->set_parent(this);
		children.at(i)->set_index_in_parent_children_array(i);
		children.at(i)->set_depth(depth + 1);
	}
}

void node::revalidate_tree() {
	revalidate();
	for (size_t i = 0; i < children.size(); i++) {
		children.at(i)->revalidate_tree();
	}
}

void node::add_to_children(node * n, bool revalidate_) {
	children.push_back(unique_ptr<node>(n));
	if (revalidate_) {
		revalidate();
	}
}

void node::replace_child_with(size_t index_in_child_array, node * n) {
	children.at(index_in_child_array).reset(n);//Replaces the pointer at index_in_child_array in the children array with n
	children.at(index_in_child_array)->set_tree_depth(this->depth + 1);
	children.at(index_in_child_array)->set_tree_stock(st);
	children.at(index_in_child_array)->set_parent(this);
}

void node::shrink_mutate() {
	node * subject = get_random_node_in_tree();
	if (subject == nullptr)return;
	if (subject->get_parent() == nullptr)return;
	node * parent = subject->get_parent();
	parent->replace_child_with(subject->index_in_parent_children_array, new node(0, this->st, depth + 1, 0));
}

void node::subtree_mutate() {
	if (des.arity == 0) {
		init(5, st, 0);
		return;
	}
	node * subject = get_random_node_in_tree();//Gets the node to be replaced
	if (subject->get_parent() == nullptr)return;//Makes sure that this node is not the root node
	node * parent = subject->get_parent();//Gets the parent node (in order to call replace child)
	parent->replace_child_with(subject->index_in_parent_children_array, new node(depth+6, this->st, depth + 1));//Replaces the node by using the parent
	//This replaces a node with a randomly generated subtree
}

void node::point_mutate() {//Replaces the current operation with a new one
	node * n = get_random_node_in_tree();
	n->change_action();
}

void node::all_mutate() {
	int i = r(0, 2);
	switch (i) {
	case 0:
		shrink_mutate();
		break;
	case 1:
		subtree_mutate();
		break;
	case 2:
		point_mutate();
		break;
	}
	revalidate_tree();
}

void node::crossover(node * n) {
	revalidate_tree();
	node * subject = get_random_node_in_tree();
	if (subject->get_parent() == nullptr)return;
	node * parent = subject->get_parent();

	n->revalidate_tree();
	node * subject1 = n->get_random_node_in_tree();
	if (subject1->get_parent() == nullptr)return;
	node * parent1 = subject1->get_parent();

	size_t index = subject->get_index_in_parent_children_array();
	size_t index1 = subject1->get_index_in_parent_children_array();

	parent->release(index);
	parent1->release(index1);

	parent->replace_child_with(index, subject1);
	parent1->replace_child_with(index1, subject);

	parent->revalidate_tree();
	parent1->revalidate_tree();
}

void node::change_action() {
	size_t inv = arity();
	if (inv == 0) return;
	if (inv >= -1) {
		cout << inv;
		throw exception("AAAAAAA"); 
	}//All sorts of funny stuff can happen when mutating an arity 0 node. Best not to
	set_random_descriptor(inv);
}

node * node::get_parent() {//Returns the parent pointer, can also be used to check if the node is a root node
	return parent;
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
	while (descriptors.size() <= arity || descriptors.size() == 0) {
		descriptors.push_back(vector<descriptor>());
	}
	descriptors.at(arity).push_back(d);
}

vector<vector<string>> node::node_graph_from_stream(istream &in) {
	string str;
	string parts;
	std::stringstream ss;
	vector<vector<string>> result;
	for (int i = 0; getline(in, str); i++) {
		ss.clear();
		ss.str(str);
		result.push_back(vector<string>());
		for (int b = 0; getline(ss, parts, node::delimiter);) {
			if (parts == string(node::end_node, 1))return result;
			result[i].push_back(parts);
		}
	}
	return result;
}

node * node::get_random_node_in_tree(node * current) {
	if (this == nullptr) return nullptr;
	int chance = r(0, depth);
	if (chance == 0 || current == nullptr) {
		current = this;
	}
	if (current->arity() == 0 || arity() == 0) {
		return current;
	}
	int index = r(0, (int)arity() - 1);
	return children.at(index)->get_random_node_in_tree(current);
}

ostream& operator<<(ostream &out, node&  other) {
	//This method allows you to print a node to an outputstream. For example: cout << some_node;
	vector<vector<string>> a;
	other.write(a);
	bool written = false;
	for (unsigned int i =  0; i < a.size(); i++) {
		for (unsigned int b = 0; b < a.at(i).size(); b++) {
			if (a.at(i).at(b) != "") {
				//Makes sure that whitespace is not printed in case the printed node does not have the
				//depth of 0. For example, if depth = 5, then 5 lines of whitespace is printed.
				//This flag prevents this behaviour
				out << a.at(i).at(b) << node::delimiter;
				written = true;
			}
		}
		if (written) {
			//Makes sure that whitespace is not printed in case the printed node does not have the
			//depth of 0. For example, if depth = 5, then 5 lines of whitespace is printed.
			//This flag prevents this behaviour
			out << endl;
			written = false;
		}
	}
	out << node::end_node << endl;
	return out;
}

ostream& operator<<(ostream &out, node *  other) {
	out << (*other);
	return out;
}

istream& operator>>(istream &in, node&  other) {
	int depth = 0;
	//Code below build vector vector structure
	vector<vector<string>> result = node::node_graph_from_stream(in);
	//Code below reads vector vector structure
	if (result.size() == 0) {
		cerr << "Size is 0";//Throws an error if the current size is 0
		throw exception();
	}
	if (result[depth].size() == 0) {
		result.erase(result.begin());
	}
	other.~node();
	new (&other) node(result, depth);
	other.revalidate_tree();
	return in;
}

istream& operator>>(istream &in, node *  other) {
	in >> (*other);
	return in;
}
