#pragma once
#include "Vector2.h"

class NoMoveEnemy
{
public:
	NoMoveEnemy();
	~NoMoveEnemy();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="x">初期X座標</param>
	/// <param name="y">初期Y座標</param>
	void Initialize(Vector2 Pos);

	//更新(動かないのであまり必要ないかも)
	void Update();

	//描画
	void Draw();

	//座標を変更する関数
	void SetPos(Vector2 Pos);

	//死んでいるかどうかを変更する関数
	void SetIsDied(bool isdied);

	//座標を返す関数
	Vector2 GetPos() { return pos; };

	//死んでいるかどうかを返す関数
	bool GetIsDied() { return isDied; };

	//攻撃に当たった時の関数
	void OnCollsion();

private:

	//座標データ
	Vector2 pos = {};

	//死んでいるかどうか
	bool isDied = false;

};

