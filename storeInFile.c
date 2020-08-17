#include <stdio.h>
#include <string.h>
#include "pbc/pbc.h"
#include "gmp.h"
#include "gcrypt.h"
#include <time.h>

int main(void)
{
    /* call PBC functions */
    //printf("out");
		int numberOfv=10;
  pairing_t pairing;
	char param[1024];
	FILE *fp = fopen("a.param", "r");
	size_t count = fread(param, 1, 1024, fp);
	if (!count) pbc_die("input error");
	pairing_init_set_buf(pairing, param, count);

	FILE *read=fopen("zhangParam.txt", "w");
	element_t g,key, pi, gpub;
	element_init_G1(g, pairing);
	element_random(g);
	fprintf(read, "%s", "g = ");
	element_out_str(read, 16,g);

	element_init_G1(gpub, pairing);

	element_init_Zr(key, pairing);
	element_random(key);
	fprintf(read, "\n%s", "key = ");
	element_out_str(read, 16,key);

	element_init_Zr(pi, pairing);
	element_random(pi);
	fprintf(read, "\n%s", "pi = ");
	element_out_str(read, 16,pi);

	element_pow_zn(gpub, g, pi);
	fprintf(read, "\n%s", "gpub = ");
	element_out_str(read, 16,gpub);

	// Define hashes
	element_t H1,H2,H3;
	element_init_G1(H1, pairing);
	element_init_G1(H2, pairing);
	element_init_G1(H3, pairing);

	element_t H4,H5;
	element_init_Zr(H4,pairing);
	element_init_Zr(H5,pairing);

	printf("success\n");
	fclose(read);
	return 0;
}
