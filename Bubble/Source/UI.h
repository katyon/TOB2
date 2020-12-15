#pragma once
#include "common.h"
#include "singleton.h"

#include "input.h"

// ƒNƒ‰ƒX --------------------------------------------------------------
#define M_UI UI::getInstance()
class UI : public Singleton<UI>
{
private:
    LPCSTR font_path = "azuki.ttf";
    int trial;
    int Color;
#if 1
    int timer;
#endif // 1

public:
    void init(void);
    void update(void);
    void draw(void);
    void end(void);
};