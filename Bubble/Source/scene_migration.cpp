#include "scene_migration.h"
#include "main.h"
#include "manage.h"
#include "input.h"
#include "Quint.h"

void Scene_Migration::init()
{
    handle0 = LoadGraph("Data\\Images\\Sprite\\bubble.png");
    handle1 = LoadGraph("Data\\Images\\Bg\\Game_Bg.png");
    zavanSH = LoadSoundMem("Data\\Sounds\\zavan.mp3");
    timer = 0;
    movement = 0;
    for (int i = 0; i < MIGRATION_MAX; i++)
    {
        pos_x[i] = 0;
        pos_y[i] = 1080;
    }
    once = true;
    ƒ¿ = 0;
}

void Scene_Migration::update0()
{
    if (once == true)
    {
        PlaySoundMem(zavanSH, DX_PLAYTYPE_BACK, true);
        ƒ¿ = 255;
        once = false;
    }

    timer++;
    if (timer > 100)
    {
        movement = Quint::easeOut(timer - 100, 0, 1, 240);
        ƒ¿ -= 255 / 100;
    }
    changing = 1080 * movement;
    Y = changing;

    sin0 = std::sinf(M_Usable.getGameTime() * 0.1 +  0) *  70;
    sin1 = std::sinf(M_Usable.getGameTime() * 0.1 + 30) * 100;
    sin2 = std::sinf(M_Usable.getGameTime() * 0.1 + 60) *  50;

    for (int i = 0; i < MIGRATION_MAX; i += 3)
    {
        pos_x[i] = sin0;
    }
    for (int j = 1; j < MIGRATION_MAX; j += 3)
    {
        pos_x[j] = sin2;
    }
    for (int k = 2; k < MIGRATION_MAX; k += 3)
    {
        pos_x[k] = sin1;
    }
    for (int i = 0; i < MIGRATION_MAX; i++)
    {
        pos_y[i] -= 30;
    }
}

void Scene_Migration::update1()
{
    if (once == true)
    {
        PlaySoundMem(zavanSH, DX_PLAYTYPE_BACK, true);
        once = false;
    }
    
    {
        timer++;
        if (timer < 60)
        {
            movement = Quint::easeOut(timer, 0, 1, 60);
            ƒ¿ += 255 / 60;
        }
        else if (timer < 120)
        {
            movement = 1;
            ƒ¿ = 255;
        }
        else
        {
            movement = Quint::easeIn(timer - 120, 1, 2, 90);
            ƒ¿ -= 255 / 60;
        }
        //else
        //{
        //    movement = Quint::easeIn(timer, 0, 1, 180);
        //}
        changing = 1080 * movement;
        Y = 1080 - changing;

        sin0 = std::sinf(M_Usable.getGameTime() * 0.1 + 0) * 70;
        sin1 = std::sinf(M_Usable.getGameTime() * 0.1 + 30) * 100;
        sin2 = std::sinf(M_Usable.getGameTime() * 0.1 + 60) * 50;
        for (int i = 0; i < MIGRATION_MAX; i += 3)
        {
            pos_x[i] = sin0;
        }
        for (int j = 1; j < MIGRATION_MAX; j += 3)
        {
            pos_x[j] = sin2;
        }
        for (int k = 2; k < MIGRATION_MAX; k += 3)
        {
            pos_x[k] = sin1;
        }
        for (int i = 0; i < MIGRATION_MAX; i++)
        {
            pos_y[i] -= 30;
        }
    }
}

void Scene_Migration::draw()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, ƒ¿);
    DrawGraph(0, 0, handle1, false);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

    for (int i = 0; i < MIGRATION_MAX; i += 3)
    {
        DrawRotaGraph(pos_x[i] +   0, pos_y[i] + i * 250 + 1080, 3.5, 0, handle0, true);
    }
    for (int j = 1; j < MIGRATION_MAX; j += 3)
    {
        DrawRotaGraph(pos_x[j] + 300, pos_y[j] + j * 250 + 1080, 1.3, 0, handle0, true);
    }
    for (int k = 2; k < MIGRATION_MAX; k += 3)
    {
        DrawRotaGraph(pos_x[k] + 600, pos_y[k] + k * 250 + 1080, 2.2, 0,handle0, true);
    }

    for (int i = 0; i < MIGRATION_MAX; i += 3)
    {
        DrawRotaGraph(pos_x[i] +  900, pos_y[i] + i * 250 + 1080, 1.8, 0, handle0, true);
    }
    for (int j = 1; j < MIGRATION_MAX; j += 3)
    {
        DrawRotaGraph(pos_x[j] + 1200, pos_y[j] + j * 250 + 1080, 3.2, 0, handle0, true);
    }
    for (int k = 2; k < MIGRATION_MAX; k += 3)
    {
        DrawRotaGraph(pos_x[k] + 1500, pos_y[k] + k * 250 + 1080, 2.7, 0, handle0, true);
    }

    for (int i = 0; i < MIGRATION_MAX; i += 3)
    {
        DrawRotaGraph(pos_x[i] + 1800, pos_y[i] + i * 250 + 1080, 1.8, 0, handle0, true);
    }
}

void Scene_Migration::end()
{
    DeleteGraph(handle0);
    DeleteGraph(handle1);
    DeleteSoundMem(zavanSH);
}

void Scene_Migration::setTimer(float time)
{
    timer = time;
}

float Scene_Migration::getTimer()
{
    return timer;
}