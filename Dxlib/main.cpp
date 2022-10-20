#include "main.h"
#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "Input.h"
#include "enemyManager.h"

bool CircleCollsion(Vector2 play, Vector2 ene) {

	int a = (play.x - ene.x) * (play.x - ene.x);
	int b = (play.y - ene.y) * (play.y - ene.y);

	int c = 26 * 26 ;

	//あたり判定
	if (a + b < c)
	{
		return true;
	}

	return false;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);


	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み

	// ゲームループで使う変数の宣言
	Stage stage;
	Player player(&stage);
	Input input;
	EnemyManager enemyManeger;

	int time = 0;

	// ゲームループ
	while (true) {
		input.Update();

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		player.Update(input);

		stage.Update();

		time++;
		if (time > 80) {
			time = 0;
			enemyManeger.enemyPop(WIN_WIDTH, WIN_HEIGHT);
		}

		/*if (input.GetTriggerKey(KEY_INPUT_S) ){
			enemyManeger.enemyPop(WIN_WIDTH, WIN_HEIGHT);
		}*/

		enemyManeger.update(player.GetPos());

		for (int i = 0; i < enemyManeger.getenemy().size(); i++)
		{
			//enemyManeger.getenemy()[i]->Update(player.GetPos());
			if (CircleCollsion(player.GetPos(), enemyManeger.getenemy()[i]->GetPos())) {

				if (enemyManeger.getenemy()[i]->GetAttackFlag()) {
					Vector2 hozon = enemyManeger.getenemy()[i]->GetSpd(player.GetPos());
 					player.KnockBack(hozon);
				}

				enemyManeger.getenemy()[i]->OnCollsion();
				player.AddCombo();
			}
		}

		// 描画処理
		stage.Draw();

		enemyManeger.draw();

		player.Draw();

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
