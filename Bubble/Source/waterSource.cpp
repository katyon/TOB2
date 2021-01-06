// インクルード --------------------------------------------------------}--------------------------
#include "DxLib.h"

#include "bubble.h"
#include "input.h"
#include "waterSource.h"
#include "stage_select.h"
#include "system.h"

// extern宣言,static初期化 ----------------------------------------------------------------------
extern PlBubbleObj I_PlBubbleObj[PL_BUBBLE_MAX];
extern WaterObj I_WatereObj[SOURCE_MAX];

// 関数 ----------------------------------------------------------------------------------------
void WaterObj::init(WaterObj* obj, float posY, float rel_posY)
{
    obj->pos.set(0, posY);
    obj->rel_pos.set(1920, rel_posY);
    obj->num = 0;
    obj->exist = false;
}

void WaterSource::init(void)
{
    for (int i = 0; i < SOURCE_MAX; i++)
    {
        I_WatereObj[i].init(&I_WatereObj[i], 0, 1080);
    }
    nowNum = 0;
    switch (M_Stage_Select.select)
    {
    case 1:
        maxNum = 3;
        I_WatereObj[0].init(&I_WatereObj[0], 128, 384);
        I_WatereObj[1].init(&I_WatereObj[1], 448, 640);
        I_WatereObj[2].init(&I_WatereObj[2], 704, 960);
        break;
    case 2:
        maxNum = 4;
        I_WatereObj[0].init(&I_WatereObj[0], 64, 256);
        I_WatereObj[1].init(&I_WatereObj[1], 320, 512);
        I_WatereObj[2].init(&I_WatereObj[2], 576, 768);
        I_WatereObj[3].init(&I_WatereObj[3], 832, 1024);
        break;
    case 3:
        maxNum = 3;
        I_WatereObj[0].init(&I_WatereObj[0], 128, 384);
        I_WatereObj[1].init(&I_WatereObj[1], 448, 640);
        I_WatereObj[2].init(&I_WatereObj[2], 704, 1024);
        break;
    case 4:
        maxNum = 3;
        I_WatereObj[0].init(&I_WatereObj[0], 64, 320);
        I_WatereObj[1].init(&I_WatereObj[1], 384, 576);
        I_WatereObj[2].init(&I_WatereObj[2], 832, 1024);
        break;
    case 5:
        maxNum = 3;
        break;
    case 6:
        maxNum = 3;
        I_WatereObj[0].init(&I_WatereObj[0], 64, 320);
        I_WatereObj[1].init(&I_WatereObj[1], 384, 576);
        I_WatereObj[2].init(&I_WatereObj[2], 832, 1024);
        break;
    default:
        maxNum = 1;
        break;
    }
    cr = GetColor(0, 200, 100);
    for (int i = 0; i < maxNum; i++)
    {
        I_WatereObj[i].exist = true;
    }
    handle = LoadGraph("Data\\Images\\Sprite\\waterSource.png");
    decisionSH = LoadSoundMem("Data\\Sounds\\decision.mp3");
    jetSH = LoadSoundMem("Data\\Sounds\\jet.mp3");
    once = true;
}

void WaterSource::update(void)
{
    for (int i = 0; i < PL_BUBBLE_MAX; i++)
    {
        if (I_PlBubbleObj[i].exist == false) continue;
        for (int j = 0; j < SOURCE_MAX; j++)
        {
            if (I_WatereObj[j].exist == false) continue;
            if (M_System.isCollCircleWithRect(I_PlBubbleObj[i].center, I_PlBubbleObj[i].radius, I_WatereObj[nowNum - 1].pos, I_WatereObj[nowNum - 1].rel_pos))
            {
                if (M_Input->GetKey(KEY_INPUT_LEFT)) I_PlBubbleObj[i].speed.x -= BUBBLE_ACCEL;
                if (M_Input->GetKey(KEY_INPUT_RIGHT)) I_PlBubbleObj[i].speed.x += BUBBLE_ACCEL;
            }
        }
    }
    if (M_Input->GetKey(KEY_INPUT_LEFT))
    {
        if (once == true)
        {
            PlaySoundMem(jetSH, DX_PLAYTYPE_LOOP, true);
            once = false;
        }
    }
    else if (M_Input->GetKey(KEY_INPUT_RIGHT))
    {
        if (once == true)
        {
            PlaySoundMem(jetSH, DX_PLAYTYPE_LOOP, true);
            once = false;
        }
    }
    else
    {
        StopSoundMem(jetSH);
        once = true;
    }
    if (M_Input->GetKeyDown(KEY_INPUT_UP))
    {
        PlaySoundMem(decisionSH, DX_PLAYTYPE_BACK, true);
        nowNum -= 1;
    }
    if (M_Input->GetKeyDown(KEY_INPUT_DOWN))
    {
        PlaySoundMem(decisionSH, DX_PLAYTYPE_BACK, true);
        nowNum += 1;
    }
    if (nowNum < 1) nowNum = 1;
    if (nowNum > maxNum) nowNum = maxNum;
}

void WaterSource::draw(void)
{
    switch (maxNum)
    {
    case 1:
        DrawExtendGraphF(I_WatereObj[0].pos.x + 128, I_WatereObj[0].pos.y, I_WatereObj[0].pos.x, I_WatereObj[0].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[0].rel_pos.x - 128, I_WatereObj[0].pos.y, I_WatereObj[0].rel_pos.x, I_WatereObj[0].rel_pos.y, handle, true);
        break;
    case 2:
        DrawExtendGraphF(I_WatereObj[0].pos.x + 128, I_WatereObj[0].pos.y, I_WatereObj[0].pos.x, I_WatereObj[0].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[0].rel_pos.x - 128, I_WatereObj[0].pos.y, I_WatereObj[0].rel_pos.x, I_WatereObj[0].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[1].pos.x + 128, I_WatereObj[1].pos.y, I_WatereObj[1].pos.x, I_WatereObj[1].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[1].rel_pos.x - 128, I_WatereObj[1].pos.y, I_WatereObj[1].rel_pos.x, I_WatereObj[1].rel_pos.y, handle, true);
        break;
    case 3:
        DrawExtendGraphF(I_WatereObj[0].pos.x + 128, I_WatereObj[0].pos.y, I_WatereObj[0].pos.x, I_WatereObj[0].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[0].rel_pos.x - 128, I_WatereObj[0].pos.y, I_WatereObj[0].rel_pos.x, I_WatereObj[0].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[1].pos.x + 128, I_WatereObj[1].pos.y, I_WatereObj[1].pos.x, I_WatereObj[1].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[1].rel_pos.x - 128, I_WatereObj[1].pos.y, I_WatereObj[1].rel_pos.x, I_WatereObj[1].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[2].pos.x + 128, I_WatereObj[2].pos.y, I_WatereObj[2].pos.x, I_WatereObj[2].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[2].rel_pos.x - 128, I_WatereObj[2].pos.y, I_WatereObj[2].rel_pos.x, I_WatereObj[2].rel_pos.y, handle, true);
        break;
    case 4:
        DrawExtendGraphF(I_WatereObj[0].pos.x + 128, I_WatereObj[0].pos.y, I_WatereObj[0].pos.x, I_WatereObj[0].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[0].rel_pos.x - 128, I_WatereObj[0].pos.y, I_WatereObj[0].rel_pos.x, I_WatereObj[0].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[1].pos.x + 128, I_WatereObj[1].pos.y, I_WatereObj[1].pos.x, I_WatereObj[1].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[1].rel_pos.x - 128, I_WatereObj[1].pos.y, I_WatereObj[1].rel_pos.x, I_WatereObj[1].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[2].pos.x + 128, I_WatereObj[2].pos.y, I_WatereObj[2].pos.x, I_WatereObj[2].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[2].rel_pos.x - 128, I_WatereObj[2].pos.y, I_WatereObj[2].rel_pos.x, I_WatereObj[2].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[3].pos.x + 128, I_WatereObj[3].pos.y, I_WatereObj[3].pos.x, I_WatereObj[3].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[3].rel_pos.x - 128, I_WatereObj[3].pos.y, I_WatereObj[3].rel_pos.x, I_WatereObj[3].rel_pos.y, handle, true);
        break;
    case 5:
        DrawExtendGraphF(I_WatereObj[0].pos.x + 128, I_WatereObj[0].pos.y, I_WatereObj[0].pos.x, I_WatereObj[0].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[0].rel_pos.x - 128, I_WatereObj[0].pos.y, I_WatereObj[0].rel_pos.x, I_WatereObj[0].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[1].pos.x + 128, I_WatereObj[1].pos.y, I_WatereObj[1].pos.x, I_WatereObj[1].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[1].rel_pos.x - 128, I_WatereObj[1].pos.y, I_WatereObj[1].rel_pos.x, I_WatereObj[1].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[2].pos.x + 128, I_WatereObj[2].pos.y, I_WatereObj[2].pos.x, I_WatereObj[2].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[2].rel_pos.x - 128, I_WatereObj[2].pos.y, I_WatereObj[2].rel_pos.x, I_WatereObj[2].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[3].pos.x + 128, I_WatereObj[3].pos.y, I_WatereObj[3].pos.x, I_WatereObj[3].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[3].rel_pos.x - 128, I_WatereObj[3].pos.y, I_WatereObj[3].rel_pos.x, I_WatereObj[3].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[4].pos.x + 128, I_WatereObj[4].pos.y, I_WatereObj[4].pos.x, I_WatereObj[4].rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[4].rel_pos.x - 128, I_WatereObj[4].pos.y, I_WatereObj[4].rel_pos.x, I_WatereObj[4].rel_pos.y, handle, true);
        break;
    }

    for (int i = 0; i < 10; i++)
    {
        switch (nowNum)
        {
        case 1:
            DrawBox(I_WatereObj[0].pos.x + i, I_WatereObj[0].pos.y + i, I_WatereObj[0].rel_pos.x - i, I_WatereObj[0].rel_pos.y - i, cr, false);
            break;
        case 2:
            DrawBox(I_WatereObj[1].pos.x + i, I_WatereObj[1].pos.y + i, I_WatereObj[1].rel_pos.x - i, I_WatereObj[1].rel_pos.y - i, cr, false);
            break;
        case 3:
            DrawBox(I_WatereObj[2].pos.x + i, I_WatereObj[2].pos.y + i, I_WatereObj[2].rel_pos.x - i, I_WatereObj[2].rel_pos.y - i, cr, false);
            break;
        case 4:
            DrawBox(I_WatereObj[3].pos.x + i, I_WatereObj[3].pos.y + i, I_WatereObj[3].rel_pos.x - i, I_WatereObj[3].rel_pos.y - i, cr, false);
            break;
        case 5:
            DrawBox(I_WatereObj[4].pos.x + i, I_WatereObj[4].pos.y + i, I_WatereObj[4].rel_pos.x - i, I_WatereObj[4].rel_pos.y - i, cr, false);
            break;
        default: break;
        }
    }
}

void WaterSource::end(void)
{
    DeleteGraph(handle);
    DeleteSoundMem(decisionSH);
    DeleteSoundMem(jetSH);
}