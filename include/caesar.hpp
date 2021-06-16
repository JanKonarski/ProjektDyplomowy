#pragma once

#include "base.hpp"

namespace ocle {

	class Caesar : public Base {

	private:
		std::string clKernelFile = "../clKernels/caesar.cl";
		std::string clKernelName = "caesar";

	public:
		Caesar(cl::Platform *platform,
			   cl::Device *device);

	public:
		virtual char * process() override;

	};

}