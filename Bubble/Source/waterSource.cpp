// インクルード --------------------------------------------------------}--------------------------
#include "DxLib.h"

#include "bubble.h"
#include "input.h"
#include "waterSource.h"
#include "stage_select.h"
#include "system.h"
#include "map.h"

// extern宣言,static初期化 ----------------------------------------------------------------------
extern PlBubbleObj I_PlBubbleObj[PL_BUBBLE_MAX];
extern WaterObj I_WatereObj[SOURCE_MAX];

// 関数 ----------------------------------------------------------------------------------------
void WaterObj::init(WaterObj* obj, float chipY, float rel_chipY)
{
    obj->pos.set(0, chipY * MAPCHIP_SIZE);
    obj->rel_pos.set(MAPCHIP_SIZE * MAPCHIP_H_MAX, rel_chipY * MAPCHIP_SIZE + MAPCHIP_SIZE);
    obj->mini_pos.set(MINI_MAP_FIX, 32 + chipY * MAPCHIP_SIZE_MINI);
    obj->mini_rel_pos.set(MINI_MAP_FIX + MAPCHIP_SIZE_MINI * MAPCHIP_H_MAX, 32 + rel_chipY * MAPCHIP_SIZE_MINI + MAPCHIP_SIZE_MINI);
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
        maxNum = 6;
        I_WatereObj[0].init(&I_WatereObj[0], 3, 6);
        I_WatereObj[1].init(&I_WatereObj[1], 8, 10);
        I_WatereObj[2].init(&I_WatereObj[2], 12, 14);
        I_WatereObj[3].init(&I_WatereObj[3], 16, 19);
        I_WatereObj[4].init(&I_WatereObj[4], 21, 24);
        I_WatereObj[5].init(&I_WatereObj[5], 28, 30);
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
        maxNum = 6;
        I_WatereObj[0].init(&I_WatereObj[0], 1, 4);
        I_WatereObj[1].init(&I_WatereObj[1], 6, 8);
        I_WatereObj[2].init(&I_WatereObj[2], 11, 12);
        I_WatereObj[3].init(&I_WatereObj[3], 18, 21);
        I_WatereObj[4].init(&I_WatereObj[4], 24, 26);
        I_WatereObj[5].init(&I_WatereObj[5], 28, 30);
        break;
    case 5:
        maxNum = 3;
        break;
    case 6:
        maxNum = 6;
        I_WatereObj[0].init(&I_WatereObj[0], 1, 4);
        I_WatereObj[1].init(&I_WatereObj[1], 6, 8);
        I_WatereObj[2].init(&I_WatereObj[2], 11, 12);
        I_WatereObj[3].init(&I_WatereObj[3], 18, 21);
        I_WatereObj[4].init(&I_WatereObj[4], 24, 26);
        I_WatereObj[5].init(&I_WatereObj[5], 28, 30);
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
    scrollTimer = 1;
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

    if (nowNum > 1 && nowNum < maxNum)
        M_MapData.scrollPos.y = I_WatereObj[nowNum - 1].pos.y - (1080 * 0.5) + 100;
}

void WaterSource::draw(void)
{
    for (int i = 0; i < maxNum; i++)
    {
        DrawExtendGraphF(I_WatereObj[i].pos.x + (MAPCHIP_SIZE * 2) - M_MapData.scrollPos.x, I_WatereObj[i].pos.y - M_MapData.scrollPos.y,
            I_WatereObj[i].pos.x - M_MapData.scrollPos.x, I_WatereObj[i].rel_pos.y - M_MapData.scrollPos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[i].rel_pos.x - (MAPCHIP_SIZE * 2) - M_MapData.scrollPos.x, I_WatereObj[i].pos.y - M_MapData.scrollPos.y,
            I_WatereObj[i].rel_pos.x - M_MapData.scrollPos.x, I_WatereObj[i].rel_pos.y - M_MapData.scrollPos.y, handle, true);
    }

    for (int i = 0; i < 10; i++)
    {
        DrawBox(I_WatereObj[nowNum - 1].pos.x - M_MapData.scrollPos.x + i, I_WatereObj[nowNum - 1].pos.y - M_MapData.scrollPos.y + i,
            I_WatereObj[nowNum - 1].rel_pos.x - M_MapData.scrollPos.x - i, I_WatereObj[nowNum - 1].rel_pos.y - M_MapData.scrollPos.y - i, cr, false);
    }

    // minimap
    for (int i = 0; i < maxNum; i++)
    {
        DrawExtendGraphF(I_WatereObj[i].mini_pos.x + (MAPCHIP_SIZE_MINI * 2), I_WatereObj[i].mini_pos.y, I_WatereObj[i].mini_pos.x, I_WatereObj[i].mini_rel_pos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[i].mini_rel_pos.x - (MAPCHIP_SIZE_MINI * 2), I_WatereObj[i].mini_pos.y, I_WatereObj[i].mini_rel_pos.x, I_WatereObj[i].mini_rel_pos.y, handle, true);
    }

    for (int i = 0; i < 4; i++)
    {
        DrawBox(I_WatereObj[nowNum - 1].mini_pos.x + i, I_WatereObj[nowNum - 1].mini_pos.y + i,
            I_WatereObj[nowNum - 1].mini_rel_pos.x - i, I_WatereObj[nowNum - 1].mini_rel_pos.y - i, cr, false);
    }
}

void WaterSource::end(void)
{
    DeleteGraph(handle);
    DeleteSoundMem(decisionSH);
    DeleteSoundMem(jetSH);
}