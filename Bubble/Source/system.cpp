// インクルード -------------------------------------------------------------------------------------
#include "DxLib.h"
#include <math.h>

#include "bubble.h"
#include "common.h"
#include "input.h"
#include "main.h"
#include "manage.h"
#include "map.h"
#include "system.h"
#include "stage_select.h"
#include "vec2.h"

// extern宣言,static初期化 ----------------------------------------------------------------------
extern PlBubbleObj I_PlBubbleObj[PL_BUBBLE_MAX];

// 関数 ----------------------------------------------------------------------------------------
// デバック文字を描画
void System::drawDebugString()
{
    SetFontSize(25);
    cr = GetColor(200, 0, 0);

    DrawFormatString(0, 0, cr, "Title :1");
    DrawFormatString(0, 20, cr, "Choice:2");
    DrawFormatString(0, 40, cr, "Game  :3");
    DrawFormatString(0, 60, cr, "Editor:4");
    DrawFormatString(0, 80, cr, "gameClear:%d", M_GameManager.clear);

    DrawFormatString(160, 0, cr, "bubblePosX  %f", I_PlBubbleObj[0].pos.x);
    DrawFormatString(160, 20, cr, "bubblePosY  %f", I_PlBubbleObj[0].pos.y);
    DrawFormatString(160, 40, cr, "bubbleSpeedX%f", I_PlBubbleObj[0].speed.x);
    DrawFormatString(160, 60, cr, "bubbleSpeedY%f", I_PlBubbleObj[0].speed.y);
    DrawFormatString(160, 80, cr, "touchBubble[0]%d", I_PlBubbleObj[0].touchBubble);
    DrawFormatString(160, 100, cr, "touchBubble[1]%d", I_PlBubbleObj[1].touchBubble);
    DrawFormatString(160, 120, cr, "touchBubble[2]%d", I_PlBubbleObj[2].touchBubble);
    DrawFormatString(160, 140, cr, "touchBubble[3]%d", I_PlBubbleObj[3].touchBubble);
    DrawFormatString(160, 160, cr, "level[0]%d", I_PlBubbleObj[0].level);
    DrawFormatString(160, 180, cr, "centerX  %f", I_PlBubbleObj[0].center.x);
    DrawFormatString(160, 200, cr, "centerY  %f", I_PlBubbleObj[0].center.y);
    DrawFormatString(160, 220, cr, "Stage_Select.size:%f", M_Stage_Select.size);
}

// デバックキー
void System::inputDebugKey(void)
{
    if (M_Input->GetKeyDown(KEY_INPUT_1)) M_System.changeSceneStateInit(State_Title);
    if (M_Input->GetKeyDown(KEY_INPUT_2)) M_System.changeSceneStateInit(State_Choice);
    if (M_Input->GetKeyDown(KEY_INPUT_3)) M_System.changeSceneStateInit(State_Game);
    if (M_Input->GetKeyDown(KEY_INPUT_4)) M_System.changeSceneStateInit(State_Editor);
}

// シーン遷移処理
void System::changeSceneStateInit(int nextScene)
{
    // 現在のシーンの終了処理
    switch (M_Usable.getSceneState())
    {
    case State_Editor:
        M_SceneEditor.end();
        break;
    case State_Title:
        M_SceneTitle.end();
        break;
    case State_Choice:
        M_SceneChoice.end();
        break;
    case State_Game:
        M_SceneGame.end();
        break;
    }

    // シーン遷移時に初期化
    switch (nextScene)
    {
    case State_Editor:
        M_SceneEditor.init();
        break;
    case State_Title:
        M_SceneTitle.init();
        break;
    case State_Choice:
        M_SceneChoice.init();
        break;
    case State_Game:
        M_SceneGame.init();
        break;
    }

    M_Usable.setSceneState(nextScene);
}

bool System::isCollRect(vec2f a, vec2f rel_a, vec2f b, vec2f rel_b)
{
    if (a.x <= rel_b.x && b.x <= rel_a.x && a.y <= rel_b.y && b.y <= rel_a.y) return true;
    return false;
}

bool System::isCollCircle(vec2f a, int ar, vec2f b, int br)
{
    if ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) <= (ar + br) * (ar + br)) return true;
    return false;
}

bool System::isCollCircleWithRect(vec2f c, int r, vec2f a, vec2f rel_a)
{
    if ((c.x > a.x) && (c.x < rel_a.x) && (c.y > (a.y - r)) && (c.y < (rel_a.y + r)))   return true;
    if ((c.y > a.y) && (c.y < rel_a.y) && (c.x > (a.x - r)) && (c.x < (rel_a.x + r)))   return true;
    if ((a.x - c.x) * (a.x - c.x) + (a.y - c.y) * (a.y - c.y) < r * r)                  return true;
    if ((rel_a.x - c.x) * (rel_a.x - c.x) + (a.y - c.y) * (a.y - c.y) < r * r)          return true;
    if ((rel_a.x - c.x) * (rel_a.x - c.x) + (rel_a.y - c.y) * (rel_a.y - c.y) < r * r)  return true;
    if ((a.x - c.x) * (a.x - c.x) + (rel_a.y - c.y) * (rel_a.y - c.y) < r * r)          return true;
    return false;
}