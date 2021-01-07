#pragma once
#include "singleton.h"
#define M_Scene_Migration Scene_Migration::getInstance()

#define MIGRATION_MAX (15)

class Scene_Migration :public Singleton<Scene_Migration>
{
private:
    int handle0;
    int handle1;
    int zavanSH;

    int Y;
    float changing;
    float movement;
    
    float sin0;
    float sin1;
    float sin2;

    float timer;
    float pos_x[MIGRATION_MAX];
    float pos_y[MIGRATION_MAX];

    bool  once;

    float ƒ¿;        // “§–¾“x

public:
    void init(void);
    void update0(void);
    void update1(void);
    void draw(void);
    void end(void);

    void setTimer(float time);
    float getTimer(void);
};