// �C���N���[�h ----------------------------------------------------------------------------------
#include "DxLib.h"

#include "UI.h"
#include "input.h"

// �֐� ----------------------------------------------------------------------------------------

void UI::init()
{
    Color = GetColor(255, 255, 255);
    timer = 0;
}

void UI::update()
{

#if 1  // 0 �Ŗ�����
    timer++;
    trial = timer / 60;
#endif // DEBUG

}

void UI::draw()
{
    SetFontSize(48);
    DrawString(1670, 200, "���s��", Color, 72);
    DrawFormatString(1760, 250, Color, "%d", trial);
}

void UI::end()
{
    int InitFontToHandle(void);
}