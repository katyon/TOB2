#pragma once

// �C���N���[�h
#include <windows.h>
#include <DxLib.h>
#include "singleton.h"

// �萔 ----------------------------------------------------
#define STR_WINTTL				"Tower of Bubble"    // �E�B���h�E�^�C�g���i�C�ӂɐݒ�j
#define STR_MSGTTL_ASKFS		"�N������"
#define STR_MSG_ASKFS			"�t���X�N���[���ŋN�����܂����H"

enum Scene_State { State_Editor, State_Title, State_Choice, State_Game };

// �N���X --------------------------------------------------
#define M_Usable Usable::getInstance()
class Usable :public Singleton<Usable>
{
public:
    void    BeforeInit(void);  // DirectX�������O����
    void    AfterInit(void);   // �Q�[���J�n�O����
    void    MainLoop(void);    // �Q�[�����C�����[�v
    void    End(void);         // �Q�[���I���㏈��

    void    setSceneState(int state) { sceneState = state; }
    int     getSceneState(void) { return sceneState; }
    void    countGameTime(void) { gameTime++; }
    int     getGameTime(void) { return gameTime; }
private:
    int     sceneState = 0;
    int     gameTime = 0;
};

// ���C�����[�v�p�̐e�N���X
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