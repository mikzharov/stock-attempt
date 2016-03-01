//Change for git
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
#include <random>
#include <assert.h>
using namespace std;
class random_in_range {
	std::mt19937 rng;
public:
	random_in_range() : rng(std::random_device()()) {}
	int operator()(int low, int high) {
		std::uniform_int_distribution<int> uni(low, high);
		return uni(rng);
	}
};
class node {
private:
	
	unsigned int arity;
	int array_index;
	double value = 0;
	bool is_value = false;
	bool is_written = false;
public:

	node& node::operator=(const node& other) {
		copy_into(&other);
		return *this;
	}
	node(int max_depth);
	node(node * n);
	node(vector<vector<string>>& n, int depth);
	node() {};//Do nothing initialization
	~node();
	

	static vector<string> symbol0;
	static vector<string> symbol1;
	static vector<string> symbol2;
	static vector<string> symbol3;
	static vector <vector<string> *> symbol_index;
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
	bool is_stock = false;
	bool is_balance = false;
	double execute(double stock_quant, double balance, stock *);
	
	void write(vector<string> *, unsigned int depth);
	void clear_write_flag() { 
		is_written = false;
		for (unsigned int i = 0; i < children_vector.size() && children_vector[i] != nullptr; i++){
			children_vector[i]->clear_write_flag();
		}
	}
	node * random_node_in_tree(int depth = 0, node * current = nullptr);
	static vector<vector<string>> node::from_file(std::istream &is);
	void copy_into(const node * copy);//Copys the node in the parameter into the node that this method is called from

	//Genetic operators below
	void point_mutate();
	void subtree_mutate(node * n = nullptr);
	void shrink_mutate();
	void mutate();
	static node * breed(node * mother, node * father);
	
};
ostream& operator<<(std::ostream &out, node *  other);
ostream& operator<<(std::ostream &out, node&  other);
istream& operator>>(std::istream &out, node *&  other);

class gen_container {

public:
	stock stock_obj;
	node node_;
	double balance = 0;
	int stock_quant = 0;
	gen_container& gen_container::operator=(const gen_container& other) {
		this->balance = other.balance;
		this->node_ = node(other.node_);
		assert(!other.stock_obj.symbol.empty());
		this->stock_obj.get_values(other.stock_obj.symbol);
		this->stock_quant = other.stock_quant;
		return *this;
	}
	//gen_container() {}; 
	//gen_container(const gen_container& other) {
	//	this->balance = other.balance;
	//	this->node_ = new node(other.node_);
	//	this->stock_obj.get_values(other.stock_obj.symbol);
	//	this->stock_quant = other.stock_quant;
	//}
	gen_container(string stock_name);
	void execute(ostream * out = nullptr) {
		while(stock_obj.next_day()){
			double result = node_.execute(stock_quant, balance, &stock_obj);
			if(out != nullptr){
				*out << result << endl;
			}
			int buy_sell =(int) result;
			
			if(buy_sell > 0){
				if(balance > stock_obj.get_high() * buy_sell) {
					balance -= stock_obj.get_high() * buy_sell;
					stock_quant += buy_sell;
				} else {
					buy_sell = (int)balance / (int)stock_obj.get_high();
					balance = 0;
					stock_quant += buy_sell;
				}
			} else if (buy_sell < 0) {
				if(stock_quant > 0) {
					if(buy_sell < stock_quant) {
						balance += stock_obj.get_low() * buy_sell;
						stock_quant -= buy_sell;
					} else {
						balance += buy_sell * stock_obj.get_low();
						stock_quant = 0;
					}
				}
			}
		}
		stock_obj.reset();

	}
	
	bool operator < (const gen_container& con) {

		if (fabs(stock_obj.get_low(latest) - con.stock_obj.get_low(latest)) > DBL_EPSILON) {
			throw exception("Stock low prices must be the same");
		}
		return (balance + (stock_quant * stock_obj.get_low(latest))) < (con.balance + (con.stock_quant * con.stock_obj.get_low(latest)));
	}
};
