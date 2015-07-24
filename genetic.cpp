#include "genetic.h"
#include <iostream>
#include <cstdlib>
#include <random>
#include <string>
#include "stock.h"

enum node_type { comparison = 500};
int random_in_range(int min, int max) {
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

	return uni(rng);
}

// if arity is -1 then any object will be returned
node * return_rand_func(gen_container &cont, int level, int arity = -1) {
	if (level <= 0) arity = 0;
	switch (arity) {
	case -2:
		cout << "Wrong get_arity call!" << endl;
		break;
	case -1://default random arity switch
		
		switch(random_in_range(0, 19)){
		case 0:
			return new multiply(cont, level);
		case 1:
			return new value();
		case 2:
			return new subtract(cont, level);
		case 3:
			return new divide(cont, level);
		case 4:
			return new add(cont, level);
		case 5:
			return new buy(cont);
		case 6:
			return new sell(cont);
		case 7:
			return new open(cont);
		case 8:
			return new high(cont);
		case 9:
			return new low(cont);
		case 10:
			return new close(cont);
		case 11:
			return new volume(cont);
		case 12:
			return new adjusted(cont);
		case 13:
			return new balance(cont);
		case 14:
			return new decision(cont, level);
		case 15:
			return new greater_than(cont, level);
		case 16:
			return new less_than(cont, level);
		case 17:
			return new less_than_equal(cont, level);
		case 18:
			return new greater_than_equal(cont, level);
		case 19:
			return new equal_node(cont, level);
		case 20:
			return new open(cont, level);
		case 21:
			return new high(cont, level);
		case 22:
			return new low(cont, level);
		case 23:
			return new close(cont, level);
		case 24:
			return new volume(cont, level);
		case 25:
			return new adjusted(cont, level);
		}
		break;
	case 0: // artity of 0 ( 0 arguments )

		switch( random_in_range(0, 7)){
		case 0:
			return new value();
		case 1:
			return new open(cont);
		case 2:
			return new high(cont);
		case 3:
			return new low(cont);
		case 4:
			return new close(cont);
		case 5:
			return new volume(cont);
		case 6:
			return new adjusted(cont);
		case 7:
			return new balance(cont);
		}
		break;
	case 1:
		switch(random_in_range(0, 7)){
		case 0:
			return new open(cont, level);
		case 1:
			return new high(cont, level);
		case 2:
			return new low(cont, level);
		case 3:
			return new close(cont, level);
		case 4:
			return new volume(cont, level);
		case 5:
			return new adjusted(cont, level);
		case 6:
			return new buy(cont, level);
		case 7:
			return new sell(cont, level);
		}
	case 2:// 2 arguments
		switch (random_in_range(0, 8)) {
		case 0:
			return new multiply(cont, level);
		case 1: 
			return new divide(cont, level);
		case 2:
			return new add(cont, level);
		case 3: 
			return new subtract(cont, level);
		case 4:
			return new greater_than(cont, level);
		case 5:
			return new less_than(cont, level);
		case 6:
			return new greater_than_equal(cont, level);
		case 7:
			return new less_than_equal(cont, level);
		case 8:
			return new equal_node(cont, level);
		}
		break;
	case 3:// 3 arguments
		return new decision(cont, level);
	case comparison://only returns comparaison operator
		switch (random_in_range(0, 4)) {
		case 0:
			return new greater_than(cont, level);
		case 1:
			return new greater_than_equal(cont, level);
		case 2:
			return new equal_node(cont, level);
		case 3:
			return new less_than(cont, level);
		case 4:
			return new less_than_equal(cont, level);
		}
	}
	throw std::exception("No arity: " + arity);
}
gen_container::gen_container(string stock_name) {
	stock_obj = new stock (stock_name);
}
double multiply::execute() {
	return right->execute() * left->execute();
}
multiply::multiply(gen_container &cont, int level) {
	left = return_rand_func(cont, level - 1);
	right = return_rand_func(cont, level - 1);
}
multiply::~multiply() {
	right->destroy();
	left->destroy();
	delete right;
	delete left;
}
double divide::execute() {
	if (left->execute()==0) {
		return 1;
	}
	return right->execute() / left->execute();
}
divide::divide(gen_container &cont, int level) {
	left = return_rand_func(cont, level - 1);
	right = return_rand_func(cont, level - 1);
}
divide::~divide() {
	right->destroy();
	left->destroy();
	delete right;
	delete left;
	delete parent_cont;

}
double add::execute() {
	return right->execute() + left->execute();
}
add::add(gen_container &cont, int level) {
	left = return_rand_func(cont, level - 1);
	right = return_rand_func(cont, level - 1);
}
add::~add() {
	right->destroy();
	left->destroy();
	delete left;
	delete right;
}
double subtract::execute() {
	return right->execute() - left->execute();
}
subtract::subtract(gen_container &cont, int level) {
	left = return_rand_func(cont, level - 1);
	right = return_rand_func(cont, level - 1);
}
subtract::~subtract() {
	right->destroy();
	left->destroy();
	delete right;
	delete left;
}
double buy::execute() {
	double high = parent_cont->stock_obj->get_high();
	int amount_to_buy = (int)amount->execute();
	if (parent_cont->balance - (amount_to_buy * high) > 0) {
		parent_cont->stock_quant += amount_to_buy;
		parent_cont->balance -= high * amount_to_buy;
		return high;
	}
	int quant = (int)(parent_cont->balance / high);
	parent_cont->stock_quant -= quant;
	parent_cont->balance -= quant * high;
	return high;
}
buy::buy(gen_container &cont, int level) {
	parent_cont = &cont;
	amount = return_rand_func(cont, level - 1);
}
buy::~buy() {
	delete amount;
}
double sell::execute() {
	double low = parent_cont->stock_obj->get_low();
	int amount_to_sell = (int)amount->execute();
	if (parent_cont->stock_quant - amount_to_sell > 0) {
		parent_cont->stock_quant-= amount_to_sell;
		parent_cont->balance += low * amount_to_sell;
		return low;
	}
	parent_cont->stock_quant -= parent_cont->stock_quant;
	parent_cont->balance += low * parent_cont->stock_quant;
	return low;
}
sell::sell(gen_container &cont, int level) {
	parent_cont = &cont;
	amount = return_rand_func(cont, level - 1);
}
sell::~sell() {
	delete amount;
}
double open::execute() {
	int day = 0;
	if (past != nullptr) {
		day = (int)past->execute();
	}
	return parent_cont->stock_obj->get_open(day);
}
open::open(gen_container &cont, int level) {
	parent_cont = &cont;
	if (level != 1) {
		past = return_rand_func(cont, level - 1);
	}
}
open::~open() {
	if(past != nullptr){
		past->destroy();
	}
	delete past;
}
double high::execute() {
	int day = 0;
	if (past != nullptr) {
		day = (int)past->execute();
	}
	return parent_cont->stock_obj->get_high(day);
}
high::high(gen_container &cont, int level) {
	parent_cont = &cont;
	if (level != 1) {
		past = return_rand_func(cont, level - 1);
	}
}
high::~high() {
	if(past!=nullptr)
	past->destroy();
	delete past;
}
double low::execute() {
	int day = 0;
	if (past != nullptr) {
		day = (int)past->execute();
	}
	return parent_cont->stock_obj->get_low(day);
}
low::low(gen_container &cont, int level) {
	parent_cont = &cont;
	if (level != 1) {
		past = return_rand_func(cont, level - 1);
	}
}
low::~low() {
	if(past!=nullptr){
		past->destroy();
	}
	delete past;

}
double close::execute() {
	return parent_cont->stock_obj->get_close();
}
close::close(gen_container &cont, int level) {
	parent_cont = &cont;
	if (level != 1) {
		past = return_rand_func(cont, level - 1);
	}
}
close::~close() {
	if(past != nullptr){
		past->destroy();
	}
	delete past;
}
double volume::execute() {
	int day = 0;
	if (past != nullptr) {
		day = (int)past->execute();
	}
	return parent_cont->stock_obj->get_volume(day);
}
volume::volume(gen_container &cont, int level) {
	parent_cont = &cont;
	if (level != 1) {
		past = return_rand_func(cont, level - 1);
	}
}
volume::~volume() {
	if(past!=nullptr){
		past->destroy();
	}
	delete past;
}
double adjusted::execute() {
	int day = 0;
	if (past != nullptr) {
		day = (int)past->execute();
	}
	return parent_cont->stock_obj->get_adjusted(day);
}
adjusted::adjusted(gen_container &cont, int level) {
	parent_cont = &cont;
	if (level != 1) {
		past = return_rand_func(cont, level - 1);
	}
}
adjusted::~adjusted() {
	if(past!=nullptr){
		past->destroy();
	}
	delete past;
}
double balance::execute() {
	return parent_cont->get_balance();
}
balance::balance(gen_container &cont) {
	parent_cont = &cont;
}
balance::~balance() {
}
double decision::execute() {
	if (comp->execute() == 1) {
		return right_output->execute();
	}
	return left_output->execute();
}
decision::decision(gen_container &cont, int level) {
	comp = return_rand_func(cont, level - 1, comparison);
	right_output = return_rand_func(cont, level - 1);
	left_output = return_rand_func(cont, level - 1);
	parent_cont = &cont;
}
decision::~decision() {
	comp->destroy();
	right_output->destroy();
	left_output->destroy();
	delete comp;
	delete right_output;
	delete left_output;
}
double greater_than::execute() {
	if (right->execute() > left->execute()) {
		return 1;
	}
	return 0;
}
greater_than::greater_than(gen_container &cont, int level) {
	right = return_rand_func(cont, level - 1);
	left = return_rand_func(cont, level - 1);
	parent_cont = &cont;
}
greater_than::~greater_than() {
	right->destroy();
	left->destroy();
	delete right;
	delete left;
}
double greater_than_equal::execute() {
	if (right->execute() >= left->execute()) {
		return 1;
	}
	return 0;
}
greater_than_equal::greater_than_equal(gen_container &cont, int level) {
	right = return_rand_func(cont, level - 1);
	left = return_rand_func(cont, level - 1);
	parent_cont = &cont;
}
greater_than_equal::~greater_than_equal() {
	right->destroy();
	left->destroy();
	delete right;
	delete left;
}
double less_than::execute() {
	if (right->execute() < left->execute()) {
		return 1;
	}
	return 0;
}
less_than::less_than(gen_container &cont, int level) {
	right = return_rand_func(cont, level - 1);
	left = return_rand_func(cont, level - 1);
	parent_cont = &cont;
}
less_than::~less_than() {
	right->destroy();
	left->destroy();
	delete right;
	delete left;
}
double less_than_equal::execute() {
	if (right->execute() <= left->execute()) {
		return 1;
	}
	return 0;
}
less_than_equal::less_than_equal(gen_container &cont, int level) {
	right = return_rand_func(cont, level - 1);
	left = return_rand_func(cont, level - 1);
	parent_cont = &cont;
}
less_than_equal::~less_than_equal() {
	right->destroy();
	left->destroy();
	delete right;
	delete left;
}
double equal_node::execute() {
	if (right->execute() == left->execute()) {
		return 1;
	}
	return 0;
}
equal_node::equal_node(gen_container &cont, int level) {
	right = return_rand_func(cont, level - 1);
	left = return_rand_func(cont, level - 1);
	parent_cont = &cont;
}
equal_node::~equal_node() {
	right->destroy();
	left->destroy();
	delete right;
	delete left;
}
double value::execute() {
	return content;
}
value::value() {
	double lower_bound = 0;
	double upper_bound = 10000;//I don't know why I chose this value
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::default_random_engine re;
	content = unif(re);
}