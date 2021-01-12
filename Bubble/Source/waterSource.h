#pragma once
#include "singleton.h"
// íËêî ----------------------------------------------------------------
#define SOURCE_MAX (16)

// ÉNÉâÉX --------------------------------------------------------------
class WaterObj
{
public:
    void init(WaterObj* obj, float chipY, float rel_chipY);

    vec2f   pos;
    vec2f   rel_pos;
    vec2f   mini_pos;
    vec2f   mini_rel_pos;
    int     num;
    bool    exist = false;
};

#define M_WaterSource WaterSource::getInstance()
class WaterSource :public Singleton<WaterSource>
{
public:
    void init(void);
    void update(void);
    void draw(void);
    void end(void);

    int maxNum;
private:
    int nowNum;
    int handle;
    int decisionSH;
    int jetSH;
    bool once;
    unsigned int cr;
};