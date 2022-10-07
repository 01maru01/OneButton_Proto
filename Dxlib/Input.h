#pragma once

class Input
{
public:
	void Update();

	bool GetKey(int key);
	bool GetTriggerKey(int key);
	bool GetReleaseKey(int key);
private:
	// 最新のキーボード情報用
	char keys[256] = { 0 };
	// 1ループ(フレーム)前のキーボード情報
	char prev[256] = { 0 };
};

