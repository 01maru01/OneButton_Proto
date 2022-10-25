#pragma once
#include "Vector2.h"
#include "DxLib.h"

class Effect
{
public:
	Effect();
	~Effect();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pos">生成場所</param>
	/// <param name="moveVec">正規化した移動ベクトル</param>
	/// <param name="LiveTime">画面に存在する時間</param>
	void Init(Vector2 pos, Vector2 moveVec, float LiveTime = 50);

	/// <summary>
	/// 更新
	/// </summary>	
	void Update();

	void Draw();

	void SetPos(Vector2 pos);
	void SetSpeed(float speed);
	void setIsGravity(bool flag);
	void setupVector(Vector2 vec);

	bool GetIsDead() { return isDead; };

private:

	Vector2 pos;
	Vector2 moveVector;
	Vector2 upVector;
	bool isDead = false;
	float liveTime = 50;
	float moveSpeed = 1;
	float moveSpeedY = 1;
	float speedAcceleration = 0;

	bool isGravity=false;
	float gravity = 0;
};
