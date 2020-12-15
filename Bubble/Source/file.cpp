#define _CRT_SECURE_NO_WARNINGS

#include "DxLib.h"
#include <stdio.h>

#include "file.h"
#include "editor.h"
#include "map.h"

// マップデータの読み込み
void File::loadMap(void)
{
    FILE* fp = 0;
    switch (M_Stage_Select.select - 1)
    {
    case Stage1:
        fp = fopen("Data\\Stages\\stage1.txt", "rt");
        break;
    case Stage2:
        fp = fopen("Data\\Stages\\stage2.txt", "rt");
        break;
    case Stage3:
        fp = fopen("Data\\Stages\\stage3.txt", "rt");
        break;
    case Stage4:
        fp = fopen("Data\\Stages\\stage4.txt", "rt");
        break;
    case Stage5:
        fp = fopen("Data\\Stages\\stage5.txt", "rt");
        break;
    case Stage6:
        fp = fopen("Data\\Stages\\stage6.txt", "rt");
        break;
    default:
        fp = 0;
        break;
    }
    if (fp == NULL)
    {
        DrawString(0, 0, "ファイルオープンエラー\n\a", GetColor(255, 255, 255));
    }

    for (int y = 0; y < MAPCHIP_V_MAX; y++)
    {
        for (int x = 0; x < MAPCHIP_H_MAX; x++)
        {
            fscanf(fp, "%d", &M_MapData.mapData[y][x]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

// エディターのマップデータの読み込み
void File::loadMapEditor(void)
{
    FILE* fp = 0;
    switch (M_Editor.stageNum)
    {
    case Stage1:
        fp = fopen("Data\\Stages\\stage1.txt", "rt");
        break;
    case Stage2:
        fp = fopen("Data\\Stages\\stage2.txt", "rt");
        break;
    case Stage3:
        fp = fopen("Data\\Stages\\stage3.txt", "rt");
        break;
    case Stage4:
        fp = fopen("Data\\Stages\\stage4.txt", "rt");
        break;
    case Stage5:
        fp = fopen("Data\\Stages\\stage5.txt", "rt");
        break;
    case Stage6:
        fp = fopen("Data\\Stages\\stage6.txt", "rt");
        break;
    default:
        fp = 0;
        break;
    }
    if (fp == NULL)
    {
        DrawString(0, 0, "ファイルオープンエラー\n\a", GetColor(255, 255, 255));
    }

    for (int y = 0; y < MAPCHIP_V_MAX; y++)
    {
        for (int x = 0; x < MAPCHIP_H_MAX; x++)
        {
            fscanf(fp, "%d", &M_Editor.map[y][x]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

// エディターのマップデータをファイルに保存
void File::saveMapEditor(void)
{
    FILE* fp = 0;
    switch (M_Editor.stageNum)
    {
    case Stage1:
        fp = fopen("Data\\Stages\\stage1.txt", "wt");
        break;
    case Stage2:
        fp = fopen("Data\\Stages\\stage2.txt", "wt");
        break;
    case Stage3:
        fp = fopen("Data\\Stages\\stage3.txt", "wt");
        break;
    case Stage4:
        fp = fopen("Data\\Stages\\stage4.txt", "wt");
        break;
    case Stage5:
        fp = fopen("Data\\Stages\\stage5.txt", "wt");
        break;
    case Stage6:
        fp = fopen("Data\\Stages\\stage6.txt", "wt");
        break;
    }
    if (fp == NULL)
    {
        DrawString(0, 0, "ファイルオープンエラー\n\a", GetColor(255, 255, 255));
    }

    for (int y = 0; y < MAPCHIP_V_MAX; y++)
    {
        for (int x = 0; x < MAPCHIP_H_MAX; x++)
        {
            fprintf(fp, "%3d", M_Editor.map[y][x]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}