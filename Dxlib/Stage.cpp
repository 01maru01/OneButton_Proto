#include "Stage.h"
#include "main.h"
#include "DxLib.h"

Stage::Stage()
{
	x = WIN_WIDTH / 2.0f;
	y = WIN_HEIGHT / 2.0f;
	maxR = 300;
	minR = 100;
}

void Stage::Update()
{
}

void Stage::Draw()
{
	DrawCircle(x, y, maxR, 0xFFFFFF, false);
	DrawCircle(x, y, minR, 0xFFFFFF, false);
}
