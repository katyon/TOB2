// インクルード ----------------------------------------------------------------------------------
#include "DxLib.h"

#include "bubble.h"
#include "common.h"
#include "input.h"
#include "main.h"
#include "system.h"

// extern宣言,static初期化 ----------------------------------------------------------------------
extern PlBubbleObj I_PlBubbleObj[PL_BUBBLE_MAX];

// 関数 ----------------------------------------------------------------------------------------
void PlBubbleObj::init(PlBubbleObj* obj, float posX, float posY)
{
    obj->pos.set(posX, posY);
    obj->level = 1;
    obj->radius = obj->level * 8 + 8;
    obj->rel_pos.set(obj->pos.x + obj->radius * 2, obj->pos.y + obj->radius * 2);
    obj->center.set(obj->pos.x + obj->radius, obj->pos.y + obj->radius);
    obj->speed.set(0, 0);
    obj->exist = false;
    obj->touchFloor = false;
    obj->touchBubble = false;
}

void PlBubble::init(void)
{
    handle = LoadGraph("Data\\Images\\Sprite\\plBubble.png");
    integrationSH = LoadSoundMem("Data\\Sounds\\integration.mp3");
    for (int i = 0; i < PL_BUBBLE_MAX; i++)
    {
        I_PlBubbleObj[i].init(&I_PlBubbleObj[i], 0, 0);
    }
}

void PlBubble::update(void)
{
    //M_Bubble.inputDebugKey();
    for (int i = 0; i < PL_BUBBLE_MAX; i++)
    {
        if (I_PlBubbleObj[i].exist == false) continue;

        M_Bubble.move(&I_PlBubbleObj[i]);
        M_Bubble.fix(&I_PlBubbleObj[i]);
    }
    M_Bubble.collAnotherBubble();
}

void PlBubble::draw(void)
{
    for (int i = 0; i < PL_BUBBLE_MAX; i++)
    {
        if (I_PlBubbleObj[i].exist == false) continue;

        DrawExtendGraphF(I_PlBubbleObj[i].pos.x, I_PlBubbleObj[i].pos.y, I_PlBubbleObj[i].rel_pos.x, I_PlBubbleObj[i].rel_pos.y, handle, true);
    }
}

void PlBubble::end(void)
{
    DeleteGraph(handle);
    DeleteSoundMem(integrationSH);
}

void PlBubble::move(PlBubbleObj* obj)
{
    // 浮力
    obj->speed.y -= BUOYANCY;
    // 減速
    if (obj->speed.x > 0.2) obj->speed.x -= BUBBLE_DECEL;
    if (obj->speed.x < -0.2) obj->speed.x += BUBBLE_DECEL;
    if (obj->speed.y > 0.2) obj->speed.y -= BUBBLE_DECEL;
    if (obj->speed.y < -0.2) obj->speed.y += BUBBLE_DECEL;
    if (obj->speed.x < 0.2 && obj->speed.x > -0.2) obj->speed.x = 0;
    if (obj->speed.y < 0.2 && obj->speed.y > -0.2) obj->speed.y = 0;
}

void PlBubble::fix(PlBubbleObj* obj)
{
    // 速度制限
    if (obj->speed.x > BUBBLE_SPEED_MAX) obj->speed.x = BUBBLE_SPEED_MAX;
    if (obj->speed.x < -BUBBLE_SPEED_MAX) obj->speed.x = -BUBBLE_SPEED_MAX;
    if (obj->speed.y > BUBBLE_SPEED_MAX) obj->speed.y = BUBBLE_SPEED_MAX;
    if (obj->speed.y < -BUBBLE_SPEED_MAX) obj->speed.y = -BUBBLE_SPEED_MAX;
    // サイズ変換
    obj->radius = obj->level * 8 + 8;
    // 座標変換
    obj->pos.x += obj->speed.x;
    obj->pos.y += obj->speed.y;
    obj->rel_pos.set(obj->pos.x + obj->radius * 2, obj->pos.y + obj->radius * 2);
    obj->center.set(obj->pos.x + obj->radius, obj->pos.y + obj->radius);
}

void PlBubble::collAnotherBubble(void)
{
    for (int i = 0; i < PL_BUBBLE_MAX; i++)
    {
        if (I_PlBubbleObj[i].exist == false) continue;

        I_PlBubbleObj[i].touchBubble = false;
    }

    for (int i = 0; i < PL_BUBBLE_MAX; i++)
    {
        if (I_PlBubbleObj[i].exist == false) continue;

        for (int j = i + 1; j < PL_BUBBLE_MAX; j++)
        {
            if (I_PlBubbleObj[j].exist == false) continue;

            if (M_System.isCollCircle(I_PlBubbleObj[i].center, I_PlBubbleObj[i].radius, I_PlBubbleObj[j].center, I_PlBubbleObj[j].radius))
            {
                PlaySoundMem(integrationSH, DX_PLAYTYPE_BACK, true);

                if (I_PlBubbleObj[i].pos.x > I_PlBubbleObj[j].pos.x) I_PlBubbleObj[i].pos.x -= I_PlBubbleObj[i].radius;
                else I_PlBubbleObj[i].pos.x += I_PlBubbleObj[i].radius;
                I_PlBubbleObj[i].speed.y += (I_PlBubbleObj[i].radius + I_PlBubbleObj[j].radius) / 8;
                I_PlBubbleObj[i].touchBubble = true;
                I_PlBubbleObj[i].level += I_PlBubbleObj[j].level;
                I_PlBubbleObj[j].exist = false;
            }
        }
    }
}

void PlBubble::inputDebugKey(void)
{
    if (M_Input->GetKey(KEY_INPUT_Z))
    {
        I_PlBubbleObj[0].init(&I_PlBubbleObj[0], 100, 600);
        I_PlBubbleObj[0].exist = true;
    }
    if (M_Input->GetKey(KEY_INPUT_X))
    {
        I_PlBubbleObj[1].init(&I_PlBubbleObj[1], 200, 600);
        I_PlBubbleObj[1].exist = true;
    }
    if (M_Input->GetKey(KEY_INPUT_C))
    {
        I_PlBubbleObj[2].init(&I_PlBubbleObj[2], 300, 600);
        I_PlBubbleObj[2].exist = true;
    }
    if (M_Input->GetKey(KEY_INPUT_V))
    {
        I_PlBubbleObj[3].init(&I_PlBubbleObj[3], 400, 600);
        I_PlBubbleObj[3].exist = true;
    }

    //if (M_Input->GetKey(KEY_INPUT_LEFT))    I_PlBubbleObj[0].speed.x -= BUBBLE_ACCEL;
    //if (M_Input->GetKey(KEY_INPUT_RIGHT))   I_PlBubbleObj[0].speed.x += BUBBLE_ACCEL;
    //if (M_Input->GetKey(KEY_INPUT_UP))      I_PlBubbleObj[0].speed.y -= BUBBLE_ACCEL;
    //if (M_Input->GetKey(KEY_INPUT_DOWN))    I_PlBubbleObj[0].speed.y += BUBBLE_ACCEL;

    //if (M_Input->GetKey(KEY_INPUT_A))   I_PlBubbleObj[1].speed.x -= BUBBLE_ACCEL;
    //if (M_Input->GetKey(KEY_INPUT_D))   I_PlBubbleObj[1].speed.x += BUBBLE_ACCEL;
    //if (M_Input->GetKey(KEY_INPUT_W))   I_PlBubbleObj[1].speed.y -= BUBBLE_ACCEL;
    //if (M_Input->GetKey(KEY_INPUT_S))   I_PlBubbleObj[1].speed.y += BUBBLE_ACCEL;

    //if (M_Input->GetKey(KEY_INPUT_F))   I_PlBubbleObj[2].speed.x -= BUBBLE_ACCEL;
    //if (M_Input->GetKey(KEY_INPUT_H))   I_PlBubbleObj[2].speed.x += BUBBLE_ACCEL;
    //if (M_Input->GetKey(KEY_INPUT_T))   I_PlBubbleObj[2].speed.y -= BUBBLE_ACCEL;
    //if (M_Input->GetKey(KEY_INPUT_G))   I_PlBubbleObj[2].speed.y += BUBBLE_ACCEL;

    //if (M_Input->GetKey(KEY_INPUT_J))   I_PlBubbleObj[3].speed.x -= BUBBLE_ACCEL;
    //if (M_Input->GetKey(KEY_INPUT_L))   I_PlBubbleObj[3].speed.x += BUBBLE_ACCEL;
    //if (M_Input->GetKey(KEY_INPUT_I))   I_PlBubbleObj[3].speed.y -= BUBBLE_ACCEL;
    //if (M_Input->GetKey(KEY_INPUT_K))   I_PlBubbleObj[3].speed.y += BUBBLE_ACCEL;
}