#pragma once
#include <string>
#include <vector>
enum type{latest};
using namespace std;
class quote {
public:
	struct stock_data {
		double open;
		double high;
		double low;
		double close;
		double volume;
		double adjusted;
		string date;
	};
	vector<stock_data> data;
};
class stock {
public:

	stock() {};
	stock(string symbol);
	void get_values(string a);
	int length;
	bool next_day();

	
	//below are overloads to get past data. Also checks that the data index is not negative
	double get_open(int past = 0) const{
		int index = array_index;
		if (past == latest) {
			index = 0;
			past = 0;
		}
		if (array_index + past < length && past >= 0)
			return content[symbol_index_int].data[index + past].open;
		else return 0; 
	}
	double get_high(int past = 0) const{
		int index = array_index;
		if (past == latest) {
			index = 0;
			past = 0;
		}
		if (array_index + past < length && past >= 0)
			return content[symbol_index_int].data[index + past].high;
		else return 0;
	}
	double get_low(int past = 0) const{
		int index = array_index;
		if (past == latest) {
			index = 0;
			past = 0;
		}
		if (array_index + past < length && past >= 0)
			return content[symbol_index_int].data[index + past].low;
		else return 0; 
	}
	double get_close(int past = 0) const {
		int index = array_index;
		if (past == latest) {
			index = 0;
			past = 0;
		}
		if (array_index + past < length  && past >= 0)
			return content[symbol_index_int].data[index + past].close;
		else return 0;
	}
	double get_volume(int past = 0) const {
		int index = array_index;
		if (past == latest) {
			index = 0;
			past = 0;
		}
		if (array_index + past < length && past >= 0)
			return content[symbol_index_int].data[index + past].volume;
		else return 0;
	}
	double get_adjusted(int past = 0) const {
		int index = array_index;
		if (past == latest) {
			index = 0;
			past = 0;
		}
		if (array_index + past < length && past >= 0)
			return content[symbol_index_int].data[index + past].adjusted;
		else return 0; 
	}
	quote::stock_data get_stock_data(int past = 0) {
		int index = array_index;
		if (past == latest) {
			index = 0;
			past = 0;
		}
		if (array_index + past < length && past >= 0) {
			return content[symbol_index_int].data[index + past];
		} else {
			return content[symbol_index_int].data[index];
		}
	}
	void reset() {
		array_index = length - 1;//This sets the array index to the first entry
	}
	string symbol;//This is the stock symbol
	int array_index;//The current entry being operated on
	unsigned int symbol_index_int;
	static vector<quote> content;//All the quotes
	static vector<string> symbol_index;
	const string url_base = "http://real-chart.finance.yahoo.com/table.csv?s=";
	vector<string> initialize();
};
