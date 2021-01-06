#include "Elastic.h" 
#include "main.h"
#include "manage.h"
#include "input.h"
#include "stage_select.h"

#define STAGE_MAX 4
void Stage_Select::init()
{
    handle = LoadGraph("Data\\Images\\Sprite\\bubble_number.png");
    integrationSH= LoadSoundMem("Data\\Sounds\\integration.mp3");
    pos = { 200, 200 };
    select = 1;
    timer = 0;
    size = 0;
    bubble_effect = true;
}

void Stage_Select::update()
{

    timer++;
    magnification = Elastic::easeOut(timer, 0, 1, 180);            // easing function
    sin  = std::sinf(M_Usable.getGameTime() * 0.04 +  0) * 20;     // sin function
    sin2 = std::sinf(M_Usable.getGameTime() * 0.04 + 30) * 20;
    sin3 = std::sinf(M_Usable.getGameTime() * 0.04 + 60) * 20;
    if (bubble_effect == true)
    {
        size += 0.008;
        if (size >= 0.5)
        {
            size = 0.5;
        }
        if (timer > 90)
        {
            timer = 12;
            select = 1;
            bubble_effect = false;
        }
    }

    if (bubble_effect == false)
    {
        if (M_Input->GetKeyDown(KEY_INPUT_LEFT))
        {
            PlaySoundMem(integrationSH, DX_PLAYTYPE_BACK, true);
            select -= 1;
            timer = 12;
        }
        if (M_Input->GetKeyDown(KEY_INPUT_RIGHT))
        {
            PlaySoundMem(integrationSH, DX_PLAYTYPE_BACK, true);
            select += 1;
            timer = 12;
        }
        if (M_Input->GetKeyDown(KEY_INPUT_SPACE))
        {
            PlaySoundMem(M_TitleManager.decisionSH, DX_PLAYTYPE_BACK, true);
            M_SelectManager.change = true;
        }
    }

    if (select > STAGE_MAX) { select = 1; }
    if (select < 1) { select = STAGE_MAX; }
    
#ifdef _DEBUG
    select = 6;
#endif // _DEBUG
}

void Stage_Select::draw()
{
    if (bubble_effect == true)
    {
        DrawRectRotaGraph2F(pos.x + 0, pos.y + sin + 50, 300 * 0, 0, 300, 300, 150, 150, 1 * magnification - size, 0, handle, true, 0, 0);
        DrawRectRotaGraph2F(pos.x + 500, pos.y + sin3 + 630, 300 * 1, 0, 300, 300, 150, 150, 1 * magnification - size, 0, handle, true, 0, 0);
        DrawRectRotaGraph2F(pos.x + 1000, pos.y + sin2 + 50, 300 * 2, 0, 300, 300, 150, 150, 1 * magnification - size, 0, handle, true, 0, 0);
        DrawRectRotaGraph2F(pos.x + 1500, pos.y + sin2 + 630, 300 * 3, 0, 300, 300, 150, 150, 1 * magnification - size, 0, handle, true, 0, 0);
        //DrawRectRotaGraph2F(pos.x + 1200, pos.y + sin + 50, 300 * 4, 0, 300, 300, 150, 150, 1 * magnification - size, 0, handle, true, 0, 0);
        //DrawRectRotaGraph2F(pos.x + 1500, pos.y + sin3 + 630, 300 * 5, 0, 300, 300, 150, 150, 1 * magnification - size, 0, handle, true, 0, 0);
    }

    else
    {
        switch (select)
        {
        case 1:
            DrawRectRotaGraph2F(pos.x + 0, pos.y + sin + 50, 300 * 0, 0, 300, 300, 150, 150, 1 * magnification, 0, handle, true, 0, 0);
            DrawRectRotaGraph2F(pos.x + 500, pos.y + sin3 + 630, 300 * 1, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            DrawRectRotaGraph2F(pos.x + 1000, pos.y + sin2 + 50, 300 * 2, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            DrawRectRotaGraph2F(pos.x + 1500, pos.y + sin2 + 630, 300 * 3, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
           // DrawRectRotaGraph2F(pos.x + 1200, pos.y + sin + 50, 300 * 4, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
           // DrawRectRotaGraph2F(pos.x + 1500, pos.y + sin3 + 630, 300 * 5, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            break;

        case 2:
            DrawRectRotaGraph2F(pos.x + 0, pos.y + sin + 50, 300 * 0, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            DrawRectRotaGraph2F(pos.x + 500, pos.y + sin3 + 630, 300 * 1, 0, 300, 300, 150, 150, 1 * magnification, 0, handle, true, 0, 0);
            DrawRectRotaGraph2F(pos.x + 1000, pos.y + sin2 + 50, 300 * 2, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            DrawRectRotaGraph2F(pos.x + 1500, pos.y + sin2 + 630, 300 * 3, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
           // DrawRectRotaGraph2F(pos.x + 1200, pos.y + sin + 50, 300 * 4, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
           // DrawRectRotaGraph2F(pos.x + 1500, pos.y + sin3 + 630, 300 * 5, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            break;

        case 3:
            DrawRectRotaGraph2F(pos.x + 0, pos.y + sin + 50, 300 * 0, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            DrawRectRotaGraph2F(pos.x + 500, pos.y + sin3 + 630, 300 * 1, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            DrawRectRotaGraph2F(pos.x + 1000, pos.y + sin2 + 50, 300 * 2, 0, 300, 300, 150, 150, 1 * magnification, 0, handle, true, 0, 0);
            DrawRectRotaGraph2F(pos.x + 1500, pos.y + sin2 + 630, 300 * 3, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
           // DrawRectRotaGraph2F(pos.x + 1200, pos.y + sin + 50, 300 * 4, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
           // DrawRectRotaGraph2F(pos.x + 1500, pos.y + sin3 + 630, 300 * 5, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            break;

        case 4:
            DrawRectRotaGraph2F(pos.x + 0, pos.y + sin + 50, 300 * 0, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            DrawRectRotaGraph2F(pos.x + 500, pos.y + sin3 + 630, 300 * 1, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            DrawRectRotaGraph2F(pos.x + 1000, pos.y + sin2 + 50, 300 * 2, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            DrawRectRotaGraph2F(pos.x + 1500, pos.y + sin2 + 630, 300 * 3, 0, 300, 300, 150, 150, 1 * magnification, 0, handle, true, 0, 0);
          //  DrawRectRotaGraph2F(pos.x + 1200, pos.y + sin + 50, 300 * 4, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
          //  DrawRectRotaGraph2F(pos.x + 1500, pos.y + sin3 + 630, 300 * 5, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            break;

        case 5:
            DrawRectRotaGraph2F(pos.x + 0, pos.y + sin + 50, 300 * 0, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            DrawRectRotaGraph2F(pos.x + 500, pos.y + sin3 + 630, 300 * 1, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            DrawRectRotaGraph2F(pos.x + 1000, pos.y + sin2 + 50, 300 * 2, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            DrawRectRotaGraph2F(pos.x + 1500, pos.y + sin2 + 630, 300 * 3, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
          //  DrawRectRotaGraph2F(pos.x + 1200, pos.y + sin + 50, 300 * 4, 0, 300, 300, 150, 150, 1 * magnification, 0, handle, true, 0, 0);
          //  DrawRectRotaGraph2F(pos.x + 1500, pos.y + sin3 + 630, 300 * 5, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            break;

        case 6:
            DrawRectRotaGraph2F(pos.x + 0, pos.y + sin + 50, 300 * 0, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            DrawRectRotaGraph2F(pos.x + 500, pos.y + sin3 + 630, 300 * 1, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            DrawRectRotaGraph2F(pos.x + 1000, pos.y + sin2 + 50, 300 * 2, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
            DrawRectRotaGraph2F(pos.x + 1500, pos.y + sin2 + 630, 300 * 3, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
         //   DrawRectRotaGraph2F(pos.x + 1200, pos.y + sin + 50, 300 * 4, 0, 300, 300, 150, 150, 0.5, 0, handle, true, 0, 0);
         //   DrawRectRotaGraph2F(pos.x + 1500, pos.y + sin3 + 630, 300 * 5, 0, 300, 300, 150, 150, 1 * magnification, 0, handle, true, 0, 0);
            break;
    }
    }

}

void Stage_Select::end()
{
    DeleteGraph(handle);
    DeleteSoundMem(integrationSH);
}