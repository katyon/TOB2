#pragma once
#include "singleton.h"
#include "vec2.h"
// �萔 -----------------------------------------------------------------------------------------
#define EFFECT_BUBBLE_MAX      (14)
#define WATER_ACCEL    (0.15f)
#define WATER_DECEL    (0.1f)
#define EFFECT_SPEED_MAX    (5.0f)

// �N���X ----------------------------------------------------------------------------------------
#define M_Water_Current Water_Current::getInstance()

class Water_Current : public Singleton<Water_Current>
{
private:
    int handle;
    float pos_x[EFFECT_BUBBLE_MAX];
    float pos_y[EFFECT_BUBBLE_MAX];

public:
    float �� = 0; // �����x
    int range;
    void init(void);
    void update(void);
    void draw(void);
    void end(void);
    //void move(Water_Current_Obj* obj);
};