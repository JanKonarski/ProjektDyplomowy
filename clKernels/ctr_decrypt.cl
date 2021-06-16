__kernel void crt_decrypt(__constant char *key, int keyN,
						  __constant char *iv, int ivN,
						  __global char *data, int dataN,
						  __global char *out)
{
	int id = get_global_id(0);

	int start = id * keyN;
	int stop = (id + 1) * keyN + 1;

	if (start < dataN && stop < dataN) {
		for (int i=start; i<=stop; i++) {
			char tmp = data[i] ^ key[i];
            out[i] = tmp ^ iv[i];
		}
	}
}