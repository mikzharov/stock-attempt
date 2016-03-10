#include "genetic.h"
#include <iostream>
#include <cstdlib>
#include <random>
#include <stdio.h>
#include <string>
#include "stock.h"
#include <chrono>
#include <iostream>
#include <sstream>
#include <assert.h>

random_in_range r;
bool is_double(const char* str) {
	char* endptr = 0;
	strtod(str, &endptr);

	if (*endptr != '\0' || endptr == str)
		return false;
	return true;
}
node::node(int depth) {
	this->depth = depth;
	if (depth > 0) {

	}
}

void descriptor_container::add_descriptor(node::action, int) {

}
