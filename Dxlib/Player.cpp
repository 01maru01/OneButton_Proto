#include "Player.h"
#include "DxLib.h"
#include "main.h"
#include <cmath>

static float deadR = 400.0f;

void Player::RespornInit()
{
	dis = stage->GetMaxR();
	prevDis = dis;
	isLive = true;
	hAttack = false;

	knockBack = false;
	kbTime = 0;

	stun = false;
	stunTime = 0;

	combo = 0;
}

void Player::SetComboSpd()
{
	int num = combo;
	if (combo > maxCombo) {
		combo = maxCombo;
		num = maxCombo;
	}

	num /= 3.0f;
	maxSpd = 0.1f + num * 0.03f;
}

Player::Player(Stage* stage_)
{
	stage = stage_;
	level = 0;
	lvMaxSpd.resize(MaxLv);
	for (int i = 0; i < lvMaxSpd.size(); i++) {
		lvMaxSpd[i] = 0.1f + i * 0.03f;
	}
	r = 16;
	Init();
}

void Player::Init()
{
	onStage = false;
	prevOnStage = false;
	maxSpd = 0.1f;
	minSpd = 0.05f;
	angle = 0.0f;

	maxCombo = 15;

	RespornInit();
}

void Player::Update(Input& input)
{
	prevOnStage = onStage;
	prevDis = dis;

	SetComboSpd();

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

			if (dis == stage->GetMaxR() && !stage->Feaver()) {
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

			if (dis >= stage->GetMaxR()) {
				if (stage->OnCollision(angle, false, combo)) {
					dis = stage->GetMaxR();
					combo = 0;
				}
				knockBack = false;
				//stun = true;
				//stunTime = 10;
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

		if (stage->Feaver()) {
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
					if (dis >= stage->GetMaxR()) {
						if (stage->OnCollision(angle, true, combo)) {
							dis = stage->GetMaxR();
							hAttack = false;
						}
					combo = 0;

					//	スタン処理
					spd.x = 0;
					//stun = true;
					//stunTime = 10;
					}
				}
			}
#pragma endregion

			stage->EndFeaver(hAttack);

#pragma region キー入力
			if (input.GetTriggerKey(KEY_INPUT_SPACE) && !hAttack) {
				hAttack = true;
				hAttackHalf = false;
				hAttackSpd = 20.0f;
			}
#pragma endregion
		}
		else {
#pragma region heavyAttack
			if (hAttack) {
				hAttackSpd += 1.0f;
				dis += hAttackSpd;
				if (dis >= stage->GetMaxR()) {
					if (stage->OnCollision(angle, true, combo)) {
						dis = stage->GetMaxR();
						hAttack = false;
						combo = 0;

						//	スタン処理
						spd.x = 0;
						//stun = true;
						//stunTime = 10;
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
			if (dis >= stage->GetMaxR()) {
				if (stage->OnCollision(angle, false)) {
					dis = stage->GetMaxR();
					combo = 0;
					spd.y = 0.0f;
				}
			}

			if (dis <= stage->GetMinR()) {
				stage->DamageCircle(combo);
				dis = stage->GetMinR();
				hAttack = true;
				hAttackSpd = 20.0f;
			}
#pragma endregion

#pragma region SetOnStage
			if (stage->OnCollision(angle + spd.x / (float)dis * 2 * PI, false, combo)) {
				onStage = true;
			}
			else {
				onStage = false;
			}
#pragma endregion

#pragma region 死亡
			if (onStage == true && prevOnStage == false && dis > stage->GetMaxR() + r * 2) {
				stage->SetDeadAngle(angle);
				pos.x = WIN_WIDTH / 2.0f + cos(angle * PI * 2) * dis;
				pos.y = WIN_HEIGHT / 2.0f + sin(angle * PI * 2) * dis;
				isLive = false;
			}
			if (dis > stage->GetMaxR() + 100) {
				isLive = false;
			}
#pragma endregion

			if (dis == stage->GetMaxR() && prevDis < stage->GetMaxR()) {
				if (stage->OnCollision(angle, true, combo)) {
					dis = stage->GetMaxR();
					combo = 0;
					spd.y = 0.0f;
				}
			}
			else if (dis == stage->GetMaxR()) {
				//	ついている間ダメージ
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
	else {
#pragma region Resporn
		if (input.GetTriggerKey(KEY_INPUT_R)) {
			if (dis > deadR) {
				stage->SetDeadAngle(angle);
				RespornInit();
			}
			else {
				RespornInit();
			}
		}
#pragma endregion
	}
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
	backSpd.x = spd.x * 10.0f * vertVec.dot(e_spd) / 30.0f;	//	最大値:1884
	backSpd.y = spd.x * 10.0f * lineVec.dot(e_spd) * 10;	//	最大値:300

	if (backSpd.x < 0) {
		backSpd.x += spd.x;
		spd.x = 0.0f;
	}
	//	速度に応じてノックバックの時間設定
	kbTime = 20;

	backSpd /= kbTime;
}
