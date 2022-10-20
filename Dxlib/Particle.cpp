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
		0xaaaaaa, true);
}

void Particle::Update() {
	pos += angle;
	radias += countDown;
	countDown += 0.1;

	if (radias > 5.0f) {
		isDied = true;
	}
}

Particle::Particle(Vector2 pos) {
	this->pos = pos;
	angle.x = GetRandomPos(-1.0, 1.0);
	angle.y = GetRandomPos(-1.0, 1.0);
	countDown = GetRandomPos(0.1f, 0.3f);
}

Particle::~Particle() {

}