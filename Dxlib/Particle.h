#pragma once
#include "Vector2.h"

class Particle {
private:
	Vector2 pos;
	Vector2 angle;
	float radias = 1;
	float countDown;
	bool isDied = false;
public:
	Particle(Vector2 pos);
	~Particle();

	//void SquareParticle();
	void Draw();
	void Update();

	bool GetIsDied() { return isDied; };
};