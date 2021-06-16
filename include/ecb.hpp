#pragma once

#include "base.hpp"

namespace ocle {

	class ECB : public Base {

	private:
		std::string clKernelFile = "../clKernels/ecb.cl";
		std::string clKernelName = "ecb";
	
	public:
		ECB(cl::Platform *platform,
			cl::Device *device);
		
	public:
		virtual char * process() override;

	};

}