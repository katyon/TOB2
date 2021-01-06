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
void WaterObj::init(WaterObj* obj, float posY, float rel_posY)
{
    obj->pos.set(0, posY);
    obj->rel_pos.set(MAPCHIP_SIZE * MAPCHIP_H_MAX, rel_posY);
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
        maxNum = 6;
        I_WatereObj[0].init(&I_WatereObj[0], MAPCHIP_SIZE * 2 - MAPCHIP_SIZE, MAPCHIP_SIZE * 5);
        I_WatereObj[1].init(&I_WatereObj[1], MAPCHIP_SIZE * 7 - MAPCHIP_SIZE, MAPCHIP_SIZE * 9);
        I_WatereObj[2].init(&I_WatereObj[2], MAPCHIP_SIZE * 12 - MAPCHIP_SIZE, MAPCHIP_SIZE * 13);
        I_WatereObj[3].init(&I_WatereObj[3], MAPCHIP_SIZE * 19 - MAPCHIP_SIZE, MAPCHIP_SIZE * 22);
        I_WatereObj[4].init(&I_WatereObj[4], MAPCHIP_SIZE * 25 - MAPCHIP_SIZE, MAPCHIP_SIZE * 27);
        I_WatereObj[5].init(&I_WatereObj[5], MAPCHIP_SIZE * 29 - MAPCHIP_SIZE, MAPCHIP_SIZE * 31);
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
    for (int i = 0; i < maxNum; i++)
    {
        DrawExtendGraphF(I_WatereObj[i].pos.x + 128 - M_MapData.scrollPos.x, I_WatereObj[i].pos.y - M_MapData.scrollPos.y,
            I_WatereObj[i].pos.x - M_MapData.scrollPos.x, I_WatereObj[i].rel_pos.y - M_MapData.scrollPos.y, handle, true);
        DrawExtendGraphF(I_WatereObj[i].rel_pos.x - 128 - M_MapData.scrollPos.x, I_WatereObj[i].pos.y - M_MapData.scrollPos.y,
            I_WatereObj[i].rel_pos.x - M_MapData.scrollPos.x, I_WatereObj[i].rel_pos.y - M_MapData.scrollPos.y, handle, true);
    }

    for (int i = 0; i < 10; i++)
    {
        DrawBox(I_WatereObj[nowNum - 1].pos.x - M_MapData.scrollPos.x + i, I_WatereObj[nowNum - 1].pos.y - M_MapData.scrollPos.y + i,
            I_WatereObj[nowNum - 1].rel_pos.x - M_MapData.scrollPos.x - i, I_WatereObj[nowNum - 1].rel_pos.y - M_MapData.scrollPos.y - i, cr, false);
    }
}

void WaterSource::end(void)
{
    DeleteGraph(handle);
    DeleteSoundMem(decisionSH);
    DeleteSoundMem(jetSH);
}