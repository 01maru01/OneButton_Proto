#pragma once
#include "Vector2.h"
#include "Input.h"

class Enemy {
private:

	Vector2 pos;
	Vector2 playerPos;
	bool isDied = false;
	float angle;
	float spd;
	float maxSpd;
	bool attackFlag = false;
	int radias = 16;
	int color = 0x00aaaa;
	int search = 80;
	int attackCount = 0;
	bool CircleCollsionE(Vector2 play, Vector2 ene);
public:
	Enemy();
	void Initialize();
	void Draw();
	void Update(Vector2 player);
	void SetPos(Vector2 Pos);
	void SetIsDied(bool isdied);
	Vector2 GetPos() { return pos; };
	Vector2 GetSpd(Vector2 player);

	void SetAttack();
	void Attack();

	bool GetIsDied() { return isDied; };
	bool GetAttackFlag() { return attackFlag; };

	void OnCollsion();

	float dis = 16;	//	プレイヤーと中心の距離
};