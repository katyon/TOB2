#pragma once
#include "bubble.h"
#include "common.h"
#include "singleton.h"
// íËêî ----------------------------------------------------------------
#define		MAPCHIP_H_MAX		(22)
#define		MAPCHIP_V_MAX		(34)
//#define		MAPCHIP_H_MAX		(30)
//#define		MAPCHIP_V_MAX		(17)
#define		MAPCHIP_SIZE		(64)

enum ChipData
{
    Void, LFloor, Floor, RFloor,
    Wall, Lift, Needle, Splitter,
    BubbleSpawner, GoalSpawner, 
    StartSource, EndSource, SubGoal
};
// ÉNÉâÉX --------------------------------------------------------------
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
    int divisionSH;
    int breakSH;
    int goals;
};