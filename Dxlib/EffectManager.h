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

	/// <summary>
	/// �����_���Ɏ���ɂ΂�܂��G�t�F�N�g
	/// </summary>
	/// <param name="activeTime">���s����</param>
	void ExplosionEffect(int activeTime);

	/// <summary>
	/// �}�l�[�W���[�̈ʒu����5�����ɔ�ԃG�t�F�N�g
	/// </summary>
	/// <param name="activeTime">��������</param>
	/// <param name="angle">���ˊp�x</param>
	/// <param name="width">�e�̕�</param>
	void way5Effect(int activeTime, float angle,float width);

	void breakEffect(int activeTime, float angle, float width,int EffectNum);

	void breakCircleEffect(int activeTime, float R, int EffectNum);

	void popEffect(Vector2 pos, float liveTime = 50,bool isGravity=false);

	void setPos(Vector2 pos);

	void draw();

	Vector2 getPos();


	void setEffectSpeed(float speed);

	void setEffectLiveTime(float liveTime);

	bool GetIsEffctEnd() { return isEffectEnd; };

	void resetEffectFlag();

private:

	void effectStartSet(int activeTime);

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

	float effectSpeed = 0.5f;

	float effectLiveTime = 50;

};

int GetRand(int min, int max);