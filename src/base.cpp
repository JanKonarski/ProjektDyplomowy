#include <iostream>
#include <fstream>

#include "../include/base.hpp"

#define BUFFER_SIZE 1024

ocle::Base::Base(cl::Platform *platform,
				 cl::Device *device) :
	platform(platform),
	device(device)
{
	context = new cl::Context({*device});
	queue = new cl::CommandQueue(*context, *device);
}

ocle::Base::~Base()
{
	delete context;
	delete queue;
	delete kernelSource;
	delete program;
	delete kernel;
	delete bufferKey;
	delete bufferData;

//	delete key;
	if (own)
		delete data;
}

void ocle::Base::buildKernel(std::string clKernelFile,
							 std::string name)
{
	kernelSource = new std::string();

	std::ifstream file(clKernelFile);
	if(!file)
		throw new std::runtime_error("Not OpenCL kernel file");

	// Load kernel file
	while(!file.eof()) {
		char buffer[BUFFER_SIZE];
		file.getline(buffer, BUFFER_SIZE - 1);
		*kernelSource += buffer;
	}

	program = new cl::Program(*context, *kernelSource);
	program->build({*device});

	kernel = new cl::Kernel(*program, name.c_str());
}

void ocle::Base::loadData() {
	bufferData = new cl::Buffer(*context,
								CL_MEM_READ_ONLY,
								data->size() * sizeof(char));
}

void ocle::Base::load(std::vector<char> *data) {
	own = false;
	this->data = data;
	loadData();
}

void ocle::Base::load(std::string fileName) {
	std::ifstream file(fileName, std::ios::binary);
	if (!file)
		throw new std::runtime_error("Data file error");

	own = true;
	data = new std::vector<char>();

	while (!file.eof())
		data->push_back(file.get());
	
	loadData();
}

void ocle::Base::setKey(std::string key) {
	if (data == nullptr)
		throw new std::runtime_error("Data not set");

	if (data->size() % key.size() != 0)
		throw new std::runtime_error("Data and key bit size error");

	this->key = &key;

	bufferKey = new cl::Buffer(*context,
							   CL_MEM_READ_ONLY,
							   this->key->size() * sizeof(char));
}