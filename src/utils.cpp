#include "../include/utils.hpp"

cl::Platform
ocle::selectPlatform()
{
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);

	if(platforms.size() == 0)
		throw new std::runtime_error("No available OpenCL platforms");
		
	if(platforms.size() == 1)
		return platforms[0];

	else {
		std::cout << "Available OpenCL platforms:" << std::endl;
		std::size_t i = 1;
		for(auto platform : platforms)
			std::cout << "\t" << i++ << ". " << platform.getInfo<CL_PLATFORM_NAME>() << std::endl;

		std::size_t idx = SIZE_MAX;
		while(idx > platforms.size()) {
			std::cout << "Select platform index: ";
			std::cin >> idx;
		}

		return platforms[idx - 1];
	}

	throw new std::runtime_error("Unknown error");
}

cl::Device
ocle::selectDevice(const cl::Platform *platform,
				   cl_device_type type)
{
	std::vector<cl::Device> devices;
	platform->getDevices(type, &devices);

	if(devices.size() == 0)
		throw new std::runtime_error("No available OpenCL devices");

	if(devices.size() == 1)
		return devices[0];

	else {
		std::cout << "Available OpenCL devices:" << std::endl;
		std::size_t i = 1;
		for(auto device : devices)
			std::cout << "\t" << i++ << ". " << device.getInfo<CL_DEVICE_NAME>() << std::endl;

		std::size_t idx = SIZE_MAX;
		while(idx > devices.size()) {
			std::cout << "Select device index: ";
			std::cin >> idx;
		}

		return devices[idx - 1];
	}

	throw new std::runtime_error("Unknown error");
}