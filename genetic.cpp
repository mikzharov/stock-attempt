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
#include <assert.h>
vector<string> node::symbol0;
vector<string> node::symbol1;
vector<string> node::symbol2;
vector<string> node::symbol3;
vector <vector<string> *> node::symbol_index = {&symbol0, &symbol1, &symbol2, &symbol3};
vector<double(*)(string *, stock *)> node::method0;
vector<double(*)(double, string *, stock *)> node::method1;
vector<double(*)(double, double, string *, stock *)> node::method2;
vector<double(*)(double, double, double, string *, stock *)> node::method3;

int node::zero_arity_percent = 25;
int node::one_arity_percent = 25;
int node::two_arity_percent = 25;
int node::three_arity_percent = 25;

random_in_range r;
bool is_double(const char* str){
	char* endptr = 0;
	strtod(str, &endptr);

	if (*endptr != '\0' || endptr == str)
		return false;
	return true;
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
		is_written = true;
		(*vect)[depth] += sstm.str();
		return;
	}
	if (is_balance) {
		std::stringstream sstm;
		sstm << "bal" << ",";

		(*vect)[depth] += sstm.str();
		is_written = true;
		return;
	}
	if (is_stock) {
		std::stringstream sstm;
		sstm << "stock" << ",";

		(*vect)[depth] += sstm.str();
		is_written = true;
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
	default:
		throw exception("Arity not found");
	}
	(*vect)[depth] += ",";
	is_written = true;
}
node::node(node * n) {
	copy_into(n);
}
void node::copy_into(const node * n) {
	//for (unsigned int i = 0; i < children_vector.size() && children_vector[i] != nullptr; i++) {
	//	delete children_vector[i];
	//}
	this->children_vector.clear();
	this->arity = n->arity;
	this->array_index = n->array_index;
	this->is_value = n->is_value;
	this->is_written = n->is_written;
	this->value = n->value;
	assert(!n->stock_data.symbol.empty());

	this->is_balance = n->is_balance;
	this->is_stock = n->is_stock;
	assert(n->arity == n->children_vector.size());
	for (unsigned int i = 0; i < n->children_vector.size(); i++) {
		this->children_vector.push_back(new node(n->children_vector[i]));
	}
}
void node::point_mutate() {
	if (arity == 0) {
		switch(r(0, 2 + symbol_index[arity]->size() - 1)){
			case 0:
				//Nothing
				break;
			case 1:
				is_balance = true;
				is_value = false;
				is_stock = false;
				
				break;
			case 2:
				is_stock = true;
				is_balance = false;
				is_value = false;
				break;
			default:
				array_index = r(0, symbol_index[arity]->size() - 1);
				is_value = false;
				is_stock = false;
				is_balance = false;
				break;
		}
	}
	array_index = r(0, symbol_index[arity]->size() - 1);
	is_value = false;
}
void node::subtree_mutate(node * n) {
	if(n != nullptr){
		copy_into(n);
	} else {
		
		this->copy_into(new node(3));
	}

}
void node::shrink_mutate() {
	if (arity == 0) {
		return;
	}
	arity = 0;
	double lower_bound = 0;
	double upper_bound = 1000;//I don't know why I chose this value
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::default_random_engine re((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
	if (symbol_index[0]->size() == 0) {
		switch (r(0, 2)) {
		case 0:
			
			is_value = true;
			value = unif(re);
			break;
		case 1:
			is_balance = true;
			break;
		case 2:
			is_stock = true;
			break;
		}
	} else {
		array_index = r(0, symbol_index[0]->size() - 1);
	}
	children_vector.clear();
}
node::node(vector<vector<string>> &n, int depth) {
	if (n.size() == 0) {
		throw exception("Vector of vectors is 0");
	}
	if (n[depth].size() == 0) {
		n.erase(n.begin());
	}
	string op = n[depth][0];
	is_value = false;
	if (is_double(op.c_str())) {
		arity = 0;
		array_index = 0;
		is_value = true;
		value = stod(op.c_str());

	}
	if (op == "bal") {
		arity = 0;
		is_balance = true;
		return;
	}
	if (op == "stock") {
		arity = 0;
		is_stock = true;
		return;
	}
	for (unsigned int i = 0; i < symbol0.size(); i++) {
		if (op == symbol0[i]) {
			arity = 0;
			array_index = i;
			break;
		}
	}
	for (unsigned int i = 0; i < symbol1.size(); i++) {
		if (op == symbol1[i]) {
			arity = 1;
			array_index = i;
			break;
		}
	}
	for (unsigned int i = 0; i < symbol2.size(); i++) {
		if (op == symbol2[i]) {
			arity = 2;
			array_index = i;
			break;
		}
	}
	for (unsigned int i = 0; i < symbol3.size(); i++) {
		if (op == symbol3[i]) {
			arity = 3;
			array_index = i;
			break;
		}
	}
	n[depth].erase(n[depth].begin());
	for (unsigned int i = 0; i < arity; i++) {
		children_vector.push_back(new node(n, depth + 1));
	}
}
vector<vector<string>> node::from_file(std::istream &is) {
	string str;
	string parts;
	std::stringstream ss;
	vector<vector<string>> result;
	for (int i = 0; getline(is, str); i++) {
		ss.clear();
		ss.str(str);
		result.push_back(vector<string>());
		for (int b = 0; getline(ss, parts, ',');) {
			if (parts == ",")continue;

			result[i].push_back(parts);
		}
	}
	return result;
}
node::node(int max_depth) {
	is_value = false;
	assert(!data.symbol.empty());

	arity = -1;
	unsigned int total_methods = method0.size() + method1.size() + method2.size() + method3.size();
	unsigned int index = r(0, total_methods + 3);
	if (total_methods + 1 == index || max_depth == 0) {
		is_value = true;
		double lower_bound = 0;
		double upper_bound = 1000;//I don't know why I chose this value
		std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
		std::default_random_engine re((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
		value = unif(re);
		arity = 0;
		return;
	}
	if (total_methods + 2 == index) {
		is_balance = true;
		arity = 0;
		return;
	}
	if (total_methods + 3 == index) {
		is_stock = true;
		arity = 0;
		return;
	}
	bool found = false;
	while(!found){
		switch (r(0, 3)) {
			case 0:
				if(method0.size() > 0){
					arity = 0;
					array_index = r(0, method0.size() - 1);
					found = true;
				}
				break;
			case 1:
				if (method1.size() > 0) {
					arity = 1;
					array_index = r(0, method1.size() - 1);
					found = true;
				}
				break;
			case 2:
				if (method2.size() > 0) {
					arity = 2;
					array_index = r(0, method2.size() - 1);
					found = true;
				}
				break;
			case 3:
				if (method3.size() > 0) {
					arity = 3;
					array_index = r(0, method3.size() - 1);
					found = true;
				}
				
				break;
			}
		}
	for (unsigned int i = 0; i < arity; i++) {
		node * result = new node(max_depth - 1);
		children_vector.push_back(result);
	}
	
}
ostream& operator<<(ostream &out, node *  other) {
	vector<string> raw_result;
	other->write(&raw_result, 0);
	for (unsigned int i = 0; i < raw_result.size(); i++) {
		out << std::fixed;
		out << raw_result[i] << endl;
	}
	other->clear_write_flag();
	return out;
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
istream& operator>>(istream &out, node *&  other) {
	other = new node(node::from_file(out), 0);
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
node * node::breed(node * mother, node * father) {
	node * result = new node(father);
	node * mdna = mother->random_node_in_tree();//Mother dna
	result->random_node_in_tree()->copy_into(mdna);
	//cout << "mDNA: " << mdna << endl;
	return result;
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
	//for (unsigned int i = 0; i < children_vector.size(); i++) {
	//		delete children_vector[i];
	//}
	children_vector.clear();
}

node * node::random_node_in_tree(int depth, node * current) {
	int chance = r(0, depth);
	if (chance == 0) {
		current = this;
	}
	if (arity == 0 || children_vector.size() == 0 || is_balance || is_stock || is_value) {
		return current;
	}
	int index = r(0, arity - 1);
	return children_vector[index]->random_node_in_tree(depth + 1, current);
}
void node::mutate() {
	switch (r(0, 2)) {
	case 0:
		this->random_node_in_tree()->point_mutate();
		break;
	case 1:
		this->random_node_in_tree()->subtree_mutate();
		break;
	case 2:
		this->random_node_in_tree()->shrink_mutate();
		break;
	}
}
double node::execute(double stock_quant, double balance, stock * stock_data) {
	string symbol = "";
	if (is_value)return value;
	if (is_stock)return stock_quant;
	if (is_balance)return balance;
	assert(!stock_data.symbol.empty());
	assert(children_vector.size() >= arity);
	switch (arity) {
		
		case 0:
			assert(method0.size() > (unsigned)array_index);
			assert(!stock_data.symbol.empty());
			return method0[array_index](&symbol, stock_data);
			break;
		case 1:
			
			assert(method1.size() > (unsigned)array_index);
			return method1[array_index](children_vector[0]->execute(stock_quant, balance, stock_data), &symbol, stock_data);
			break;
		case 2:
			
			assert(method2.size() > (unsigned)array_index);
			double arg1;
			
			arg1 = children_vector[0]->execute(stock_quant, balance, stock_data);
			double arg2;
			arg2 = children_vector[1]->execute(stock_quant, balance, stock_data);
			return method2[array_index](arg1, arg2, &symbol, stock_data);
			break;
		case 3:
			assert(method3.size() > (unsigned)array_index);
			
			return method3[array_index](children_vector[0]->execute(stock_quant, balance, stock_data), children_vector[1]->execute(stock_quant, balance, stock_data), children_vector[2]->execute(stock_quant, balance, stock_data), &symbol, stock_data);
			break;
		}
	throw exception("Strange arity: " + arity);
}
gen_container::gen_container(string stock_name) {
	if (stock_name.empty())throw exception("No empty strings allowed");
	stock_obj.get_values(stock_name);
	node_ = node(3);
	assert(!node_.stock_data.symbol.empty());
	
	balance = 500;
}
