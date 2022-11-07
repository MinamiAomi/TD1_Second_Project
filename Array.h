#pragma once
#include <initializer_list>
#include <iostream>
#include <assert.h>

// ���I�z��N���X
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
	// �v�f���Ȃ��ꍇ��������
	bool New(size_t s) {
		if (mData == nullptr && mSize == 0) {
			mData = new TYPE[s];
			this->mSize = s;
			return true;
		}
		return false;
	}
	// �v�f������ꍇ�폜����
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

// ���I�z����d�z��̂悤�Ɉ����N���X
template<class TYPE> class DoubleDynamicArray :
	public DynamicArray<TYPE> {

private:
	size_t mColumn; // �s��
	size_t mRow; // ��

public:
	DoubleDynamicArray() : mRow(0), mColumn(0) {}
	DoubleDynamicArray(size_t col, size_t row) :
		DynamicArray<TYPE>(col * row), mRow(row), mColumn(col) {}
	
	/// <summary>
	/// �v�f���Ȃ��ꍇ��������i�v�f������ꍇ false)
	/// </summary>
	/// <param name="col">�s�i�c�̐��j</param>
	/// <param name="raw">��i���̐��j</param>
	/// <returns> true : ����   false : ���s</returns>
	bool New(size_t col, size_t row) {
		if (DynamicArray<TYPE>::New(col * row)) {
			mRow = row;
			mColumn = col;
			return true;
		}	
		return false;
	}
	/// <summary>
	/// �v�f������ꍇ�폜����i�v�f���Ȃ��ꍇ false)
	/// </summary>
	/// <returns> true : ����   false : ���s</returns>
	bool Delete() {
		if (DynamicArray<TYPE>::Delete()) {
			mRow = 0;
			mColumn = 0;
			return true;
		}
		return false;
	}
	/// <summary>
	/// �v�f�ɃA�N�Z�X���� ( col * rawNum + raw )
	/// </summary>
	/// <param name="col">�s�i�c�̐��j</param>
	/// <param name="raw">��i���̐��j</param>
	/// <returns>value</returns>
	TYPE& at(size_t col, size_t raw) {
		
		return DynamicArray<TYPE>::at(col * mRow + raw);
	}
	/// <summary>
	/// �v�f�ɃA�N�Z�X���� ( col * rawNum + raw )
	/// </summary>
	/// <param name="col">�s�i�c�̐��j</param>
	/// <param name="raw">��i���̐��j</param>
	/// <returns>value</returns>
	const TYPE& at(size_t col, size_t raw) const {
		return DynamicArray<TYPE>::at(col* mRow + raw);
	}

	// ��i���j
	size_t row() const { return mRow; }
	// �s�i�c�j
	size_t column() const { return mColumn; }
};

