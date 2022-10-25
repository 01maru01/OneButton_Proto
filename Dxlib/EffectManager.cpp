#include "EffectManager.h"
#include <stdlib.h>
#include <time.h>
#include <random>

bool CircleCollsion(Vector2 play, Vector2 ene,float R1,float R2) {

	int a = (play.x - ene.x) * (play.x - ene.x);
	int b = (play.y - ene.y) * (play.y - ene.y);

	int c = (R1+R2) * (R1+R2);

	//‚ ‚½‚è”»’è
	if (a + b < c)
	{
		return true;
	}

	return false;
}

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{


}

void EffectManager::Init()
{
	pos = { 200,200 };
}

void EffectManager::Update()
{
	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->Update();
	}

	for (int i = 0; i < effects.size(); i++)
	{
		if (effects[i]->GetIsDead())
		{
			effects.erase(effects.begin() + i);
		}
	}

	

}

void EffectManager::effectStartSet(int activeTime)
{

	if (isStart == false)
	{
		activeTimer = activeTime;
		isStart = true;
	}


	if (activeTimer <= 0 and isEffectEnd == false)
	{
		isEffectEnd = true;
	}

}

void EffectManager::ExplosionEffect(int activeTime)
{
	effectStartSet(activeTime);

	if (isEffectEnd == false)
	{

		if (coolTime <= 0)
		{
			float x = GetRand(-10,10);
			float y = GetRand(-10,10);
			moveVecor = { x,y};
			moveVecor.normalize();
			popEffect(pos, effectLiveTime);
			coolTime = maxCoolTime;
		}

		coolTime--;
		activeTimer--;

	}

}

void EffectManager::way5Effect(int activeTime, float angle, float width)
{

	effectStartSet(activeTime);

	if (isEffectEnd == false)
	{

		if (coolTime <= 0)
		{
			float x = sinf(angle);
			float y = cosf(angle);
			moveVecor = { x,y };
			moveVecor.normalize();
			popEffect(pos, effectLiveTime);

			x = sinf(angle-width);
			y = cosf(angle- width);
			moveVecor = { x,y };
			moveVecor.normalize();
			popEffect(pos, effectLiveTime);

			x = sinf(angle- width*2);
			y = cosf(angle- width* 2);
			moveVecor = { x,y };
			moveVecor.normalize();
			popEffect(pos, effectLiveTime);

			x = sinf(angle+ width);
			y = cosf(angle+ width);
			moveVecor = { x,y };
			moveVecor.normalize();
			popEffect(pos, effectLiveTime);

			x = sinf(angle+ width* 2);
			y = cosf(angle+ width* 2);
			moveVecor = { x,y };
			moveVecor.normalize();
			popEffect(pos, effectLiveTime);
			coolTime = maxCoolTime;
		}

		coolTime--;
		activeTimer--;

	}

}

void EffectManager::breakEffect(int activeTime, float angle, float width, int EffectNum)
{

	effectStartSet(activeTime);

	if (isEffectEnd == false)
	{

		if (coolTime <= 0)
		{
			float widthSize = width / EffectNum;
			for (int i = 0; i < EffectNum; i++)
			{
				Vector2 startPos = { pos.x+(sinf(angle)) * (widthSize*(-5+i)),pos.y+ (cosf(angle)) * (widthSize * (-5 + i)) };
				float x = 5;
				float y = 1;
				moveVecor = { x,y };
				moveVecor.normalize();
				popEffect(startPos, effectLiveTime+5*(EffectNum-i),true);
				
			}

			coolTime = maxCoolTime;
		}

		coolTime--;
		activeTimer--;

	}

}

void EffectManager::breakCircleEffect(int activeTime, float R, int EffectNum)
{

	effectStartSet(activeTime);

	if (isEffectEnd == false)
	{

		if (coolTime <= 0)
		{
			int num = 0;
			while (num!=EffectNum)
			{

				float x = GetRand(-R, R);
				float y = GetRand(-R, R);
				Vector2 startPos = { x+pos.x , y+pos.y };
				if (!CircleCollsion(startPos, pos, 1, R))
				{
					continue;
				}
			
				moveVecor = { 0,0 };
				moveVecor.normalize();
				popEffect(startPos, effectLiveTime, true);

				num++;
			}

			coolTime = maxCoolTime;
		}

		coolTime--;
		activeTimer--;

		DrawCircle(pos.x, pos.y, R, 0xffffff);

	}

}

void EffectManager::fallFragmentEffect(int activeTime, Vector2 upVec)
{

	effectStartSet(activeTime);

	if (isEffectEnd == false)
	{

		if (coolTime <= 0)
		{
			for (int i = 0; i < 2; i++)
			{
				
				float x = 50+sinf(upVec.x);
				float y = upVec.y;
				moveVecor = { x,y };
				
				if (i == 1)
				{
					moveVecor.x = -50 - sinf(upVec.x);
				}
				
				moveVecor.y += cosf((30 + ((1 * i)) * 30));
				moveVecor.normalize();

				//moveVecor += upVec.normalize();
				
				/*if (i == 1)
				{
					moveVecor = { -moveVecor.x,moveVecor.y };
				}*/
				popEffect(pos, effectLiveTime,false,upVec);
			}
			coolTime = maxCoolTime;
		}

		coolTime--;
		activeTimer--;
	}

}

void EffectManager::popEffect(Vector2 pos,float liveTime, bool isGravity, Vector2 upVec)
{

	std::unique_ptr<Effect> newEffect = std::make_unique<Effect>();
	newEffect->Init(pos, moveVecor,liveTime);
	newEffect->SetSpeed(effectSpeed);
	newEffect->setupVector(upVec);
	newEffect->setIsGravity(isGravity);

	//“GƒLƒƒƒ‰‚ð“o˜^
	effects.push_back(std::move(newEffect));

}

void EffectManager::setPos(Vector2 pos)
{
	this->pos = pos;
}

Vector2 EffectManager::getPos()
{

	return pos;

}

void EffectManager::draw()
{

	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->Draw();
	}
	DrawCircle(pos.x, pos.y, 1,0x00ff00);
}

void EffectManager::resetEffectFlag()
{

	isEffectEnd = false;
	isStart = false;
	coolTime = 0;

}

void EffectManager::setEffectSpeed(float speed)
{
	effectSpeed = speed;
}

void EffectManager::setEffectLiveTime(float liveTime)
{
	effectLiveTime = liveTime;
}

int GetRand(int min, int max)
{

	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<> distr(min, max);
	return distr(eng);

}