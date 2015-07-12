#include "genetic.h"
#include <iostream>
#include <cstdlib>
#include <random>

int random_in_range(int min, int max) {
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

	return uni(rng);

}
node * return_rand_func(int level, int arity = -1) {
	switch(arity){
	case -1:
		int decision = random_in_range(0, 1);
		if (decision == 0) {
			return new multiply(level);
		} else if (decision == 1) {
			return new value();
		}
	case 0:
		return new value();
	case 2:
		return new multiply(level);
	}
	throw std::exception("No arity");
}
double multiply::execute() {
	return (*right).execute() + (*left).execute();
}
multiply::multiply(int level) {
	left = return_rand_func(level - 1);
	right = return_rand_func(level - 1);
}
multiply::~multiply() {
	delete right;
	delete left;
}
double value::execute() {
	return content;
}
value::value() {
	double lower_bound = 0;
	double upper_bound = 10000;
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::default_random_engine re;
	content = unif(re);
}