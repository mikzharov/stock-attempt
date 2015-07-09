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
	stock(string symbol);
private:
	string symbol;
	quote content;
	const string url_base = "http://real-chart.finance.yahoo.com/table.csv?s=";
	vector<string> initialize();
};
