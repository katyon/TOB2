#include "water_current.h"
#include "main.h"
#include "manage.h"
#include "map.h"
#include "input.h"
#include "waterSource.h"
#include "stage_select.h"
// extern -----------------------
extern WaterObj I_WatereObj[SOURCE_MAX];

// ä÷êîÅ@------------------------

// init ------------------------
void Water_Current::init()
{
    handle = LoadGraph("Data\\Images\\Sprite\\bubble.png");
    range = 0;
    Éø = 0;

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
            Éø += 2;
        }
        if (M_Input->GetKey(KEY_INPUT_RIGHT))
        {
            pos_x[i] += 8;
            Éø += 2;
        }
        if (Éø > 150) { Éø = 150; }
        if (Éø > 0) { Éø -= 1; }
        if (pos_x[i] < 0.0) { pos_x[i] = MAPCHIP_SIZE * 21; }
        if (pos_x[i] > MAPCHIP_SIZE * 21) { pos_x[i] = 0.0; }
    }
    if (M_Input->GetKeyDown(KEY_INPUT_UP)) { range--; Éø = 0; }
    if (M_Input->GetKeyDown(KEY_INPUT_DOWN)) { range++; Éø = 0; }
    switch (M_Stage_Select.select)
    {
    case 1:
        if (range > 5) { range = 5; }
        if (range < 0) { range = 0; }
        break;
    case 2:
        if (range > 6) { range = 6; }
        if (range < 0) { range = 0; }
        break;
    case 3:
        if (range > 2) { range = 2; }
        if (range < 0) { range = 0; }
        break;
    case 4:
        if (range > 2) { range = 2; }
        if (range < 0) { range = 0; }
        break;
    case 5:
        if (range > 2) { range = 2; }
        if (range < 0) { range = 0; }
        break;
    case 6:
        if (range > 5) { range = 5; }
        if (range < 0) { range = 0; }
        break;
    case 7:
        if (range > 6) { range = 6; }
        if (range < 0) { range = 0; }
        break;
    }
}


// draw -------------------------
void Water_Current::draw()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, Éø);
    switch (M_Stage_Select.select)
    {
    case 1:
        for (int i = 0; i < EFFECT_BUBBLE_MAX; i++)
        {
            if (range == 0) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 3 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 1) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 8 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 2) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 12 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 3) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 16 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 4) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 21 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 5) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 27 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
        }
        break;
    case 2:
        for (int i = 0; i < EFFECT_BUBBLE_MAX; i++)
        {
            if (range == 0) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 2 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 1) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 6 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 2) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 10 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 3) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 15 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 4) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 19 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 5) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 23 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 6) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 28 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
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
            if (range == 0) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 1 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 1) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 6 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 2) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 11 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 3) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 18 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 4) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 24 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 5) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 28 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
        }
        break;
    case 5:
        for (int i = 0; i < EFFECT_BUBBLE_MAX; i++)
        {
            if (range == 0) { DrawRectRotaGraph2F(pos_x[i], pos_y[i] + 64, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 1) { DrawRectRotaGraph2F(pos_x[i], pos_y[i] + 384, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 2) { DrawRectRotaGraph2F(pos_x[i], pos_y[i] + 832, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
        }
        break;
    case 6:
        for (int i = 0; i < EFFECT_BUBBLE_MAX; i++)
        {
            if (range == 0) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 1 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 1) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 6 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 2) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 11 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 3) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 18 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 4) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 24 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
            if (range == 5) { DrawRectRotaGraph2F(pos_x[i] - M_MapData.scrollPos.x, pos_y[i] - M_MapData.scrollPos.y + 28 * MAPCHIP_SIZE, 0, 0, 300, 300, 150, 150, 0.05, 0, handle, true, 0, 0); }
        }
        break;
    default:
        break;
    }
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}


// end --------------------------
void Water_Current::end()
{
    DeleteGraph(handle);
}