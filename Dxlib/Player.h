#pragma once
#include "Input.h"
#include "Vector2.h"
#include "Stage.h"

class Player
{
private:
	bool isLive;
	Vector2 pos;
	float dis;	//	プレイヤーと中心の距離
	float angle;
	float spd;
	float maxSpd;
	float minSpd;
	bool hAttack;	//	強攻撃フラグ
	bool hAttackHalf;	//	feaver用

	//	ダメージ
	bool damage;

	//	スタン
	bool stun;
	int stunTime;

	//	KnockBack
	bool knockBack;
	int kbTime;
	Vector2 backSpd;	//	x:spd,y:dis

	//	combo
	int combo;
public:
	Player();
	void Init();
	void Update(Input& input, Stage& stage);
	void Draw();
	void KnockBack(Vector2& e_spd);
	bool Damage();
	Vector2 GetPos() { return pos; };
};

