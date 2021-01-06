#include "DxLib.h"

#include "bg.h"
#include "bubble.h"
#include "editor.h"
#include "goals.h"
#include "common.h"
#include "input.h"
#include "main.h"
#include "manage.h"
#include "map.h"
#include "system.h"
#include "UI.h"
#include "stage_select.h"
#include "waterSource.h"
#include "water_current.h"
#include "scene_migration.h"

//////////////////////////////////////////////////////////////////////////
//	各ゲームで使用するクラスインスタンスやグローバル変数はここに記述
//

PlBubbleObj I_PlBubbleObj[PL_BUBBLE_MAX];
WaterObj    I_WatereObj[SOURCE_MAX];
GoalsObj    I_GoalsObj[GOALS_MAX];
//Water_Current_Obj I_Water_Current_Obj[EFFECT_BUBBLE_MAX];

//
// 定義ここまで
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	ここからエディターの処理
//

// エディター初期化処理
void Scene_Editor::init(void)
{
    M_Editor.init();
}

// エディター更新処理
void Scene_Editor::update(void)
{
    M_Editor.update();
}

// エディター描画処理
void Scene_Editor::draw(void)
{
    M_Editor.draw();
}

// エディター終了処理
void Scene_Editor::end(void)
{
    M_Editor.end();
}

//
//	エディターの処理ここまで
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	ここからタイトルの処理
//

// タイトル初期化処理
void Scene_Title::init(void)
{
    M_TitleBg.init();
    M_TitleManager.init();
    M_Scene_Migration.init();
}

// タイトル更新処理
void Scene_Title::update(void)
{
    M_TitleBg.update();
    M_TitleManager.update();
    M_Scene_Migration.update0();
}

// タイトル描画処理
void Scene_Title::draw(void)
{
    M_TitleBg.draw();
    M_TitleManager.draw();
    M_Scene_Migration.draw();
}

// タイトル終了処理
void Scene_Title::end(void)
{
    M_TitleBg.end();
    M_TitleManager.end();
    M_Scene_Migration.end();
}

//
//	タイトルの処理ここまで
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	ここからステージ選択の処理
//

// ステージ選択初期化処理
void Scene_Choice::init(void)
{
    M_ChoiceBg.init();
    M_Stage_Select.init();
    M_SelectManager.init();
    if (M_GameManager.migration == true) M_Scene_Migration.init();
}

// ステージ選択更新処理
void Scene_Choice::update(void)
{
    M_ChoiceBg.update();
    M_Stage_Select.update();
    M_SelectManager.update();
    M_Scene_Migration.update1();
}

// ステージ選択描画処理
void Scene_Choice::draw(void)
{
    M_ChoiceBg.draw();
    M_Stage_Select.draw();
    M_SelectManager.draw();
    M_Scene_Migration.draw();
}

// ステージ選択終了処理
void Scene_Choice::end(void)
{
    M_ChoiceBg.end();
    M_Stage_Select.end();
    M_SelectManager.end();
    M_Scene_Migration.end();
}

//
//	ステージ選択の処理ここまで
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	ここからゲームの処理
//

// ゲーム初期化処理
void Scene_Game::init(void)
{
    M_GameBg.init();
    M_Water_Current.init();
    M_Bubble.init();
    M_MapData.init();
    M_WaterSource.init();
    M_Goals.init();
    //M_UI.init();
    M_GameManager.init();
    M_MigrationBg.init();
    M_Scene_Migration.init();
}

// ゲーム更新処理
void Scene_Game::update(void)
{
    if (M_Scene_Migration.getTimer() > 60)
    {
        if (M_GameManager.clear == false)
        {
            M_MapData.update();
            M_Water_Current.update();
            M_GameBg.update();
            M_Bubble.update();
            M_WaterSource.update();
            M_Goals.update();
            // M_UI.update();
        }
        M_GameManager.update();
    }
    else
    {
        M_MigrationBg.update();
    }
    M_Scene_Migration.update1();
}

// ゲーム描画処理
void Scene_Game::draw(void)
{
    if (M_Scene_Migration.getTimer() > 60)
    {
        M_GameBg.draw();
        M_Water_Current.draw();
        M_MapData.draw();
        M_Bubble.draw();
        M_WaterSource.draw();
        M_Goals.draw();
        //M_UI.draw();
        M_GameManager.draw();
    }
    else
    {
        M_MigrationBg.draw();
    }
    M_Scene_Migration.draw();
}

// ゲーム終了処理
void Scene_Game::end(void)
{
    M_MapData.end();
    M_Water_Current.end();
    M_GameBg.end();
    M_Bubble.end();
    M_WaterSource.end();
    M_Goals.end();
    //M_UI.end();
    M_GameManager.end();
    M_MigrationBg.end();
    M_Scene_Migration.end();
}

//
//	ゲームの処理ここまで
//////////////////////////////////////////////////////////////////////////

// DirectX初期化前処理
void Usable::BeforeInit(void)
{
    //int mbResult;
    int win_mode = TRUE;
    //
    //// フルスクリーンにするか選択する
    //mbResult = MessageBox(NULL, STR_MSG_ASKFS, STR_MSGTTL_ASKFS, MB_YESNO);
    //if (mbResult == IDYES) win_mode = FALSE;
    ChangeWindowMode(win_mode);
    // ウィンドウタイトルを設定する
    SetMainWindowText(STR_WINTTL);
}

// ゲーム開始前処理
void Usable::AfterInit(void)
{
    // InputClass
    Input::Create();
    Input::GetInstance()->Init();

    sceneState = State_Title;
    //sceneState = State_Editor;
    M_SceneTitle.init();
}

// ゲーム終了後処理
void Usable::End(void)
{
    // InputClassの終了処理
    Input::Destroy();
    // 全グラフィックの削除
    DxLib::InitGraph();
    // 全音データの削除
    InitSoundMem();
}

// ゲームメインループ
void Usable::MainLoop(void)
{
    M_Usable.AfterInit();    // ゲーム開始前処理

    while (ProcessMessage() == 0)		    // ProcessMessageが正常に処理されている間はループ
    {
        ClearDrawScreen();  				// 裏画面を削除
        Input::GetInstance()->Updata();     // 入力状態の更新処理

        switch (sceneState)
        {
        case State_Editor:
            M_SceneEditor.update();        // エディター更新処理
            break;
        case State_Title:
            M_SceneTitle.update();         // タイトル更新処理
            M_SceneTitle.draw();           // タイトル描画処理
            break;
        case State_Choice:
            M_SceneChoice.update();        // ステージ選択更新処理
            M_SceneChoice.draw();          // ステージ選択描画処理
            break;
        case State_Game:
            M_SceneGame.update();          // ゲーム更新処理
            M_SceneGame.draw();            // ゲーム描画処理
            break;
        }

#ifdef _DEBUG
        if(sceneState!= State_Editor) M_System.drawDebugString();
        M_System.inputDebugKey();
#endif // _DEBUG

        ScreenFlip();   // VSYNCを待つ

        // ESCキーだけは常に監視。押されたら直ちに終了
        int stick = CheckHitKey(KEY_INPUT_ESCAPE);
        if (stick == 1) break;
        M_Usable.countGameTime();   // ゲームカウンタを進める
    }
}

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    M_Usable.BeforeInit();                // DirectX初期化前処理
    if (DxLib_Init() == -1) return -1;  // エラーが起きたら直ちに終了

    SetGraphMode(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, 32);
    SetDrawScreen(DX_SCREEN_BACK);      // 描画スクリーンを裏側に指定
    SetWaitVSyncFlag(TRUE);             // VSYNCを有効にする
    M_Usable.AfterInit();                 // DirectX初期化後処理
    M_Usable.MainLoop();                  // ゲーム本体(メインループ)
    M_Usable.End();                       // ゲーム終了後処理
    DxLib_End();                        // ＤＸライブラリ使用の終了処理
    return 0;                           // ソフトの終了
}
