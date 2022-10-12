#include "Enemy.h"
#include "DxLib.h"
#include "main.h"


Enemy::Enemy() {
	Initialize();
}

void Enemy::Initialize() {
	maxSpd = 0.1f;
	spd = 0.0f;
	angle = 0.0f;
	//dis = 300.0f;
	//pos.x = WIN_WIDTH / 2.0f + cos(angle * PI * 2) * dis;
	//pos.y = WIN_HEIGHT / 2.0f + sin(angle * PI * 2) * dis;
}


void Enemy::Draw() {
	DrawCircle(pos.x, pos.y, dis, 0x00ff00, true);
}


void Enemy::Update() {
	
	/*angle += spd / (float)dis * 2 * PI;
	if (angle >= 1) angle -= 1;

	pos.x = WIN_WIDTH / 2.0f + cos(angle * PI * 2) * dis;
	pos.y = WIN_HEIGHT / 2.0f + sin(angle * PI * 2) * dis;*/
}

void Enemy::SetPos(Vector2 Pos)
{
	pos = Pos;
}

void Enemy::SetIsDied(bool isdied)
{
	isDied = isdied;
}

void Enemy::OnCollsion()
{

	isDied = true;

}