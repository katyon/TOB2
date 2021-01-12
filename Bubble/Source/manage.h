#pragma once
#include "singleton.h"
#include "vec2.h"
// íËêî ----------------------------------------------------------------
#define PAUSE_MAX (3)

// ÉNÉâÉX --------------------------------------------------------------
#define M_TitleManager TitleManager::getInstance()
class TitleManager : public Singleton<TitleManager>
{
public:
    void init(void);
    void update(void);
    void draw(void);
    void end(void);

    bool change = false;
    int decisionSH;
private:
    int bgmSH;
    bool once;
};

#define M_SelectManager SelectManager::getInstance()
class SelectManager : public Singleton<SelectManager>
{
public:
    void init(void);
    void update(void);
    void draw(void);
    void end(void);

    bool change = false;
    int state = 0;
private:
    unsigned int cr = 0;
    int handle;
    int bgmSH;
    bool once;
};

#define M_GameManager GameManager::getInstance()
class GameManager : public Singleton<GameManager>
{
public:
    void init(void);
    void update(void);
    void draw(void);
    void end(void);

    bool change = false;
    bool clear = false;
    bool migration = false;

    bool pause;
private:
    unsigned int cr = 0;
    int state = 0;
    int handle;
    int bubble;
    int bgmSH;
    bool once;
    int num;
    int timer;
    float bubble_magnification;
    vec2f   pos;
    vec2f   src;

    int pause_num;
};