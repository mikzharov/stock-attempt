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
using namespace std;




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

	
	//cout << fixed << mult.execute() << endl;
	stock a("AMZN");
	gen_container b(a);
	buy c(b);
	b.balance = 500;
	c.execute();
	cout << b.balance << endl;
	cout << b.stock_quant << endl;

	string hi;
	cin >> hi;
	return 0;
}

