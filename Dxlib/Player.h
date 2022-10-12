#pragma once
#include "Input.h"
#include "Vector2.h"

class Player
{
private:
	Vector2 pos;
	float dis;	//	プレイヤーと中心の距離
	float angle;
	float spd;
	float maxSpd;
	bool hAttack;	//	強攻撃フラグ

	//	ダメージ
	bool damage;

	//	スタン

	//	KnockBack
	bool knockBack;
	int kbTime;
	Vector2 backSpd;	//	x:spd,y:dis
public:
	Player();
	void Init();
	void Update(Input& input);
	void Draw();
	void KnockBack(Vector2& e_spd);
	float Damage();
};

