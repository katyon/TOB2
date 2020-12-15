#include "DxLib.h"

#include "common.h"
#include "editor.h"
#include "input.h"
#include "file.h"

// �֐����� ------------------------------------------------
// �����ݒ�
void Editor::init(void)
{
    M_Editor.timer = 0;
    M_Editor.saveTimer = 0;
    M_Editor.state = 0;
    M_Editor.stageNum = Stage1;
    M_Editor.mousePos.set(0, 0);
    M_Editor.mousePosBuf.set(0, 0);
    M_Editor.mapPos.set(0, 0);
    M_Editor.mapSrc.set(0, 0);
    M_Editor.scrollSpeed = MAPCHIP_SIZE;
    M_Editor.chipNum = 0;
    M_Editor.cursorHND = LoadGraph("Data\\Images\\Sprite\\cursor.png");
    M_Editor.chipHND = LoadGraph("Data\\Images\\Sprite\\MapChip.png");
    M_Editor.initFlg = false;
    M_Editor.saveFlg = false;
    M_Editor.cr = GetColor(200, 0, 0);
}

// �X�V����
void Editor::update(void)
{
    switch (M_Editor.state)
    {
    case Init:
        ///// �����ݒ� /////
#pragma region Init
        M_Editor.init();
        M_Editor.state++;
        break;
#pragma endregion
    case Select:
        ///// �X�e�[�W�I�� /////
#pragma region Select
        // �X�e�[�W�I��
        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 200, M_Editor.cr, "�ǂ̃X�e�[�W��ҏW���܂����H");
        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 170, M_Editor.cr, "�I���FW,S or ��,��");
        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 140, M_Editor.cr, "����FEnter");

        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 90, GetColor(255, 255, 255), "stage1");
        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 60, GetColor(255, 255, 255), "stage2");
        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 30, GetColor(255, 255, 255), "stage3");
        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2, GetColor(255, 255, 255), "stage4");
        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 + 30, GetColor(255, 255, 255), "stage5");
        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 + 60, GetColor(255, 255, 255), "stage6");

        if (M_Input->GetKeyDown(KEY_INPUT_W) || M_Input->GetKeyDown(KEY_INPUT_UP))
        {
            M_Editor.stageNum--;
        }
        if (M_Input->GetKeyDown(KEY_INPUT_S) || M_Input->GetKeyDown(KEY_INPUT_DOWN))
        {
            M_Editor.stageNum++;
        }
        if (M_Editor.stageNum < Stage1)
        {
            M_Editor.stageNum = Stage1;
        }
        if (M_Editor.stageNum > Stage6)
        {
            M_Editor.stageNum = Stage6;
        }

        switch (M_Editor.stageNum)
        {
        case Stage1:
            DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 90, M_Editor.cr, "stage1");
            break;
        case Stage2:
            DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 60, M_Editor.cr, "stage2");
            break;
        case Stage3:
            DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 30, M_Editor.cr, "stage3");
            break;
        case Stage4:
            DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2, M_Editor.cr, "stage4");
            break;
        case Stage5:
            DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 + 30, M_Editor.cr, "stage5");
            break;
        case Stage6:
            DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 + 60, M_Editor.cr, "stage6");
            break;
        }
        if (M_Input->GetKeyDown(KEY_INPUT_RETURN))
        {
            M_Editor.state++;
        }

        break;
#pragma endregion
    case Mode:
        ///// ���[�h�I�� /////
#pragma region Mode
        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 180, M_Editor.cr, "�X�e�[�W�����������܂����H");
        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 160, M_Editor.cr, "�I���FW,S or ��,��");
        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 140, M_Editor.cr, "����FEnter");

        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 90, GetColor(255, 255, 255), "Yes");
        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 60, GetColor(255, 255, 255), "No");

        if (M_Input->GetKeyDown(KEY_INPUT_W) || M_Input->GetKeyDown(KEY_INPUT_UP))
        {
            M_Editor.initFlg = true;
        }
        if (M_Input->GetKeyDown(KEY_INPUT_S) || M_Input->GetKeyDown(KEY_INPUT_DOWN))
        {
            M_Editor.initFlg = false;
        }

        if (M_Editor.initFlg == true)
        {
            DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 90, M_Editor.cr, "Yes");
        }
        else
        {
            DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 60, M_Editor.cr, "No");
        }
        if (M_Input->GetKeyDown(KEY_INPUT_RETURN))
        {
            if (M_Editor.initFlg == false)
            {
                M_File.loadMapEditor();
            }

            M_Editor.state++;
        }
        break;
#pragma endregion
    case Update:
        ///// �X�V���� /////
#pragma region Update
        // �}�E�X�J�[�\���̈ʒu���擾
        GetMousePoint(&M_Editor.mousePos.x, &M_Editor.mousePos.y);

        // �X�N���[��
        if (M_Input->GetKey(KEY_INPUT_W) || M_Input->GetKeyDown(KEY_INPUT_UP))
        {
            M_Editor.mousePosBuf.y -= M_Editor.scrollSpeed;
            M_Editor.mapPos.y -= M_Editor.scrollSpeed;
        }
        if (M_Input->GetKey(KEY_INPUT_LCONTROL) == false)
        {
            if (M_Input->GetKey(KEY_INPUT_S) || M_Input->GetKeyDown(KEY_INPUT_DOWN))
            {
                M_Editor.mousePosBuf.y += M_Editor.scrollSpeed;
                M_Editor.mapPos.y += M_Editor.scrollSpeed;
            }
        }
        if (M_Input->GetKey(KEY_INPUT_A) || M_Input->GetKeyDown(KEY_INPUT_LEFT))
        {
            M_Editor.mousePosBuf.x -= M_Editor.scrollSpeed;
            M_Editor.mapPos.x -= M_Editor.scrollSpeed;
        }
        if (M_Input->GetKey(KEY_INPUT_D) || M_Input->GetKeyDown(KEY_INPUT_RIGHT))
        {
            M_Editor.mousePosBuf.x += M_Editor.scrollSpeed;
            M_Editor.mapPos.x += M_Editor.scrollSpeed;
        }

        // �}�b�v�`�b�v�؂�ւ�
        // �L�[�{�[�h����
        if (M_Input->GetKeyDown(KEY_INPUT_C))
        {
            M_Editor.chipNum++;
        }
        if (M_Input->GetKeyDown(KEY_INPUT_X))
        {
            M_Editor.chipNum--;
        }
        // �z�C�[������
        M_Editor.chipNum += GetMouseWheelRotVol();
        if (M_Editor.chipNum < 0)
        {
            M_Editor.chipNum = 0;
        }
        if (M_Editor.chipNum > CHIP_ALLNUM - 1)
        {
            M_Editor.chipNum = CHIP_ALLNUM - 1;
        }

        // �h��
        if (GetMouseInput() & MOUSE_INPUT_LEFT || M_Input->GetKey(KEY_INPUT_SPACE))
        {
            M_Editor.map[(M_Editor.mousePos.y + M_Editor.mousePosBuf.y) / MAPCHIP_SIZE][(M_Editor.mousePos.x + M_Editor.mousePosBuf.x) / MAPCHIP_SIZE] = M_Editor.chipNum;
        }
        // ����(0��h��)
        if (GetMouseInput() & MOUSE_INPUT_RIGHT || M_Input->GetKeyDown(KEY_INPUT_V))
        {
            M_Editor.map[(M_Editor.mousePos.y + M_Editor.mousePosBuf.y) / MAPCHIP_SIZE][(M_Editor.mousePos.x + M_Editor.mousePosBuf.x) / MAPCHIP_SIZE] = 0;
        }

        // �R���t�B�O
        if (M_Input->GetKeyDown(KEY_INPUT_0))
        {
            M_Editor.chipNum = 0;
        }
        if (M_Input->GetKeyDown(KEY_INPUT_1))
        {
            M_Editor.chipNum = 1;
        }
        if (M_Input->GetKeyDown(KEY_INPUT_2))
        {
            M_Editor.chipNum = 2;
        }
        if (M_Input->GetKeyDown(KEY_INPUT_3))
        {
            M_Editor.chipNum = 3;
        }
        if (M_Input->GetKeyDown(KEY_INPUT_4))
        {
            M_Editor.chipNum = 4;
        }
        if (M_Input->GetKeyDown(KEY_INPUT_5))
        {
            M_Editor.chipNum = 5;
        }
        if (M_Input->GetKeyDown(KEY_INPUT_6))
        {
            M_Editor.chipNum = 6;
        }
        if (M_Input->GetKeyDown(KEY_INPUT_7))
        {
            M_Editor.chipNum = 7;
        }
        if (M_Input->GetKeyDown(KEY_INPUT_8))
        {
            M_Editor.chipNum = 8;
        }
        if (M_Input->GetKeyDown(KEY_INPUT_9))
        {
            M_Editor.chipNum = 9;
        }

        // �}�b�v���t�@�C���ɕۑ�
        if (M_Input->GetKey(KEY_INPUT_LCONTROL) || M_Input->GetKey(KEY_INPUT_RCONTROL))
        {
            if (M_Input->GetKeyDown(KEY_INPUT_S))
            {
                M_File.saveMapEditor();
                M_Editor.saveFlg = true;
            }
        }

        //// �Q�[���V�[���ɐ؂�ւ�
        //if (key_trg[KEY_INPUT_RETURN])
        //{
        //    nextScene = SCENE_GAME;
        //}

        M_Editor.draw();

        M_Editor.timer++;
        break;
#pragma endregion
    }
}

// �`�揈��
void Editor::draw(void)
{
    // �`�揈��
    // �}�b�v�`�b�v
    for (int Ver = 0; Ver < MAPCHIP_V_MAX; Ver++)
    {
        for (int Hor = 0; Hor < MAPCHIP_H_MAX; Hor++)
        {
            switch (map[Ver][Hor])
            {
            case Void:
                mapSrc.set(130 * 0, 130 * 0);
                DrawBox(MAPCHIP_SIZE * Hor - M_Editor.mapPos.x, MAPCHIP_SIZE * Ver - M_Editor.mapPos.y, MAPCHIP_SIZE * Hor - M_Editor.mapPos.x + MAPCHIP_SIZE, MAPCHIP_SIZE * Ver - M_Editor.mapPos.y + MAPCHIP_SIZE, GetColor(0, 0, 0), true);
                DrawBox(MAPCHIP_SIZE * Hor - M_Editor.mapPos.x, MAPCHIP_SIZE * Ver - M_Editor.mapPos.y, MAPCHIP_SIZE * Hor - M_Editor.mapPos.x + MAPCHIP_SIZE, MAPCHIP_SIZE * Ver - M_Editor.mapPos.y + MAPCHIP_SIZE, GetColor(50, 50, 50), false);
                DrawFormatString(MAPCHIP_SIZE * Hor - M_Editor.mapPos.x + MAPCHIP_SIZE / 4, MAPCHIP_SIZE * Ver - M_Editor.mapPos.y + MAPCHIP_SIZE / 4, GetColor(50, 50, 50), "��");
                break;
            case LFloor:        mapSrc.set(130 * 1, 130 * 0);  break;
            case Floor:         mapSrc.set(130 * 2, 130 * 0);  break;
            case RFloor:        mapSrc.set(130 * 3, 130 * 0);  break;
            case Wall:          mapSrc.set(130 * 0, 130 * 1);  break;
            case Lift:          mapSrc.set(130 * 1, 130 * 1);  break;
            case Needle:        mapSrc.set(130 * 2, 130 * 1);  break;
            case Splitter:      mapSrc.set(130 * 3, 130 * 1);  break;
            case BubbleSpawner: mapSrc.set(130 * 0, 130 * 2);  break;
            case GoalSpawner:   mapSrc.set(130 * 1, 130 * 2);  break;
            case StartSource:   mapSrc.set(130 * 2, 130 * 2);  break;
            case EndSource:     mapSrc.set(130 * 3, 130 * 2);  break;
            default: mapSrc.set(0, 0);  break;
            }
            DrawRectExtendGraph(MAPCHIP_SIZE * Hor - M_Editor.mapPos.x, MAPCHIP_SIZE * Ver - M_Editor.mapPos.y, MAPCHIP_SIZE * Hor - M_Editor.mapPos.x + MAPCHIP_SIZE, MAPCHIP_SIZE * Ver - M_Editor.mapPos.y + MAPCHIP_SIZE, mapSrc.x, mapSrc.y, 130, 130, chipHND, true);
        }
    }
    // �J�[�\��
    if (M_Editor.timer / 30 % 2)
    {
        //SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
        switch (chipNum)
        {
        case Void:          mapSrc.set(130 * 0, 130 * 0);  break;
        case LFloor:        mapSrc.set(130 * 1, 130 * 0);  break;
        case Floor:         mapSrc.set(130 * 2, 130 * 0);  break;
        case RFloor:        mapSrc.set(130 * 3, 130 * 0);  break;
        case Wall:          mapSrc.set(130 * 0, 130 * 1);  break;
        case Lift:          mapSrc.set(130 * 1, 130 * 1);  break;
        case Needle:        mapSrc.set(130 * 2, 130 * 1);  break;
        case Splitter:      mapSrc.set(130 * 3, 130 * 1);  break;
        case BubbleSpawner: mapSrc.set(130 * 0, 130 * 2);  break;
        case GoalSpawner:   mapSrc.set(130 * 1, 130 * 2);  break;
        case StartSource:   mapSrc.set(130 * 2, 130 * 2);  break;
        case EndSource:     mapSrc.set(130 * 3, 130 * 2);  break;
        default: mapSrc.set(0, 0);  break;
        }
        DrawRectExtendGraph((mousePos.x + mousePosBuf.x % MAPCHIP_SIZE) / MAPCHIP_SIZE * MAPCHIP_SIZE, (mousePos.y + mousePosBuf.y % MAPCHIP_SIZE) / MAPCHIP_SIZE * MAPCHIP_SIZE,
            (mousePos.x + mousePosBuf.x % MAPCHIP_SIZE) / MAPCHIP_SIZE * MAPCHIP_SIZE + MAPCHIP_SIZE, (mousePos.y + mousePosBuf.y % MAPCHIP_SIZE) / MAPCHIP_SIZE * MAPCHIP_SIZE + MAPCHIP_SIZE,
            mapSrc.x, mapSrc.y, 130, 130, chipHND, true);
        //SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
    DrawGraph((mousePos.x + mousePosBuf.x % MAPCHIP_SIZE) / MAPCHIP_SIZE * MAPCHIP_SIZE,
        (mousePos.y + mousePosBuf.y % MAPCHIP_SIZE) / MAPCHIP_SIZE * MAPCHIP_SIZE, cursorHND, true);

    // �g��������
    DrawFormatString(10, 0, cr, "0�L�[:�`�悵�Ȃ�");
    DrawFormatString(10, 30, cr, "1�L�[:�n�`(��)");
    DrawFormatString(10, 60, cr, "2�L�[:�n�`(��)");
    DrawFormatString(10, 90, cr, "3�L�[:�n�`(�E)");
    DrawFormatString(10, 120, cr, "4�L�[:��");
    DrawFormatString(10, 150, cr, "5�L�[:��");
    DrawFormatString(10, 180, cr, "6�L�[:�j");
    DrawFormatString(10, 210, cr, "7�L�[:����");
    DrawFormatString(10, 240, cr, "8�L�[:�N��");
    DrawFormatString(10, 270, cr, "9�L�[:�S�[��");


    DrawFormatString(250, 0, cr, "�`�b�v�؂�ւ�:�z�C�[�� or X,C");
    DrawFormatString(250, 30, cr, "�h��:���N���b�N or Space");
    DrawFormatString(250, 60, cr, "�폜(0��h��):�E�N���b�N or V");
    DrawFormatString(250, 90, cr, "�J�[�\���ړ�:�}�E�X");
    DrawFormatString(250, 120, cr, "��ʃX�N���[��:W,A,S,D");
    DrawFormatString(250, 150, cr, "�P�}�X�����X�N���[��:��,��,��,��");
    DrawFormatString(250, 180, cr, "�f�[�^��ۑ�:Ctrl + S");
    DrawFormatString(250, 210, cr, "�I���FEsc");

    DrawFormatString(710, 0, cr, "���݂̃J�[�\���̈ʒu(�}�b�v�`�b�v��)");
    DrawFormatString(710, 30, cr, "X�F%d", (mousePos.x + mousePosBuf.x) / MAPCHIP_SIZE);
    DrawFormatString(710, 60, cr, "Y�F%d", (mousePos.y + mousePosBuf.y) / MAPCHIP_SIZE);

    DrawFormatString(1700, 0, cr, "�}�b�v�`�b�v���X�g");
    DrawFormatString(1700, 30, cr, "0��:�`�悵�Ȃ�");
    DrawFormatString(1700, 60, cr, "1��:�n�`(��)");
    DrawFormatString(1700, 90, cr, "2��:�n�`(��)");
    DrawFormatString(1700, 120, cr, "3��:�n�`(�E)");
    DrawFormatString(1700, 150, cr, "4��:��");
    DrawFormatString(1700, 180, cr, "5��:��");
    DrawFormatString(1700, 210, cr, "6��:�j");
    DrawFormatString(1700, 240, cr, "7��:����");
    DrawFormatString(1700, 270, cr, "8��:�N��");
    DrawFormatString(1700, 300, cr, "9��:�S�[��");
    DrawFormatString(1700, 330, cr, "10��:��������");
    DrawFormatString(1700, 360, cr, "11��:�����E��");

    if (saveTimer > 300)
    {
        saveFlg = false;
        saveTimer = 0;
    }
    if (saveFlg == true)
    {
        DrawFormatString(mousePos.x - 50, mousePos.y - 30, cr, "�Z�[�u���܂���");
        saveTimer++;
    }
}

void Editor::end(void)
{
    DeleteGraph(chipHND);
    DeleteGraph(cursorHND);
}