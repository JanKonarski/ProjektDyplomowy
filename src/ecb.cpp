#include "../include/ecb.hpp"
#include <iostream>

ocle::ECB::ECB(cl::Platform *platform,
               cl::Device *device) :
        Base(platform, device)
{
    buildKernel(clKernelFile, clKernelName);
}

char * ocle::ECB::process() {
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

	queue->enqueueWriteBuffer(*bufferOut,
							  true,
							  0,
							  data->size() * sizeof(char),
							  (void*)out);
	
	int keyN = key->size();
	int dataN = data->size();

	kernel->setArg(0, *bufferKey);
	kernel->setArg(1, sizeof(int), &keyN);
	kernel->setArg(2, *bufferData);
	kernel->setArg(3, sizeof(int), &dataN);
	kernel->setArg(4, *bufferOut);

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