#pragma once
#include "vec2.h"

// ’è”’è‹`
#define GAME_SCREEN_WIDTH	(1920)      // ƒQ[ƒ€‰æ–Ê‚Ì•
#define GAME_SCREEN_HEIGHT	(1080)      // ƒQ[ƒ€‰æ–Ê‚Ì‚‚³
#define PI          (3.1415926535f)     // ‰~ü—¦
#define ROOT2       (1.41421356f)       // ã2
#define ROOT5       (2.2360679f)        // ã5

class Sprite
{
public:
    virtual void init(void) = 0;
    virtual void update(void) = 0;
    virtual void draw(void) = 0;
    virtual void end(void) = 0;

protected:
    vec2f pos;
    vec2f rel_pos;
    vec2i src;
    int width = 0;
    int height = 0;
    int handle = 0;
};