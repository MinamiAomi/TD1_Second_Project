#include "Map.h"
#include "Game.h"
#include "Container.h"
#include "InputDevice.h"


#ifdef _DEBUG
#include "Debug.h"
#endif // _DEBUG


#define MAP_DATA getGame()->getContainer()->getMapData()

static Map::ChipIndex debugindex1 = {};
static Map::ChipIndex debugindex2 = {};

void Map::Create() {
	mMapData.New(MAP_DATA.chipColmunNum, MAP_DATA.chipRowNum);
	mChipScale = static_cast<float>(MAP_DATA.chipSize) / static_cast<float>(MAP_DATA.chipImageSize);
	mChipSize = MAP_DATA.chipSize;
	mChipRow = MAP_DATA.chipRowNum;
	mChipColumn = MAP_DATA.chipColmunNum;
	mMapHeight = (float)MAP_DATA.mapHeight;
	mMapWidth = (float)MAP_DATA.mapWidth;
	LoadMapData();
}

void Map::Update() {
#ifdef _DEBUG
	if (KEY->isTrigger(DIK_SPACE)) {
		LoadMapData();
	}
#endif // _DEBUG
}

void Map::Draw() {
	int rawMin = Math::Clamp<int>(getChipRow(CAMERA->getDrawArea().Left()) - 2, 0, mChipRow);
	int rawMax = Math::Clamp<int>(getChipRow(CAMERA->getDrawArea().Right()) + 2, 0, mChipRow);
	int colMax = Math::Clamp<int>(getChipColmun(CAMERA->getDrawArea().Bottom()) + 2, 0, mChipColumn);
	int colMin = Math::Clamp<int>(getChipColmun(CAMERA->getDrawArea().Top()) - 2, 0, mChipColumn);

	for (int col = colMin; col < colMax; col++) {
		for (int raw = rawMin; raw < rawMax; raw++) {
			if (mMapData.at(col, raw) != kChipTypeNone) {
				getGame()->getCamera()->DrawSprite(
					{ (float)(MAP_DATA.chipSize * raw),  (float)(MAP_DATA.mapHeight - (MAP_DATA.chipSize * col)) },
					MAP_DATA.chipImageHandle[mMapData.at(col, raw)],
					mChipScale);
			}
		}
	}
	
#ifdef _DEBUG
	if (getChipType(debugindex1) != kChipTypeNone) {
		Novice::SetBlendMode(kBlendModeSubtract);
		getGame()->getCamera()->DrawRect(
			{ { (float)(MAP_DATA.chipSize * debugindex1.row),  (float)(MAP_DATA.mapHeight - (MAP_DATA.chipSize * debugindex1.column)) },	(float)mChipSize, (float)mChipSize }, 0xFF00FFFF);
		Novice::SetBlendMode(kBlendModeNormal);
	}
	if (getChipType(debugindex2) != kChipTypeNone) {
		Novice::SetBlendMode(kBlendModeSubtract);
		getGame()->getCamera()->DrawRect(
			{ { (float)(MAP_DATA.chipSize * debugindex2.row),  (float)(MAP_DATA.mapHeight - (MAP_DATA.chipSize * debugindex2.column)) },	(float)mChipSize, (float)mChipSize }, 0xFFFF00FF);
		Novice::SetBlendMode(kBlendModeNormal);
	}
	if (Game::_debugMode) {
		Debug::Print("Raw     %d  |  %d", rawMin, rawMax);
		Debug::Print("Column  %d  |  %d", colMin, colMax);
		Vec2 mouse = MOUSE->getPosition();
		int raw = getChipRow(mouse.x);
		int col = getChipColmun(mouse.y);
		Debug::Print("MousePos %d : %d  |  %d", raw, col, (int)getChipType(raw, col));
		if (getChipType(raw, col) != kChipTypeNone) {
			Novice::SetBlendMode(kBlendModeSubtract);
			getGame()->getCamera()->DrawRect(
				{ { (float)(MAP_DATA.chipSize * raw),  (float)(MAP_DATA.mapHeight - (MAP_DATA.chipSize * col)) },	(float)mChipSize, (float)mChipSize }, 0x00FFFFFF);
			Novice::SetBlendMode(kBlendModeNormal);
		}
		else {
			getGame()->getCamera()->DrawRect(
				{ { (float)(MAP_DATA.chipSize * raw),  (float)(MAP_DATA.mapHeight - (MAP_DATA.chipSize * col)) },	(float)mChipSize, (float)mChipSize }, 0xFF0000FF);
		}
		static Rect mapArea = { {0,mMapHeight},mMapWidth,mMapHeight };
		CAMERA->DrawRect(mapArea, 0x0000FFFF, kFillModeWireFrame);
	}
#endif // _DEBUG

}


void Map::LoadMapData() {
	static char buf[256] = {};
	FILE* fp = NULL;

	fopen_s(&fp, MAP_DATA.fileName, "r");
	if (fp == NULL) {
		return;
	}
	fgets(buf, 256, fp);
	for (auto& it : mMapData) {
		fscanf_s(fp, "%d,", &it);
	}
	fclose(fp);
}

Vec2 Map::PushOut(const Vec2& pos, const Vec2& vel, const Rect& rect) const {
	
	/// ����ł���`�b�v�̂����O�ȊO�̃`�b�v��T��
	/// ���x�̌������Ƃɂǂ̃`�b�v�ɍŏ��ɓ���������������o��
	/// �ŏ��ɓ��������`�b�v�Ɣ�������

	Vec2 out = pos;
	
	if (vel.IsZero()) {
		return out;
	}

	std::vector<ChipData> steppingChipData; // ��`�̓���ł���O�ȊO�`�b�v������
	Rect collRect(rect.leftTop + pos, rect.width - 1.0f, rect.height - 1.0f);
	Rect transRect(rect.leftTop + pos, rect.width, rect.height);

	ChipIndex leftTopChipIndex = getInMapChipIndex(collRect.LeftTop()); // ����̃`�b�v���W
	ChipIndex rightBottomChipIndex = getInMapChipIndex(collRect.RightBottom()); // �E���̃`�b�v���W������

	for (int col = leftTopChipIndex.column; col <= rightBottomChipIndex.column; col++) {
		for (int row = leftTopChipIndex.row; row <= rightBottomChipIndex.row; row++) {
			ChipType type = getChipType(row, col);
			if (type != kChipTypeNone && type != kChipTypeError) { // �O�ȊO�̃`�b�v���i�[
				steppingChipData.emplace_back(row, col, type);
			}
		}
	}

	// ����ł���`�b�v�����ׂĂO
	if (steppingChipData.empty()) {
		return out;
	}

	Direction_2D vel_direct = vel.Direction(); // ���x�̌���
	// �������Ƃɍŏ��ɂ�����`�b�v��T��
	switch (vel_direct)
	{
	// ���ړ� 
	case kDirectionLeft:
		out += LeftPushBack(pos, vel, transRect, steppingChipData);
		break;
	// �E�ړ�
	case kDirectionRight:
		out += RightPushBack(pos, vel, transRect, steppingChipData);
		break;
	// ��ړ�
	case kDirectionUp:
		out += UpPushBack(pos, vel, transRect, steppingChipData);
		break;
	// ���ړ�
	case kDirectionDown:
		out += DownPushBack(pos, vel, transRect, steppingChipData);
		break;
	// ����ړ�
	case kDirectionLeftUp:
		out += LeftUpPushBack(pos, vel, transRect, steppingChipData);
		break;
	// �E��ړ�
	case kDirectionRightUp:
		out += RightUpPushBack(pos, vel, transRect, steppingChipData);
		break;
	// �����ړ�
	case kDirectionLeftDown:
		out += LeftDownPushBack(pos, vel, transRect, steppingChipData);
		break;
	// �E���ړ�
	case kDirectionRightDown:
		out += RightDownPushBack(pos, vel, transRect, steppingChipData);
		break;
	case kDirectionNone:
	default:
		break;
	}
	return out;
}


Vec2 Map::LeftPushBack(const Vec2& pos, const Vec2& vel, const Rect& rect, std::vector<ChipData>& steppingChipData) const {
	auto firstCollidedChip = &steppingChipData[0]; // �ŏ��ɂ�����`�b�v
	if (steppingChipData.size() > 1) {
		for (auto& it : steppingChipData) {
			if (it.index.row > firstCollidedChip->index.row) {
				firstCollidedChip = &it;
			}
		}
	}
	return { getChipRightWorldPosition(firstCollidedChip->index.row) - rect.Left(),0.0f};
}
Vec2 Map::RightPushBack(const Vec2& pos, const Vec2& vel, const Rect& rect, std::vector<ChipData>& steppingChipData) const {
	auto firstCollidedChip = &steppingChipData[0]; // �ŏ��ɂ�����`�b�v
	if (steppingChipData.size() > 1) {
		for (auto& it : steppingChipData) {
			if (it.index.row < firstCollidedChip->index.row) {
				firstCollidedChip = &it;
			}
		}
	}
	return { getChipLeftWorldPosition(firstCollidedChip->index.row) - rect.Right(),0.0f };
}
Vec2 Map::UpPushBack(const Vec2& pos, const Vec2& vel, const Rect& rect, std::vector<ChipData>& steppingChipData) const {
	auto firstCollidedChip = &steppingChipData[0]; // �ŏ��ɂ�����`�b�v
	if (steppingChipData.size() > 1) {
		for (auto& it : steppingChipData) {
			if (it.index.column < firstCollidedChip->index.column) {
				firstCollidedChip = &it;
			}
		}
	}
	return { 0.0f ,getChipBottomWorldPosition(firstCollidedChip->index.column) - rect.Top() };
}
Vec2 Map::DownPushBack(const Vec2& pos, const Vec2& vel, const Rect& rect, std::vector<ChipData>& steppingChipData) const {
	auto firstCollidedChip = &steppingChipData[0]; // �ŏ��ɂ�����`�b�v
	if (steppingChipData.size() > 1) {
		for (auto& it : steppingChipData) {
			if (it.index.column > firstCollidedChip->index.column) {
				firstCollidedChip = &it;
			}
		}
	}
	return {0.0f ,getChipTopWorldPosition(firstCollidedChip->index.column) - rect.Bottom() };
}
Vec2 Map::LeftUpPushBack(const Vec2& pos, const Vec2& vel, const Rect& rect, std::vector<ChipData>& steppingChipData) const {

	ChipIndex collidedChip = {}; // �ŏI�I�ɔ�������`�b�v

	Rect preRect = rect.Translation(-vel); // �ړ��O�̋�`

	if (steppingChipData.size() == 1) {
		collidedChip = steppingChipData[0].index; // ���������`�b�v�����
	}
	else {
		auto firstRightCollidedChip = &steppingChipData[0]; // �ŏ��ɂ�����E���̃`�b�v
		auto firstDownCollidedChip = &steppingChipData[0]; // �ŏ��ɂ����鉺���̃`�b�v
		
		for (auto& it : steppingChipData) {
			if (it.index.row > firstRightCollidedChip->index.row) {
				firstRightCollidedChip = &it;
			}
			if (it.index.column > firstDownCollidedChip->index.column) {
				firstDownCollidedChip = &it;
			}
		}

		float rightDistance = preRect.RightTop().Distance(getChipLeftTopWorldPosition(firstRightCollidedChip->index));
		float downDistance = preRect.LeftBottom().Distance(getChipLeftTopWorldPosition(firstDownCollidedChip->index));

		if (firstRightCollidedChip->index.row != firstDownCollidedChip->index.row &&
			firstRightCollidedChip->index.column != firstDownCollidedChip->index.column) {
			if (Math::Abs(rightDistance < downDistance) < mChipSize) { // �E�A�������Ƀ`�b�v�ɂ�������
				return { getChipRightWorldPosition(firstDownCollidedChip->index.row) - rect.Left(),
					getChipBottomWorldPosition(firstRightCollidedChip->index.column) - rect.Top() };
			}
		}
		if (rightDistance < downDistance) { // ������ɂ�������
			collidedChip = firstRightCollidedChip->index;
		}
		else  { // �オ��ɂ�������
			collidedChip = firstDownCollidedChip->index;
		}
	}
	
	float chipRight = getChipRightWorldPosition(collidedChip.row);
	float chipBottom = getChipBottomWorldPosition(collidedChip.column);

	if (0.0f < vel.Cross(Vec2{ chipRight,chipBottom } - preRect.leftTop)) {			 // preLeftPos
		return { chipRight - rect.Left(),0.0f };
	}
	return { 0.0f, chipBottom - rect.Top() };
	
}
Vec2 Map::RightUpPushBack(const Vec2& pos, const Vec2& vel, const Rect& rect, std::vector<ChipData>& steppingChipData) const {
	ChipIndex collidedChip = {}; // �ŏI�I�ɔ�������`�b�v

	Rect preRect = rect.Translation(-vel); // �ړ��O�̋�`

	if (steppingChipData.size() == 1) {
		collidedChip = steppingChipData[0].index; // ���������`�b�v�����
	}
	else {
		auto firstLeftCollidedChip = &steppingChipData[0]; // �ŏ��ɂ����鍶���̃`�b�v
		auto firstDownCollidedChip = &steppingChipData[0]; // �ŏ��ɂ����鉺���̃`�b�v

		for (auto& it : steppingChipData) {
			if (it.index.row < firstLeftCollidedChip->index.row) {
				firstLeftCollidedChip = &it;
			}
			if (it.index.column > firstDownCollidedChip->index.column) {
				firstDownCollidedChip = &it;
			}
		}

		float leftDistance =  preRect.LeftTop().Distance(getChipRightTopWorldPosition(firstLeftCollidedChip->index));
		float downDistance = preRect.RightBottom().Distance(getChipRightTopWorldPosition(firstDownCollidedChip->index));

		if (firstLeftCollidedChip->index.row != firstDownCollidedChip->index.row &&
			firstLeftCollidedChip->index.column != firstDownCollidedChip->index.column) {
			if (Math::Abs(leftDistance < downDistance) < mChipSize) { // �E�A�������Ƀ`�b�v�ɂ�������
				return { getChipLeftWorldPosition(firstDownCollidedChip->index.row) - rect.Right(),
					getChipBottomWorldPosition(firstLeftCollidedChip->index.column) - rect.Top() };
			}
		}
		if (leftDistance < downDistance) { // ������ɂ�������
			collidedChip = firstLeftCollidedChip->index;
		}
		else { // �オ��ɂ�������
			collidedChip = firstDownCollidedChip->index;
		}
	}
	float chipLeft = getChipLeftWorldPosition(collidedChip.row);
	float chipBottom = getChipBottomWorldPosition(collidedChip.column);
	if (0.0f > vel.Cross(Vec2{ chipLeft, chipBottom } - preRect.RightTop())) {
		return { chipLeft - rect.Right(),0.0f };
	}
	return { 0.0f, chipBottom - rect.Top() };
}
Vec2 Map::LeftDownPushBack(const Vec2& pos, const Vec2& vel, const Rect& rect, std::vector<ChipData>& steppingChipData) const {
	ChipIndex collidedChip = {}; // �ŏI�I�ɔ�������`�b�v

	Rect preRect = rect.Translation(-vel); // �ړ��O�̋�`

	if (steppingChipData.size() == 1) {
		collidedChip = steppingChipData[0].index; // ���������`�b�v�����
	}
	else {
		auto firstRightCollidedChip = &steppingChipData[0]; // �ŏ��ɂ�����E���̃`�b�v
		auto firstTopCollidedChip = &steppingChipData[0]; // �ŏ��ɂ�����㑤�̃`�b�v

		for (auto& it : steppingChipData) {
			if (it.index.row > firstRightCollidedChip->index.row) {
				firstRightCollidedChip = &it;
			}
			if (it.index.column < firstTopCollidedChip->index.column) {
				firstTopCollidedChip = &it;
			}
		}

		float rightDistance = preRect.RightBottom().Distance(getChipLeftTopWorldPosition(firstRightCollidedChip->index));
		float topDistance = preRect.LeftTop().Distance(getChipLeftTopWorldPosition(firstTopCollidedChip->index));

		if (firstRightCollidedChip->index.row != firstTopCollidedChip->index.row &&
			firstRightCollidedChip->index.column != firstTopCollidedChip->index.column) {
			if (Math::Abs(rightDistance < topDistance) < mChipSize) { // �E�A�������Ƀ`�b�v�ɂ�������
				return { getChipRightWorldPosition(firstTopCollidedChip->index.row) - rect.Left(),
					getChipTopWorldPosition(firstRightCollidedChip->index.column) - rect.Bottom() };
			}
		}
		if (rightDistance < topDistance) { // ������ɂ�������
			collidedChip = firstRightCollidedChip->index;
		}
		else { // �オ��ɂ�������
			collidedChip = firstTopCollidedChip->index;
		}
	}

	float chipRight = getChipRightWorldPosition(collidedChip.row);
	float chipTop = getChipTopWorldPosition(collidedChip.column);

	if (0.0f > vel.Cross(Vec2{ chipRight,chipTop } - preRect.LeftBottom())) {
		return { chipRight - rect.Left(),0.0f };
	}
	return { 0.0f, chipTop - rect.Bottom() };
}
Vec2 Map::RightDownPushBack(const Vec2& pos, const Vec2& vel, const Rect& rect, std::vector<ChipData>& steppingChipData) const {
	ChipIndex collidedChip = {}; // �ŏI�I�ɔ�������`�b�v

	Rect preRect = rect.Translation(-vel); // �ړ��O�̋�`

	if (steppingChipData.size() == 1) {
		collidedChip = steppingChipData[0].index; // ���������`�b�v�����
	}
	else {
		auto firstLeftCollidedChip = &steppingChipData[0]; // �ŏ��ɂ����鍶���̃`�b�v
		auto firstUpCollidedChip = &steppingChipData[0]; // �ŏ��ɂ����鉺���̃`�b�v

		for (auto& it : steppingChipData) {
			if (it.index.row < firstLeftCollidedChip->index.row) {
				firstLeftCollidedChip = &it;
			}
			if (it.index.column < firstUpCollidedChip->index.column) {
				firstUpCollidedChip = &it;
			}
		}

		float leftDistance = preRect.LeftBottom().Distance(getChipRightBottomWorldPosition(firstLeftCollidedChip->index));
		float UpDistance = preRect.RightTop().Distance(getChipRightBottomWorldPosition(firstUpCollidedChip->index));

		if (firstLeftCollidedChip->index.row != firstUpCollidedChip->index.row &&
			firstLeftCollidedChip->index.column != firstUpCollidedChip->index.column) {
			if (Math::Abs(leftDistance < UpDistance) < mChipSize) { // �E�A�������Ƀ`�b�v�ɂ�������
				return { getChipLeftWorldPosition(firstUpCollidedChip->index.row) - rect.Right(),
					getChipTopWorldPosition(firstLeftCollidedChip->index.column) - rect.Bottom() };
			}
		}
		if (leftDistance < UpDistance) { // ������ɂ�������
			collidedChip = firstLeftCollidedChip->index;
		}
		else { // �オ��ɂ�������
			collidedChip = firstUpCollidedChip->index;
		}
	}

	float chipLeft = getChipLeftWorldPosition(collidedChip.row);
	float chipTop = getChipTopWorldPosition(collidedChip.column);

	if (0.0f < vel.Cross(Vec2{ chipLeft,chipTop } - preRect.RightBottom())) {
		return { chipLeft - rect.Right(),0.0f };
	}
	return { 0.0f, chipTop - rect.Bottom() };
}


