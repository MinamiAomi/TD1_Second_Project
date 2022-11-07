#pragma once
#include <time.h>
#include <stdlib.h>

namespace Func {

	unsigned int HSVAToRGBA(float h, float s, float v, unsigned char alpha);

	template<class TYPE>
	void SafeDelete(TYPE*& ptr) {
		//  不完全な型のポインタをdeleteしようとした時にコンパイルエラーにする
		typedef char type_must_be_complete[sizeof(TYPE) ? 1 : -1];
		(void)sizeof(type_must_be_complete);

		delete ptr;
		ptr = nullptr;
	}

	template<class TYPE>
	void SafeDeleteArray(TYPE*& arrayptr) {
		//  不完全な型のポインタをdeleteしようとした時にコンパイルエラーにする
		typedef char type_must_be_complete[sizeof(TYPE) ? 1 : -1];
		(void)sizeof(type_must_be_complete);

		delete arrayptr;
		arrayptr = nullptr;
	}

	inline void Srand() {
		srand((unsigned int)time(NULL));
	}

	inline int Random(int min, int max) {
		return  min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
	}

	inline float Random() {
		return (float)rand() / RAND_MAX;
	}
}