#include "../include/ctr_decrypt.hpp"

ocle::CTR_DECRYPT::CTR_DECRYPT(cl::Platform *platform,
							   cl::Device *device) :
	CTR(platform, device)
{
	buildKernel(clKernelFile, clKernelName);
}

void ocle::CTR_DECRYPT::setBuffers() {
	if (iv.size() == 0)
		throw new std::runtime_error("Initial vector empty");

	if (iv.size() != key->size())
		throw new std::runtime_error("Key and IV bit size error");

	bufferIV = new cl::Buffer(*context,
								CL_MEM_READ_ONLY,
								iv.size() * sizeof(char));
}

char * ocle::CTR_DECRYPT::process() {
	char *out = new char[data->size() + 1];

	bufferOut = new cl::Buffer(*context,
							   CL_MEM_WRITE_ONLY,
							   data->size() * sizeof(char));

	queue->enqueueWriteBuffer(*bufferData,
							  true,
							  0,
							  data->size() * sizeof(char),
							  (void*)data->data());

	queue->enqueueWriteBuffer(*bufferKey,
							  true,
							  0,
							  key->size() * sizeof(char),
							  (void*)key->c_str());

	queue->enqueueWriteBuffer(*bufferIV,
							  true,
							  0,
							  iv.size() * sizeof(char),
							  (void*)iv.data());

	queue->enqueueWriteBuffer(*bufferOut,
							  true,
							  0,
							  data->size() * sizeof(char),
							  (void*)out);

	int keyN = key->size();
	int saltN = iv.size();
	int dataN = data->size();

	kernel->setArg(0, *bufferKey);
	kernel->setArg(1, sizeof(int), &keyN);
	kernel->setArg(2, *bufferIV);
	kernel->setArg(3, sizeof(int), &saltN);
	kernel->setArg(4, *bufferData);
	kernel->setArg(5, sizeof(int), &dataN);
	kernel->setArg(6, *bufferOut);

	cl::Event event;

	queue->enqueueNDRangeKernel(*kernel,
								cl::NullRange,
								cl::NDRange(data->size()/key->size(), 1),
								cl::NullRange,
								NULL,
								&event);
	
	queue->enqueueReadBuffer(*bufferOut,
							 true,
							 0,
							 data->size() * sizeof(char),
							 (void*)out);
	
	out[data->size()] = '\0';

	return out;
}