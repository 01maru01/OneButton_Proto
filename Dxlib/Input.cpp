#include "Input.h"
#include "DxLib.h"

bool Input::GetKey(int key)
{
	//if (key >= 256)	return false;
	return keys[key];
}
bool Input::GetTriggerKey(int key)
{
	return keys[key] && !prev[key];
}
bool Input::GetReleaseKey(int key)
{
	return !keys[key] && prev[key];
}

void Input::Update()
{
	// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
	for (int i = 0; i < 256; i++)
	{
		prev[i] = keys[i];
	}
	// �ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);
}
