#pragma once

#include "base.hpp"

namespace ocle {

	class CTR : public Base {

	protected:
		std::vector<char> iv;

	protected:
		cl::Buffer *bufferIV = nullptr;

	public:
		CTR(cl::Platform *platform,
			cl::Device *device);
		
	public:
		void setIV(std::vector<char> iv);

	protected:
		virtual void setBuffers() = 0;

	};

}