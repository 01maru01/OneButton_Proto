#pragma once
#include "Input.h"
#include "Vector2.h"
#include "Stage.h"

class Player
{
private:
	bool prevOnStage;
	bool onStage;

	int r;
	bool isLive;
	Vector2 pos;
	float dis;	//	プレイヤーと中心の距離
	float angle;
	Vector2 spd;
	float maxSpd;
	float minSpd;

	//	heavyAttack
	bool hAttack;	//	強攻撃フラグ
	bool hAttackHalf;	//	feaver用
	float hAttackSpd;

	//	スタン
	bool stun;
	int stunTime;

	//	KnockBack
	bool knockBack;
	int kbTime;
	Vector2 backSpd;	//	x:spd,y:dis

	//	combo
	int combo;

	void RespornInit();
	void SetComboSpd();
public:
	Player();
	void Init();
	void Update(Input& input, Stage& stage);
	void Draw();
	void KnockBack(Vector2& e_spd);
	Vector2 GetPos() {
		Vector2 c_center(r * cos(angle * PI * 2), r * sin(angle * PI * 2));
		return pos - c_center;
	};
	void AddCombo() { combo++; }
};

