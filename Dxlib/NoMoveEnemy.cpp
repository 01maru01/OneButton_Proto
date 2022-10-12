#include "NoMoveEnemy.h"
#include "DxLib.h"

NoMoveEnemy::NoMoveEnemy()
{
}

NoMoveEnemy::~NoMoveEnemy()
{
}

void NoMoveEnemy::Initialize(Vector2 Pos)
{
	SetPos(Pos);


}

void NoMoveEnemy::Update()
{

}

void NoMoveEnemy::Draw()
{

	DrawBox(pos.x - 8, pos.y - 8, pos.x + 8, pos.y + 8, 0x0000ff, true);

}

void NoMoveEnemy::SetPos(Vector2 Pos)
{
	pos = Pos;
}

void NoMoveEnemy::SetIsDied(bool isdied)
{

	isDied = isdied;

}

void NoMoveEnemy::OnCollsion()
{

	isDied = true;

}