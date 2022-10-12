#pragma once
#include "Vector2.h"

class NoMoveEnemy
{
public:
	NoMoveEnemy();
	~NoMoveEnemy();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="x">����X���W</param>
	/// <param name="y">����Y���W</param>
	void Initialize(Vector2 Pos);

	//�X�V(�����Ȃ��̂ł��܂�K�v�Ȃ�����)
	void Update();

	//�`��
	void Draw();

	//���W��ύX����֐�
	void SetPos(Vector2 Pos);

	//����ł��邩�ǂ�����ύX����֐�
	void SetIsDied(bool isdied);

	//���W��Ԃ��֐�
	Vector2 GetPos() { return pos; };

	//����ł��邩�ǂ�����Ԃ��֐�
	bool GetIsDied() { return isDied; };

	//�U���ɓ����������̊֐�
	void OnCollsion();

private:

	//���W�f�[�^
	Vector2 pos = {};

	//����ł��邩�ǂ���
	bool isDied = false;

};

