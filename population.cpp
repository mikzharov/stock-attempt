#include "population.h"
#include <stdio.h>
#include <string>
#include "stock.h"
#include <chrono>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <memory>
#include "gen_cont.h"


population::population(int size, int initial_worth, string stock1) {
	st.reset(new stock(stock1));
	this->size = size;
	for (int i = 0; i < size; i++) {
		pop.emplace_back(st.get(), initial_worth);//This initializes the object in the vector
	}
}


population::~population() {
}

void population::next_generation() {
	for (int i = 0; i < pop.size(); i++) {
		pop.at(i).evaluate();
	}
	
}
