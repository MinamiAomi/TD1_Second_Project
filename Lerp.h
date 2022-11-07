#pragma once


/// ※ Vector2などのクラスで使う場合　
///   (Vec + Vec) と (Vec * float) ができる必要がある （演算子のオーバーロード）

// 線形補間クラス（テンプレート）
template<class TYPE>
class Lerp
{
private:
	float param; // 変化値
	float deltaParam; // 変化量
	TYPE start, end; // スタート、エンド
public:
	Lerp() : param(0), deltaParam(0), start(), end() {}
	Lerp(const TYPE& sta, const TYPE& end) : param(0), deltaParam(0), start(sta), end(end) {}
	Lerp(float dpa, const TYPE& sta, const TYPE& end) : param(0), deltaParam(dpa), start(sta), end(end) {};
	Lerp(float par, float dpa, const TYPE& sta, const TYPE& end) : param(par), deltaParam(dpa), start(sta), end(end) {};

	// アクセッサ

	float Param() const { return param; }
	float DeltaParam() const { return deltaParam; }
	const TYPE& Start() const { return start; }
	const TYPE& End() const { return end; }

	void SetParam(float par) { param = par; }
	void SetDeltaParam(float dpa) { deltaParam = dpa; }
	void SetStart(const TYPE& sta) { start = sta; }
	void SetEnd(const TYPE& en) { end = en; }

	//

	void Set(float par, float dpa, const TYPE& sta, const TYPE& end) {
		SetParam(par);
		SetDeltaParam(dpa);
		SetStart(sta);
		SetEnd(end);
	}

	// 増加
	Lerp& operator++() {
		param += deltaParam;
		return *this;
	}
	// 増加
	Lerp operator++(int) {
		Lerp temp = *this;
		++* this;
		return temp;
	}
	// 増加
	Lerp& Increment(float deltaTime) {
		param += deltaParam * deltaTime;
		return *this;
	}
	// 減少
	Lerp& operator--() {
		param += -deltaParam;
		return *this;
	}
	// 減少
	Lerp operator--(int) {
		Lerp temp = *this;
		--* this;
		return temp;
	}
	// 減少
	Lerp& Decrement(float deltaTime) {
		param += -deltaParam * deltaTime;
		return *this;
	}

	// 線形補間
	static TYPE Calc(float par, const TYPE& sta, const TYPE& end) {
		return 	sta + (end - sta) * par;
	}
	// 計算
	TYPE Calc() const {
		return 	start + (end - start) * param;
	}
	// 計算
	// 関数ポインタでイージングさせる
	TYPE Calc(float (* easinc_func)(float)) const {
		return 	start + (end - start) * easinc_func(param);
	}

	bool IsStart() const { return param == 0.0f; }
	bool IsEnd() const { return param == 1.0f; }
	// 端
	bool IsEdge() const { return IsStart() || IsEnd(); }
	// 0未満
	bool IsUnder() const { return param < 0.0f; }
	// 1を超える
	bool IsOver() const { return 1.0f < param; }
	// 範囲外
	bool IsOutRange() const { return IsUnder() || IsOver(); }

	// 収める
	void ParamClamp() {
		if (IsUnder()) {
			param = 0.0f;
		}
		if (IsOver()) {
			param = 1.0f;
		}
	}

	// 型変換
	operator TYPE () const{
		return Calc();
	}
};

// 線形補間クラス（float特殊化 逆算追加）
template<>
class Lerp<float>
{
private:
	float param; // 変化値
	float deltaParam; // 変化量
	float start, end; // スタート、エンド
public:
	Lerp() : param(0), deltaParam(0), start(), end() {}
	Lerp(float sta, float end) : param(0), deltaParam(0), start(sta), end(end) {}
	Lerp(float dpa, float sta, float end) : param(0), deltaParam(dpa), start(sta), end(end) {};
	Lerp(float par, float dpa, float sta, float end) : param(par), deltaParam(dpa), start(sta), end(end) {};

	// アクセッサ

	float Param() const { return param; }
	float DeltaParam() const { return deltaParam; }
	float Start() const { return start; }
	float End() const { return end; }

	void SetParam(float par) { param = par; }
	void SetDeltaParam(float dpa) { deltaParam = dpa; }
	void SetStart(float sta) { start = sta; }
	void SetEnd(float en) { end = en; }

	//

	void Set(float par, float dpa, float sta, float end) {
		SetParam(par);
		SetDeltaParam(dpa);
		SetStart(sta);
		SetEnd(end);
	}

	// 増加
	Lerp& operator++() {
		param += deltaParam;
		return *this;
	}
	// 増加
	Lerp operator++(int) {
		Lerp temp = *this;
		++* this;
		return temp;
	}
	// 増加
	Lerp& Increment(float deltaTime) {
		param += deltaParam * deltaTime;
		return *this;
	}
	// 減少
	Lerp& operator--() {
		param += -deltaParam;
		return *this;
	}
	// 減少
	Lerp operator--(int) {
		Lerp temp = *this;
		--* this;
		return temp;
	}
	// 減少
	Lerp& Decrement(float deltaTime) {
		param += -deltaParam * deltaTime;
		return *this;
	}

	// 線形補間
	static float Calc(float par, float sta, float end) {
		return 	sta + par * (end - sta);
	}
	// 計算
	float Calc() const {
		return 	start + param * (end - start);
	}
	// 計算
	// 関数ポインタでイージングさせる
	float Calc(float (*easinc_func)(float)) const {
		return 	start + easinc_func(param) * (end - start);
	}
	// 逆算
	static float InverseCalc(float param, float sta, float end) {
		return (-sta + param) / (end - sta);
	}
	// 逆算
	float InverseCalc(float param) const {
		return (-start + param) / (end - start);
	}

	bool IsStart() const { return param == 0.0f; }
	bool IsEnd() const { return param == 1.0f; }
	// 端
	bool IsEdge() const { return IsStart() || IsEnd(); }
	// 0未満
	bool IsUnder() const { return param < 0.0f; }
	// 1を超える
	bool IsOver() const { return 1.0f < param; }
	// 範囲外
	bool IsOutRange() const { return IsUnder() || IsOver(); }

	// 収める
	void ParamClamp() {
		if (IsUnder()) {
			param = 0.0f;
		}
		if (IsOver()) {
			param = 1.0f;
		}
	}

	// 型変換
	operator float () const {
		return Calc();
	}
};
