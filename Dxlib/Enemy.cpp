#include "Enemy.h"
#include "DxLib.h"
#include "main.h"


Enemy::Enemy() {
	Initialize();
}

void Enemy::Initialize() {

	dis = 16;
}


void Enemy::Draw() {
	DrawCircle(pos.x, pos.y, dis, 0x00ff00, true);
}


void Enemy::Update(Input& input) {
	if (input.GetTriggerKey(KEY_INPUT_S)) {
		Initialize();
	}

}

void Enemy::SetPos(Vector2 Pos)
{
	pos = Pos;
}