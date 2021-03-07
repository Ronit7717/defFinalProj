
#include "pch.h"
#include <modes.h>
#include <aes.h>
#include <filters.h>
#include "pch.h"
#include <iostream>
#include <string>
#include <immintrin.h>	// _rdrand32_step

#include "aes_crypto.h"

class Aes_crypto{
	private:
		char key[];
	public:
		Aes_crypto() {
			this->key = "ronit";
		}
};

void aes_crypto() {

}