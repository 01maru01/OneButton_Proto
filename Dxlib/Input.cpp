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
	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for (int i = 0; i < 256; i++)
	{
		prev[i] = keys[i];
	}
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
}
