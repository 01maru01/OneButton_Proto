#include "Enemy.h"
#include "DxLib.h"
#include "main.h"


Enemy::Enemy() {
	Initialize();
}

void Enemy::Initialize() {

}


void Enemy::Draw() {
	DrawCircle(pos.x, pos.y, dis, 0x00ff00, true);
}


void Enemy::Update(Input& input) {
	

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