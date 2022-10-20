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

	/// <summary>
	/// ランダムに周りにばらまくエフェクト
	/// </summary>
	/// <param name="activeTime">実行時間</param>
	void ExplosionEffect(int activeTime);

	/// <summary>
	/// マネージャーの位置から5方向に飛ぶエフェクト
	/// </summary>
	/// <param name="activeTime">発生時間</param>
	/// <param name="angle">発射角度</param>
	/// <param name="width">弾の幅</param>
	void way5Effect(int activeTime, float angle,float width);

	void breakEffect(int activeTime, float angle, float width,int EffectNum);

	void breakCircleEffect(int activeTime, float R, int EffectNum);

	void popEffect(Vector2 pos, float liveTime = 50,bool isGravity=false);

	void setPos(Vector2 pos);

	void draw();

	Vector2 getPos();


	void setEffectSpeed(float speed);

	void setEffectLiveTime(float liveTime);

	bool GetIsEffctEnd() { return isEffectEnd; };

	void resetEffectFlag();

private:

	void effectStartSet(int activeTime);

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

	float effectSpeed = 0.5f;

	float effectLiveTime = 50;

};

int GetRand(int min, int max);