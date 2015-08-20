#include "genetic.h"
#include <iostream>
#include <cstdlib>
#include <random>
#include <stdio.h>
#include <string>
#include "stock.h"
#include <chrono>
#include <iostream>
#include <sstream>

vector<string> node::symbol0;
vector<string> node::symbol1;
vector<string> node::symbol2;
vector<string> node::symbol3;

vector<double(*)(string *, stock *)> node::method0;
vector<double(*)(double, string *, stock *)> node::method1;
vector<double(*)(double, double, string *, stock *)> node::method2;
vector<double(*)(double, double, double, string *, stock *)> node::method3;

int node::zero_arity_percent = 25;
int node::one_arity_percent = 25;
int node::two_arity_percent = 25;
int node::three_arity_percent = 25;

int random_in_range(int min, int max) {
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased
	return uni(rng);
}

void node::write(vector<string> * vect, unsigned int depth) {
	if (vect == nullptr) {
		throw exception("Null vector pointer");
	}
	if (vect->size() <= depth) {
		for (unsigned int i = vect->size(); i <= depth; i++){
			vect->push_back("");
		}
	}
	if(arity != 0){
		for (unsigned int i = 0; i < children_vector.size() && children_vector[i] != nullptr; i++) {
			if (!children_vector[i]->is_written) {
				children_vector[i]->write(vect, depth + 1);
			}
		}
	}
	
	if (is_value) {

		std::stringstream sstm;
		sstm << value << ",";

		(*vect)[depth] += sstm.str();
		return;
	}
	switch (arity) {
	case 0:
		(*vect)[depth] += symbol0[array_index];
		break;
	case 1:
		(*vect)[depth] += symbol1[array_index];
		break;
	case 2:
		(*vect)[depth] += symbol2[array_index];
		break;
	case 3:
		(*vect)[depth] += symbol3[array_index];
		break;
	}
	(*vect)[depth] += ",";
	is_written = true;
}
node node::copy() {
	return node(this);
}
node::node(node * n) {
	this->arity = n->arity;
	this->array_index = n->array_index;
	this->is_value = n->is_value;
	this->is_written = n->is_written;
	this->value = n->value;
	this->stock_data = n->stock_data->copy();

	for (unsigned int i = 0; i < n->children_vector.size() && n->children_vector[i] != nullptr; i++) {
		cout << "COPYING" << endl;
		this->children_vector.push_back(new node(n->children_vector[i])); 
	}
}
node::node(stock * data, int max_depth) {
	is_value = false;
	stock_data = data;
	arity = -1;
	unsigned int total_methods = method0.size() + method1.size() + method2.size() + method3.size();
	unsigned int index = random_in_range(0, total_methods);
	if (total_methods == index || max_depth == 0) {
		is_value = true;
		double lower_bound = 0;
		double upper_bound = 1000;//I don't know why I chose this value
		std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
		std::default_random_engine re((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
		value = unif(re);
		arity = 0;
		return;
	}
	bool found = false;
	while(!found){
		switch (random_in_range(0, 3)) {
			case 0:
				if(method0.size() > 0){
					arity = 0;
					array_index = random_in_range(0, method0.size() - 1);
					found = true;
				}
				break;
			case 1:
				if (method1.size() > 0) {
					arity = 1;
					array_index = random_in_range(0, method1.size() - 1);
					found = true;
				}
				break;
			case 2:
				if (method2.size() > 0) {
					arity = 2;
					array_index = random_in_range(0, method2.size() - 1);
					found = true;
				}
				break;
			case 3:
				if (method3.size() > 0) {
					arity = 3;
					array_index = random_in_range(0, method3.size() - 1);
					found = true;
				}
				
				break;
			}
		}
	for (unsigned int i = 0; i < arity; i++) {
		node * result = new node(data, max_depth - 1);
		
		children_vector.push_back(result);
		cout << children_vector[i] << endl;
	}
	
}
ostream& operator<<(ostream &out, node&  other) {
	vector<string> raw_result;
	other.write(&raw_result, 0);
	for (unsigned int i = 0; i < raw_result.size(); i++) {
		out << std::fixed;
		out << raw_result[i] << endl;
	}
	other.clear_write_flag();
	return out;
}
void node::add_func(double(*op)(string *, stock *)) {
	string op_id;
	(*op)(&op_id, nullptr);
	for (unsigned int i = 0; i < node::symbol0.size(); i++) {
		if (node::symbol0[i] == op_id) {
			return;
		}
	}
	node::symbol0.push_back(op_id);
	node::method0.push_back(op);
}
void node::add_func(double (*op)(double, string *, stock *)) {
	string op_id;
	(*op)(1, &op_id, nullptr);
	for (unsigned int i = 0; i < node::symbol1.size(); i++) {
		if (node::symbol1[i] == op_id) {
			return;
		}
	}
	node::symbol1.push_back(op_id);
	node::method1.push_back(op);
}
void node::add_func(double(*op)(double, double, string *, stock *)) {
	string op_id;
	(*op)(1, 1, &op_id, nullptr);
	for (unsigned int i = 0; i < node::symbol2.size(); i++) {
		if (node::symbol2[i] == op_id) {
			return;
		}
	}
	node::symbol2.push_back(op_id);
	node::method2.push_back(op);
	cout << "Success adding method" << endl;
}
void node::add_func(double(*op)(double, double, double, string *, stock *)) {
	string op_id;
	(*op)(1, 1, 1, &op_id, nullptr);
	for (unsigned int i = 0; i < node::symbol3.size(); i++) {
		if (node::symbol3[i] == op_id) {
			return;
		}
	}
	node::symbol3.push_back(op_id);
	node::method3.push_back(op);
}
node::~node() {
	for (unsigned int i = 0; i < children_vector.size() && children_vector.size() > 0 && children_vector[i] != nullptr; i++) {
			delete children_vector[i];
	}
}
node * node::random_node_in_tree(int depth) {
	int chance = random_in_range(0, depth);
	if (chance == 0) {
		return this;
	}
	return children_vector[random_in_range(0, arity)]->random_node_in_tree(depth + 1);
}
double node::execute() {
	string symbol = "";
	if (is_value)return value;
	
	switch (arity) {
		case 0:
			return method0[array_index](&symbol, stock_data);
			break;
		case 1:
			return method1[array_index](children_vector[0]->execute(), &symbol, stock_data);
			break;
		case 2:
			double arg1;
			arg1 = children_vector[0]->execute();
			double arg2;
			arg2 = children_vector[1]->execute();
			return method2[array_index](arg1, arg2, &symbol, stock_data);
			break;
		case 3:
			return method3[array_index](children_vector[0]->execute(), children_vector[1]->execute(), children_vector[2]->execute(), &symbol, stock_data);
			break;
		}
	throw exception("Strange arity: " + arity);
}
gen_container::gen_container(string stock_name) {
	stock_obj = new stock (stock_name);
}
gen_container * gen_container::copy() {
	return new gen_container(this);
}
gen_container::gen_container(gen_container * self) {
	stock_obj = self->stock_obj->copy();
	stock_quant = self->stock_quant;
	balance = self->balance;
}
