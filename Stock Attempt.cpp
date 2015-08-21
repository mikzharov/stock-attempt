// Stock Attempt.cpp : Defines the entry point for the console application.




#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <vector>
#include <sstream>
#include <iomanip>
#include <chrono>

#include <cstdlib>

#include "genetic.h"
#include "stock.h"

#include <random>
using namespace std;





double add(double a, double b, string * symbol, stock * data) {
	if (symbol != nullptr) {
		(*symbol) = "+";
	}
	return a + b;
}
double subtract(double a, double b, string * symbol, stock * data) {
	if (symbol != nullptr) {
		(*symbol) = "-";
	}
	return a - b;
}
double multiply(double a, double b, string * symbol, stock * data) {
	if (symbol != nullptr) {
		(*symbol) = "*";
	}
	return a * b;
}
double protected_divide(double a, double b, string * symbol, stock * data) {
	if (symbol != nullptr) {
		(*symbol) = "/";
	}
	if (b == 0) {
		return 0;
	}
	return a / b;
}
double adjusted(string * symbol, stock * data) {
	if (symbol != nullptr) {
		(*symbol) = "adjusted";
	}
	if (data != nullptr) {
		return data->get_adjusted();
	}
	return 0;
}
double close(string * symbol, stock * data) {
	if (symbol != nullptr) {
		(*symbol) = "close";
	}
	if (data != nullptr) {
		return data->get_close();
	}
	return 0;
}
double high(string * symbol, stock * data) {
	if (symbol != nullptr) {
		(*symbol) = "high";
	}
	if (data != nullptr) {
		return data->get_high();
	}
	return 0;
}
double low(string * symbol, stock * data) {
	if (symbol != nullptr) {
		(*symbol) = "low";
	}
	if (data != nullptr) {
		return data->get_low();
	}
	return 0;
}
double open(string * symbol, stock * data) {
	if (symbol != nullptr) {
		(*symbol) = "open";
	}
	if (data != nullptr) {
		return data->get_open();
	}
	return 0;
}
double volume(string * symbol, stock * data) {
	if (symbol != nullptr) {
		(*symbol) = "volume";
	}
	if (data != nullptr) {
		return data->get_volume();
	}
	return 0;
}

std::random_device rd;


int once_seeded(int min, int max) {
	// only used once to initialise (seed) engine
	std::mt19937 rng(rd());   // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased
	return uni(rng);
}
int inf_seeded(int min, int max) {
	std::random_device rb;
	std::mt19937 rng(rb());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased
	return uni(rng);
}
int main()
{
	stock a("AMZN");
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

	/*while(true){
		
		node b(&a, 10);
		cout << std::fixed;
		cout << b << endl;
		cout << "Result: " << b.execute() << endl; 
		cout << "--------------------------------" << endl;
		node c = b.copy();
		cout << c << endl;
		
	}*/
	for (int i = 0; i < 10; i++) {
		cout << once_seeded(0, 1);
	}
	cout << endl;
	for (int i = 0; i < 10; i++) {
		cout << inf_seeded(0, 1);
	}
	string hi;
	cin >> hi;
	return 0;
}
