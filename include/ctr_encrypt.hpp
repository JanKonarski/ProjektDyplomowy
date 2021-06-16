#pragma once

#include "ctr.hpp"

namespace ocle {

	class CTR_ENCRYPT : public CTR {
	
	protected:
		std::string clKernelFile = "../clKernels/ctr_encrypt.cl";
		std::string clKernelName = "ctr_encrypt";

	public:
		CTR_ENCRYPT(cl::Platform *platform,
					cl::Device *device);
		
	protected:
		virtual void setBuffers() override;
	
	public:
		virtual char * process() override;

	};

}