#include "../include/ctr.hpp"

ocle::CTR::CTR(cl::Platform *platform,
			   cl::Device *device) :
					Base(platform, device) {}

void ocle::CTR::setIV(std::vector<char> iv) {
	if (iv.size() != key->size())
		throw new std::runtime_error("Key and IV bit size error");
	
	this->iv = iv;

	setBuffers();
}