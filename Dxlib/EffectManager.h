#pragma once
#include "Effect.h"
#include <vector>
#include <memory>

class EffectManager
{
public:
	EffectManager();
	~EffectManager();

	void Init();
	void Update();

	void ExplosionEffect(int activeTime);
	void popEffect(Vector2 pos, float liveTime = 50);

	void setPos(Vector2 pos);

	void draw();

	Vector2 getPos();

	bool GetIsEffctEnd() { return isEffectEnd; };


private:

	std::vector<std::unique_ptr<Effect>> effects;

	Vector2 pos;

	//実行時間が終わったらtrueになるFlag
	bool isEffectEnd = false;

	//単体がどっちにに動くかを入れる変数
	Vector2 moveVecor = {};

	//始まったか(タイマーセットのため)
	bool isStart = false;
	//エフェクトを動かす時間
	int activeTimer = 0;

	
	const int maxCoolTime = 3;

	int coolTime = maxCoolTime;

	float effctSpeed = 0.5f;

};

int GetRand(int min, int max);