#include "Particle.h"
#include "Dxlib.h"
#include <random>

float GetRandomPos(float min, float max)
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<float> distr(min, max);
	return distr(eng);
}

void Particle::Draw() {
	DrawBox(
		pos.x - radias,
		pos.y - radias,
		pos.x + radias,
		pos.y + radias,
		color, true);
}

void Particle::Update() {

	if (count < 2) {
		pos += angle;
		radias += countDown;
		countDown += 0.1;
		colorParamater += 5;
		color = GetColor(colorParamater, colorParamater, colorParamater);
	}

	if (radias > 10.0f && count < 10) {
		angle.normalize();
		count++;
		pos += angle;
	}

	if (count > 9)
		radias -= 1.0f;
	if (radias < 0)
		isDied = true;
}

Particle::Particle(Vector2 pos) {
	int speed = 5;
	this->pos = pos;
	angle.x = GetRandomPos(-speed, speed);
	angle.y = GetRandomPos(-speed, speed);
	countDown = GetRandomPos(0.1f, 0.3f);
	colorParamater = 150;
	color = GetColor(colorParamater, colorParamater, colorParamater);
	count = 0;
}

Particle::~Particle() {

}