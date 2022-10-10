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

void Stage::Update()
{
	for (int i = 0; i < line.size(); i++) {
		if (line[i].life <= 0) line[i].isActive = false;
	}

	//	UŒ‚H‚ç‚Á‚½‚Æ‚«‚ÌÀ•W
}

void Stage::Draw()
{
	for (int i = 0; i < line.size(); i++) {
		int color = 0xFFFFFF;
		if (line[i].isActive) {
			DrawLine(line[i].x1, line[i].y1, line[i].x2, line[i].y2, 0xFFFFFF, 2);
		}
	}
	//DrawCircle(x, y, maxR, 0xFFFFFF, false);
	DrawCircle(x, y, minR, 0xFFFFFF, false);
}
