// インクルード ----------------------------------------------------------------------------------
#include "DxLib.h"

#include "common.h"
#include "file.h"
#include "goals.h"
#include "input.h"
#include "main.h"
#include "manage.h"
#include "map.h"
#include "system.h"

// extern宣言,static初期化 ----------------------------------------------------------------------
extern PlBubbleObj I_PlBubbleObj[PL_BUBBLE_MAX];
extern GoalsObj    I_GoalsObj[GOALS_MAX];

// 関数 ----------------------------------------------------------------------------------------
void MapData::init(void)
{
    pos.set(0, 0);
    rel_pos.set(0, 0);
    src.set(0, 0);
    width = 130;
    height = 130;
    handle = LoadGraph("Data\\Images\\Sprite\\MapChip.png");
    minimapHND = LoadGraph("Data\\Images\\Sprite\\minimap.png");
    divisionSH = LoadSoundMem("Data\\Sounds\\division.mp3");
    breakSH = LoadSoundMem("Data\\Sounds\\break.mp3");
    goals = LoadGraph("Data\\Images\\Sprite\\goals.png");
    M_MapData.setMapData();
    M_MapData.spawnBubble();
    scrollPos.set(0, 0);
}

void MapData::update(void)
{
    for (int i = 0; i < PL_BUBBLE_MAX; i++)
    {
        if (I_PlBubbleObj[i].exist == false) continue;

        M_MapData.collMapChipWithBubble(&I_PlBubbleObj[i]);
        M_MapData.collGoalsWithBubble(&I_PlBubbleObj[i]);
    }

#ifdef _DEBUG
    if (M_Input->GetKey(KEY_INPUT_A)) scrollPos.x -= 10;
    if (M_Input->GetKey(KEY_INPUT_D)) scrollPos.x += 10;
    if (M_Input->GetKey(KEY_INPUT_W)) scrollPos.y -= 10;
    if (M_Input->GetKey(KEY_INPUT_S)) scrollPos.y += 10;
#endif // _DEBUG

}

//void MapData::draw(void)
//{
//    for (int Ver = 0; Ver < MAPCHIP_V_MAX; Ver++)
//    {
//        for (int Hor = 0; Hor < MAPCHIP_H_MAX; Hor++)
//        {
//            //if (mapData[Ver][Hor] == GoalSpawner)
//            //{
//            //    src.set(0, 0);
//            //    DrawRectExtendGraph(MAPCHIP_SIZE * Hor, MAPCHIP_SIZE * Ver, MAPCHIP_SIZE * Hor + MAPCHIP_SIZE, MAPCHIP_SIZE * Ver + MAPCHIP_SIZE, src.x, src.y, 300, 300, goals, true);
//            //}
//            //else
//            {
//                switch (mapData[Ver][Hor])
//                {
//                case Void:          src.set(130 * 0, 130 * 0);  break;
//                case LFloor:        src.set(130 * 1, 130 * 0);  break;
//                case Floor:         src.set(130 * 2, 130 * 0);  break;
//                case RFloor:        src.set(130 * 3, 130 * 0);  break;
//                case Wall:          src.set(130 * 0, 130 * 1);  break;
//                case Lift:          src.set(130 * 1, 130 * 1);  break;
//                case Needle:        src.set(130 * 2, 130 * 1);  break;
//                case Splitter:      src.set(130 * 3, 130 * 1);  break;
//                case BubbleSpawner: src.set(130 * 0, 130 * 2);  break;
//                    //case GoalSpawner:   src.set(130 * 1, 130 * 2);  break;
//                    //case StartSource:   src.set(130 * 2, 130 * 2);  break;
//                    //case EndSource:     src.set(130 * 3, 130 * 2);  break;
//                default: src.set(0, 0);  break;
//                }
//                DrawRectExtendGraph(MAPCHIP_SIZE * Hor, MAPCHIP_SIZE * Ver, MAPCHIP_SIZE * Hor + MAPCHIP_SIZE, MAPCHIP_SIZE * Ver + MAPCHIP_SIZE, src.x, src.y, width, height, handle, true);
//            }
//        }
//    }
//}

void MapData::draw(void)
{
    for (int Ver = 0; Ver < MAPCHIP_V_MAX; Ver++)
    {
        for (int Hor = 0; Hor < MAPCHIP_H_MAX; Hor++)
        {
            //if (mapData[Ver][Hor] == GoalSpawner)
            //{
            //    src.set(0, 0);
            //    DrawRectExtendGraph(MAPCHIP_SIZE * Hor, MAPCHIP_SIZE * Ver, MAPCHIP_SIZE * Hor + MAPCHIP_SIZE, MAPCHIP_SIZE * Ver + MAPCHIP_SIZE, src.x, src.y, 300, 300, goals, true);
            //}
            //else
            {
                switch (mapData[Ver][Hor])
                {
                case Void:          src.set(130 * 0, 130 * 0);  break;
                case LFloor:        src.set(130 * 1, 130 * 0);  break;
                case Floor:         src.set(130 * 2, 130 * 0);  break;
                case RFloor:        src.set(130 * 3, 130 * 0);  break;
                case LFloor2:       src.set(130 * 0, 130 * 1);  break;
                case RFloor2:       src.set(130 * 1, 130 * 1);  break;
                case Needle:        src.set(130 * 2, 130 * 1);  break;
                case Splitter:      src.set(130 * 3, 130 * 1);  break;
                case BubbleSpawner: src.set(130 * 0, 130 * 2);  break;
                    //case GoalSpawner:   src.set(130 * 1, 130 * 2);  break;
                    //case StartSource:   src.set(130 * 2, 130 * 2);  break;
                    //case EndSource:     src.set(130 * 3, 130 * 2);  break;
                case ULCorner:      src.set(130 * 0, 130 * 3);  break;
                case URCorner:      src.set(130 * 1, 130 * 3);  break;
                case DLCorner:      src.set(130 * 2, 130 * 3);  break;
                case DRCorner:      src.set(130 * 3, 130 * 3);  break;
                case UFloor:        src.set(130 * 0, 130 * 4);  break;
                case DFloor:        src.set(130 * 1, 130 * 4);  break;
                case NOFloor:       src.set(130 * 2, 130 * 4);  break;
                default: src.set(0, 0);  break;
                }
                DrawRectExtendGraph(MAPCHIP_SIZE * Hor - scrollPos.x, MAPCHIP_SIZE * Ver - scrollPos.y,
                    MAPCHIP_SIZE * Hor + MAPCHIP_SIZE - scrollPos.x, MAPCHIP_SIZE * Ver + MAPCHIP_SIZE - scrollPos.y, src.x, src.y, width, height, handle, true);

                // minimap
                DrawRectExtendGraph(MINI_MAP_FIX + MAPCHIP_SIZE_MINI * Hor, 32 + MAPCHIP_SIZE_MINI * Ver,
                    MINI_MAP_FIX + MAPCHIP_SIZE_MINI * Hor + MAPCHIP_SIZE_MINI, 32 + MAPCHIP_SIZE_MINI * Ver + MAPCHIP_SIZE_MINI, src.x, src.y, width, height, handle, true);
            }
        }
    }

    DrawGraph(MINI_MAP_FIX - 10, 32 - 10, minimapHND, true);
}

void MapData::end(void)
{
    DeleteGraph(handle);
    DeleteGraph(goals);
    DeleteGraph(minimapHND);
    DeleteSoundMem(divisionSH);
    DeleteSoundMem(breakSH);
}

void MapData::setMapData(void)
{
    M_File.loadMap();
}

void MapData::spawnBubble(void)
{
    for (int Ver = 0; Ver < MAPCHIP_V_MAX; Ver++)
    {
        for (int Hor = 0; Hor < MAPCHIP_H_MAX; Hor++)
        {
            if (mapData[Ver][Hor] == BubbleSpawner)
            {
                for (int i = 0; i < PL_BUBBLE_MAX; i++)
                {
                    if (I_PlBubbleObj[i].exist == true) continue;
                    I_PlBubbleObj[i].init(&I_PlBubbleObj[i], MAPCHIP_SIZE * Hor + MAPCHIP_SIZE / 2 - I_PlBubbleObj[i].radius - scrollPos.x, MAPCHIP_SIZE * Ver - I_PlBubbleObj[i].radius * 2 - scrollPos.y);
                    I_PlBubbleObj[i].exist = true;
                    break;
                }
            }
        }
    }
}

void MapData::collMapChipWithBubble(PlBubbleObj* obj)
{
    //チップ当たり判定処理
    for (int Ver = 0; Ver < MAPCHIP_V_MAX; Ver++)
    {
        for (int Hor = 0; Hor < MAPCHIP_H_MAX; Hor++)
        {
            int chipLeft;
            int chipRight;
            int chipTop;
            int chipBottom;
            int bubbleCollLeft;
            int bubbleCollRight;
            int bubbleCollTop;
            int bubbleCollBottom;
            pos.set(MAPCHIP_SIZE * Hor, MAPCHIP_SIZE * Ver);
            rel_pos.set(pos.x + MAPCHIP_SIZE, pos.y + MAPCHIP_SIZE);

            // 押し出し判定
            if (mapData[Ver][Hor] > 0)
            {
                //マップチップ4点座標
                chipLeft = Hor * MAPCHIP_SIZE;
                chipRight = (Hor + 1) * MAPCHIP_SIZE;
                chipTop = Ver * MAPCHIP_SIZE;
                chipBottom = (Ver + 1) * MAPCHIP_SIZE;
                //泡当たり判定部4点座標
                bubbleCollLeft = obj->pos.x;
                bubbleCollRight = obj->pos.x + obj->radius * 2;
                bubbleCollTop = obj->pos.y;
                bubbleCollBottom = obj->pos.y + obj->radius * 2;

                if (bubbleCollLeft + 5 < chipRight && bubbleCollRight - 5 > chipLeft&& bubbleCollTop < chipBottom && bubbleCollBottom > chipTop)
                {
                    //縦方向の押し戻し
                    if (obj->speed.y != 0)
                    {
                        if (obj->speed.y > 0)
                        {
                            if (bubbleCollLeft + 15 < chipRight && bubbleCollRight - 15 > chipLeft&& bubbleCollTop + 15 < chipBottom && bubbleCollBottom > chipTop)
                            {
                                //判定のあったチップの上方向にチップが存在しなければ処理を行う
                                if (mapData[Ver - 1][Hor] == 0 && Ver != 0)
                                {
                                    obj->pos.y = chipTop - obj->radius * 2;
                                    obj->speed.y = 0;
                                }
                            }
                        }
                        if (obj->speed.y < 0)
                        {
                            if (bubbleCollLeft + 15 < chipRight && bubbleCollRight - 15 > chipLeft&& bubbleCollTop < chipBottom && bubbleCollBottom - 15 > chipTop)
                            {
                                //判定のあったチップの下方向にチップが存在しなければ処理を行う
                                if (mapData[Ver + 1][Hor] == 0 && Ver != (MAPCHIP_V_MAX - 1))
                                {
                                    obj->pos.y = chipBottom;
                                    obj->speed.y = 0;
                                }
                            }
                        }
                    }
                }
                //押し戻し後の泡座標を再取得
                bubbleCollLeft = obj->pos.x;
                bubbleCollRight = obj->pos.x + obj->radius * 2;
                bubbleCollTop = obj->pos.y;
                bubbleCollBottom = obj->pos.y + obj->radius * 2;

                if (bubbleCollLeft < chipRight && bubbleCollRight > chipLeft&& bubbleCollTop + 15 < chipBottom && bubbleCollBottom - 15 > chipTop)
                {
                    //横方向の押し戻し処理
                    if (obj->speed.x != 0)
                    {
                        if (obj->speed.x > 0)
                        {
                            //判定のあったチップの左方向にチップが存在しなければ処理を行う
                            if (mapData[Ver][Hor - 1] == 0 && Hor != 0)
                            {
                                obj->pos.x = chipLeft - obj->radius * 2;
                            }
                        }
                        if (obj->speed.x < 0)
                        {
                            //判定のあったチップの右方向にチップが存在しなければ処理を行う
                            if (mapData[Ver][Hor + 1] == 0 && Hor != (MAPCHIP_H_MAX - 1))
                            {
                                obj->pos.x = chipRight;
                            }
                        }
                    }
                }
                //押し戻し後の泡座標を再取得
                bubbleCollLeft = obj->pos.x;
                bubbleCollRight = obj->pos.x + obj->radius * 2;
                bubbleCollTop = obj->pos.y;
                bubbleCollBottom = obj->pos.y + obj->radius * 2;

                //接地判定
                if (bubbleCollBottom == chipTop && bubbleCollRight > chipLeft&& bubbleCollLeft < chipRight)
                {
                    obj->touchFloor = true;
                }
            }
            if (M_System.isCollCircleWithRect(obj->center, obj->radius, pos, rel_pos))
            {
                switch (mapData[Ver][Hor])
                {
                    // 針
                case Needle:
                    PlaySoundMem(breakSH, DX_PLAYTYPE_BACK, true);

                    obj->exist = false;
                    break;
                    // 分裂
                case Splitter:
                    PlaySoundMem(divisionSH, DX_PLAYTYPE_BACK, true);

                    obj->pos.y -= MAPCHIP_SIZE + obj->radius * 3;

                    if (obj->level > 1)
                    {
                        obj->pos.x -= MAPCHIP_SIZE / 2 - 10;
                        obj->speed.x = -2;
                        obj->level -= 1;

                        for (int i = 0; i < PL_BUBBLE_MAX; i++)
                        {
                            if (I_PlBubbleObj[i].exist == true) continue;
                            I_PlBubbleObj[i].init(&I_PlBubbleObj[i], obj->pos.x + MAPCHIP_SIZE * 2, obj->pos.y);
                            I_PlBubbleObj[i].speed.x = 2;
                            I_PlBubbleObj[i].exist = true;
                            I_PlBubbleObj[i].level = obj->level;
                            break;
                        }
                    }
                    break;
                    // ゴール
                //case GoalSpawner:
                //    for (int i = 0; i < PL_BUBBLE_MAX; i++)
                //    {
                //        for (int j = 0; j < GOALS_MAX; j++)
                //        {
                //            if (I_PlBubbleObj[i].exist == true) continue;
                //            if (I_PlBubbleObj[i].level > I_GoalsObj[j].num)
                //                M_GameManager.clear = true;
                //            break;
                //        }
                //    }
                //    break;
                //case SubGoal:
                //    for (int i = 0; i < PL_BUBBLE_MAX; i++)
                //    {
                //        for (int j = 0; j < GOALS_MAX; j++)
                //        {
                //            if (I_PlBubbleObj[i].exist == true) continue;
                //            if (I_PlBubbleObj[i].level > I_GoalsObj[j].num)
                //                M_GameManager.clear = true;
                //            break;
                //        } 
                //    }
                //    break;
                default:
                    break;
                }
            }
            // 水流
            if (mapData[Ver][Hor] == StartSource)
            {

            }
        }
    }
}

void MapData::collGoalsWithBubble(PlBubbleObj* obj)
{
    int goalLeft;
    int goalRight;
    int goalTop;
    int goalBottom;
    int bubbleCollLeft;
    int bubbleCollRight;
    int bubbleCollTop;
    int bubbleCollBottom;

    //泡当たり判定部4点座標
    bubbleCollLeft = obj->pos.x;
    bubbleCollRight = obj->pos.x + obj->radius * 2;
    bubbleCollTop = obj->pos.y;
    bubbleCollBottom = obj->pos.y + obj->radius * 2;
    for (int i = 0; i < GOALS_MAX; i++)
    {
        if (I_GoalsObj[i].exist == false) continue;
        if (I_GoalsObj[i].clear == true) continue;
        //ゴール4点座標
        goalLeft = I_GoalsObj[i].pos.x;
        goalRight = I_GoalsObj[i].rel_pos.x;
        goalTop = I_GoalsObj[i].pos.y;
        goalBottom = I_GoalsObj[i].rel_pos.y;

        if (goalLeft <= bubbleCollRight && bubbleCollLeft <= goalRight && goalTop <= bubbleCollBottom && bubbleCollTop <= goalBottom)
        {
            if (obj->level >= I_GoalsObj[i].num)
            {
                PlaySoundMem(M_TitleManager.decisionSH, DX_PLAYTYPE_BACK, true);

                I_GoalsObj[i].clear = true;
                obj->exist = false;
            }
        }
    }
}