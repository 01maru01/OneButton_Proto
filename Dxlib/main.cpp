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

	//�����蔻��
	if (a + b < c)
	{
		return true;
	}

	return false;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);


	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	Stage stage;
	Player player(&stage);
	Input input;
	EnemyManager enemyManeger;

	int time = 0;

	// �Q�[�����[�v
	while (true) {
		input.Update();

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
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

		// �`�揈��
		stage.Draw();

		enemyManeger.draw();

		player.Draw();

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
