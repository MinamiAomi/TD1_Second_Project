#pragma once
#include <math.h>
#include "Array.h"
class SinCosTable {
public:
	struct TableElement
	{
		float sin;
		float cos;
	};

public:
	static constexpr int kDegreeMax = 360;
	static constexpr int kAccuracy = 10; // 0.1’PˆÊ
	static constexpr int kTableNum = kDegreeMax * kAccuracy;

private:
	DynamicArray<TableElement> table;
	static constexpr float Pi = 3.14159265359f;

public:
	static const SinCosTable& getInstance() {
		static SinCosTable instance;
		return instance;
	}

	const TableElement& tableElement(int i) const { return table[i]; }

	float getSin(int i) const { return table[i].sin; }
	float getCos(int i) const { return table[i].cos; }

	float getSin(float i) const { 
		int n = (int)(i * kAccuracy);
		return table[n].sin;
	}
	float getCos(float i) const { 
		int n = (int)(i * kAccuracy);
		return table[n].cos;
	}

private:
	SinCosTable() {
		table.New(kTableNum);
		float t = 1.0f / kAccuracy * Pi / 180.0f;
		float n = 0;
		for (auto& it : table) {
			it.sin = sinf(n);
			it.cos = cosf(n);
			n += t;
		}
	};
	~SinCosTable() = default;
	SinCosTable(const SinCosTable& s) = delete;
	SinCosTable& operator=(const SinCosTable& s) = delete;
};

