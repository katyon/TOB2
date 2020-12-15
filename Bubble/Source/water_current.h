#pragma once
#include "singleton.h"
#include "vec2.h"
// íËêî -----------------------------------------------------------------------------------------
#define EFFECT_BUBBLE_MAX      (20)
#define WATER_ACCEL    (0.15f)
#define WATER_DECEL    (0.1f)
#define EFFECT_SPEED_MAX    (5.0f)

// ÉNÉâÉX ----------------------------------------------------------------------------------------
#define M_Water_Current Water_Current::getInstance()

class Water_Current : public Singleton<Water_Current>
{
private:
    int handle;
    int range;
    float pos_x[EFFECT_BUBBLE_MAX];
    float pos_y[EFFECT_BUBBLE_MAX];

public:
    float Éø = 0; // ìßñæìx
    void init(void);
    void update(void);
    void draw(void);
    void end(void);
    //void move(Water_Current_Obj* obj);
};