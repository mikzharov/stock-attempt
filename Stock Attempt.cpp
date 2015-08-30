// Stock Attempt.cpp : Defines the entry point for the console application.




#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <vector>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <cstdlib>

#include "genetic.h"
#include "stock.h"

#include <random>
using namespace std;




double decision(double dec, double a, double b, string * symbol, stock * data) {
	if (data != nullptr && data->symbol.empty())throw exception("Symbol must not be null");
	if (symbol != nullptr) {
		(*symbol) = "?";
	}
	if (dec == 0) {
		return a;
	}
	return b;
}
double add(double a, double b, string * symbol, stock * data) {
	if (data != nullptr && data->symbol.empty())throw exception("Symbol must not be null");
	if (symbol != nullptr) {
		(*symbol) = "+";
	}
	return a + b;
}
double subtract(double a, double b, string * symbol, stock * data) {
	if (data != nullptr && data->symbol.empty())throw exception("Symbol must not be null");
	if (symbol != nullptr) {
		(*symbol) = "-";
	}
	return a - b;
}
double multiply(double a, double b, string * symbol, stock * data) {
	if (data != nullptr && data->symbol.empty())throw exception("Symbol must not be null");
	if (symbol != nullptr) {
		(*symbol) = "*";
	}
	return a * b;
}
double protected_divide(double a, double b, string * symbol, stock * data) {
	if (data != nullptr && data->symbol.empty())throw exception("Symbol must not be null");
	if (symbol != nullptr) {
		(*symbol) = "/";
	}
	if (b == 0) {
		return 0;
	}
	return a / b;
}
double adjusted(string * symbol, stock * data) {
	if (data != nullptr && data->symbol.empty())throw exception("Symbol must not be null");
	if (symbol != nullptr) {
		(*symbol) = "adjusted";
	}
	if (data != nullptr) {
		return data->get_adjusted();
	}
	return 0;
}
double adjusted_days(double d, string * symbol, stock * data) {
	if (data != nullptr && data->symbol.empty())throw exception("Symbol must not be null");
	if (symbol != nullptr) {
		(*symbol) = "adjusted_days";
	}
	if (data != nullptr) {
		return data->get_adjusted((int)d);
	}
	return 0;
}
double close(string * symbol, stock * data) {
	if (data != nullptr && data->symbol.empty())throw exception("Symbol must not be null");
	if (symbol != nullptr) {
		(*symbol) = "close";
	}
	if (data != nullptr) {
		return data->get_close();
	}
	return 0;
}
double close_days(double d, string * symbol, stock * data) {
	if (data != nullptr && data->symbol.empty())throw exception("Symbol must not be null");
	if (symbol != nullptr) {
		(*symbol) = "close_days";
	}
	if (data != nullptr) {
		return data->get_close((int)d);
	}
	return 0;
}
double high(string * symbol, stock * data) {
	if (data != nullptr && data->symbol.empty())throw exception("Symbol must not be null");
	if (symbol != nullptr) {
		(*symbol) = "high";
	}
	if (data != nullptr) {
		return data->get_high();
	}
	return 0;
}
double high_days(double d, string * symbol, stock * data) {
	if (data != nullptr && data->symbol.empty())throw exception("Symbol must not be null");
	if (symbol != nullptr) {
		(*symbol) = "high_days";
	}
	if (data != nullptr) {
		return data->get_high((int)d);
	}
	return 0;
}
double low(string * symbol, stock * data) {
	if (data != nullptr && data->symbol.empty())throw exception("Symbol must not be null");
	if (symbol != nullptr) {
		(*symbol) = "low";
	}
	if (data != nullptr) {
		return data->get_low();
	}
	return 0;
}
double low_days(double d, string * symbol, stock * data) {
	if (data != nullptr && data->symbol.empty())throw exception("Symbol must not be null");
	if (symbol != nullptr) {
		(*symbol) = "low_days";
	}
	if (data != nullptr) {
		return data->get_low((int)d);
	}
	return 0;
}
double open(string * symbol, stock * data) {
	if (data != nullptr && data->symbol.empty())throw exception("Symbol must not be null");
	if (symbol != nullptr) {
		(*symbol) = "open";
	}
	if (data != nullptr) {
		return data->get_open();
	}
	return 0;
}
double open_days(double d, string * symbol, stock * data) {
	if (data != nullptr && data->symbol.empty())throw exception("Symbol must not be null");
	if (symbol != nullptr) {
		(*symbol) = "open_days";
	}
	if (data != nullptr) {
		return data->get_open((int)d);
	}
	return 0;
}
double volume(string * symbol, stock * data) {
	if (data != nullptr && data->symbol.empty())throw exception("Symbol must not be null");
	if (symbol != nullptr) {
		(*symbol) = "volume";
	}
	if (data != nullptr) {
		return data->get_volume();
	}
	return 0;
}
double volume_days(double d, string * symbol, stock * data) {
	if (data != nullptr && data->symbol.empty())throw exception("Symbol must not be null");
	if (symbol != nullptr) {
		(*symbol) = "volume_days";
	}
	if (data != nullptr) {
		return data->get_volume((int)d);
	}
	return 0;
}
random_in_range b;
void global_mutate(vector<gen_container>& population, double percent) {
	int total_mutations = (int)((population.size() * percent)/100.0);
	for (int i = 0; i < total_mutations; i++) {
		population[b(0, population.size())].node_.mutate();
	}
}
void global_breed(vector<gen_container>& population, double percent) {
	int pop_size = population.size();
	int total_crossovers = (int)((pop_size * percent) / 100.0);
	for (int i = 0; i < total_crossovers; i++) {
		int rand_1 = pop_size / 4 * 3;
		int rand_2 = b(rand_1, pop_size - 1);
		int rand_3 = b(rand_1, pop_size - 1);
		node::breed(&population[rand_2].node_, &population[rand_3].node_);
	}
}
void run(int population_, int generation) {
	vector<gen_container> population;


	for (int i = 0; i < population_; i++) {
		population.push_back(gen_container("AMZN"));
	}


	for (int i = 0; i < generation; i++) {
		for (int i = 0; i < population_; i++) {
			population[i].execute();
		}
		std::sort(population.begin(), population.end());

		std::fstream out("C:/Users/Misha/Desktop/output.txt", std::fstream::out | std::fstream::trunc);
		out << population.back().node_;
		out.close();
		cout << "Generation: " << i << endl;

		global_mutate(population, 1);
		global_breed(population, 5);
	}
}
int main()
{

	node::add_func(add);
	node::add_func(subtract);
	node::add_func(multiply);
	node::add_func(protected_divide);
	node::add_func(adjusted);
	node::add_func(close);
	node::add_func(high);
	node::add_func(low);
	node::add_func(open);
	node::add_func(volume);
	node::add_func(adjusted_days);
	node::add_func(close_days);
	node::add_func(high_days);
	node::add_func(low_days);
	node::add_func(open_days);
	node::add_func(volume_days);
	node::add_func(decision);
	
	run(500, 500);
	return 0;
}
