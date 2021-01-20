#pragma once
#include "singleton.h"

class Effect : public Singleton<Effect>
{
private:
    int effectResourceHandle;
    int grBackgroundHandle;
    int grFrontHandle;
    int playingEffectHandle;

    int time;

public:
    bool  effectFlg = false;

    float position_x;
    float position_y;

    void init();
    void update();
    void draw();
    void end();
};

#define M_Effect Effect::getInstance()
