#pragma once
// �萔 ----------------------------------------------------------------
#include "singleton.h"
// �N���X --------------------------------------------------------------
#define M_System (System::getInstance())
class System : public Singleton<System>
{
public:
    void    drawDebugString(void);
    void    inputDebugKey(void);
    void    changeSceneStateInit(int next_scene);    // �V�[���J�ڏ���
    bool    isCollRect(vec2f a, vec2f rel_a, vec2f b, vec2f rel_b);
    bool    isCollCircle(vec2f a, int ar, vec2f b, int br);
    bool    isCollCircleWithRect(vec2f c,int r, vec2f a, vec2f rel_a);

private:
    unsigned int cr = 0;
};