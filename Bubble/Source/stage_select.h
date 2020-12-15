#pragma once
#include "singleton.h"
#include "vec2.h"

// ƒNƒ‰ƒX ----------------------------------------------------------------------------------------
#define M_Stage_Select Stage_Select::getInstance()
class Stage_Select : public Singleton<Stage_Select>
{
private:
    vec2f pos;
    int   handle;
    int   integrationSH;
    float magnification;  // Šg‘å—¦
    int   timer;
    int   effect_timer;
    float sin;
    float sin2;
    float sin3;
    bool  bubble_effect;


public:
    int  select;
    float size;

    void init();
    void update();
    void draw();
    void end();
};