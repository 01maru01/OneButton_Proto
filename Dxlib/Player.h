#pragma once
#include "Input.h"

class Player
{
private:
	float x;
	float y;
	int dis;	//	�v���C���[�ƒ��S�̋���
	float angle;
	float spd;
	bool hAttack;	//	���U���t���O
public:
	Player();
	void Init();
	void Update(Input& input);
	void Draw();
};

