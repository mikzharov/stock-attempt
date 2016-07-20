#include "population.h"
#include <stdio.h>
#include <string>
#include "stock.h"
#include <chrono>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <memory>
#include "gen_cont.h"
#include <algorithm>
#include "node.h"
#include <iostream>
#include <fstream>
#ifdef __APPLE__
	#include "OpenCL/opencl.h"//Probably won't use an apple device for this program, but why not
#else
	#include "CL/cl.h"
#endif
random_in_range c;

vector<float> adjusted;
vector<float> close;
vector<float> high;
vector<float> low;
vector<float> open;
vector<float> volume;
vector<int> index;

population::population(int size, int initial_worth, string stock1) {
	st.reset(new stock(stock1));
	this->size = size;
	for (int i = 0; i < size; i++) {
		pop.emplace_back(initial_worth, st.get());//This initializes the object in the vector
	}
}

population::~population() {
}

void population::next_day() {
	while (st->next_day()) {
		for (int i = 0; i < pop.size(); i++) {
			pop.at(i).evaluate();
			pop.at(i).update_fitness();
		}
	}
	st->reset();
	for (int i = 0; i < pop.size(); i++) {
		pop.at(i).reset();
	}
}

void population::simulate() {
	for (int i = 0; i < generations; i++) {
		cout << i << endl;
		next_day();

		std::sort(pop.begin(), pop.end());
		size_t size = pop.size();

		for (int i = 0; i < size * crossover_rate; i++) {
			node * to_crossover_with = (pop.at(c((int)(size - (int)((double)size * top_percent_to_crossover)), (int)size - 1)).n.get());
			pop.at(c((int)(size - (double)size * top_percent_to_crossover), (int)size - 1)).n->crossover(to_crossover_with);
		}

		for (int i = 0; i < size * mutation_rate; i++) {
			pop.at(c(0, (int)size - 1)).n->all_mutate();
		}
		//if (pop.at(pop.size() - 1).get_money() == 0 && pop.at(pop.size() - 1).get_stock_owned() == 0) break;
	}
	ofstream myfile;
	myfile.open("NODE.txt");
	myfile << pop.at(pop.size()-1).n.get();
	myfile.close();
	cout << "Stock day: " << st->day_since_start << endl;
	cout << pop.at(pop.size() - 1).n.get() << endl;
	cout << "Money: " << pop.at(pop.size() - 1).get_money() << endl;
	cout << "Stock: " << pop.at(pop.size() - 1).get_stock_owned() << endl;

	cout << "Money 1: " << pop.at(0).get_money() << endl;
	cout << "Stock 1: " << pop.at(0).get_stock_owned() << endl;
}

void population::init_opencl() {
	cl_uint platform_id_count = 0;//cl unsigned int used only for OpenCL
	clGetPlatformIDs(0, nullptr, &platform_id_count);//Gets the amount of platforms available on this computer, stores it in platform id count

	std::vector<cl_platform_id> platform_ids(platform_id_count);//Makes a vector to store the different platforms
	clGetPlatformIDs(platform_id_count, platform_ids.data(), nullptr);//Fetches the different platforms into the vector

	cl_uint device_id_count = 0;//The amount of devices on the first platform
	clGetDeviceIDs(platform_ids[0], CL_DEVICE_TYPE_ALL, 0, nullptr,&device_id_count);//Gets the amount of devices on the first platform
	std::vector<cl_device_id> device_ids(device_id_count);//Makes a vector to store the devices
	clGetDeviceIDs(platform_ids[0], CL_DEVICE_TYPE_ALL, device_id_count, device_ids.data(), nullptr);//Puts the devices in the vectors

	const cl_context_properties context_properties[] =//An array to store the properties of the context that will be used
	{
		CL_CONTEXT_PLATFORM,//Some enum that must be present
		reinterpret_cast<cl_context_properties> (platform_ids[0]),//The platform id for the context
		0, 
		0,//Must end with 0
	};
	cl_int error = 0;//The variable that error codes will be stored in
	cl_context context = clCreateContext(//Creates a context to use for opencl
		context_properties,//Properties
		device_id_count,//Number of devices
		device_ids.data(),//Devices
		nullptr,//Callback
		nullptr,//user_data (used in the callback)
		&error);//The error variable pointer
	cl_error(error, "clCreateContext");//Not an OpenCl call, defined in population.h, checks if error == CL_SUCCESS

	size_t size = st->content[st->symbol_index_int].data.size();//Copies all stock data into neat arrays
	for (size_t i = 0; i < size; i++) {
		adjusted.push_back((float)st->content[st->symbol_index_int].data.at(0).adjusted);
	}
	for (size_t i = 0; i < size; i++) {
		close.push_back((float)st->content[st->symbol_index_int].data.at(0).close);
	}
	for (size_t i = 0; i < size; i++) {
		high.push_back((float)st->content[st->symbol_index_int].data.at(0).high);
	}
	for (size_t i = 0; i < size; i++) {
		low.push_back((float)st->content[st->symbol_index_int].data.at(0).low);
	}
	for (size_t i = 0; i < size; i++) {
		open.push_back((float)st->content[st->symbol_index_int].data.at(0).open);
	}
	for (size_t i = 0; i < size; i++) {
		volume.push_back((float)st->content[st->symbol_index_int].data.at(0).volume);
	}
	for (size_t i = 0; i < size; i++) {
		volume.push_back((float)st->content[st->symbol_index_int].data.at(0).volume);
	}
	for (size_t i = 0; i < size; i++) {
		index.push_back((int)i);
	}

	cl_mem adjusted_buf = clCreateBuffer(context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,//Will only read from adjusted array, will copy adjusted array to GPU
		sizeof(float) * (adjusted.size()),//Size of adjusted array
		adjusted.data(),//The pointer to the data
		&error);//Error code
	cl_error(error, "adjusted buf");

	cl_mem close_buf = clCreateBuffer(context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,//Will only read from adjusted array, will copy adjusted array to GPU
		sizeof(float) * (close.size()),//Size of adjusted array
		close.data(),//The pointer to the data
		&error);//Error code
	cl_error(error, "close buf");

	cl_mem high_buf = clCreateBuffer(context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,//Will only read from adjusted array, will copy adjusted array to GPU
		sizeof(float) * (high.size()),//Size of adjusted array
		high.data(),//The pointer to the data
		&error);//Error code
	cl_error(error, "high buf");

	cl_mem low_buf = clCreateBuffer(context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,//Will only read from adjusted array, will copy adjusted array to GPU
		sizeof(float) * (low.size()),//Size of adjusted array
		low.data(),//The pointer to the data
		&error);//Error code
	cl_error(error, "low buf");

	cl_mem open_buf = clCreateBuffer(context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,//Will only read from adjusted array, will copy adjusted array to GPU
		sizeof(float) * (open.size()),//Size of adjusted array
		open.data(),//The pointer to the data
		&error);//Error code
	cl_error(error, "open buf");

	cl_mem volume_buf = clCreateBuffer(context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,//Will only read from adjusted array, will copy adjusted array to GPU
		sizeof(float) * (volume.size()),//Size of adjusted array
		volume.data(),//The pointer to the data
		&error);//Error code
	cl_error(error, "volume buf");

	cl_mem index_buf = clCreateBuffer(context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,//Will only read from adjusted array, will copy adjusted array to GPU
		sizeof(int) * (index.size()),//Size of adjusted array
		index.data(),//The pointer to the data
		&error);//Error code
	cl_error(error, "index buf");
}
