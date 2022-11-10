#pragma once
#include "GameObject.h"
#include "Array.h"
#include "MyMath.h"
#include "Shape.h"
#include <vector>

enum ChipType {
	kChipTypeNone, // なし
	kChipTypeBlock, // 通常ブロック


	kChipTypeNum, 

	kChipTypeError // 画面外
};

class Map :
	public GameObject {

public:

	struct InitData	{
		const char* fileName;
		int chipImageHandle[kChipTypeNum];
		int chipImageSize;
		int chipSize;
		int chipRowNum;
		int chipColmunNum;
		int mapWidth;
		int mapHeight;
	};

	struct ChipIndex {
		int row; // 列
		int column; // 行
		ChipIndex() : row(0), column(0) {}
		ChipIndex(int r, int c) : row(r), column(c) {}
		bool operator==(const ChipIndex& i) {
			return row == i.row && column == i.column;
		}
		friend ChipIndex operator-(const ChipIndex& a, const ChipIndex& b) {
			return { a.row - b.row,a.column - b.column };
		}
	};

	struct ChipData {
		ChipIndex index;
		ChipType type;
		ChipData() : index(), type() {}
		ChipData(int r, int c, ChipType t) : index(r, c), type(t) {}
		ChipData(ChipIndex in, ChipType t) : index(in), type(t) {}
	};

private:
	DoubleDynamicArray<int> mMapData;
	float mChipScale = 0.0f;

	int mChipSize = 0; // インラインゲッター用
	int mChipRow = 0; // インラインゲッター用
	int mChipColumn = 0; // インラインゲッター用
	float mMapHeight = 0.0f; // インラインゲッター用
	float mMapWidth = 0.0f; // インラインゲッター用

public:
	Map(class Game* game) : GameObject(game) {}
	~Map() {}

	void Create();
	void Update();
	void Draw();

	int getChipRow(float x) const { return static_cast<int>(x / (float)mChipSize); }
	int getChipColmun(float y) const { return static_cast<int>((mMapHeight - y)/ (float)mChipSize); }
	ChipIndex getChipIndex(const Vec2& pos) const { return { getChipRow(pos.x),getChipColmun(pos.y) }; }
	int getMapInChipRow(float x) const { return Math::Clamp<int>(getChipRow(x), 0, mChipRow); }
	int getMapInChipColumn(float x) const { return Math::Clamp<int>(getChipColmun(x), 0, mChipColumn); }
	ChipIndex getInMapChipIndex(const Vec2& pos) const { return { getMapInChipRow(pos.x),getMapInChipColumn(pos.y) }; }

	float getChipLeftWorldPosition(int row) const { return static_cast<float>(mChipSize * row + 0); }
	float getChipTopWorldPosition(int col) const { return static_cast<float>(mMapHeight - (mChipSize * col)); }
	float getChipRightWorldPosition(int row) const { return static_cast<float>(mChipSize * row + mChipSize); }
	float getChipBottomWorldPosition(int col) const { return static_cast<float>(mMapHeight - (mChipSize * col) - mChipSize); }

	Vec2 getChipLeftTopWorldPosition(const ChipIndex& index) const {
		return { getChipLeftWorldPosition(index.row),getChipTopWorldPosition(index.column) };
	}
	Vec2 getChipRightTopWorldPosition(const ChipIndex& index) const {
		return { getChipRightWorldPosition(index.row),getChipTopWorldPosition(index.column) };
	}
	Vec2 getChipLeftBottomWorldPosition(const ChipIndex& index) const {
		return { getChipLeftWorldPosition(index.row),getChipBottomWorldPosition(index.column) };
	}
	Vec2 getChipRightBottomWorldPosition(const ChipIndex& index) const {
		return { getChipRightWorldPosition(index.row),getChipBottomWorldPosition(index.column) };
	}

	ChipType getChipType(int x, int y) const {
		if (x < 0 || y < 0 || x >= mChipRow || y >= mChipColumn) {
			return kChipTypeError;
		}
		return static_cast<ChipType>(mMapData.at(y, x));
	}
	ChipType getChipType(ChipIndex i) const {
		return getChipType(i.row, i.column);
	}
	ChipType getChipType(float x, float y) const { 
		if (x < 0 || y < 0 || x >= mMapWidth || y >= mMapHeight) {
			return kChipTypeError;
		}
		return static_cast<ChipType>( mMapData.at(getChipColmun(y), getChipRow(x)) ); 
	}
	ChipType getChipType(const Vec2& v) const {
		return getChipType(v.x, v.y);
	}

	Vec2 PushOut(const Vec2& pos, const Vec2& vel, const Rect& rect) const;
	// 当たったかの判定付き
	Vec2 PushOut(const Vec2& pos, const Vec2& vel, const Rect& rect, bool* isHit) const {
		Vec2 out = PushOut(pos, vel, rect);
		if (pos == out) {
			*isHit = false;
			return out;
		}
		*isHit = true;
		return out;
	}
	// 当たった壁の法線付き
	Vec2 PushOut(const Vec2& pos, const Vec2& vel, const Rect& rect, Vec2* wallNormal) const {
		Vec2 out = PushOut(pos, vel, rect);
		if (pos == out) {
			*wallNormal = { 0,0 };
			return out;
		}
		*wallNormal = (out - pos).Normalized();
		return out;
	}

	Vec2 HighSpeedPushOut(const Vec2& pos, const Vec2& vel, const Rect& rect) const;

	bool isGround(const Rect& rect) const; // 移動後の矩形の下が地面であるか
	bool isWallonRight(const Rect& rect) const; // 移動後の矩形の右が壁であるか
	bool isWallonLeft(const Rect& rect) const; // 移動後の矩形の左が壁であるか
	bool isCeiling(const Rect& rect) const; // 移動後の矩形の上が天井であるか

private:
	void LoadMapData();

	bool SideAllChip(const Vec2& v1, const Vec2& v2) const;

	Vec2 LeftPushBack(const Vec2& pos, const Vec2& vel, const Rect& rect, std::vector<ChipData>& steppingChipData) const;
	Vec2 RightPushBack(const Vec2& pos, const Vec2& vel, const Rect& rect, std::vector<ChipData>& steppingChipData) const;
	Vec2 UpPushBack(const Vec2& pos, const Vec2& vel, const Rect& rect, std::vector<ChipData>& steppingChipData) const;
	Vec2 DownPushBack(const Vec2& pos, const Vec2& vel, const Rect& rect, std::vector<ChipData>& steppingChipData) const;
	Vec2 LeftUpPushBack(const Vec2& pos, const Vec2& vel, const Rect& rect, std::vector<ChipData>& steppingChipData) const;
	Vec2 RightUpPushBack(const Vec2& pos, const Vec2& vel, const Rect& rect, std::vector<ChipData>& steppingChipData) const;
	Vec2 LeftDownPushBack(const Vec2& pos, const Vec2& vel, const Rect& rect, std::vector<ChipData>& steppingChipData) const;
	Vec2 RightDownPushBack(const Vec2& pos, const Vec2& vel, const Rect& rect, std::vector<ChipData>& steppingChipData) const;

};

