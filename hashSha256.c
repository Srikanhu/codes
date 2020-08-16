
#include <stdio.h>
#include <string.h>
#include "pbc/pbc.h"
#include "gmp.h"
#include "gcrypt.h"

const char* sha256(char * msg){
	unsigned char* x;
	unsigned i;
	unsigned int l = gcry_md_get_algo_dlen(GCRY_MD_SHA256); /* get digest length (used later to print the result) */
	// printf("\nL value %d\n",l );
	gcry_md_hd_t h;
	gcry_md_open(&h, GCRY_MD_SHA256, GCRY_MD_FLAG_SECURE); /* initialise the hash context */
	gcry_md_write(h, msg, strlen(msg)); /* hash some text */
	x = gcry_md_read(h, GCRY_MD_SHA256); /* get the result */
	FILE *fptr = fopen("hashInLibgcrypt.txt", "w");
	if (fptr == NULL)
	{
			printf("Could not open file");
			return "failed";
	}
	for (i = 0; i < l; i++)
				fprintf(fptr,"%x", x[i]);

	int length = strlen((char*)x);
	// printf("length %d\n",length );

	fclose(fptr);
	FILE *fread = fopen("hashInLibgcrypt.txt", "r");

	char *digest= malloc(sizeof(char)*100);
	// char *digest= malloc(sizeof(char)*strlen(x));
	fgets (digest, 100, fread);
	// digest = gcryptOutput(x);
	printf("digest 1: %s\n",digest );
	// printf("\n Rop %d %s\n",i, rop );
	fclose(fread);
	return digest;
}



int main(){
	char *msg ="Hello world world ", *digest;

	digest=(char*)sha256(msg);
	printf("Digest %s\n", digest);

	printf("Success\n");
	return 0;
}
