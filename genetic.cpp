#include "genetic.h"
#include <iostream>
#include <cstdlib>
#include <random>
#include <string>
#include "stock.h"
int random_in_range(int min, int max) {
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

	return uni(rng);

}

// if arity is -1 then any object will be returned
node * return_rand_func(gen_container &cont, int level, int arity = -1) {
	if (level <= 0) return new value();
	switch(arity){
	case -1:
		int decision;
		decision = random_in_range(0, 4);
		if (decision == 0) {
			return new multiply(cont, level);
		} else if (decision == 1) {
			return new value();
		} else if (decision == 2) {
			return new subtract(cont, level);
		} else if (decision == 3) {
			return new divide(cont, level);
		} else if (decision == 4) {
			return new add(cont, level);
		}
		break;
	case 0:
		return new value();

	case 2:
		switch (random_in_range(0, 3)) {
		case 0:
			return new multiply(cont, level);
		case 1: 
			return new divide(cont, level);
		case 2:
			return new add(cont, level);
		case 3: 
			return new subtract(cont, level);
		}
		
	}
	throw std::exception("No arity: " + arity);
}
gen_container::gen_container(string stock_name) {
	stock_obj = new stock (stock_name);
}
double multiply::execute() {
	return (*right).execute() * (*left).execute();
}
multiply::multiply(gen_container &cont, int level) {
	left = return_rand_func(cont, level - 1);
	right = return_rand_func(cont, level - 1);
}
multiply::~multiply() {
	delete right;
	delete left;
	delete parent_cont;
}
double divide::execute() {
	if ((*left).execute()==0) {
		return 1;
	}
	return (*right).execute() / (*left).execute();
}
divide::divide(gen_container &cont, int level) {
	left = return_rand_func(cont, level - 1);
	right = return_rand_func(cont, level - 1);
}
divide::~divide() {
	delete right;
	delete parent_cont;
	delete left;
}
double add::execute() {
	return (*right).execute() + (*left).execute();
}
add::add(gen_container &cont, int level) {
	left = return_rand_func(cont, level - 1);
	right = return_rand_func(cont, level - 1);
}
add::~add() {
	delete right;
	delete parent_cont;
	delete left;
}
double subtract::execute() {
	return (*right).execute() - (*left).execute();
}
subtract::subtract(gen_container &cont, int level) {
	left = return_rand_func(cont, level - 1);
	right = return_rand_func(cont, level - 1);
}
subtract::~subtract() {
	delete right;
	delete left;
	delete parent_cont;
}
double buy::execute() {
	double high = (*(*parent_cont).stock_obj).get_high();
	if ((*parent_cont).balance >= high) {
		(*parent_cont).stock_quant++;
		(*parent_cont).balance -= high;
		return high;
	}
	return 0;
}
buy::buy(gen_container &cont) {
	parent_cont = &cont;
}
buy::~buy() {
	delete parent_cont;
}
double value::execute() {
	return content;
}
value::value() {
	double lower_bound = 0;
	double upper_bound = 10000;
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::default_random_engine re;
	content = unif(re);
}