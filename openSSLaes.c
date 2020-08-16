// this is openssl example of AES cryptography.
// To run > gcc openSSLaes.c -lssl -lcrypto

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

// static void
 char* hex_print(const void* pv, size_t len)
{
	const unsigned char * p = (const unsigned char*)pv;
	const unsigned char *retMsg=malloc(sizeof(const unsigned char)*len);
	char hex[5];
	if (NULL == pv)
	    printf("NULL");
	else
	{
	    FILE *fptr = fopen("opensslAES.txt", "w");
			if (fptr == NULL)
			{
					printf("Could not open file");
					return "failed";
			}
			for (int i = 0; i < len; i++)
						fprintf(fptr,"%02x", *p++);
			fclose(fptr);
			FILE *fread = fopen("opensslAES.txt", "r");
			char *digest= malloc(sizeof(char)*len);
			fgets (digest, len, fread);
			// printf("digest 1: %s\n",digest );
			fclose(fread);
			return digest;
	}
	// printf("\n");
}

// main entrypoint
int main(int argc, char **argv)
{
    int keylength=128; //Give a key length [only 128 or 192 or 256!

    /* generate a key with a given length */
    unsigned char aes_key[keylength/8];
    memset(aes_key, 0, keylength/8);
    if (!RAND_bytes(aes_key, keylength/8))
        exit(-1);

    char plaintext[]="Give a key length [only 128 or 192 or 256!";

    /* init vector */
    unsigned char iv_enc[AES_BLOCK_SIZE], iv_dec[AES_BLOCK_SIZE];
    RAND_bytes(iv_enc, AES_BLOCK_SIZE);
    memcpy(iv_dec, iv_enc, AES_BLOCK_SIZE);

    // buffers for encryption and decryption
		int inputslength=strlen(plaintext);
    const size_t encslength = ((inputslength + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char enc_out[encslength];
    unsigned char dec_out[inputslength];
    memset(enc_out, 0, sizeof(enc_out));
    memset(dec_out, 0, sizeof(dec_out));

    AES_KEY enc_key, dec_key;
    AES_set_encrypt_key(aes_key, keylength, &enc_key);
    AES_cbc_encrypt(plaintext, enc_out, inputslength, &enc_key, iv_enc, AES_ENCRYPT);

    AES_set_decrypt_key(aes_key, keylength, &dec_key);
    AES_cbc_encrypt(enc_out, dec_out, encslength, &dec_key, iv_dec, AES_DECRYPT);

		char *msg;
    msg=hex_print((unsigned char *)plaintext, strlen(plaintext));
		printf("plaintext : %s\n", msg);

    msg=hex_print(enc_out, sizeof(enc_out));
		printf("encrypt : %s\n", msg);

    msg=hex_print(dec_out, sizeof(dec_out));
		printf("decrypt:\t%s\n",msg);

    return 0;
}
