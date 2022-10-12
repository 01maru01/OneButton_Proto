#include "Stage.h"
#include "main.h"
#include "DxLib.h"
#include <cmath>

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
		
		float angle = i / (float)line.size() * 2 * PI;
		line[i].x1 = x + maxR * cos(angle);
		line[i].y1 = y + maxR * sin(angle);

		angle = (i + 1) / (float)line.size() * 2 * PI;
		line[i].x2 = x + maxR * cos(angle);
		line[i].y2 = y + maxR * sin(angle);
	}
}

void Stage::Update(float angle)
{
	for (int i = 0; i < line.size(); i++) {
		if (line[i].life <= 0) line[i].isActive = false;
	}

	//	UŒ‚H‚ç‚Á‚½‚Æ‚«‚ÌÀ•W
	if (angle != NULL) {
		int index = angle * line.size();
		idx = index;
		line[index].life--;
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
			if (line[i].life == 1) {
				color = 0xFF0000;
			}
			DrawLine(line[i].x1, line[i].y1, line[i].x2, line[i].y2, color, 2);
		}
	}
	//DrawFormatString(10, 10, 0xFFFFFF, "index:%d", idx);
	//DrawCircle(x, y, maxR, 0xFFFFFF, false);
	DrawCircle(x, y, minR, 0xFFFFFF, false);
}

bool Stage::OnCollision(float angle)
{
	float p_size = 10.0f;
	float circleLenght = maxR * 2 * PI;
	float leftAngle = angle + p_size / circleLenght;
	float rightAngle = angle - p_size / circleLenght;

	int indexL = leftAngle * line.size();
	int indexR = rightAngle * line.size();

	if (indexL >= line.size()) indexL -= line.size();
	if (indexR >= line.size()) indexR -= line.size();

	return line[indexL].isActive || line[indexR].isActive;
}
