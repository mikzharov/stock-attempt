#include "stdafx.h"
#include <stdio.h>
#include "stock.h"
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
vector<quote> stock::content;
vector<string> stock::symbol_index;
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
	get_values(symbol);
}
void stock::get_values(string symbol) {
	if (symbol.empty()) throw exception("No empty symbols");
	for (unsigned int i = 0; i < symbol_index.size(); i++) {
		if (symbol == symbol_index[i]) {
			symbol_index_int = i;
			length = content[i].date.size();
			array_index = content[i].date.size() - 1;
			this->symbol = symbol;
			return;
		}
	}
	vector<string> lines;
	this->symbol = symbol;
	ifstream file_exists(this->symbol);
	if (file_exists.good()) {
		string line;
		while (!file_exists.eof()) {
			getline(file_exists, line);
			if (line.empty())continue;
			lines.push_back(line);
		}
		file_exists.close();
	} else {
		file_exists.close();
		lines = initialize();
		ofstream outputFile(this->symbol);
		for (auto &i : lines) {
			outputFile << i << endl;
		}
		outputFile.close();
	}
	int lines_ = lines.size() + 2;
	quote content_;
	int b = 0;
	for (auto &i : lines) {
		if (i.empty())continue;
		std::istringstream ss(i);
		string temp;

		getline(ss, content_.date[b], ',');
		getline(ss, temp, ',');
		content_.open.push_back(stod(temp));
		getline(ss, temp, ',');
		content_.high.push_back(stod(temp));
		getline(ss, temp, ',');
		content_.low.push_back(stod(temp));
		getline(ss, temp, ',');
		content_.close.push_back(stod(temp));
		getline(ss, temp, ',');
		content_.volume.push_back(stoi(temp));
		getline(ss, temp, ',');
		content_.adjusted.push_back(stod(temp));
		b++;
	}
	symbol_index_int = content.size();
	content.push_back(content_);
	symbol_index.push_back(symbol);
	length = b;
	array_index = length - 1;
}
bool stock::next_day() {

	if(array_index != 0){
		array_index--;
		return true;
	}
	return false;
}
