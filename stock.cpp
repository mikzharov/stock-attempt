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
#include <assert.h>
using namespace std;
static size_t write_data(char *contents, size_t size, size_t nmemb, string &userp) {
	
	for (unsigned int c = 0; c < size * nmemb; c++)
	{
		userp.push_back(contents[c]);
		
	}

	return size * nmemb;
}
tm string_to_date(const string &date) {
	tm time;
	stringstream ss(date);
	ss >> get_time(&time, "%Y-%m-%d");
	time.tm_hour = 0;
	time.tm_min = 0;
	time.tm_sec = 0;
	
	return time;
}
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
quote::~quote() {
	if(date != nullptr)
	delete[] date;
	if (open != nullptr)
	delete[] open;
	if (high != nullptr)
	delete[] high;
	if (low != nullptr)
	delete[] low;
	if (close != nullptr)
	delete[] close;
	if (volume != nullptr)
	delete[] volume;
	if (adjusted != nullptr)
	delete[] adjusted;
}
class stock {
public:
	stock(string symbol);
	tm get_date();
	int length;
	void next_day();
	time_t operation_time;
	
private:
	int array_index;
	string symbol;
	quote content;
	const string url_base = "http://real-chart.finance.yahoo.com/table.csv?s=";
	vector<string> initialize();
	
};

vector<string> stock::initialize() {
	CURL *curl;
	CURLcode res;
	char buffer[2048];
	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	string final_url = url_base + this->symbol + "&g=d";
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, final_url.c_str());
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, &buffer);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		string readBuffer;
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);//stdout does not matter
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
			cout << buffer << endl;
			exit(EXIT_FAILURE);
		}
		/* always cleanup */
		curl_easy_cleanup(curl);
		curl_global_cleanup();
		istringstream f(readBuffer);
		vector<string> result;
		string line;
		getline(f, line);
		while (getline(f, line)) {
			if (line.empty())continue;
			result.push_back(line);
		}
		return result;
	}
	throw exception("Curl not initialized");
}
stock::stock(string symbol) {
	vector<string> lines;
	this->symbol = symbol;
	ifstream file_exists(this->symbol);
	if (file_exists.good()) {
		string line;
		while(!file_exists.eof()){
			getline(file_exists, line);
			if (line.empty())continue;
			lines.push_back(line);
		}
		file_exists.close();
	}else{
		file_exists.close();
		lines = initialize();
		ofstream outputFile(this->symbol);
		for (auto &i : lines) {
			outputFile << i <<endl;
		}
		outputFile.close();
	}
	content.date = new string[lines.size()];
	content.open = new double[lines.size()];
	content.high = new double[lines.size()];
	content.low = new double[lines.size()];
	content.close = new double[lines.size()];
	content.volume = new long[lines.size()];
	content.adjusted = new double[lines.size()];
	int b = 0;
	for (auto &i : lines) {
		if (i.empty())continue;
		std::istringstream ss(i);
		string temp;
		getline(ss, content.date[b], ',');
		getline(ss, temp, ',');
		content.open[b] = stod(temp);
		getline(ss, temp, ',');
		content.high[b] = stod(temp);
		getline(ss, temp, ',');
		content.low[b] = stod(temp);
		getline(ss, temp, ',');
		content.close[b] = stod(temp);
		getline(ss, temp, ',');
		content.volume[b] = stoi(temp);
		getline(ss, temp, ',');
		content.adjusted[b] = stod(temp);
		b++;
	}
	length = b;
	array_index = length - 1;
	tm time;
	
	time = string_to_date(content.date[length - 1]);
	operation_time = mktime(&time);
	if (operation_time == -1) {
		throw exception("Operation time is invalid");
	}
}
void stock::next_day() {
	operation_time += 86400;//adds a day
	tm temp;
	localtime_s(&temp, &operation_time);
	if (temp.tm_wday == 0) {
		operation_time += 86400;
	}//Skips weekends
	if (temp.tm_wday == 6) {
		operation_time += 86400 * 2;
	}
	if(array_index != 0){
		array_index--;
	}
	tm now = get_date();
	localtime_s(&temp, &operation_time);
	assert(now.tm_year == temp.tm_year);
	assert(now.tm_mon == temp.tm_mon);
	assert(now.tm_mday == temp.tm_mday);
}
tm stock::get_date() {
	return string_to_date(content.date[array_index]);
}