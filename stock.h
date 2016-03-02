#pragma once
#include <string>
#include <vector>
enum type{latest};
using namespace std;
class quote {
public:
	vector<string> date;
	vector<double> open;
	vector<double> high;
	vector<double> low;
	vector<double> close;
	vector<double> volume;
	vector<double> adjusted;

	quote() {};
	~quote() {};
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
			return content[symbol_index_int].open[index + past];
		else return 0; 
	}
	double get_high(int past = 0) const{
		int index = array_index;
		if (past == latest) {
			index = 0;
			past = 0;
		}
		if (array_index + past < length && past >= 0)
			return content[symbol_index_int].high[index + past];
		else return 0;
	}
	double get_low(int past = 0) const{
		int index = array_index;
		if (past == latest) {
			index = 0;
			past = 0;
		}
		if (array_index + past < length && past >= 0)
			return content[symbol_index_int].low[index + past];
		else return 0; 
	}
	double get_close(int past = 0) const {
		int index = array_index;
		if (past == latest) {
			index = 0;
			past = 0;
		}
		if (array_index + past < length  && past >= 0)
			return content[symbol_index_int].close[index + past];
		else return 0;
	}
	double get_volume(int past = 0) const {
		int index = array_index;
		if (past == latest) {
			index = 0;
			past = 0;
		}
		if (array_index + past < length && past >= 0)
			return content[symbol_index_int].volume[index + past];
		else return 0;
	}
	double get_adjusted(int past = 0) const {
		int index = array_index;
		if (past == latest) {
			index = 0;
			past = 0;
		}
		if (array_index + past < length && past >= 0)
			return content[symbol_index_int].adjusted[index + past];
		else return 0; 
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
