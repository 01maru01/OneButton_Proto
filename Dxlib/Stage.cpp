#include "Stage.h"
#include "main.h"
#include "DxLib.h"
#include <cmath>
#include "Vector2.h"

static const float PI = 3.1415926535f;

Stage::Stage()
{
	x = WIN_WIDTH / 2.0f;
	y = WIN_HEIGHT / 2.0f;
	maxR = 300;
	minR = 100;

	line.resize(60);
	for (int i = 0; i < line.size(); i++) {
		line[i].isActive = true;
		line[i].life = 3;
		line[i].activeTime = 60;
		line[i].flashing = false;
		
		float angle = i / (float)line.size() * 2 * PI;
		line[i].x1 = x + maxR * cos(angle);
		line[i].y1 = y + maxR * sin(angle);

		angle = (i + 1) / (float)line.size() * 2 * PI;
		line[i].x2 = x + maxR * cos(angle);
		line[i].y2 = y + maxR * sin(angle);
	}
}

void Stage::Update()
{
	for (int i = 0; i < line.size(); i++) {
		if (line[i].flashing && line[i].activeTime > 0) line[i].activeTime--;
		if (line[i].flashing && line[i].activeTime <= 0) line[i].isActive = false;

		if (line[i].shake && line[i].shakeTime > 0) line[i].shakeTime--;
		if (line[i].shake && line[i].shakeTime <= 0) line[i].shake = false;
	}

	if (circle.life <= 0) circle.isActive = false;
	if (!circle.isActive) circle.feaverTimer--;
	if (circle.feaverTimer <= 0) {
		circle.feaverTimer = 300;
		circle.isActive = true;
		circle.life = 50;
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
			DrawLine(line[i].x1 + shakePos.x, line[i].y1 + shakePos.y, line[i].x2 + shakePos.x, line[i].y2 + shakePos.y, color, 2);
		}
	}

	if (circle.isActive) {
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

	//	isActiveê›íË
	for (int i = 0; i < line.size(); i++) {
		if (line[i].life <= 0) line[i].flashing = true;
	}

	return line[indexL].isActive || line[indexR].isActive;
}
