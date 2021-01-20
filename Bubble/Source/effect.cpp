#include "DxLib.h"
#include "effect.h"
// EffekseerForDXLib.h���C���N���[�h���܂��B
#include "EffekseerForDXLib.h"
void Effect::init()
{
	//�`���𗠉�ʂɕύX����B
	SetDrawScreen(DX_SCREEN_BACK);

	// DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
	}

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	//SetChangeScreenModeGraphicsSystemResetFlag(TRUE);

	// Effekseer��2D�`��̐ݒ������B
	Effekseer_Set2DSetting(1920, 1080);

	// �G�t�F�N�g���\�[�X��ǂݍ��ށB
	// �ǂݍ��ގ��ɑ傫�����w�肷��B
	effectResourceHandle = LoadEffekseerEffect("Effect\\splash.efk", 10.0f);

	// ���Ԃ�����������(����I�ɃG�t�F�N�g���Đ����邽��)
	time = 0;

	// �G�t�F�N�g�̕\������ʒu��ݒ肷��B
	position_x = 0.0f;
	position_y = 0.0f;

	// �Đ����̃G�t�F�N�g�̃n���h��������������B
	playingEffectHandle = -1;

	// Z�o�b�t�@��L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetUseZBuffer3D(TRUE);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetWriteZBuffer3D(TRUE);
}

void Effect::update()
{
	// ����I�ɃG�t�F�N�g���Đ�����
	if (!ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		if (effectFlg)
		{
			// �G�t�F�N�g���Đ�����B
			playingEffectHandle = PlayEffekseer2DEffect(effectResourceHandle);

			if (time > 30)
			{
				time = 0;
				effectFlg = false;
			}
		}

		// �Đ����̃G�t�F�N�g���ړ�����B
		SetPosPlayingEffekseer2DEffect(playingEffectHandle, position_x, position_y, 0);

		// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
		UpdateEffekseer2D();

		// �X�N���[�������ւ���B
		//ScreenFlip();

		// ���Ԃ��o�߂�����B
		time++;
	}
}

void Effect::draw()
{
	DrawEffekseer2D();
}

void Effect::end()
{
	// �G�t�F�N�g���\�[�X���폜����B(Effekseer�I�����ɔj�������̂ō폜���Ȃ��Ă�����)
	DeleteEffekseerEffect(effectResourceHandle);

	// Effekseer���I������B
	Effkseer_End();
}


