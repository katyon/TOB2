#pragma once
#include "singleton.h"
#include "vec2.h"
// íËêî ----------------------------------------------------------------
#define GOALS_MAX (3)

// ÉNÉâÉX --------------------------------------------------------------
class GoalsObj
{
public:
    void init(GoalsObj* obj, float posX, float posY, int rateX, int rateY, int Num);

    vec2f   pos;
    vec2f   rel_pos;
    vec2f   src;
    int     num;
    bool    exist = false;
    bool    clear = false;
};

#define M_Goals Goals::getInstance()
class Goals :public Singleton<Goals>
{
public:
    void init(void);
    void update(void);
    void draw(void);
    void end(void);

private:
    int maxNum;
    int handle;
};