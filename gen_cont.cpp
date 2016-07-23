#pragma once
#include "gen_cont.h"

gen_cont::gen_cont(double money, stock * st) {
	n.reset(new node(5, st));
	this->st = st;
	this->money = money;
}

double gen_cont::get_money() const {
	return money;
}

int gen_cont::get_stock_owned() const {
	return stock_owned;
}

double gen_cont::get_result() const {
	return result;
}

double gen_cont::evaluate() {
	/*
	result = n->result();
	if (result * st->get_high(latest) < money && result >= 0) {//Simulates the program buying / selling stock if it has enough money
		money -= result * st->get_high(latest);
		stock_owned += (int)result;
		return result;
	}
	if (result >= 0) {//Simulates buying maximum possible
		int stock_bought = (int)(money / st->get_high(latest));//Find the maximum amount the can be bought
		money -= stock_bought * st->get_high(latest);
		stock_owned += stock_bought;
		return result;
	}
	if (result < 0 && -result < stock_owned) {//Simulates selling stock it has
		stock_owned += (int)result;
		money += -((int)result) * st->get_low(latest);
		return result;
	}
	if (result < 0) {//Simulates selling everything
		money += stock_owned * st->get_low(latest);
		stock_owned = 0;
		return result;
	}
	return result;
	*/
	return 0.0;
}

void gen_cont::update_fitness() {
	fitness = stock_owned * st->get_low(latest) + money;
}

string header = 
"__kernel void GENINDIV (__global float* adjusted_buf, __global float* close_buf, __global float* high_buf, __global float* low_buf, __global float* open_buf, __global float* volume_buf, __global float* result, int buf_size)"
"	{                                                                  "
"		const int i = get_global_id(0);                                ";
string gen_cont::compile() {
	string kernel = header;
	kernel += "int b = " + to_string(n->leaves.size() - 1) + ";";//B will be used by methods to check which array indices they should use data from
	kernel += "float leaves["+ to_string((n->leaves.size() + n->children.size())-1) +"] = {";
	for (size_t i = 0; i < n->leaves.size(); i++) {
		kernel += to_string(n->leaves.at(i));
		kernel += ",";
	}
	kernel += "};";
	for (size_t i = n->children.size() - 1; i > 0; i--) {
		kernel += n->children.at(i)->a;
		kernel += "b++;";
	}
	kernel += "result[i]=leaves[" + to_string((n->leaves.size() + n->children.size()) - 2) + "];}";
	return kernel;
}