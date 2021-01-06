#pragma once
#include "singleton.h"
#include "vec2.h"
// íËêî ----------------------------------------------------------------
#define PL_BUBBLE_MAX      (64)
#define BUBBLE_ACCEL    (0.1f)
#define BUBBLE_DECEL    (0.1f)
#define BUBBLE_SPEED_MAX    (5.0f)
#define BUOYANCY        (0.5f)

// ÉNÉâÉX --------------------------------------------------------------
class PlBubbleObj
{
public:
    void init(PlBubbleObj* obj, float posX,float posY);

    vec2f   pos;
    vec2f   rel_pos;
    vec2f   center;
    vec2f   speed;
    int     radius = 0;
    int     state = 0;
    int     level = 0;
    bool    exist = false;
    bool    touchFloor = false;
    bool    touchBubble = false;
};

#define M_Bubble PlBubble::getInstance()
class PlBubble :public Singleton<PlBubble>
{
public:
    void init(void);
    void update(void);
    void draw(void);
    void end(void);
    void move(PlBubbleObj* obj);
    void fix(PlBubbleObj* obj);
    void collAnotherBubble(void);
    void inputDebugKey(void);

private:
    int handle;
    int integrationSH;
};