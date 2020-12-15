#pragma once
#include "singleton.h"
#include "stage_select.h"
// �萔 ----------------------------------------------------------------

// �N���X --------------------------------------------------------------
#define M_File (File::getInstance())
class File : public Singleton<File>
{
public:
    void loadMap(void);         // �}�b�v�f�[�^�̓ǂݍ���
    void loadMapEditor(void);   // �G�f�B�^�[�̃}�b�v�f�[�^�̓ǂݍ���
    void saveMapEditor(void);   // �G�f�B�^�[�̃}�b�v�f�[�^���t�@�C���ɕۑ�

private:
    unsigned int cr = 0;
};