#include "EffectManager.h"
#include <stdlib.h>
#include <time.h>
#include <random>

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
		if (effects[i]->GetIsDead())
		{
			effects.erase(effects.begin() + i);
		}
	}

	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->Update();
	}

}

void EffectManager::ExplosionEffect(int activeTime)
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

	if (isEffectEnd == false)
	{

		if (coolTime <= 0)
		{
			float x = GetRand(-10,10);
			float y = GetRand(-10,10);
			moveVecor = { x,y};
			moveVecor.normalize();
			popEffect(pos, 50);
			coolTime = maxCoolTime;
		}

		coolTime--;
		activeTimer--;

	}

}

void EffectManager::popEffect(Vector2 pos,float liveTime)
{

	std::unique_ptr<Effect> newEffect = std::make_unique<Effect>();
	newEffect->Init(pos, moveVecor,liveTime);
	newEffect->SetSpeed(effctSpeed);
	
	//“GƒLƒƒƒ‰‚ð“o˜^
	effects.push_back(std::move(newEffect));

}

void EffectManager::setPos(Vector2 pos)
{

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

}

int GetRand(int min, int max)
{

	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<> distr(min, max);
	return distr(eng);

}