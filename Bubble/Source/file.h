#pragma once
#include "singleton.h"
#include "stage_select.h"
// 定数 ----------------------------------------------------------------

// クラス --------------------------------------------------------------
#define M_File (File::getInstance())
class File : public Singleton<File>
{
public:
    void loadMap(void);         // マップデータの読み込み
    void loadMapEditor(void);   // エディターのマップデータの読み込み
    void saveMapEditor(void);   // エディターのマップデータをファイルに保存

private:
    unsigned int cr = 0;
};