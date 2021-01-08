// インクルード ----------------------------------------------------------------------------------
#include "DxLib.h"

#include "bg.h"
#include "bubble.h"
#include "goals.h"
#include "input.h"
#include "manage.h"
#include "map.h"
#include "main.h"
#include "system.h"
#include "water_current.h"
#include "waterSource.h"
#include "scene_migration.h"

// 関数 ----------------------------------------------------------------------------------------
// Title
void TitleManager::init(void)
{
    change = false;
    decisionSH = LoadSoundMem("Data\\Sounds\\decision.mp3");
    bgmSH = LoadSoundMem("Data\\Sounds\\opning.mp3");
    once = true;
}

void TitleManager::update(void)
{
    if (once == true)
    {
        PlaySoundMem(bgmSH, DX_PLAYTYPE_LOOP, true);
        once = false;
    }
    if (M_Input->GetKeyDown(KEY_INPUT_SPACE))
    {
        PlaySoundMem(M_TitleManager.decisionSH, DX_PLAYTYPE_BACK, true);
        change = true;
    }
    if (change)
    {
        M_System.changeSceneStateInit(State_Choice);
    }
}

void TitleManager::draw(void)
{

}

void TitleManager::end(void)
{
    DeleteSoundMem(bgmSH);
}
// Select
void SelectManager::init(void)
{
    change = false;
    state = 0;
    cr = GetColor(0, 0, 0);
    handle = LoadGraph("Data\\Images\\Bg\\Game_Bg.png");
    bgmSH = LoadSoundMem("Data\\Sounds\\Voyage_SE.mp3");
    once = true;
}

void SelectManager::update(void)
{
    if (once == true)
    {
        PlaySoundMem(bgmSH, DX_PLAYTYPE_LOOP, true);
        once = false;
    }
    if (change)
    {
        M_System.changeSceneStateInit(State_Game);
    }
    if (M_Input->GetKeyDown(KEY_INPUT_BACK))
    {
        PlaySoundMem(M_TitleManager.decisionSH, DX_PLAYTYPE_BACK, true);
        M_System.changeSceneStateInit(State_Title);
    }
    //if (M_GameManager.migration == true)
    //{
    //    switch (state)
    //    {
    //    case 0:
    //        M_Scene_Migration.init();
    //        state = 1;
    //        break;
    //    case 1:
    //        M_Scene_Migration.update1();
    //        M_Scene_Migration.draw();
    //        if (M_Scene_Migration.getTimer() > 200) state = 2;
    //        break;
    //    case 2:
    //        M_Scene_Migration.end();
    //        M_GameManager.migration = false;
    //        break;
    //    default:
    //        break;
    //    }
    //}
}

void SelectManager::draw(void)
{
    SetFontSize(50);
    //DrawFormatString(1350, 1020, cr, "タイトルへ：BackSpace");
    if (M_GameManager.migration == true)
    {
        if (M_Scene_Migration.getTimer() < 60)
        {
            DrawGraph(0, 0, handle, true);
        }
    }
}

void SelectManager::end(void)
{
    M_GameManager.migration = false;
    DeleteGraph(handle);
    DeleteSoundMem(bgmSH);
}
// Game
void GameManager::init(void)
{
    change = false;
    clear = false;
    migration = false;
    cr = GetColor(0, 153, 255);
    state = 0;
    handle = LoadGraph("Data\\Images\\Bg\\Clear_Bg.png");
    bubble = LoadGraph("Data\\Images\\Sprite\\bubble.png");
    bgmSH = LoadSoundMem("Data\\Sounds\\game.mp3");
    once = true;
    num = 0;
    timer = 0;
    pos.set(0, 0);
    src.set(0, 0);
    bubble_magnification = 0.0f;
}

void GameManager::update(void)
{
    if (once == true)
    {
        PlaySoundMem(bgmSH, DX_PLAYTYPE_LOOP, true);
        once = false;
    }

    if (clear == false)
    {
        if (M_Input->GetKeyDown(KEY_INPUT_BACK))
        {
            PlaySoundMem(M_TitleManager.decisionSH, DX_PLAYTYPE_BACK, true);
            M_System.changeSceneStateInit(State_Choice);
        }
        if (M_Input->GetKeyDown(KEY_INPUT_R))
        {
            PlaySoundMem(M_TitleManager.decisionSH, DX_PLAYTYPE_BACK, true);
            M_GameManager.end();
            M_GameManager.init();
            M_GameBg.init();
            M_Water_Current.init();
            M_MapData.init();
            M_Bubble.init();
            M_MapData.spawnBubble();
            M_WaterSource.init();
            M_Goals.init();
        }
    }
    else
    {
        switch (state)
        {
        case 0:
            M_WaterSource.end();
            if (timer < 60)
            {
                bubble_magnification += 0.25;
            }
            else
            {
                state = 1;
            }
            break;
        case 1:
            num = timer / 40 % 2;
            if (num < 0) num = 0;
            if (num > 1) num = 1;
            switch (num)
            {
            case 0:
                src.set(0, 0);
                break;
            case 1:
                src.set(1920, 0);
                break;
            default: break;
            }
            if (M_Input->GetKeyDown(KEY_INPUT_SPACE)) state = 2;
            break;
        case 2:
            M_GameManager.migration = true;
            M_System.changeSceneStateInit(State_Choice);
            break;
        default:
            break;
        }
        ++timer;
    }
}

void GameManager::draw(void)
{
    SetFontSize(50);

    DrawFormatString(1500, 940, cr, "リトライ：R");
    DrawFormatString(1500, 1000, cr, "ポーズ　：P");
    //DrawFormatString(1220, 1030, cr, "ステージ選択へ：BackSpace");
    if (clear == true)
    {
        DrawRotaGraph(1920 / 2, 1080 / 2, bubble_magnification, 0, bubble, TRUE);
        if (timer > 60)
        {
            DrawRectGraphF(pos.x, pos.y, src.x, src.y, 1920, 1080, handle, true, false, false);
        }
    }
}

void GameManager::end(void)
{
    DeleteGraph(handle);
    DeleteSoundMem(bgmSH);
}