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
	gen_cont(stock * st, double money);
	~gen_cont();
	double get_money() const;
	int get_stock_owned() const;
	double get_result() const;
	double evaluate();
	bool operator < (const gen_cont& con) {
		return (money + result < (con.get_money() + con.result));
	}
private:
	stock * st;
	int stock_owned = 0;
	double money = 0;//Money probably shouldn't be a double
	double result = 0;
	unique_ptr<node> n;
};


