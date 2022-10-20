#include "Stage.h"
#include "main.h"
#include "DxLib.h"
#include <cmath>

Stage::Stage()
{
	x = WIN_WIDTH / 2.0f;
	y = WIN_HEIGHT / 2.0f;
	maxR = 300.0f;

	Init();

	line.resize(30);
	for (int i = 0; i < line.size(); i++) {
		float angle1 = i / (float)line.size() * 2 * PI;
		float angle2 = (i + 1) / (float)line.size() * 2 * PI;

		Vector2 _pos1(x + maxR * cos(angle1), y + maxR * sin(angle1));
		Vector2 _pos2(x + maxR * cos(angle2), y + maxR * sin(angle2));
		line[i].Init(_pos1, _pos2);
	}

	circle.Init();
}

void Stage::Init()
{
	minR = 100.0f;
	minCount = 0;
	clearNum = 5;
}

void Stage::Update()
{
	for (int i = 0; i < line.size(); i++) {
		if (line[i].flashing && line[i].activeTime > 0) line[i].activeTime--;
		if (line[i].flashing && line[i].activeTime <= 0 && line[i].isActive) {
			line[i].isActive = false;
			if (circle.isActive) {
				clearNum--;
			}
		}

		if (line[i].shake && line[i].shakeTime > 0) line[i].shakeTime--;
		if (line[i].shake && line[i].shakeTime <= 0) line[i].shake = false;
	}

	if (circle.life <= 0) circle.isActive = false;
	if (!circle.isActive) {
		circle.feaverTimer--;

		for (int i = 0; i < line.size(); i++) {
			line[i].isActive = true;
		}
	}
}

void Stage::Draw()
{
	for (int i = 0; i < line.size(); i++) {
		int color = 0xFFFFFF;
		if (line[i].isActive) {
			if (line[i].life <= 0) {
				color = 0x00FF00;
			}
			else if (line[i].life <= 1) {
				color = 0xFF0000;
			}
			else if (line[i].life <= 3) {
				color = 0x888888;
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
		DrawCircle(x, y, minR - 32, 0xFFFFFF, false);
	}
	DrawFormatString(10, 30, 0xFFFFFF, "ClearÇ‹Ç≈:%d\n%d", clearNum, minCount);

#pragma region îÕàÕäO
	DrawCircle(x, y, maxR + 100, 0xFF0000, false);
#pragma endregion
}

bool Stage::OnCollision(float angle, bool damage, int combo)
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
		line[indexL].life -= combo + 1;
		line[indexL].shake = true;
		line[indexL].shakeTime = 60;
		if (indexL != indexR) {
			line[indexR].life -= combo + 1;
			line[indexR].shake = true;
			line[indexR].shakeTime = 60;
		}
	}

	//	isActiveê›íË
	for (int i = 0; i < line.size(); i++) {
		if (line[i].life <= 0) line[i].flashing = true;
	}

	return line[indexL].isActive || line[indexR].isActive;
}

void Stage::EndFeaver(bool hAttack)
{
	if (circle.feaverTimer <= 0 && !hAttack) {
		circle.Init();

		for (int i = 0; i < line.size(); i++) {
			if (line[i].activeTime <= 0 && line[i].isActive) {
				line[i].isActive = false;
			}
		}

		minR = 50.0f + 100.0f * minCount / 150.0f;
		minCount = 0;
	}
}

void Stage::DamageCircle(int damage)
{
	circle.life--;
	minCount += damage;
}

void Stage::SetDeadAngle(float& angle)
{
	int index = angle * line.size();
	int i = 0;
	while (true) {
		index++;
		if (index >= line.size()) index = 0;
		if (line[index].isActive) {
			angle = index / (float)line.size();
			break;
		}
		i++;
		if (i > line.size()) break;
	}
}

void Line::Init(Vector2& _pos1, Vector2& _pos2)
{
	isActive = true;
	life = 5;
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
