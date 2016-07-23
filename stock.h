#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
enum type{latest};
using namespace std;
class quote {
public:
	struct stock_data {
		double open = 0.0;
		double high = 0.0;
		double low = 0.0;
		double close = 0.0;
		double volume = 0.0;
		double adjusted = 0.0;
		string date;
	};
	vector<stock_data> data;
};
class stock {
private:
	static vector<string> symbol_index;
	int array_index;//The current entry being operated on
public:
	int day_since_start = 0;
	stock() {};
	stock(string symbol);
	void get_values(string a);
	int length;
	bool next_day();

	
	//below are overloads to get past data. Also checks that the data index is not negative
	quote::stock_data get(int past) const {
		if (array_index + past < length && past >= 0)
			return content[symbol_index_int].data[array_index + past];
		else return quote::stock_data();
	}
	double get_open(int past) const{
		return get(past).open;
	}
	double get_high(int past = 0) const{
		return get(past).high;
	}
	double get_low(int past = 0) const{
		return get(past).low;
	}
	double get_close(int past = 0) const {
		return get(past).close;
	}
	double get_volume(int past = 0) const {
		return get(past).volume;
	}
	double get_adjusted(int past = 0) const {
		return get(past).adjusted;
	}

	void reset() {
		array_index = length - 1;//This sets the array index to the first entry
	}
	string symbol;//This is the stock symbol
	unsigned int symbol_index_int;//Defines in which index the content is
	static vector<quote> content;//All the quotes
	
	const string url_base = "http://real-chart.finance.yahoo.com/table.csv?s=";
	vector<string> initialize();
};
