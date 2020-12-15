#include "DxLib.h"

#include "bg.h"
#include "bubble.h"
#include "editor.h"
#include "goals.h"
#include "common.h"
#include "input.h"
#include "main.h"
#include "manage.h"
#include "map.h"
#include "system.h"
#include "UI.h"
#include "stage_select.h"
#include "waterSource.h"
#include "water_current.h"
#include "scene_migration.h"

//////////////////////////////////////////////////////////////////////////
//	�e�Q�[���Ŏg�p����N���X�C���X�^���X��O���[�o���ϐ��͂����ɋL�q
//

PlBubbleObj I_PlBubbleObj[PL_BUBBLE_MAX];
WaterObj    I_WatereObj[SOURCE_MAX];
GoalsObj    I_GoalsObj[GOALS_MAX];
//Water_Current_Obj I_Water_Current_Obj[EFFECT_BUBBLE_MAX];

//
// ��`�����܂�
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	��������G�f�B�^�[�̏���
//

// �G�f�B�^�[����������
void Scene_Editor::init(void)
{
    M_Editor.init();
}

// �G�f�B�^�[�X�V����
void Scene_Editor::update(void)
{
    M_Editor.update();
}

// �G�f�B�^�[�`�揈��
void Scene_Editor::draw(void)
{
    M_Editor.draw();
}

// �G�f�B�^�[�I������
void Scene_Editor::end(void)
{
    M_Editor.end();
}

//
//	�G�f�B�^�[�̏��������܂�
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	��������^�C�g���̏���
//

// �^�C�g������������
void Scene_Title::init(void)
{
    M_TitleBg.init();
    M_TitleManager.init();
    M_Scene_Migration.init();
}

// �^�C�g���X�V����
void Scene_Title::update(void)
{
    M_TitleBg.update();
    M_TitleManager.update();
    M_Scene_Migration.update0();
}

// �^�C�g���`�揈��
void Scene_Title::draw(void)
{
    M_TitleBg.draw();
    M_TitleManager.draw();
    M_Scene_Migration.draw();
}

// �^�C�g���I������
void Scene_Title::end(void)
{
    M_TitleBg.end();
    M_TitleManager.end();
    M_Scene_Migration.end();
}

//
//	�^�C�g���̏��������܂�
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	��������X�e�[�W�I���̏���
//

// �X�e�[�W�I������������
void Scene_Choice::init(void)
{
    M_ChoiceBg.init();
    M_Stage_Select.init();
    M_SelectManager.init();
    if (M_GameManager.migration == true) M_Scene_Migration.init();
}

// �X�e�[�W�I���X�V����
void Scene_Choice::update(void)
{
    M_ChoiceBg.update();
    M_Stage_Select.update();
    M_SelectManager.update();
    M_Scene_Migration.update1();
}

// �X�e�[�W�I��`�揈��
void Scene_Choice::draw(void)
{
    M_ChoiceBg.draw();
    M_Stage_Select.draw();
    M_SelectManager.draw();
    M_Scene_Migration.draw();
}

// �X�e�[�W�I���I������
void Scene_Choice::end(void)
{
    M_ChoiceBg.end();
    M_Stage_Select.end();
    M_SelectManager.end();
    M_Scene_Migration.end();
}

//
//	�X�e�[�W�I���̏��������܂�
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	��������Q�[���̏���
//

// �Q�[������������
void Scene_Game::init(void)
{
    M_GameBg.init();
    M_Water_Current.init();
    M_Bubble.init();
    M_MapData.init();
    M_WaterSource.init();
    M_Goals.init();
    //M_UI.init();
    M_GameManager.init();
    M_MigrationBg.init();
    M_Scene_Migration.init();
}

// �Q�[���X�V����
void Scene_Game::update(void)
{
    if (M_Scene_Migration.getTimer() > 60)
    {
        if (M_GameManager.clear == false)
        {
            M_MapData.update();
            M_Water_Current.update();
            M_GameBg.update();
            M_Bubble.update();
            M_WaterSource.update();
            M_Goals.update();
            // M_UI.update();
        }
        M_GameManager.update();
    }
    else
    {
        M_MigrationBg.update();
    }
    M_Scene_Migration.update1();
}

// �Q�[���`�揈��
void Scene_Game::draw(void)
{
    if (M_Scene_Migration.getTimer() > 60)
    {
        M_GameBg.draw();
        M_Water_Current.draw();
        M_MapData.draw();
        M_Bubble.draw();
        M_WaterSource.draw();
        M_Goals.draw();
        //M_UI.draw();
        M_GameManager.draw();
    }
    else
    {
        M_MigrationBg.draw();
    }
    M_Scene_Migration.draw();
}

// �Q�[���I������
void Scene_Game::end(void)
{
    M_MapData.end();
    M_Water_Current.end();
    M_GameBg.end();
    M_Bubble.end();
    M_WaterSource.end();
    M_Goals.end();
    //M_UI.end();
    M_GameManager.end();
    M_MigrationBg.end();
    M_Scene_Migration.end();
}

//
//	�Q�[���̏��������܂�
//////////////////////////////////////////////////////////////////////////

// DirectX�������O����
void Usable::BeforeInit(void)
{
    //int mbResult;
    int win_mode = TRUE;
    //
    //// �t���X�N���[���ɂ��邩�I������
    //mbResult = MessageBox(NULL, STR_MSG_ASKFS, STR_MSGTTL_ASKFS, MB_YESNO);
    //if (mbResult == IDYES) win_mode = FALSE;
    ChangeWindowMode(win_mode);
    // �E�B���h�E�^�C�g����ݒ肷��
    SetMainWindowText(STR_WINTTL);
}

// �Q�[���J�n�O����
void Usable::AfterInit(void)
{
    // InputClass
    Input::Create();
    Input::GetInstance()->Init();

    sceneState = State_Title;
    //sceneState = State_Editor;
    M_SceneTitle.init();
}

// �Q�[���I���㏈��
void Usable::End(void)
{
    // InputClass�̏I������
    Input::Destroy();
    // �S�O���t�B�b�N�̍폜
    DxLib::InitGraph();
    // �S���f�[�^�̍폜
    InitSoundMem();
}

// �Q�[�����C�����[�v
void Usable::MainLoop(void)
{
    M_Usable.AfterInit();    // �Q�[���J�n�O����

    while (ProcessMessage() == 0)		    // ProcessMessage������ɏ�������Ă���Ԃ̓��[�v
    {
        ClearDrawScreen();  				// ����ʂ��폜
        Input::GetInstance()->Updata();     // ���͏�Ԃ̍X�V����

        switch (sceneState)
        {
        case State_Editor:
            M_SceneEditor.update();        // �G�f�B�^�[�X�V����
            break;
        case State_Title:
            M_SceneTitle.update();         // �^�C�g���X�V����
            M_SceneTitle.draw();           // �^�C�g���`�揈��
            //M_System.drawDebugString(); // debug
            break;
        case State_Choice:
            M_SceneChoice.update();        // �X�e�[�W�I���X�V����
            M_SceneChoice.draw();          // �X�e�[�W�I��`�揈��
            //M_System.drawDebugString(); // debug
            break;
        case State_Game:
            M_SceneGame.update();          // �Q�[���X�V����
            M_SceneGame.draw();            // �Q�[���`�揈��
            //M_System.drawDebugString(); // debug
            break;
        }

        //M_System.inputDebugKey();   // debug
        ScreenFlip();   // VSYNC��҂�

        // ESC�L�[�����͏�ɊĎ��B�����ꂽ�璼���ɏI��
        int stick = CheckHitKey(KEY_INPUT_ESCAPE);
        if (stick == 1) break;
        M_Usable.countGameTime();   // �Q�[���J�E���^��i�߂�
    }
}

// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    M_Usable.BeforeInit();                // DirectX�������O����
    if (DxLib_Init() == -1) return -1;  // �G���[���N�����璼���ɏI��

    SetGraphMode(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, 32);
    SetDrawScreen(DX_SCREEN_BACK);      // �`��X�N���[���𗠑��Ɏw��
    SetWaitVSyncFlag(TRUE);             // VSYNC��L���ɂ���
    M_Usable.AfterInit();                 // DirectX�������㏈��
    M_Usable.MainLoop();                  // �Q�[���{��(���C�����[�v)
    M_Usable.End();                       // �Q�[���I���㏈��
    DxLib_End();                        // �c�w���C�u�����g�p�̏I������
    return 0;                           // �\�t�g�̏I��
}
