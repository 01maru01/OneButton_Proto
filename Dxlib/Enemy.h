#pragma once
#include "Vector2.h"
#include "Input.h"

static const float PI = 3.141592f;

class Enemy {
private:

	Vector2 pos;
	bool isDied = false;
	float angle;
	float spd;
	float maxSpd;
	bool attackFlag = false;
	int radias = 16;
	int color = 0x00aaaa;
	int search = 100;
	bool CircleCollsionE(Vector2 play, Vector2 ene);
public:
	Enemy();
	void Initialize();
	void Draw();
	void Update(Vector2 player);
	void SetPos(Vector2 Pos);
	void SetIsDied(bool isdied);
	Vector2 GetPos() { return pos; };

	void SetAttack(Vector2 player);
	void Attack();

	bool GetIsDied() { return isDied; };

	void OnCollsion();

	float dis = 16;	//	プレイヤーと中心の距離
};