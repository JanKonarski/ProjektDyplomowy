#include <iostream>
#include <vector>

#include "../include/oclencrypt.hpp"

int main(int argc, char **argv) {
	try {
		cl::Platform platform = ocle::selectPlatform();
		cl::Device device = ocle::selectDevice(&platform, CL_DEVICE_TYPE_ALL);

		ocle::ECB ecb(&platform, &device);

		std::vector<char> data = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!', '!', '!', '!', '!'};
		ecb.load(&data);
		ecb.setKey("abcdefghijklmnop");
		char *out = ecb.process();

		std::cout << out << std::endl;
	}
	catch(std::exception e) {
		std::cerr << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}