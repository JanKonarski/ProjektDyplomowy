
#include <bitset>

#include "../include/oclencrypt.hpp"


int main(int argc, char **argv) {
	cl::Platform platform = ocle::selectPlatform();
	cl::Device device = ocle::selectDevice(&platform, CL_DEVICE_TYPE_ALL);

	std::vector<char> data = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!', '!', '!', '!', '!'};
//	std::vector<char> data = {
//		0b01001000, 0b01100101, 0b01101100, 0b01101100,
//		0b01101111, 0b00100000, 0b01110111, 0b01101111,
//		0b01110010, 0b01101100, 0b01100100, 0b00100001,
//		0b00100001, 0b00100001, 0b00100001, 0b00100001
//	};
	std::vector<char> iv = {0x54, 0x0F, 0x7A, 0x1C, 0x43, 0x6D, 0x71, 0x5B};
	std::string key = "abcdefgh";

	ocle::CTR_ENCRYPT ctr(&platform, &device);
	ctr.load(&data);
	ctr.setKey(key);
	ctr.setIV(iv);

	char *out = ctr.process();

	std::cout << out << std::endl;

	return EXIT_SUCCESS;
}