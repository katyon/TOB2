#include "water_current.h"
#include "main.h"
#include "manage.h"
#include "input.h"
#include "waterSource.h"
#include "stage_select.h"
// extern -----------------------
extern WaterObj I_WatereObj[SOURCE_MAX];

// ŠÖ”@------------------------

// init ------------------------
void Water_Current::init()
{
    handle = LoadGraph("Data\\Images\\Sprite\\bubble.png");
    range  = 0;
    ƒ¿ = 0;

    for (int i = 0; i < EFFECT_BUBBLE_MAX; i++)
    {
        pos_x[i] = i * 100;
    }
    for (int i = 0; i < EFFECT_BUBBLE_MAX; i++)
    {
        pos_y[i] = GetRand(20) * 10;
    }
}


// update -----------------------
void Water_Current::update()
{
    for (int i = 0; i < EFFECT_BUBBLE_MAX; i++)
    {
        if (M_Input->GetKey(KEY_INPUT_LEFT))
        {
            pos_x[i] -= 8;
            ƒ¿ += 2;
        }
        if (M_Input->GetKey(KEY_INPUT_RIGHT))
        {
            pos_x[i] += 8;
            ƒ¿ += 2;
        }
        if (ƒ¿ > 150 ) { ƒ¿ = 150; }
        if (ƒ¿ > 0) { ƒ¿ -= 1; }
        if (pos_x[i] < 0.0) { pos_x[i] = 1920.0; }
        if (pos_x[i] > 1920.0) { pos_x[i] = 0.0; }
    }
    if (M_Input->GetKeyDown(KEY_INPUT_UP)) { range--; ƒ¿ = 0; }
    if (M_Input->GetKeyDown(KEY_INPUT_DOWN)) { range++; ƒ¿ = 0; }
    switch (M_Stage_Select.select)
    {
    case 1:
        if (range > 2) { range = 2; }
        if (range < 0) { range = 0; }
        break;
    case 2:
        if (range > 3) { range = 3; }
        if (range < 0) { range = 0; }
        break;
    case 3:
        if (range > 2) { range = 2; }
        if (range < 0) { range = 0; }
        break;
    case 4:
        if (range > 2) { range = 2; }
        if (range < 0) { range = 0; }
    }
}


// draw -------------------------
void Water_Current::draw()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, ƒ¿);
    switch (M_Stage_Select.select)
    {
    case 1:
        for (int i = 0; i < EFFECT_BUBBLE_MAX; i++)
        {
            if (range == 0) { DrawRectRotaGraph2F(pos_x[i], pos_y[i] + 128, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 1) { DrawRectRotaGraph2F(pos_x[i], pos_y[i] + 448, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 2) { DrawRectRotaGraph2F(pos_x[i], pos_y[i] + 704, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
        }
        break;
    case 2:
        for (int i = 0; i < EFFECT_BUBBLE_MAX; i++)
        {
            if (range == 0) { DrawRectRotaGraph2F(pos_x[i], pos_y[i] +  64, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 1) { DrawRectRotaGraph2F(pos_x[i], pos_y[i] + 320, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 2) { DrawRectRotaGraph2F(pos_x[i], pos_y[i] + 576, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 3) { DrawRectRotaGraph2F(pos_x[i], pos_y[i] + 832, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
        }
        break;
    case 3:
        for (int i = 0; i < EFFECT_BUBBLE_MAX; i++)
        {
            if (range == 0) { DrawRectRotaGraph2F(pos_x[i], pos_y[i] + 128, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 1) { DrawRectRotaGraph2F(pos_x[i], pos_y[i] + 448, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 2) { DrawRectRotaGraph2F(pos_x[i], pos_y[i] + 704, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
        }
        break;
    case 4:
        for (int i = 0; i < EFFECT_BUBBLE_MAX; i++)
        {
            if (range == 0) { DrawRectRotaGraph2F(pos_x[i], pos_y[i] +  64, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 1) { DrawRectRotaGraph2F(pos_x[i], pos_y[i] + 384, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 2) { DrawRectRotaGraph2F(pos_x[i], pos_y[i] + 832, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
        }
        break;
    }
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}


// end --------------------------
void Water_Current::end()
{
    DeleteGraph(handle);
}