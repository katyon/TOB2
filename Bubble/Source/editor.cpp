#include "DxLib.h"

#include "common.h"
#include "editor.h"
#include "input.h"
#include "file.h"

// 関数実体 ------------------------------------------------
// 初期設定
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

// 更新処理
void Editor::update(void)
{
    switch (M_Editor.state)
    {
    case Init:
        ///// 初期設定 /////
#pragma region Init
        M_Editor.init();
        M_Editor.state++;
        break;
#pragma endregion
    case Select:
        ///// ステージ選択 /////
#pragma region Select
        // ステージ選択
        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 200, M_Editor.cr, "どのステージを編集しますか？");
        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 170, M_Editor.cr, "選択：W,S or ↑,↓");
        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 140, M_Editor.cr, "決定：Enter");

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
        ///// モード選択 /////
#pragma region Mode
        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 180, M_Editor.cr, "ステージを初期化しますか？");
        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 160, M_Editor.cr, "選択：W,S or ↑,↓");
        DrawFormatString(GAME_SCREEN_WIDTH / 2 - 100, GAME_SCREEN_HEIGHT / 2 - 140, M_Editor.cr, "決定：Enter");

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
        ///// 更新処理 /////
#pragma region Update
        // マウスカーソルの位置を取得
        GetMousePoint(&M_Editor.mousePos.x, &M_Editor.mousePos.y);

        // スクロール
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

        // マップチップ切り替え
        // キーボード操作
        if (M_Input->GetKeyDown(KEY_INPUT_C))
        {
            M_Editor.chipNum++;
        }
        if (M_Input->GetKeyDown(KEY_INPUT_X))
        {
            M_Editor.chipNum--;
        }
        // ホイール操作
        M_Editor.chipNum += GetMouseWheelRotVol();
        if (M_Editor.chipNum < 0)
        {
            M_Editor.chipNum = 0;
        }
        if (M_Editor.chipNum > CHIP_ALLNUM - 1)
        {
            M_Editor.chipNum = CHIP_ALLNUM - 1;
        }

        // 塗り
        if (GetMouseInput() & MOUSE_INPUT_LEFT || M_Input->GetKey(KEY_INPUT_SPACE))
        {
            M_Editor.map[(M_Editor.mousePos.y + M_Editor.mousePosBuf.y) / MAPCHIP_SIZE][(M_Editor.mousePos.x + M_Editor.mousePosBuf.x) / MAPCHIP_SIZE] = M_Editor.chipNum;
        }
        // 消去(0を塗る)
        if (GetMouseInput() & MOUSE_INPUT_RIGHT || M_Input->GetKeyDown(KEY_INPUT_V))
        {
            M_Editor.map[(M_Editor.mousePos.y + M_Editor.mousePosBuf.y) / MAPCHIP_SIZE][(M_Editor.mousePos.x + M_Editor.mousePosBuf.x) / MAPCHIP_SIZE] = 0;
        }

        // コンフィグ
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

        // マップをファイルに保存
        if (M_Input->GetKey(KEY_INPUT_LCONTROL) || M_Input->GetKey(KEY_INPUT_RCONTROL))
        {
            if (M_Input->GetKeyDown(KEY_INPUT_S))
            {
                M_File.saveMapEditor();
                M_Editor.saveFlg = true;
            }
        }

        //// ゲームシーンに切り替え
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

// 描画処理
void Editor::draw(void)
{
    // 描画処理
    // マップチップ
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
                DrawFormatString(MAPCHIP_SIZE * Hor - M_Editor.mapPos.x + MAPCHIP_SIZE / 4, MAPCHIP_SIZE * Ver - M_Editor.mapPos.y + MAPCHIP_SIZE / 4, GetColor(50, 50, 50), "無");
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
    // カーソル
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

    // 使い方説明
    DrawFormatString(10, 0, cr, "0キー:描画しない");
    DrawFormatString(10, 30, cr, "1キー:地形(左)");
    DrawFormatString(10, 60, cr, "2キー:地形(中)");
    DrawFormatString(10, 90, cr, "3キー:地形(右)");
    DrawFormatString(10, 120, cr, "4キー:壁");
    DrawFormatString(10, 150, cr, "5キー:台");
    DrawFormatString(10, 180, cr, "6キー:針");
    DrawFormatString(10, 210, cr, "7キー:分割");
    DrawFormatString(10, 240, cr, "8キー:湧き");
    DrawFormatString(10, 270, cr, "9キー:ゴール");


    DrawFormatString(250, 0, cr, "チップ切り替え:ホイール or X,C");
    DrawFormatString(250, 30, cr, "塗り:左クリック or Space");
    DrawFormatString(250, 60, cr, "削除(0を塗る):右クリック or V");
    DrawFormatString(250, 90, cr, "カーソル移動:マウス");
    DrawFormatString(250, 120, cr, "画面スクロール:W,A,S,D");
    DrawFormatString(250, 150, cr, "１マスだけスクロール:↑,←,↓,→");
    DrawFormatString(250, 180, cr, "データを保存:Ctrl + S");
    DrawFormatString(250, 210, cr, "終了：Esc");

    DrawFormatString(710, 0, cr, "現在のカーソルの位置(マップチップ数)");
    DrawFormatString(710, 30, cr, "X：%d", (mousePos.x + mousePosBuf.x) / MAPCHIP_SIZE);
    DrawFormatString(710, 60, cr, "Y：%d", (mousePos.y + mousePosBuf.y) / MAPCHIP_SIZE);

    DrawFormatString(1700, 0, cr, "マップチップリスト");
    DrawFormatString(1700, 30, cr, "0番:描画しない");
    DrawFormatString(1700, 60, cr, "1番:地形(左)");
    DrawFormatString(1700, 90, cr, "2番:地形(中)");
    DrawFormatString(1700, 120, cr, "3番:地形(右)");
    DrawFormatString(1700, 150, cr, "4番:壁");
    DrawFormatString(1700, 180, cr, "5番:台");
    DrawFormatString(1700, 210, cr, "6番:針");
    DrawFormatString(1700, 240, cr, "7番:分割");
    DrawFormatString(1700, 270, cr, "8番:湧き");
    DrawFormatString(1700, 300, cr, "9番:ゴール");
    DrawFormatString(1700, 330, cr, "10番:水流左上");
    DrawFormatString(1700, 360, cr, "11番:水流右下");

    if (saveTimer > 300)
    {
        saveFlg = false;
        saveTimer = 0;
    }
    if (saveFlg == true)
    {
        DrawFormatString(mousePos.x - 50, mousePos.y - 30, cr, "セーブしました");
        saveTimer++;
    }
}

void Editor::end(void)
{
    DeleteGraph(chipHND);
    DeleteGraph(cursorHND);
}