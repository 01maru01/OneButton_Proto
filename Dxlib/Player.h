#pragma once
#include "Input.h"
#include "Vector2.h"
#include "Stage.h"
#include <vector>

class Player
{
private:
	std::vector<int> lvMaxSpd;

	int level;

	bool prevOnStage;
	bool onStage;

	int r;
	bool isLive;
	Vector2 pos;
	float dis;	//	�v���C���[�ƒ��S�̋���
	float prevDis;
	float angle;
	Vector2 spd;
	float maxSpd;
	float minSpd;

	//	heavyAttack
	bool hAttack;	//	���U���t���O
	bool hAttackHalf;	//	feaver�p
	float hAttackSpd;

	//	�X�^��
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

