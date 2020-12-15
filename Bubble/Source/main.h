#pragma once

// インクルード
#include <windows.h>
#include <DxLib.h>
#include "singleton.h"

// 定数 ----------------------------------------------------
#define STR_WINTTL				"Tower of Bubble"    // ウィンドウタイトル（任意に設定）
#define STR_MSGTTL_ASKFS		"起動処理"
#define STR_MSG_ASKFS			"フルスクリーンで起動しますか？"

enum Scene_State { State_Editor, State_Title, State_Choice, State_Game };

// クラス --------------------------------------------------
#define M_Usable Usable::getInstance()
class Usable :public Singleton<Usable>
{
public:
    void    BeforeInit(void);  // DirectX初期化前処理
    void    AfterInit(void);   // ゲーム開始前処理
    void    MainLoop(void);    // ゲームメインループ
    void    End(void);         // ゲーム終了後処理

    void    setSceneState(int state) { sceneState = state; }
    int     getSceneState(void) { return sceneState; }
    void    countGameTime(void) { gameTime++; }
    int     getGameTime(void) { return gameTime; }
private:
    int     sceneState = 0;
    int     gameTime = 0;
};

// メインループ用の親クラス
class Scene
{
public:
    virtual void init(void) = 0;
    virtual void update(void) = 0;
    virtual void draw(void) = 0;
    virtual void end(void) = 0;
};

#define M_SceneEditor Scene_Editor::getInstance()
class Scene_Editor :public Scene, public Singleton<Scene_Editor>
{
public:
    void init(void);
    void update(void);
    void draw(void);
    void end(void);
};

#define M_SceneTitle Scene_Title::getInstance()
class Scene_Title :public Scene, public Singleton<Scene_Title>
{
public:
    void init(void);
    void update(void);
    void draw(void);
    void end(void);
};

#define M_SceneChoice Scene_Choice::getInstance()
class Scene_Choice :public Scene, public Singleton<Scene_Choice>
{
public:
    void init(void);
    void update(void);
    void draw(void);
    void end(void);
};

#define M_SceneGame Scene_Game::getInstance()
class Scene_Game :public Scene, public Singleton<Scene_Game>
{
public:
    void init(void);
    void update(void);
    void draw(void);
    void end(void);
};