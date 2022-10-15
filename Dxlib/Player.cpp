#include "Player.h"
#include "DxLib.h"
#include "main.h"
#include <cmath>

Player::Player()
{
	Init();
}

void Player::Init()
{
	onStage = false;
	prevOnStage = false;
	r = 10;
	isLive = true;
	hAttack = false;
	maxSpd = 0.1f;
	minSpd = 0.05f;
	angle = 0.0f;
	dis = 300.0f;

	knockBack = false;
	kbTime = 0;

	damage = false;

	stun = false;
	stunTime = 0;

	combo = 0;

	explosion = false;
	ex_R = 0;
}

void Player::Update(Input& input, Stage& stage)
{
	prevOnStage = onStage;

	float minR = 100.0f;
	float maxR = 300.0f;

	explosion = false;

	int maxCombo = 15;
	int num = combo;
	if (combo > maxCombo) num = maxCombo;
	num /= 5.0f;
	maxSpd = 0.1f + num * 0.01f;

#pragma region SetKcockBackSpd
	if(input.GetTriggerKey(KEY_INPUT_Q)) {
		Vector2 e_spd(GetRand(10) - 5, GetRand(10) - 5);
		KnockBack(e_spd);
	}
	if(input.GetTriggerKey(KEY_INPUT_E)&&isLive) {
		Vector2 e_spd(GetRand(10) - 5, GetRand(10) - 5);
		KnockBack(e_spd);
		backSpd.x = 0.0f;
		backSpd.y = 100.0f;
	}
#pragma endregion

	if (isLive) {
#pragma region スタン
		if (stun) {
			stunTime--;
			if (stunTime <= 0) stun = false;
		}
#pragma endregion

#pragma region 加速処理
		if (!knockBack && !stun) {
			spd.x += 0.01f;

			if (dis == maxR && !stage.Feaver()) {
				//	壁ずり(Feaver中はなし)
				if (spd.x > minSpd) {
					spd.x -= 0.015f;
				}
				if (spd.x < minSpd) {
					spd.x = minSpd;
				}
			}
			else {
				if (spd.x > maxSpd) {
					spd.x = maxSpd;
				}
			}
		}
#pragma endregion

#pragma region KnockBack
		if (knockBack) {
			if (kbTime <= 0 && spd.x <= maxSpd) knockBack = false;
			if (kbTime > 0) kbTime--;

			if (kbTime <= 0) backSpd.y = 0.0f;
			dis += backSpd.y;

			if (dis >= maxR) {
				if (stage.OnCollision(angle, Damage())) {
					dis = maxR;
					combo = 0;
				}
				else {
					//	変更必須
					isLive = false;
					dis = maxR;
				}
				//	ダメージ
				damage = true;
				knockBack = false;
				stun = true;
				stunTime = 10;
			}
		
			if (kbTime <= 0 && spd.x > maxSpd) {
				spd.x -= backSpd.x;
				if (spd.x > maxSpd) {
					spd.x = maxSpd;
				}
			}
			else {
				spd.x += backSpd.x;
			}
		}
#pragma endregion

		if (stage.Feaver()) {
#pragma region heavyAttack
		if (hAttack) {
			hAttackSpd += 5.0f;
			if (!hAttackHalf) {
				dis -= hAttackSpd;
				if (dis < 0) {
					dis = abs(dis);
					angle += 0.5f;
					if (angle >= 1) angle -= 1;
					hAttackHalf = true;
				}
			}
			else {
				dis += hAttackSpd;
				if (dis >= maxR) {
					dis = maxR;
					hAttack = false;
					explosion = true;
#pragma region 座標更新
					ex_pos.x = WIN_WIDTH / 2.0f + cos(angle * PI * 2) * dis;
					ex_pos.y = WIN_HEIGHT / 2.0f + sin(angle * PI * 2) * dis;
#pragma endregion
					combo = 0;

					//	スタン処理
					spd.x = 0;
					stun = true;
					stunTime = 10;
				}
			}
		}
#pragma endregion

#pragma region キー入力
		if (isLive) {
			if (input.GetTriggerKey(KEY_INPUT_SPACE) && !hAttack) {
				hAttack = true;
				hAttackHalf = false;
				hAttackSpd = 20.0f;
			}
		}
#pragma endregion

#pragma region 速度処理
		angle += spd.x / (float)maxR * 2 * PI;
#pragma endregion
	}
		else {
#pragma region heavyAttack
			if (hAttack) {
				hAttackSpd += 1.0f;
				dis += hAttackSpd;
				if (dis >= maxR) {
					if (stage.OnCollision(angle, true)) {
						dis = maxR;
						hAttack = false;
						explosion = true;
#pragma region 座標更新
						ex_pos.x = WIN_WIDTH / 2.0f + cos(angle * PI * 2) * dis;
						ex_pos.y = WIN_HEIGHT / 2.0f + sin(angle * PI * 2) * dis;
#pragma endregion
						combo = 0;

						//	スタン処理
						spd.x = 0;
						stun = true;
						stunTime = 10;
					}
					else {
						//	強攻撃中に穴に落ちた処理
					}
				}
			}
#pragma endregion

#pragma region キー入力
			if (input.GetKey(KEY_INPUT_SPACE) && !stun) {
				spd.y += 0.2f;
				if (spd.y > 5.0f) spd.y = 5.0f;
				dis -= spd.y;
			}
			else {
				spd.y -= 0.5f;
				if (spd.y < -3.0f) spd.y = -3.0f;
				if (!hAttack) {
					dis -= spd.y;
				}
			}
#pragma endregion

#pragma region Dis範囲制限
			if (dis >= maxR) {
				if (stage.OnCollision(angle, false)) {
					dis = maxR;
					combo = 0;
					spd.y = 0.0f;
				}
			}

			if (dis <= minR) {
				dis = minR;
				ex_R = 30 + 10 * combo;
				stage.DamageCircle(1);
				hAttack = true;
				hAttackSpd = 20.0f;
			}
#pragma endregion

			if (stage.OnCollision(angle + spd.x / (float)dis * 2 * PI, false)) {
				onStage = true;
			}
			else {
				onStage = false;
			}

#pragma region 死亡
			if (onStage == true && prevOnStage == false && dis > maxR) {
				isLive = false;
			}
			if (dis > maxR + 100) {
				isLive = false;
			}
#pragma endregion
		}
	}

#pragma region 速度処理
	angle += spd.x / (float)dis * 2 * PI;
#pragma endregion
	
	if (angle >= 1) angle -= 1;
	
#pragma region 座標更新
	pos.x = WIN_WIDTH / 2.0f + cos(angle * PI * 2) * dis;
	pos.y = WIN_HEIGHT / 2.0f + sin(angle * PI * 2) * dis;
#pragma endregion
}

void Player::Draw()
{
	Vector2 center(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f);

#pragma region 進行方向ベクトル
	//Vector2 lineVec(cos(angle * PI * 2), sin(angle * PI * 2));
	//Vector2 vertVec(-lineVec.y, lineVec.x);
	//vertVec *= 100;
	//DrawLine(pos.x, pos.y, pos.x + vertVec.x, pos.y + vertVec.y, 0xFF0000);
#pragma endregion
	int color = 0xFFFFFF;
	if (knockBack) color = 0xFF0000;

	int ex_color = 0x555555;
	if (explosion) {
		ex_color = 0xFF0000;
	}
	if(!hAttack)
	DrawCircle(ex_pos.x, ex_pos.y, ex_R, ex_color);

	Vector2 c_center(r * cos(angle * PI * 2), r * sin(angle * PI * 2));
	DrawLine(pos.x - c_center.x, pos.y - c_center.y, center.x, center.y, 0xFF0000);
	DrawCircle(pos.x - c_center.x, pos.y - c_center.y, r, color);

	DrawFormatString(10, 10, color, "spd:%f dis:%f angle:%f combo:%d onStage:%d prev:%d", spd.x, dis, angle, combo, onStage, prevOnStage);
}

void Player::KnockBack(Vector2& e_spd)
{
	knockBack = true;

	Vector2 lineVec(cos(angle * PI * 2), sin(angle * PI * 2));
	Vector2 vertVec(-lineVec.y, lineVec.x);

	//	大きさ注意
	backSpd.x = vertVec.dot(e_spd) / 30.0f;
	backSpd.y = lineVec.dot(e_spd) * 50;

	if (backSpd.x < 0) {
		backSpd.x += spd.x;
		spd.x = 0.0f;
	}
	//	速度に応じてノックバックの時間設定
	kbTime = 20;

	backSpd /= kbTime;
}

bool Player::Damage()
{
	if (damage) {
		damage = false;
		return true;
	}
	return false;
}
