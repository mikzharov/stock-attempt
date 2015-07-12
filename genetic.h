#pragma once
#include <iostream>
class node {
public:
	virtual double execute() { std::cout << "Wrong execute call"; return 0; };
	virtual void destroy() {};
	
};
class multiply : public node {
public:
	node *left;
	node *right;
	double execute();
	~multiply();
	void destroy() { this->~multiply(); };
	multiply(int level = 0);
};
class value : public node {
public:
	double content;
	double execute();
	void destroy() {/*does nothing*/};
	value();
};