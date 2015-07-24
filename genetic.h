#pragma once
#include <iostream>
#include <string>
#include "stock.h"

class node {
public:
	virtual double execute() { std::cout << "Wrong execute call" << endl; return 0; };
	virtual void destroy() { std::cout << "Wrong destroy call" << endl; };
	virtual ~node() { std::cout << "Wrong destructor call" << endl; };
	virtual int get_arity() { return -2; };
};
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
	bool operator < (const gen_container& con) const {
		return (balance + (stock_quant * stock_obj->get_low())) < (con.balance + (con.stock_quant * con.stock_obj->get_low()));
	}
};
class multiply : public node {
public:
	virtual int get_arity() { return 2; };
	multiply() {}; //default constructor so pointers can be placed manually
	node *left;
	node *right;
	double execute();
	~multiply();
	void destroy() { this->~multiply(); };
	gen_container * parent_cont;
	multiply(gen_container * cont, int level = 1);

};
class divide : public node {
public:
	virtual int get_arity() { return 2; };
	divide() {}; //default constructor so pointers can be placed manually
	gen_container * parent_cont;
	node *left;
	node *right;
	double execute();
	~divide();
	void destroy() { this->~divide(); };
	divide(gen_container * cont, int level = 1);
};
class add : public node {
public:
	virtual int get_arity() { return 2; };
	add() {}; //default constructor so pointers can be placed manually
	gen_container * parent_cont;
	node *left;
	node *right;
	double execute();
	~add();
	void destroy() { this->~add(); };
	add(gen_container * cont, int level = 1);
};
class subtract : public node {
public:
	virtual int get_arity() { return 2; };
	subtract() {}; //default constructor so pointers can be placed manually
	gen_container * parent_cont;
	node *left;
	node *right;
	double execute();
	~subtract();
	void destroy() { this->~subtract(); };
	subtract(gen_container * cont, int level = 1);
};
class buy : public node {
public:
	node * amount;
	virtual int get_arity() { return 1; };
	buy() {}; //default constructor so pointers can be placed manually
	gen_container * parent_cont;
	double execute();
	~buy();
	void destroy() { this->~buy(); };
	buy(gen_container * cont, int level = 1);
};
class sell : public node {
public:
	node * amount;
	virtual int get_arity() { return 1; };
	sell() {}; //default constructor so pointers can be placed manually
	gen_container * parent_cont;
	double execute();
	~sell();
	void destroy() { this->~sell(); };
	sell(gen_container * cont, int level = 1);
};
class open : public node {
public:
	virtual int get_arity() { return (int)(past != nullptr); };
	node * past;
	open() {}; //default constructor so pointers can be placed manually
	gen_container * parent_cont;
	double execute();
	~open();
	void destroy() { this->~open(); };
	open(gen_container * cont, int level = 1);
};
class high : public node {
public:
	virtual int get_arity() { return (int)(past != nullptr); };
	high() {}; //default constructor so pointers can be placed manually
	node * past;
	gen_container * parent_cont;
	double execute();
	~high();
	void destroy() { this->~high(); };
	high(gen_container * cont, int level = 1);
};
class low : public node {
public:
	virtual int get_arity() { return (int)(past != nullptr); };
	low() {}; //default constructor so pointers can be placed manually
	node * past;
	gen_container * parent_cont;
	double execute();
	~low();
	void destroy() { this->~low(); };
	low(gen_container *cont, int level = 1);
};
class close : public node {
public:
	virtual int get_arity() { return (int)(past != nullptr); };
	close() {}; //default constructor so pointers can be placed manually
	node * past;
	gen_container * parent_cont;
	double execute();
	~close();
	void destroy() { this->~close(); };
	close(gen_container *cont, int level = 1);
};
class volume : public node {
public:
	virtual int get_arity() { return (int)(past != nullptr); };
	volume() {}; //default constructor so pointers can be placed manually
	node * past;
	gen_container * parent_cont;
	double execute();
	~volume();
	void destroy() { this->~volume(); };
	volume(gen_container *cont, int level = 1);
};
class adjusted : public node {
public:
	virtual int get_arity() { return (int)(past != nullptr); };
	adjusted() {}; //default constructor so pointers can be placed manually
	node * past;
	gen_container * parent_cont;
	double execute();
	~adjusted();
	void destroy() { this->~adjusted(); };
	adjusted(gen_container *cont, int level = 1);
};
class balance : public node {
public:
	virtual int get_arity() { return 0; };
	balance() {}; //default constructor so pointers can be placed manually
	gen_container * parent_cont;
	double execute();
	~balance();
	void destroy() { this->~balance(); };
	balance(gen_container *cont);
};
class decision : public node {
public:
	virtual int get_arity() { return 3; };
	decision() {}; //default constructor so pointers can be placed manually
	node * comp;
	node * right_output, *left_output;
	gen_container * parent_cont;
	double execute();
	~decision();
	void destroy() { this->~decision(); };
	decision(gen_container *cont, int level = 1);
};
class greater_than : public node {
public:
	virtual int get_arity() { return 2; };
	greater_than() {}; //default constructor so pointers can be placed manually
	node * right, *left;
	gen_container * parent_cont;
	double execute();
	~greater_than();
	void destroy() { this->~greater_than(); };
	greater_than(gen_container *cont, int level = 1);
};
class greater_than_equal : public node {
public:
	virtual int get_arity() { return 2; };
	greater_than_equal() {}; //default constructor so pointers can be placed manually
	node * right, *left;
	gen_container * parent_cont;
	double execute();
	~greater_than_equal();
	void destroy() { this->~greater_than_equal(); };
	greater_than_equal(gen_container *cont, int level = 1);
};
class less_than : public node {
public:
	virtual int get_arity() { return 2; };
	less_than() {}; //default constructor so pointers can be placed manually
	node * right, *left;
	gen_container * parent_cont;
	double execute();
	~less_than();
	void destroy() { this->~less_than(); };
	less_than(gen_container *cont, int level = 1);
};
class less_than_equal : public node {
public:
	virtual int get_arity() { return 2; };
	less_than_equal() {}; //default constructor so pointers can be placed manually
	node * right, *left;
	gen_container * parent_cont;
	double execute();
	~less_than_equal();
	void destroy() { this->~less_than_equal(); };
	less_than_equal(gen_container *cont, int level = 1);
};
//originally named just "equal" but renamed after conflicts with other things named "equal"
class equal_node : public node {
public:
	virtual int get_arity() { return 2; };
	equal_node() {}; //default constructor so pointers can be placed manually
	node * right, *left;
	gen_container * parent_cont;
	double execute();
	~equal_node();
	void destroy() { this->~equal_node(); };
	equal_node(gen_container *cont, int level = 1);
};
class value : public node {
public:
	virtual int get_arity() { return 0; };
	double content;
	double execute();
	void destroy() {/*does nothing*/};
	~value() {};
	value();
};
