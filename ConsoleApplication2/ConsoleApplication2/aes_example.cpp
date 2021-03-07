#include <modes.h>
#include <aes.h>
#include <filters.h>

#include <iostream>
#include <string>
#include <immintrin.h>	// _rdrand32_step

#include "aes_example.h"


// size must be a 4 bytes align.
char* generate_key(char* buff, size_t size)
{
	for (size_t i = 0; i < size; i += 4)
		_rdrand32_step(reinterpret_cast<unsigned int*>(&buff[i]));
	return buff;
}

void aes_example()
{
	std::cout << "=== AES EXAMPLE ===" << std::endl;

	// Key and IV setup
	// AES encryption uses a secret key of  a variable length (128-bit, 196-bit or 256-bit).
	// This key is secretly exchanged between two parties before communication begins.
	//

	CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];

	memset(key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
	memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);

	generate_key(reinterpret_cast<char*>(key), CryptoPP::AES::DEFAULT_KEYLENGTH);

	std::string plaintext = "Hello from crypto++. Whatsapp?";
	std::string ciphertext;
	std::string decryptedtext;

	std::cout << "Plain text:" << std::endl;
	std::cout << plaintext << std::endl;

	// create cipher text
	CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);

	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length());
	stfEncryptor.MessageEnd();


	std::cout << "cipher text:" << std::endl;
	for (size_t i = 0; i < ciphertext.size(); i++)
	{
		std::cout << "0x" << std::hex << (0xFF & static_cast<CryptoPP::byte>(ciphertext[i])) << " ";
	}
	std::cout << std::endl << std::endl;


	// decrypt
	CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(ciphertext.c_str()), ciphertext.size());
	stfDecryptor.MessageEnd();

	std::cout << "decrypt test:" << std::endl;
	std::cout << decryptedtext;
	std::cout << std::endl;
}
