// For AES128 in ECB mode, the size of the data to be encrypted must be a multiple of 128 bits. The plaintext and ciphertext sizes must be precisely the same.
//
// Here's working code to give you an idea of what you need to do to make it work. But I'd strongly suggest you rethink using ECB.

#include <gcrypt.h>
#include "iostream"
#include <vector>
#include <stdio.h>
// #include <stdlib.h>
#include <stddef.h>


class aes
{
public:
    aes(std::string);
    ~aes() { ; }

    gcry_cipher_hd_t handle;
    void encrypt(std::string, std::vector<char>&);
    std::string decrypt(std::vector<char> const&);

private:
    std::string key_;
    size_t keyLength_;
};

#define GCRY_CIPHER GCRY_CIPHER_AES128
#define GCRY_MODE GCRY_CIPHER_MODE_ECB

aes::aes(std::string k)
{
    key_ = k;
    keyLength_ = gcry_cipher_get_algo_keylen(GCRY_CIPHER);

    gcry_control (GCRYCTL_DISABLE_SECMEM, 0);
    gcry_control (GCRYCTL_INITIALIZATION_FINISHED, 0);
    gcry_cipher_open(&handle, GCRY_CIPHER, GCRY_MODE, 0);
    gcry_cipher_setkey(handle, key_.c_str(), keyLength_);
}

void aes::encrypt(std::string text, std::vector<char>& ret)
{

    // round up to the nearest multiple of the AES block size
    while ((text.size() & 0xf) != 0xf)
        text += " ";

    size_t textLength = text.size() + 1;
    ret.resize(textLength);
    int err = gcry_cipher_encrypt(handle, ret.data(), textLength, text.c_str(), textLength);
    if (err != 0)
    {
       std::cout << "encrypt fail" <<
           gcry_strsource(err) << " " <<
           gcry_strerror(err) << std::endl;
    }
}

std::string aes::decrypt(std::vector<char> const& text) {
    size_t textLength = text.size();

    char * decBuffer = new char[textLength];

    int err=gcry_cipher_decrypt(handle, decBuffer, textLength, text.data(), textLength);
    if (err != 0)
    {
       std::cout << "decrypt fail: " <<
           gcry_strsource(err) <<  " " <<
           gcry_strerror(err) << std::endl;
     }

    std::string ret (decBuffer);
    delete [] decBuffer;
    return ret;
}

int main()
{
    std::vector<char> data;

    aes bb = aes("one test AES key");
    bb.encrypt("Some message", data);

    std::string dec = bb.decrypt(data);
    std::cout << "decrypted string " << dec << std::endl;

	// 	std::string s(data.begin(), data.end());
	// std::cout << s;
    return 0;
}
