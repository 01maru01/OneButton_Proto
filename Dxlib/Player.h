#pragma once
#include "Input.h"
#include "Vector2.h"

class Player
{
private:
	Vector2 pos;
	float dis;	//	�v���C���[�ƒ��S�̋���
	float angle;
	float spd;
	float maxSpd;
	bool hAttack;	//	���U���t���O

	bool knockBack;
public:
	Player();
	void Init();
	void Update(Input& input);
	void Draw();
};

