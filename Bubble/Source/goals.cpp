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
void GoalsObj::init(GoalsObj* obj, float chipX, float chipY, int rateX, int rateY, int Num)
{
    obj->pos.set(chipX * MAPCHIP_SIZE, chipY * MAPCHIP_SIZE);
    obj->rel_pos.set(pos.x + (MAPCHIP_SIZE * rateX), pos.y + (MAPCHIP_SIZE * rateY));
    obj->mini_pos.set(MINI_MAP_FIX + chipX * MAPCHIP_SIZE_MINI, 32 + chipY * MAPCHIP_SIZE_MINI);
    obj->mini_rel_pos.set(mini_pos.x + (MAPCHIP_SIZE_MINI * rateX), mini_pos.y + (MAPCHIP_SIZE_MINI * rateY));
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
        I_GoalsObj[0].init(&I_GoalsObj[0], 2, 0, 4, 2, 4);
        I_GoalsObj[1].init(&I_GoalsObj[1], 16, 0, 4, 2, 4);
        break;
    case 2:
        maxNum = 2;
        I_GoalsObj[0].init(&I_GoalsObj[0], 2, 2, 3, 1, 4);
        I_GoalsObj[1].init(&I_GoalsObj[1], 12, 15, 2, 1, 3);
        break;
    case 3:
        maxNum = 2;
        I_GoalsObj[0].init(&I_GoalsObj[0], 2, 2, 3, 1, 4);
        I_GoalsObj[1].init(&I_GoalsObj[1], 12, 15, 2, 1, 3);
        break;
    case 4:
        maxNum = 3;
        I_GoalsObj[0].init(&I_GoalsObj[0], 3, 0, 2, 1, 2);
        I_GoalsObj[1].init(&I_GoalsObj[1], 9, 0, 5, 1, 5);
        I_GoalsObj[2].init(&I_GoalsObj[2], 17, 0, 3, 1, 3);
        break;
    case 6:
        maxNum = 3;
        I_GoalsObj[0].init(&I_GoalsObj[0], 3, 0, 2, 1, 2);
        I_GoalsObj[1].init(&I_GoalsObj[1], 9, 0, 5, 1, 5);
        I_GoalsObj[2].init(&I_GoalsObj[2], 17, 0, 3, 1, 3);
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
    blackHND = LoadGraph("Data\\Images\\Sprite\\goals_black.png");
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
                if (I_PlBubbleObj[i].speed.y < 0)
                {
                    if (I_PlBubbleObj[i].level == I_GoalsObj[j].num)
                    {
                        I_PlBubbleObj[i].exist = false;
                        if (I_PlBubbleObj[i].exist == false)
                        {
                            I_GoalsObj[j].clear = true;

                        }
                    }
                }
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
    case 4:
        if (I_GoalsObj[0].clear == true &&
            I_GoalsObj[1].clear == true &&
            I_GoalsObj[2].clear == true &&
            I_GoalsObj[3].clear == true) M_GameManager.clear = true;
        break;
    case 5:
        if (I_GoalsObj[0].clear == true &&
            I_GoalsObj[1].clear == true &&
            I_GoalsObj[2].clear == true &&
            I_GoalsObj[3].clear == true &&
            I_GoalsObj[4].clear == true) M_GameManager.clear = true;
        break;
    case 6:
        if (I_GoalsObj[0].clear == true &&
            I_GoalsObj[1].clear == true &&
            I_GoalsObj[2].clear == true &&
            I_GoalsObj[3].clear == true &&
            I_GoalsObj[4].clear == true &&
            I_GoalsObj[5].clear == true) M_GameManager.clear = true;
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

        if (I_GoalsObj[i].clear == false)
        {
            DrawRectExtendGraph(I_GoalsObj[i].pos.x - M_MapData.scrollPos.x, I_GoalsObj[i].pos.y - M_MapData.scrollPos.y,
                I_GoalsObj[i].rel_pos.x - M_MapData.scrollPos.x, I_GoalsObj[i].rel_pos.y - M_MapData.scrollPos.y, I_GoalsObj[i].src.x, I_GoalsObj[i].src.y, 300, 300, handle, true);
        }
        else
        {
            DrawRectExtendGraph(I_GoalsObj[i].pos.x - M_MapData.scrollPos.x, I_GoalsObj[i].pos.y - M_MapData.scrollPos.y,
                I_GoalsObj[i].rel_pos.x - M_MapData.scrollPos.x, I_GoalsObj[i].rel_pos.y - M_MapData.scrollPos.y, I_GoalsObj[i].src.x, I_GoalsObj[i].src.y, 300, 300, blackHND, true);
        }

        // minimap
        if (I_GoalsObj[i].clear == false)
        {
            DrawRectExtendGraph(I_GoalsObj[i].mini_pos.x, I_GoalsObj[i].mini_pos.y,
                I_GoalsObj[i].mini_rel_pos.x, I_GoalsObj[i].mini_rel_pos.y, I_GoalsObj[i].src.x, I_GoalsObj[i].src.y, 300, 300, handle, true);
        }
        else
        {
            DrawRectExtendGraph(I_GoalsObj[i].mini_pos.x, I_GoalsObj[i].mini_pos.y,
                I_GoalsObj[i].mini_rel_pos.x, I_GoalsObj[i].mini_rel_pos.y, I_GoalsObj[i].src.x, I_GoalsObj[i].src.y, 300, 300, blackHND, true);
        }
    }
}

void Goals::end(void)
{
    DeleteGraph(handle);
    DeleteGraph(blackHND);
}