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
#include <algorithm>
#include "node.h"
#include <iostream>
#include <fstream>
random_in_range c;
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
		pop.at(i).n->revalidate_tree();
		pop.at(i).fitness = pop.at(i).get_money() + pop.at(i).get_stock_owned() * st->get_low(latest);
		if (pop.at(i).n->max_depth() > 400 || pop.at(i).n->count() > 400) {
			pop.at(i).fitness = 0;//Absolutely demolishes fitness if the node gets too big
			pop.at(i).n.reset(new node(5, st.get()));
		}
	}
	std::sort(pop.begin(), pop.end());
	size_t size = pop.size();

	for (int i = 0; i < size * crossover_rate; i++) {
		node * to_crossover_with = (pop.at(c((int)(size - (int)((double)size * top_percent_to_crossover)), (int)size - 1)).n.get());
		pop.at(c((int)((double)size * top_percent_to_crossover), (int)size - 1)).n->crossover(to_crossover_with);
	}

	for (int i = 0; i < size * mutation_rate; i++) {
		pop.at(c(0, (int)size - 1)).n->all_mutate();
	}
	if (!st->next_day())st->reset();
}

void population::simulate() {
	for (int i = 0; i < generations; i++) {
		cout << i << endl;
		next_generation();
	}
	ofstream myfile;
	myfile.open("NODE.txt");
	myfile << pop.at(pop.size()-1).n.get();
	myfile.close();

	cout << pop.at(pop.size() - 1).n.get() << endl;
	cout << "Money: " << pop.at(pop.size() - 1).get_money();
	cout << "Stock: " << pop.at(pop.size() - 1).get_stock_owned();
}
