#pragma once
#include "general.h"
#include <iostream>
#include <cstdlib>
#include <random>
#include <stdio.h>
#include <string>
#include "stock.h"
#include <chrono>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <memory>
#include "node.h"
class gen_cont {//Genetic container
public:
	gen_cont(double money, stock * st);
	double get_money() const;
	int get_stock_owned() const;
	double get_result() const;
	double evaluate();
	void update_fitness();
	bool operator < (const gen_cont& con) {
		return (fitness < con.fitness);
	}
	double result = 0;
	unique_ptr<node> n;
	void reset() {
		money = 0;
		stock_owned = 0;
	}
	stock * st;
	double get_fitness() {
		return fitness;
	}
	void set_fitness(double f) {
		fitness = f;
	}
private:
	double fitness = 0;
	int stock_owned = 0;
	double money = 0;//Money probably shouldn't be a double
};


