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
int main()
{
	/*tm temp;
	cout << RAND_MAX;


	try{
		stock a("AMZN");
		localtime_s(&temp, &a.operation_time);
		cout << put_time(&temp, "%c") << endl;

		a.next_day();

		localtime_s(&temp, &a.operation_time);
		cout << put_time(&temp, "%c") << endl;
	}
	catch (exception e) {
		cout << e.what();
	}*/


	stock a("AMZN");
	gen_container b(a);
	b.balance = 100;
	b.stock_quant = 1;
	sell * c = new sell(&b, 2);
	c->amount->destroy();
	value * d = new value ();
	d->content = 500;
	c->amount = d;
	b.node = c;
	b.node->execute();
	cout << b.balance << " _ " << b.stock_quant << endl;

	gen_container e = b.copy();
	e.node->execute();
	cout << e.balance << " _ " << e.stock_quant << endl;

	string hi;
	cin >> hi;
	return 0;
}

