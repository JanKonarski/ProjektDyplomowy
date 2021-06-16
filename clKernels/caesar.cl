__kernel void caesar(__constant char *key, int keyN,
					 __global char *data, int dataN,
					 __global char *out) {
	int id = get_global_id(0);

	if (id < dataN)
		out[id] = (data[id] + key[0]) % 127;
}