#pragma once

class Input
{
public:
	void Update();

	bool GetKey(int key);
	bool GetTriggerKey(int key);
	bool GetReleaseKey(int key);
private:
	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };
	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char prev[256] = { 0 };
};

