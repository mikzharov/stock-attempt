#pragma once
#include "gen_cont.h"

gen_cont::gen_cont(stock * st, double money) {
	n.reset(new node(0, st));
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
}

void gen_cont::update_fitness() {
	fitness = stock_owned * st->get_low(latest) + money;
}
