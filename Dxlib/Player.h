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

	bool knockBack;
public:
	Player();
	void Init();
	void Update(Input& input);
	void Draw();
};

