#include "effect.h"
#include <cassert>

Effect::Effect()
{

}

Effect::~Effect()
{

}

void Effect::Init(Vector2 pos, Vector2 moveVec, float LiveTime)
{

	this->pos = pos;
	liveTime = LiveTime;
	moveVector = moveVec;

}

void Effect::Update()
{
	liveTime--;
	if (liveTime <= 0)
	{
		isDead = true;
	}
	
	pos += moveVector * moveSpeed;
	

}

void Effect::Draw()
{

	DrawCircle(pos.x, pos.y, 3, 0x0000ff);

}

void Effect::SetPos(Vector2 pos)
{

	this->pos = pos;

}

void Effect::SetSpeed(float speed)
{

	moveSpeed = speed;

}

