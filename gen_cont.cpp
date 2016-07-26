#pragma once
#include "gen_cont.h"

gen_cont::gen_cont(double money, stock * st) {
	n.reset(new node(5, st));
	original_money = money;
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
	result = (int)n->result();
	if (result * st->get_high(latest) < money && result > 0 && st->get_high(latest) > 0) {//Simulates the program buying / selling stock if it has enough money
		money -= result * st->get_high(latest);
		stock_owned += result;
		trades++;
		return result;
	} else if (result > 0 && money > st->get_high(latest)) {//Simulates buying maximum possible
		int stock_bought = (int)(money / st->get_high(latest));//Find the maximum amount the can be bought
		if (stock_bought == 0) throw exception();
		money -= stock_bought * st->get_high(latest);
		stock_owned += stock_bought;
		if (stock_owned == 0) throw exception();
		trades++;
		return result;
	} else if (result < 0 && -result < stock_owned && stock_owned > 0) {//Simulates selling stock it has
		if (stock_owned == 0) throw exception();
		stock_owned += result;
		money += -(result) * st->get_low(latest);
		trades++;
		return result;
	} else if (result < 0 && stock_owned > 0) {//Simulates selling everything
		if (stock_owned == 0) throw exception();
		money += stock_owned * st->get_low(latest);
		stock_owned = 0;
		trades++;
		return result;
	}
	return result;
}

void gen_cont::update_fitness() {
	fitness = stock_owned * st->get_low(latest) + money;
	if (trades == 0) {
		fitness = 0;
		return;
	}
	fitness += trades;
}
