#pragma once
#include "vec2.h"

// �萔��`
#define GAME_SCREEN_WIDTH	(1920)      // �Q�[����ʂ̕�
#define GAME_SCREEN_HEIGHT	(1080)      // �Q�[����ʂ̍���
#define PI          (3.1415926535f)     // �~����
#define ROOT2       (1.41421356f)       // ��2
#define ROOT5       (2.2360679f)        // ��5

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