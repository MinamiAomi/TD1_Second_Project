#pragma once
#include <Novice.h>

class Debug {

private:
	static int mPrintCount;

public:

	static inline void PrintCountReset() {
		mPrintCount = 0;
	}

	static inline void Print(const char* format, ...) {
		va_list args;
		va_start(args, format);
		Novice::ScreenPrintf(0, 20 * mPrintCount, format, args);
		va_end(args);
		mPrintCount++;
	}

private:
	Debug() {}

};