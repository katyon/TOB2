#pragma once
#include "bubble.h"
#include "common.h"
#include "singleton.h"
// 定数 ----------------------------------------------------------------
#define		MAPCHIP_H_MAX		(22)
#define		MAPCHIP_V_MAX		(34)
//#define		MAPCHIP_H_MAX		(30)
//#define		MAPCHIP_V_MAX		(17)
#define		MAPCHIP_SIZE		(64)
#define		MAPCHIP_SIZE_MINI	(20) // 0.3125
#define     MINI_MAP_FIX        (MAPCHIP_SIZE * 22 + 32)

enum ChipData
{
    Void, LFloor, Floor, RFloor,
    LFloor2, RFloor2, Needle, Splitter,
    BubbleSpawner, GoalSpawner,
    StartSource, EndSource,
    ULCorner, URCorner, DLCorner, DRCorner,
    UFloor, DFloor, NOFloor
};
// クラス --------------------------------------------------------------
#define M_MapData MapData::getInstance()
class MapData :public Sprite, public Singleton<MapData>
{
public:
    void init(void);
    void update(void);
    void draw(void);
    void end(void);
    void setMapData(void);
    void spawnBubble(void);
    void collMapChipWithBubble(PlBubbleObj* obj);
    void collGoalsWithBubble(PlBubbleObj* obj);

    int mapData[MAPCHIP_V_MAX][MAPCHIP_H_MAX] = { 0 };

    vec2i scrollPos;
private:
    int minimapHND;
    int bubbleHND;
    int divisionSH;
    int breakSH;
    int goals;
};