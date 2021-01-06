// インクルード --------------------------------------------------------}--------------------------
#include "DxLib.h"

#include "bubble.h"
#include "input.h"
#include "goals.h"
#include "manage.h"
#include "map.h"
#include "stage_select.h"
#include "system.h"

// extern宣言,static初期化 ----------------------------------------------------------------------
extern PlBubbleObj I_PlBubbleObj[PL_BUBBLE_MAX];
extern GoalsObj    I_GoalsObj[GOALS_MAX];

// 関数 ----------------------------------------------------------------------------------------
void GoalsObj::init(GoalsObj* obj, float posX, float posY, int rateX, int rateY, int Num)
{
    obj->pos.set(posX, posY);
    obj->rel_pos.set(posX + (MAPCHIP_SIZE * rateX), posY + (MAPCHIP_SIZE * rateY));
    obj->num = Num;
    obj->src.set(0, 0);
    obj->exist = false;
    obj->clear = false;
}

void Goals::init(void)
{
    for (int i = 0; i < GOALS_MAX; i++)
    {
        I_GoalsObj[i].init(&I_GoalsObj[i], 0, 0, 0, 0, 0);
    }
    switch (M_Stage_Select.select)
    {
    case 1:
        maxNum = 2;
        //I_GoalsObj[0].init(&I_GoalsObj[0], 0,0, 0);
        //I_GoalsObj[1].init(&I_GoalsObj[1], 46 * 64, 64 ,0);
        I_GoalsObj[0].init(&I_GoalsObj[0], 8 * MAPCHIP_SIZE, 1 * MAPCHIP_SIZE, 3, 1, 4);
        I_GoalsObj[1].init(&I_GoalsObj[1], 18 * MAPCHIP_SIZE, 1 * MAPCHIP_SIZE, 3, 1, 3);
        break;
    case 2:
        maxNum = 1;
        I_GoalsObj[0].init(&I_GoalsObj[0], 2 * MAPCHIP_SIZE, 0 * MAPCHIP_SIZE, 2, 1, 8);
        break;
    case 3:
        maxNum = 1;
        I_GoalsObj[0].init(&I_GoalsObj[0], 24 * MAPCHIP_SIZE, 0 * MAPCHIP_SIZE, 4, 2, 9);
        break;
    case 4:
        maxNum = 3;
        I_GoalsObj[0].init(&I_GoalsObj[0], 6 * MAPCHIP_SIZE, 0 * MAPCHIP_SIZE, 2, 1, 3);
        I_GoalsObj[1].init(&I_GoalsObj[1], 14 * MAPCHIP_SIZE, 0 * MAPCHIP_SIZE, 2, 1, 4);
        I_GoalsObj[2].init(&I_GoalsObj[2], 22 * MAPCHIP_SIZE, 0 * MAPCHIP_SIZE, 2, 1, 3);
        break;
    case 6:
        maxNum = 3;
        I_GoalsObj[0].init(&I_GoalsObj[0], 6 * MAPCHIP_SIZE, 0 * MAPCHIP_SIZE, 2, 1, 3);
        I_GoalsObj[1].init(&I_GoalsObj[1], 14 * MAPCHIP_SIZE, 0 * MAPCHIP_SIZE, 2, 1, 4);
        I_GoalsObj[2].init(&I_GoalsObj[2], 22 * MAPCHIP_SIZE, 0 * MAPCHIP_SIZE, 2, 1, 3);
        break;
    default:
        maxNum = 1;
        break;
    }
    for (int i = 0; i < GOALS_MAX; ++i)
    {
        switch (I_GoalsObj[i].num)
        {
        case 1:
            I_GoalsObj[i].src.set(0, 0);
            break;
        case 2:
            I_GoalsObj[i].src.set(300, 0);
            break;
        case 3:
            I_GoalsObj[i].src.set(600, 0);
            break;
        case 4:
            I_GoalsObj[i].src.set(900, 0);
            break;
        case 5:
            I_GoalsObj[i].src.set(1200, 0);
            break;
        case 6:
            I_GoalsObj[i].src.set(1500, 0);
            break;
        case 7:
            I_GoalsObj[i].src.set(1800, 0);
            break;
        case 8:
            I_GoalsObj[i].src.set(2100, 0);
            break;
        case 9:
            I_GoalsObj[i].src.set(2400, 0);
            break;
        default:
            I_GoalsObj[i].src.set(0, 0);
            break;
        }
    }
    for (int i = 0; i < maxNum; i++)
    {
        I_GoalsObj[i].exist = true;
    }
    handle = LoadGraph("Data\\Images\\Sprite\\goals.png");
}

void Goals::update(void)
{
    //switch (I_GoalsObj[1].num)
    //{
    //case 1:
    //    I_GoalsObj[1].src.set(0, 0);
    //    break;
    //case 2:
    //    I_GoalsObj[1].src.set(300, 0);
    //    break;
    //case 3:
    //    I_GoalsObj[1].src.set(600, 0);
    //    break;
    //default:
    //    break;
    //}
    //switch (I_GoalsObj[2].num)
    //{
    //case 1:
    //    I_GoalsObj[2].src.set(0, 0);
    //    break;
    //case 2:
    //    I_GoalsObj[2].src.set(300, 0);
    //    break;
    //case 3:
    //    I_GoalsObj[2].src.set(600, 0);
    //    break;
    //default:
    //    break;
    //}
    for (int i = 0; i < PL_BUBBLE_MAX; i++)
    {
        if (I_PlBubbleObj[i].exist == false) continue;
        for (int j = 0; j < GOALS_MAX; j++)
        {
            if (I_GoalsObj[j].exist == false) continue;
            if (M_System.isCollCircleWithRect(I_PlBubbleObj[i].center, I_PlBubbleObj[i].radius, I_GoalsObj[j].pos, I_GoalsObj[j].rel_pos))
            {
                if (I_PlBubbleObj[i].level == I_GoalsObj[j].num) I_GoalsObj[j].clear = true;
            }
        }
    }
    switch (maxNum)
    {
    case 1:
        if (I_GoalsObj[0].clear == true) M_GameManager.clear = true;
        break;
    case 2:
        if (I_GoalsObj[0].clear == true &&
            I_GoalsObj[1].clear == true) M_GameManager.clear = true;
        break;
    case 3:
        if (I_GoalsObj[0].clear == true &&
            I_GoalsObj[1].clear == true &&
            I_GoalsObj[2].clear == true) M_GameManager.clear = true;
        break;
    default:
        break;
    }
}

//void Goals::draw(void)
//{
//    for (int i = 0; i < GOALS_MAX; i++)
//    {
//        if (I_GoalsObj[i].exist == false) continue;
//        DrawRectExtendGraph(I_GoalsObj[i].pos.x, I_GoalsObj[i].pos.y, I_GoalsObj[i].rel_pos.x, I_GoalsObj[i].rel_pos.y, I_GoalsObj[i].src.x, I_GoalsObj[i].src.y, 300, 300, handle, true);
//
//        if (I_GoalsObj[i].clear == true)
//        {
//            for (int j = 0; j < 7; ++j)
//            {
//                DrawCircle(I_GoalsObj[i].pos.x + (I_GoalsObj[i].rel_pos.x - I_GoalsObj[i].pos.x) / 2,
//                    I_GoalsObj[i].pos.y + (I_GoalsObj[i].rel_pos.y - I_GoalsObj[i].pos.y) / 2, 32 - j, GetColor(0, 200, 0), false);
//            }
//        }
//    }
//}

void Goals::draw(void)
{
    for (int i = 0; i < GOALS_MAX; i++)
    {
        if (I_GoalsObj[i].exist == false) continue;
        DrawRectExtendGraph(I_GoalsObj[i].pos.x - M_MapData.scrollPos.x, I_GoalsObj[i].pos.y - M_MapData.scrollPos.y,
            I_GoalsObj[i].rel_pos.x - M_MapData.scrollPos.x, I_GoalsObj[i].rel_pos.y - M_MapData.scrollPos.y, I_GoalsObj[i].src.x, I_GoalsObj[i].src.y, 300, 300, handle, true);

        if (I_GoalsObj[i].clear == true)
        {
            for (int j = 0; j < 7; ++j)
            {
                DrawCircle(I_GoalsObj[i].pos.x + (I_GoalsObj[i].rel_pos.x - I_GoalsObj[i].pos.x) / 2 - M_MapData.scrollPos.x,
                    I_GoalsObj[i].pos.y + (I_GoalsObj[i].rel_pos.y - I_GoalsObj[i].pos.y) / 2 - M_MapData.scrollPos.y, 32 - j, GetColor(0, 200, 0), false);
            }
        }
    }
}
void Goals::end(void)
{
    DeleteGraph(handle);
}