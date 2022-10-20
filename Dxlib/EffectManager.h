#pragma once
#include "Effect.h"
#include <vector>
#include <memory>

class EffectManager
{
public:
	EffectManager();
	~EffectManager();

	void Init();
	void Update();

	void ExplosionEffect(int activeTime);
	void popEffect(Vector2 pos, float liveTime = 50);

	void setPos(Vector2 pos);

	void draw();

	Vector2 getPos();

	bool GetIsEffctEnd() { return isEffectEnd; };


private:

	std::vector<std::unique_ptr<Effect>> effects;

	Vector2 pos;

	//���s���Ԃ��I�������true�ɂȂ�Flag
	bool isEffectEnd = false;

	//�P�̂��ǂ����ɂɓ�����������ϐ�
	Vector2 moveVecor = {};

	//�n�܂�����(�^�C�}�[�Z�b�g�̂���)
	bool isStart = false;
	//�G�t�F�N�g�𓮂�������
	int activeTimer = 0;

	
	const int maxCoolTime = 3;

	int coolTime = maxCoolTime;

	float effctSpeed = 0.5f;

};

int GetRand(int min, int max);