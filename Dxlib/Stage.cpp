#include "Stage.h"
#include "main.h"
#include "DxLib.h"
#include <cmath>

Stage::Stage()
{
	x = WIN_WIDTH / 2.0f;
	y = WIN_HEIGHT / 2.0f;
	maxR = 300;
	minR = 100;

	clearNum = 5;

	line.resize(10);
	for (int i = 0; i < line.size(); i++) {
		float angle1 = i / (float)line.size() * 2 * PI;
		float angle2 = (i + 1) / (float)line.size() * 2 * PI;

		Vector2 _pos1(x + maxR * cos(angle1), y + maxR * sin(angle1));
		Vector2 _pos2(x + maxR * cos(angle2), y + maxR * sin(angle2));
		line[i].Init(_pos1, _pos2);
	}

	circle.Init();
}

void Stage::Update()
{
	for (int i = 0; i < line.size(); i++) {
		if (line[i].flashing && line[i].activeTime > 0) line[i].activeTime--;
		if (line[i].flashing && line[i].activeTime <= 0 && line[i].isActive) {
			line[i].isActive = false;
			clearNum--;
		}

		if (line[i].shake && line[i].shakeTime > 0) line[i].shakeTime--;
		if (line[i].shake && line[i].shakeTime <= 0) line[i].shake = false;
	}

	if (circle.life <= 0) circle.isActive = false;
	if (!circle.isActive) circle.feaverTimer--;
	if (circle.feaverTimer <= 0) {
		circle.Init();
	}
}

void Stage::Draw()
{
	for (int i = 0; i < line.size(); i++) {
		int color = 0xFFFFFF;
		if (line[i].isActive) {
			if (line[i].life == 2) {
				color = 0x888888;
			}
			if (line[i].life <= 1) {
				color = 0xFF0000;
			}
			
			Vector2 shakePos;
			if (line[i].shake) {
				shakePos = Vector2(GetRand(line[i].shakeTime) - line[i].shakeTime / 2.0f, GetRand(line[i].shakeTime) - line[i].shakeTime / 2.0f);
				shakePos /= 2.0f;
			}
			DrawLine(line[i].pos1.x + shakePos.x, line[i].pos1.y + shakePos.y, line[i].pos2.x + shakePos.x, line[i].pos2.y + shakePos.y, color, 2);
		}
	}

	if (circle.isActive) {
		DrawFormatString(WIN_WIDTH / 2 - 10, WIN_HEIGHT / 2, 0xFFFFFF, "%d", circle.life);
		DrawFormatString(10, 20, 0xFFFFFF, "Clear�܂�:%d", clearNum);
		DrawCircle(x, y, minR - 20, 0xFFFFFF, false);
	}
}

bool Stage::OnCollision(float angle, bool damage)
{
	float p_size = 10.0f;
	float circleLenght = maxR * 2 * PI;
	float leftAngle = angle + p_size / circleLenght;
	float rightAngle = angle - p_size / circleLenght;

	int indexL = leftAngle * line.size();
	int indexR = rightAngle * line.size();

	if (indexL >= line.size()) indexL -= line.size();
	if (indexR >= line.size()) indexR -= line.size();

	if (damage) {
		line[indexL].life--;
		line[indexL].shake = true;
		line[indexL].shakeTime = 60;
		if (indexL != indexR) {
			line[indexR].life--;
			line[indexR].shake = true;
			line[indexR].shakeTime = 60;
		}
	}

	//	isActive�ݒ�
	for (int i = 0; i < line.size(); i++) {
		if (line[i].life <= 0) line[i].flashing = true;
	}

	return line[indexL].isActive || line[indexR].isActive;
}

void Line::Init(Vector2& _pos1, Vector2& _pos2)
{
	isActive = true;
	life = 3;
	activeTime = 60;
	flashing = false;

	pos1 = _pos1;
	pos2 = _pos2;
}

void SmallCircle::Init()
{
	feaverTimer = 300;
	isActive = true;
	life = 10;
}
