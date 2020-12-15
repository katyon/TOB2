#pragma once
#include "map.h"
#include "singleton.h"
#include "vec2.h"
// �萔 ----------------------------------------------------------------------------
#define CHIP_ALLNUM (12)

enum StateEditor { Init, Select, Mode, Update };
enum StageNum { Stage1, Stage2, Stage3, Stage4, Stage5, Stage6 };

// �N���X --------------------------------------------------------------------------
#define M_Editor Editor::getInstance()
class Editor :public Singleton<Editor>
{
public:
    void init(void);     // �����ݒ�
    void update(void);   // �X�V����
    void draw(void);     // �`�揈��]
    void end(void);

    vec2i mapPos;
    vec2i mapSrc;
    vec2i mousePos;
    vec2i mousePosBuf;
    unsigned int cr;
    int timer = 0;
    int saveTimer = 0;
    int state = 0;
    int stageNum = 0;
    int map[MAPCHIP_V_MAX][MAPCHIP_H_MAX] = { 0 };
    int scrollSpeed = 0;
    int chipHND = 0;
    int chipNum = 0;
    int cursorHND = 0;
    bool initFlg = false;
    bool saveFlg = false;
private:

};