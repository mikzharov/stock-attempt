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
#include <future>
#include <thread>
random_in_range c;
population::population(int size, int initial_worth, string stock1) {
	st.reset(new stock(stock1));
	symbol = stock1;
	this->size = size;
	for (int i = 0; i < size; i++) {
		pop.emplace_back(initial_worth, st.get());//This initializes the object in the vector
	}
}

void population::next_gen(int section) {
	stock s(symbol);
	size_t s_size = pop.size() / max_async;
	size_t initial = (size_t) (s_size * section);
	size_t end = (size_t) (s_size * section + s_size);
	while (s.next_day()) {
		for (size_t i = initial; i < end; i++) {
			pop.at(i).evaluate();
			pop.at(i).update_fitness();
		}
	}
	s.reset();
}

void population::simulate() {
	for (int i = 0; i < generations; i++) {
		for (int i = 0; i < pop.size(); i++) {
			pop.at(i).reset();
		}

		//cout << i << endl;
		//Visual studios is flagging this as an error, but it compiles and runs
		auto handle0 = std::async(std::launch::async, &population::next_gen, this, 0);
		auto handle1 = std::async(std::launch::async, &population::next_gen, this, 1);
		auto handle2 = std::async(std::launch::async, &population::next_gen, this, 2);
		auto handle3 = std::async(std::launch::async, &population::next_gen, this, 3);
		auto handle4 = std::async(std::launch::async, &population::next_gen, this, 4);
		auto handle5 = std::async(std::launch::async, &population::next_gen, this, 5);
		auto handle6 = std::async(std::launch::async, &population::next_gen, this, 6);
		auto handle7 = std::async(std::launch::async, &population::next_gen, this, 7);
		auto handle8 = std::async(std::launch::async, &population::next_gen, this, 8);
		auto handle9 = std::async(std::launch::async, &population::next_gen, this, 9);

		handle0.wait();
		//cout << "0 done" << endl;
		handle1.wait();
		//cout << "1 done" << endl;
		handle2.wait();
		//cout << "2 done" << endl;
		handle3.wait();
		//cout << "3 done" << endl;
		handle4.wait();
		//cout << "4 done" << endl;
		handle5.wait();
		//cout << "5 done" << endl;
		handle6.wait();
		//cout << "6 done" << endl;
		handle7.wait();
		//cout << "7 done" << endl;
		handle8.wait();
		//cout << "8 done" << endl;
		handle9.wait();
		//cout << "9 done" << endl;
		//next_gen();

		std::sort(pop.begin(), pop.end());
		size_t size = pop.size();

		for (int i = 0; i < size * crossover_rate; i++) {
			node * to_crossover_with = (pop.at(c((int)(size - (int)((double)size * top_percent_to_crossover)), (int)size - 1)).n.get());
			pop.at(c((int)(size - (double)size * top_percent_to_crossover), (int)size - 1)).n->crossover(to_crossover_with);
		}

		for (int i = 0; i < (int)((double)size * mutation_rate); i++) {
			pop.at(c(0, (int)size - 1)).n->all_mutate();
		}
		cout << "=============================" << endl;
		cout << "Fitness " << i << ": " << pop.at(pop.size() - 1).get_fitness() << endl;
		cout << "Money " << i << ": " << pop.at(pop.size() - 1).get_money() << endl;
		cout << "Stock Owned " << i << ": " << pop.at(pop.size() - 1).get_stock_owned() << endl;
		cout << "Trades " << i << ": " << pop.at(pop.size() - 1).get_trades() << endl;
		if (pop.at(pop.size() - 1).get_fitness() == 0) throw exception();
	}
	ofstream myfile;
	myfile.open("NODE.txt");
	myfile << pop.at(0).n.get();
	myfile.close();
	cout << "Stock day: " << st->array_index << endl;
	cout << pop.at(pop.size() - 1).n.get() << endl;
	cout << "Fitness: " << pop.at(pop.size() - 1).get_fitness() << endl;
	cout << "Money: " << pop.at(pop.size() - 1).get_money() << endl;
	cout << "Stock Owned: " << pop.at(pop.size() - 1).get_stock_owned() << endl;
	cout << "Trades: " << pop.at(pop.size() - 1).get_trades() << endl << endl;

	cout << "Fitness 1: " << pop.at(0).get_fitness() << endl;
	cout << "Money 1: " << pop.at(0).get_money() << endl;
	cout << "Stock Owned 1: " << pop.at(0).get_stock_owned() << endl;
	cout << "Trades 1: " << pop.at(0).get_trades() << endl;
	cout << pop.at(0).n.get() << endl;
}
