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
	speedAcceleration+=0.05;
	gravity += 0.98;
	Vector2 gravityVec = { -(upVector.x),(upVector.y) };
	gravityVec.normalize();
	if (liveTime <= 0)
	{
		isDead = true;
	}
	
	float speed= moveSpeed * speedAcceleration;
	
	if (upVector.x != 0 or upVector.y != 0)
	{

		moveSpeedY += gravityVec.y;

		pos.x += moveVector.x* moveSpeed;
		pos.y += moveVector.y* moveSpeedY;
	}
	else
	{
		if (isGravity)
		{
			pos.x += moveVector.x * moveSpeed;
			pos.y += (moveVector.y * moveSpeed) + gravity;
		}
		else
		{
			pos += moveVector * speed;
		}
	}

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

void Effect::setIsGravity(bool flag)
{
	isGravity = flag;
}

void Effect::setupVector(Vector2 vec)
{

	upVector = vec;

}
