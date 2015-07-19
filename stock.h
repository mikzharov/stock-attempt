#pragma once
#include <string>
#include <vector>
using namespace std;
class quote {
public:
	string *date = nullptr;
	double *open = nullptr;
	double *high = nullptr;
	double *low = nullptr;
	double *close = nullptr;
	long *volume = nullptr;
	double *adjusted = nullptr;
	~quote();
};
class stock {
public:
	stock() {};
	stock(string symbol);
	
	int length;
	void next_day();
	tm get_date();
	
	//below are overloads to get past data. Also checks that the data index is not negative
	double get_open(int past = 0) { if (array_index + past >= 0 && past >= 0)return content.open[array_index + past]; else return 0; }
	double get_high(int past = 0) { if (array_index + past >= 0 && past >= 0)return content.high[array_index + past]; else return 0; }
	double get_low(int past = 0) { if (array_index + past >= 0 && past >= 0)return content.low[array_index + past]; else return 0; }
	double get_close(int past = 0) { if (array_index + past >= 0 && past >= 0)return content.close[array_index + past]; else return 0; }
	long get_volume(int past = 0) { if (array_index + past >= 0 && past >= 0)return content.volume[array_index + past]; else return 0; }
	double get_adjusted(int past = 0) { if (array_index + past >= 0 && past >= 0)return content.adjusted[array_index + past]; else return 0; }
	time_t operation_time;
private:
	int array_index;
	string symbol;
	quote content;
	const string url_base = "http://real-chart.finance.yahoo.com/table.csv?s=";
	vector<string> initialize();
};
