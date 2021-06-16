#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>

#define __CL_ENABLE_EXTENSIONS

#ifdef defined(__MACOSX__) || defined(APPLE)
	#include <OpenCL/cl.hpp>
#else
	#include <CL/cl.hpp>
#endif

namespace ocle {

	cl::Platform selectPlatform();
	cl::Device selectDevice(const cl::Platform *platform, cl_device_type type);

}

#endif // UTILS_HPP