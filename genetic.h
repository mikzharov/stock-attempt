#pragma once
#include <iostream>
#include <string>
#include "stock.h"

class node {
public:
	virtual double execute() { std::cout << "Wrong execute call"; return 0; };
	virtual void destroy() {};
};
class gen_container {
public:
	double get_balance() { return balance; }
	node node;
	double balance = 0;
	int stock_quant = 0;
	stock * stock_obj;
	gen_container() {}; 
	gen_container(stock &s) { stock_obj = &s; };
	gen_container(string stock_name);
};
class multiply : public node {
public:
	node *left;
	node *right;
	double execute();
	~multiply();
	void destroy() { this->~multiply(); };
	gen_container * parent_cont;
	multiply(gen_container &cont, int level = 1);

};
class divide : public node {
public:
	gen_container * parent_cont;
	node *left;
	node *right;
	double execute();
	~divide();
	void destroy() { this->~divide(); };
	divide(gen_container &cont, int level = 1);
};
class add : public node {
public:
	gen_container * parent_cont;
	node *left;
	node *right;
	double execute();
	~add();
	void destroy() { this->~add(); };
	add(gen_container &cont, int level = 1);
};
class subtract : public node {
public:
	gen_container * parent_cont;
	node *left;
	node *right;
	double execute();
	~subtract();
	void destroy() { this->~subtract(); };
	subtract(gen_container &cont, int level = 1);
};
class buy : public node {
public:
	gen_container * parent_cont;
	double execute();
	~buy();
	void destroy() { this->~buy(); };
	buy(gen_container &cont);
};
class sell : public node {
public:
	gen_container * parent_cont;
	double execute();
	~sell();
	void destroy() { this->~sell(); };
	sell(gen_container &cont);
};
class open : public node {
public:
	gen_container * parent_cont;
	double execute();
	~open();
	void destroy() { this->~open(); };
	open(gen_container &cont);
};
class high : public node {
public:
	gen_container * parent_cont;
	double execute();
	~high();
	void destroy() { this->~high(); };
	high(gen_container &cont);
};
class low : public node {
public:
	gen_container * parent_cont;
	double execute();
	~low();
	void destroy() { this->~low(); };
	low(gen_container &cont);
};
class close : public node {
public:
	gen_container * parent_cont;
	double execute();
	~close();
	void destroy() { this->~close(); };
	close(gen_container &cont);
};
class volume : public node {
public:
	gen_container * parent_cont;
	double execute();
	~volume();
	void destroy() { this->~volume(); };
	volume(gen_container &cont);
};
class adjusted : public node {
public:
	gen_container * parent_cont;
	double execute();
	~adjusted();
	void destroy() { this->~adjusted(); };
	adjusted(gen_container &cont);
};
class balance : public node {
public:
	gen_container * parent_cont;
	double execute();
	~balance();
	void destroy() { this->~balance(); };
	balance(gen_container &cont);
};
class decision : public node {
public:
	node * comp;
	node * right_output, *left_output;
	gen_container * parent_cont;
	double execute();
	~decision();
	void destroy() { this->~decision(); };
	decision(gen_container &cont, int level = 1);
};
class greater_than : public node {
public:
	node * right, *left;
	gen_container * parent_cont;
	double execute();
	~greater_than();
	void destroy() { this->~greater_than(); };
	greater_than(gen_container &cont, int level = 1);
};
class greater_than_equal : public node {
public:
	node * right, *left;
	gen_container * parent_cont;
	double execute();
	~greater_than_equal();
	void destroy() { this->~greater_than_equal(); };
	greater_than_equal(gen_container &cont, int level = 1);
};
class less_than : public node {
public:
	node * right, *left;
	gen_container * parent_cont;
	double execute();
	~less_than();
	void destroy() { this->~less_than(); };
	less_than(gen_container &cont, int level = 1);
};
class less_than_equal : public node {
public:
	node * right, *left;
	gen_container * parent_cont;
	double execute();
	~less_than_equal();
	void destroy() { this->~less_than_equal(); };
	less_than_equal(gen_container &cont, int level = 1);
};
//originally named just "equal" but renamed after conflicts with other things named "equal"
class equal_node : public node {
public:
	node * right, *left;
	gen_container * parent_cont;
	double execute();
	~equal_node();
	void destroy() { this->~equal_node(); };
	equal_node(gen_container &cont, int level = 1);
};
class value : public node {
public:
	double content;
	double execute();
	void destroy() {/*does nothing*/};
	value();
};
