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
class value : public node {
public:
	double content;
	double execute();
	void destroy() {/*does nothing*/};
	value();
};
