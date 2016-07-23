
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

#include <chrono>
#include <thread>
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
vector<float> results_v;
population::population(int size, int initial_worth, string stock1) {
	st.reset(new stock(stock1));
	this->size = size;
	for (int i = 0; i < size; i++) {
		pop.emplace_back(initial_worth, st.get());//This initializes the object in the vector
	}
}

population::~population() {
}

cl_int error;
cl_context context;
cl_uint platform_id_count;
cl_platform_id platform_ids[100];
cl_uint device_id_count;
cl_device_id device_ids[100];

cl_mem adjusted_buf;
cl_mem close_buf;
cl_mem high_buf;
cl_mem low_buf;
cl_mem open_buf;
cl_mem volume_buf;
cl_mem result_buf;

void population::next_day() {
	for (size_t i = 0; i < pop.size(); i++) {
		string s_src = pop.at(i).compile();
		//string s_src = "__kernel void GENINDIV (__global float* adjusted_buf, __global float* close_buf, __global float* high_buf, __global float* low_buf, __global float* open_buf, __global float* volume_buf, __global float* result, int buf_size){result[get_global_id(0)]=close_buf[get_global_id(0)];}";
		const char * src = s_src.c_str();
		cl_program pr = clCreateProgramWithSource(
			context,//OpenCL context
			1,//Number of strings
			&src,//Source
			nullptr,//Indicated that the string is null terminated
			&error);
		cl_error(error, "making cl_program");
		error = clBuildProgram(
			pr,//Program
			device_id_count,//Device info
			device_ids,
			nullptr,
			nullptr,//Callback info and options
			nullptr);
		/*char buffer[10000];
		size_t length = 0;
		clGetProgramBuildInfo(
			pr,
			device_ids[0],
			CL_PROGRAM_BUILD_LOG,
			sizeof(buffer),
			&buffer,
			&length);
		cout << buffer;*/
		cl_error(error, "building cl_program");
		cl_kernel kernel = clCreateKernel(pr, "GENINDIV", &error);
		cl_error(error, "making kernel");
		error = clSetKernelArg(kernel, 0, sizeof(cl_mem), &adjusted_buf);
		cl_error(error, "arg1");
		error = clSetKernelArg(kernel, 1, sizeof(cl_mem), &close_buf);
		cl_error(error, "arg2");
		error = clSetKernelArg(kernel, 2, sizeof(cl_mem), &high_buf);
		cl_error(error, "arg3");
		error = clSetKernelArg(kernel, 3, sizeof(cl_mem), &low_buf);//Binds buffer to method call
		cl_error(error, "arg4");
		error = clSetKernelArg(kernel, 4, sizeof(cl_mem), &open_buf);
		cl_error(error, "arg5");
		error = clSetKernelArg(kernel, 5, sizeof(cl_mem), &volume_buf);
		cl_error(error, "arg6");
		error = clSetKernelArg(kernel, 6, sizeof(cl_mem), &result_buf);
		cl_error(error, "arg7");
		static const int buf_size = (int)volume.size();
		error = clSetKernelArg(kernel, 7, sizeof(int), &buf_size);
		cl_error(error, "arg8");
		cl_command_queue cmd = clCreateCommandQueue(
			context,
			device_ids[0],
			CL_QUEUE_PROFILING_ENABLE,
			&error);
		cl_error(error, "making command queue");
		const size_t globalWorkSize[] = { (size_t)buf_size };
		const size_t localWorkSize[] = { (size_t)1 };
		cl_event finish;
		error = clEnqueueNDRangeKernel(
			cmd,
			kernel,
			1, // One dimension
			nullptr, // Offset
			globalWorkSize,
			nullptr,
			0, 
			nullptr, 
			&finish);

		cl_error(error, "clEnqueueNDRangeKernel");
		//float * result = (float *)malloc(volume.size() * sizeof(float));
		float * result = (float *) clEnqueueMapBuffer(cmd,
			result_buf,
			CL_TRUE,
			CL_MAP_READ,
			0,
			sizeof(float) * volume.size(),
			1,
			&finish,
			nullptr,
			&error);

		cl_error(error, "cl enquerange kernel");

		pop.at(i).evaluate(result, buf_size);

		error = clFlush(cmd);
		cl_error(error, "clflush cmd");
		error = clFinish(cmd);
		cl_error(error, "clfinish cmd");
		error = clReleaseKernel(kernel);
		cl_error(error, "release kernel");
		error = clReleaseProgram(pr);
		cl_error(error, "release program");
		error = clReleaseCommandQueue(cmd);
		cl_error(error, "release cmd");
		cout << i << endl;
	}
}

void population::simulate() {
	init_opencl(&cout);
	for (int i = 0; i < generations; i++) {
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

void population::init_opencl(ostream * log) {
	platform_id_count = 0;//cl unsigned int used only for OpenCL
	error = clGetPlatformIDs(100, platform_ids, &platform_id_count);//Fetches the different platforms into the vector
	cl_error(error, "clgetplatformids");
	if (log != nullptr) *log << "Getting platforms" << endl;
	device_id_count = 0;//The amount of devices on the first platform
	clGetDeviceIDs(platform_ids[0], CL_DEVICE_TYPE_GPU, 100, device_ids, &device_id_count);//Puts the devices in the vectors
	if (log != nullptr) *log << "Getting devices on first platform: " << device_id_count << endl;
	error = 0;//The variable that error codes will be stored in
	const cl_context_properties context_properties[] =//An array to store the properties of the context that will be used
	{
		CL_CONTEXT_PLATFORM,//Some enum that must be present
		reinterpret_cast<cl_context_properties> (platform_ids[0]),//The platform id for the context
		0,
		0,//Must end with 0
	};
	context = clCreateContext(//Creates a context to use for opencl
		context_properties,//Properties
		device_id_count,//Number of devices
		device_ids,//Devices
		nullptr,//Callback
		nullptr,//user_data (used in the callback)
		&error);//The error variable pointer
	cl_error(error, "clCreateContext");//Not an OpenCl call, defined in population.h, checks if error == CL_SUCCESS
	if (log != nullptr) *log << "Created context" << endl;
	size_t size = st->content[st->symbol_index_int].data.size();//Copies all stock data into neat arrays
	for (size_t i = 0; i < size; i++) {
		adjusted.push_back((float)st->content[st->symbol_index_int].data.at(i).adjusted);
	}
	for (size_t i = 0; i < size; i++) {
		close.push_back((float)st->content[st->symbol_index_int].data.at(i).close);
	}
	for (size_t i = 0; i < size; i++) {
		high.push_back((float)st->content[st->symbol_index_int].data.at(i).high);
	}
	for (size_t i = 0; i < size; i++) {
		low.push_back((float)st->content[st->symbol_index_int].data.at(i).low);
	}
	for (size_t i = 0; i < size; i++) {
		open.push_back((float)st->content[st->symbol_index_int].data.at(i).open);
	}
	for (size_t i = 0; i < size; i++) {
		volume.push_back((float)st->content[st->symbol_index_int].data.at(i).volume);
	}
	results_v.resize(volume.size());
	if (log != nullptr) *log << "Got arrays from stock data" << endl;
	adjusted_buf = clCreateBuffer(context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,//Will only read from array, will copy adjusted array to GPU
		sizeof(float) * (adjusted.size()),//Size of array
		adjusted.data(),//The pointer to the data
		&error);//Error code
	cl_error(error, "adjusted buf");

	close_buf = clCreateBuffer(context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,//Will only read from array, will copy adjusted array to GPU
		sizeof(float) * (close.size()),//Size of array
		close.data(),//The pointer to the data
		&error);//Error code
	cl_error(error, "close buf");

	high_buf = clCreateBuffer(context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,//Will only read from array, will copy adjusted array to GPU
		sizeof(float) * (high.size()),//Size of array
		high.data(),//The pointer to the data
		&error);//Error code
	cl_error(error, "high buf");

	low_buf = clCreateBuffer(context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,//Will only read from array, will copy adjusted array to GPU
		sizeof(float) * (low.size()),//Size of array
		low.data(),//The pointer to the data
		&error);//Error code
	cl_error(error, "low buf");

	open_buf = clCreateBuffer(context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,//Will only read from array, will copy adjusted array to GPU
		sizeof(float) * (open.size()),//Size of array
		open.data(),//The pointer to the data
		&error);//Error code
	cl_error(error, "open buf");

	volume_buf = clCreateBuffer(context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,//Will only read from array, will copy adjusted array to GPU
		sizeof(float) * (volume.size()),//Size of array
		volume.data(),//The pointer to the data
		&error);//Error code
	cl_error(error, "volume buf");

	result_buf = clCreateBuffer(context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,//Will only WRITE to array, will copy adjusted array to GPU
		sizeof(float) * (volume.size()),//Size of array
		results_v.data(),//The pointer to the data
		&error);//Error code   //Uses the size of volume
	cl_error(error, "result buf");
	if (log != nullptr) *log << "Allocated and copied arrays to OpenCL device" << endl;
}
