#pragma once
#include "Input.h"
#include "Vector2.h"
#include "Stage.h"
#include <vector>
#include <memory>

class Player
{
private:
	Stage* stage = nullptr;
	std::vector<int> lvMaxSpd;
	static const int MaxLv = 5;
	int level;

	bool prevOnStage;
	bool onStage;

	int r;
	bool isLive;
	Vector2 pos;
	float dis;	//	プレイヤーと中心の距離
	float prevDis;
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
	int maxCombo;
	int combo;

	void RespornInit();
	void SetComboSpd();
public:
	Player(Stage* stage_);
	void Init();
	void Update(Input& input);
	void Draw();
	void KnockBack(Vector2& e_spd);
	Vector2 GetPos() {
		Vector2 c_center(r * cos(angle * PI * 2), r * sin(angle * PI * 2));
		return pos - c_center;
	};
	void AddCombo() { combo++; }
};

