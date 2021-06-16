__kernel void ecb(__constant char *key, int keyN,
				  __global char *data, int dataN,
				  __global char *out)
{
	int id = get_global_id(0);

	int start = id * keyN;
	int stop = (id + 1) * keyN - 1;

	if (stop < dataN)
		for (int i=0; i<keyN; i++)
			out[start+i] = (data[start+i] ^ key[start+i]);
}