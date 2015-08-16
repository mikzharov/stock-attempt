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



int random_in_range1(int min, int max) {
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

	return uni(rng);
}

double add(double a, double b, string * symbol, stock * data) {
	if (symbol != nullptr) {
		(*symbol) = "+";
	}
	return a + b;
}
int main()
{
	stock a("AMZN");
	while(true){
		node::add_func(add);
		node node(&a);
		

		cout << node << endl;

		string hi;
		cin >> hi;
	}
	return 0;
}

