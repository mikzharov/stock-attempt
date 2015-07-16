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
	double get_open() { return content.open[array_index]; }
	double get_high() { return content.high[array_index]; }
	double get_low() { return content.low[array_index]; }
	double get_close() { return content.close[array_index]; }
	long get_volume() { return content.volume[array_index]; }
	double get_adjusted() { return content.open[array_index]; }
	time_t operation_time;
private:
	int array_index;
	string symbol;
	quote content;
	const string url_base = "http://real-chart.finance.yahoo.com/table.csv?s=";
	vector<string> initialize();
};
