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
#include "stock.h"
using namespace std;




int main()
{
	tm temp;
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
	}
	


	string hi;
	cin >> hi;
	return 0;
}

