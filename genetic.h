#pragma once
#include <iostream>
#include <string>
#include "stock.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ostream>
#include "stock.h"
using namespace std;
class node {
public:
	node(stock * data, int max_depth);
	node(node * n);
	~node();
	stock * stock_data;
	unsigned int arity;
	int array_index;

	double value = 0;
	bool is_value = false;
	bool is_written = false;

	static vector<string> symbol0;
	static vector<string> symbol1;
	static vector<string> symbol2;
	static vector<string> symbol3;

	static vector<double(*)(string *, stock *)> method0;
	static vector<double(*)(double, string *, stock *)> method1;
	static vector<double(*)(double, double, string *, stock *)> method2;
	static vector<double(*)(double, double, double, string *, stock *)> method3;

	vector<node *> children_vector;

	void static add_func(double(*op)(string *, stock *));
	void static add_func(double(*op)(double, string *, stock *));
	void static add_func(double(*op)(double, double, string *, stock *));
	void static add_func(double(*op)(double, double, double, string *, stock *));

	static int zero_arity_percent;
	static int one_arity_percent;
	static int two_arity_percent;
	static int three_arity_percent;

	double execute();

	void write(vector<string> *, unsigned int depth);
	void clear_write_flag() { 
		is_written = false;
		for (unsigned int i = 0; i < children_vector.size() && children_vector[i] != nullptr; i++){
			children_vector[i]->is_written = false;
		}
	}
	node copy();
	node * random_node_in_tree(int depth = 0);
};
ostream& operator<<(ostream &out, node&  other);
class gen_container {
public:
	double get_balance() { return balance; }
	node * node;
	double balance = 0;
	int stock_quant = 0;
	stock * stock_obj;
	gen_container() {}; 
	gen_container(stock &s) { stock_obj = &s; };
	gen_container(string stock_name);
	gen_container * copy();
	gen_container(gen_container * self);
	bool operator < (const gen_container& con) const {
		if (fabs(stock_obj->get_low() - con.stock_obj->get_low()) > DBL_EPSILON) {
			throw exception("Stock low prices must be the same");
		}
		return (balance + (stock_quant * stock_obj->get_low())) < (con.balance + (con.stock_quant * con.stock_obj->get_low()));
	}
};
