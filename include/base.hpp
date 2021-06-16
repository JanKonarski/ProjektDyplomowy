#pragma once

#include <string>
#include <vector>

#define __CL_ENABLE_EXTENSIONS

#ifdef defined(__MACOSX__) || defined(APPLE)
	#include <OpenCL/cl.hpp>
#else
	#include <CL/cl.hpp>
#endif

namespace ocle {

	class Base {

	protected:
		cl::Platform *platform = nullptr;
		cl::Device *device = nullptr;
		cl::Context *context = nullptr;
		cl::CommandQueue *queue = nullptr;
		std::string *kernelSource = nullptr;
		cl::Program *program = nullptr;
		cl::Kernel *kernel = nullptr;
		cl::Buffer *bufferData = nullptr;
		cl::Buffer *bufferKey = nullptr;
		cl::Buffer *bufferOut = nullptr;

		bool own = false;
		std::vector<char> *data = nullptr;
		std::string *key = nullptr;

	public:
		Base(cl::Platform *platform,
			 cl::Device *device);
		~Base();

	protected:
		void buildKernel(std::string clKernelFile,
						 std::string name);

	public:
		virtual char * process() = 0;

	private:
		void loadData();

	public:
		void load(std::vector<char> *data);
		void load(std::string fileName);
		void setKey(std::string key);


	};

}