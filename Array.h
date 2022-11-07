#pragma once
#include <initializer_list>
#include <iostream>
#include <assert.h>

// 動的配列クラス
template<class TYPE> class DynamicArray {
protected:
	TYPE* mData;
	size_t mSize;

public:
	DynamicArray() : mData(nullptr), mSize(0) {}
	DynamicArray(size_t size) : mSize(size) {
		mData = new TYPE[size];
	}
	DynamicArray(std::initializer_list<TYPE> list) {
		mSize = list.size();
		mData = new TYPE[mSize];
		std::copy(list.begin(), list.end(), mData);
	}
	~DynamicArray() { 
		if (mData != nullptr && mSize != 0) {
			delete[] mData;
		}
	}
	// 要素がない場合生成する
	bool New(size_t s) {
		if (mData == nullptr && mSize == 0) {
			mData = new TYPE[s];
			this->mSize = s;
			return true;
		}
		return false;
	}
	// 要素がある場合削除する
	bool Delete() {
		if (mData != nullptr && mSize != 0) {
			delete[] mData;
			mData = nullptr;
			mSize = 0;
			return true;
		}
		return false;
	}
	TYPE& operator[](size_t i) { return mData[i]; }
	const TYPE& operator[](size_t i) const { return mData[i]; }

	TYPE& at(size_t i) { 
		assert(i < mSize);
		return mData[i]; 
	}
	const TYPE& at(size_t i) const { 
		assert(i < mSize);
		return mData[i];
	}

	size_t size() const { return mSize; }

public:
	using iterator = TYPE*;
	using const_iterator = const TYPE*;

	iterator begin() { return mData; }
	iterator end() { return mData + mSize; }
	const iterator begin() const { return mData; }
	const iterator end() const {return mData + mSize;	}
};

// 動的配列を二重配列のように扱うクラス
template<class TYPE> class DoubleDynamicArray :
	public DynamicArray<TYPE> {

private:
	size_t mColumn; // 行数
	size_t mRow; // 列数

public:
	DoubleDynamicArray() : mRow(0), mColumn(0) {}
	DoubleDynamicArray(size_t col, size_t row) :
		DynamicArray<TYPE>(col * row), mRow(row), mColumn(col) {}
	
	/// <summary>
	/// 要素がない場合生成する（要素がある場合 false)
	/// </summary>
	/// <param name="col">行（縦の数）</param>
	/// <param name="raw">列（横の数）</param>
	/// <returns> true : 成功   false : 失敗</returns>
	bool New(size_t col, size_t row) {
		if (DynamicArray<TYPE>::New(col * row)) {
			mRow = row;
			mColumn = col;
			return true;
		}	
		return false;
	}
	/// <summary>
	/// 要素がある場合削除する（要素がない場合 false)
	/// </summary>
	/// <returns> true : 成功   false : 失敗</returns>
	bool Delete() {
		if (DynamicArray<TYPE>::Delete()) {
			mRow = 0;
			mColumn = 0;
			return true;
		}
		return false;
	}
	/// <summary>
	/// 要素にアクセスする ( col * rawNum + raw )
	/// </summary>
	/// <param name="col">行（縦の数）</param>
	/// <param name="raw">列（横の数）</param>
	/// <returns>value</returns>
	TYPE& at(size_t col, size_t raw) {
		
		return DynamicArray<TYPE>::at(col * mRow + raw);
	}
	/// <summary>
	/// 要素にアクセスする ( col * rawNum + raw )
	/// </summary>
	/// <param name="col">行（縦の数）</param>
	/// <param name="raw">列（横の数）</param>
	/// <returns>value</returns>
	const TYPE& at(size_t col, size_t raw) const {
		return DynamicArray<TYPE>::at(col* mRow + raw);
	}

	// 列（横）
	size_t row() const { return mRow; }
	// 行（縦）
	size_t column() const { return mColumn; }
};

