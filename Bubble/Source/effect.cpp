#include "DxLib.h"
#include "effect.h"
// EffekseerForDXLib.hをインクルードします。
#include "EffekseerForDXLib.h"
void Effect::init()
{
	//描画先を裏画面に変更する。
	SetDrawScreen(DX_SCREEN_BACK);

	// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	//SetChangeScreenModeGraphicsSystemResetFlag(TRUE);

	// Effekseerに2D描画の設定をする。
	Effekseer_Set2DSetting(1920, 1080);

	// エフェクトリソースを読み込む。
	// 読み込む時に大きさを指定する。
	effectResourceHandle = LoadEffekseerEffect("Effect\\splash.efk", 10.0f);

	// 時間を初期化する(定期的にエフェクトを再生するため)
	time = 0;

	// エフェクトの表示する位置を設定する。
	position_x = 0.0f;
	position_y = 0.0f;

	// 再生中のエフェクトのハンドルを初期化する。
	playingEffectHandle = -1;

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);
}

void Effect::update()
{
	// 定期的にエフェクトを再生する
	if (!ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		if (effectFlg)
		{
			// エフェクトを再生する。
			playingEffectHandle = PlayEffekseer2DEffect(effectResourceHandle);

			if (time > 30)
			{
				time = 0;
				effectFlg = false;
			}
		}

		// 再生中のエフェクトを移動する。
		SetPosPlayingEffekseer2DEffect(playingEffectHandle, position_x, position_y, 0);

		// Effekseerにより再生中のエフェクトを更新する。
		UpdateEffekseer2D();

		// スクリーンを入れ替える。
		//ScreenFlip();

		// 時間を経過させる。
		time++;
	}
}

void Effect::draw()
{
	DrawEffekseer2D();
}

void Effect::end()
{
	// エフェクトリソースを削除する。(Effekseer終了時に破棄されるので削除しなくてもいい)
	DeleteEffekseerEffect(effectResourceHandle);

	// Effekseerを終了する。
	Effkseer_End();
}


