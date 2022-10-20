#pragma once
#include "Vector2.h"
#include "DxLib.h"

class Effect
{
public:
	Effect();
	~Effect();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pos">�����ꏊ</param>
	/// <param name="moveVec">���K�������ړ��x�N�g��</param>
	/// <param name="LiveTime">��ʂɑ��݂��鎞��</param>
	void Init(Vector2 pos, Vector2 moveVec, float LiveTime = 50);

	/// <summary>
	/// �X�V
	/// </summary>
	
	void Update();
	void Draw();

	void SetPos(Vector2 pos);
	void SetSpeed(float speed);

	bool GetIsDead() { return isDead; };

private:

	Vector2 pos;
	Vector2 moveVector;
	bool isDead = false;
	float liveTime = 50;
	float moveSpeed = 1;
};
