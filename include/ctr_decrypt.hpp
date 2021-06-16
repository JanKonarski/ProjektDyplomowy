#pragma once

#include "ctr.hpp"

namespace ocle {

	class CTR_DECRYPT : public CTR {

	protected:
		std::string clKernelFile = "../clKernels/ctr_decode.cl";
		std::string clKernelName = "ctr_decrypt";

	public:
		CTR_DECRYPT(cl::Platform *platform,
					cl::Device *device);
	
	protected:
		virtual void setBuffers() override;
	
	public:
		virtual char * process() override;

	};

}