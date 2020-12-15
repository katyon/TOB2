// インクルード --------------------------------------------------
#include "Input.h"

// 関数実体 ------------------------------------------------------

Input* Input::instance = NULL;

void Input::Create()
{
    if (!instance)
    {
        instance = new Input;
    }
}

void Input::Destroy()
{
    delete instance;
    instance = NULL;
}

void Input::Init()
{

}

void Input::Updata()
{
    GetHitKeyStateAll(key);

    for (int i = 0; i < 256; i++)
    {
        if (key[i])
        {
            if (key_buf[i] == Not)
                key_buf[i] = Down;
            else if (key_buf[i] == Down)
                key_buf[i] = Stay;
        }
        else key_buf[i] = Not;
        key[i] = key_buf[i];
    }

    GetJoypadXInputState(DX_INPUT_PAD1, &input);

    for (int i = 0; i < 16; i++)
    {
        if (input.Buttons[i])
        {
            if (button[i] == Not)
                button[i] = Down;
            else if (button[i] == Down)
                button[i] = Stay;
        }
        else button[i] = Not;
    }
#pragma region Thumb
    if (input.ThumbLX > 0)
    {
        if (input.ThumbLX < 8000)
            ThumbLX = Not;
        else if (input.ThumbLX < 20000)
            ThumbLX = Mid;
        else if (input.ThumbLX < 35000)
            ThumbLX = Max;
    }
    if (input.ThumbLX < 0)
    {
        if (input.ThumbLX > -8000)
            ThumbLX = Not;
        else if (input.ThumbLX > -20000)
            ThumbLX = -Mid;
        else if (input.ThumbLX > -35000)
            ThumbLX = -Max;
    }

    if (input.ThumbLY > 0)
    {
        if (input.ThumbLY < 8000)
            ThumbLY = Not;
        else if (input.ThumbLY < 20000)
            ThumbLY = Mid;
        else if (input.ThumbLY < 35000)
            ThumbLY = Max;
    }
    if (input.ThumbLY < 0)
    {
        if (input.ThumbLY > -8000)
            ThumbLY = Not;
        else if (input.ThumbLY > -20000)
            ThumbLY = -Mid;
        else if (input.ThumbLY > -35000)
            ThumbLY = -Max;
    }

    if (input.ThumbRX > 0)
    {
        if (input.ThumbRX < 8000)
            ThumbRX = Not;
        else if (input.ThumbRX < 20000)
            ThumbRX = Mid;
        else if (input.ThumbRX < 35000)
            ThumbRX = Max;
    }
    if (input.ThumbRX < 0)
    {
        if (input.ThumbRX > -8000)
            ThumbRX = Not;
        else if (input.ThumbRX > -20000)
            ThumbRX = -Mid;
        else if (input.ThumbRX > -35000)
            ThumbRX = -Max;
    }

    if (input.ThumbRY > 0)
    {
        if (input.ThumbRY < 8000)
            ThumbRY = Not;
        else if (input.ThumbRY < 20000)
            ThumbRY = Mid;
        else if (input.ThumbRY < 35000)
            ThumbRY = Max;
    }
    if (input.ThumbRY < 0)
    {
        if (input.ThumbRY > -8000)
            ThumbRY = Not;
        else if (input.ThumbRY > -20000)
            ThumbRY = -Mid;
        else if (input.ThumbRY > -35000)
            ThumbRY = -Max;
    }
#pragma endregion
}

// 押した瞬間だけTRUEを返す
bool Input::GetKeyDown(int inputKey)
{
    if (key[inputKey] == Down)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 押した瞬間だけTRUEを返す(全てのキー)
bool Input::GetKeyDownAll(void)
{
    for (int inputKey = 0; inputKey < 256; inputKey++)
    {
        if (key[inputKey] == Down)
        {
            return true;
        }
    }

    return false;
}

// 押している間TRUEを返す
bool Input::GetKey(int inputKey)
{
    if (key[inputKey] == Stay || key[inputKey] == Down)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 押した瞬間だけTRUEを返す
bool Input::GetButtonDown(int inputKey)
{
    if (button[inputKey] == Down)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 押した瞬間だけTRUEを返す(全てのボタン)
bool Input::GetButtonDownAll(void)
{
    for (int inputKey = 0; inputKey < 16; inputKey++)
    {
        if (button[inputKey] == Down)
        {
            return true;
        }
    }

    return false;
}

// 押している間TRUEを返す
bool Input::GetButton(int inputKey)
{
    if (button[inputKey] == Stay || button[inputKey] == Down)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 左スティックを倒している時、各方向にTRUEを返す
bool Input::GetLeftThumb(int  LeftThumb)
{
    switch (LeftThumb)
    {
    case Thumb::Not:
        if (ThumbLX == Input::Thumb_State::Zero && ThumbLY == Input::Thumb_State::Zero)   return true;
        break;
    case Thumb::Up:
        if (ThumbLX == Input::Thumb_State::Zero && ThumbLY == Input::Thumb_State::Max)    return true;
        break;
    case Thumb::Before_Upper_Right:
        if (ThumbLX == Input::Thumb_State::Mid && ThumbLY == Input::Thumb_State::Max)     return true;
        break;
    case Thumb::Upper_Right:
        if (ThumbLX == Input::Thumb_State::Max && ThumbLY == Input::Thumb_State::Max)     return true;
        break;
    case Thumb::After_Upper_Right:
        if (ThumbLX == Input::Thumb_State::Max && ThumbLY == Input::Thumb_State::Mid)     return true;
        break;
    case Thumb::Right:
        if (ThumbLX == Input::Thumb_State::Max && ThumbLY == Input::Thumb_State::Zero)    return true;
        break;
    case Thumb::Before_Lower_Right:
        if (ThumbLX == Input::Thumb_State::Max && ThumbLY == -Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Lower_Right:
        if (ThumbLX == Input::Thumb_State::Max && ThumbLY == -Input::Thumb_State::Max)    return true;
        break;
    case Thumb::After_Lower_Right:
        if (ThumbLX == Input::Thumb_State::Mid && ThumbLY == -Input::Thumb_State::Max)    return true;
        break;
    case Thumb::Down:
        if (ThumbLX == Input::Thumb_State::Zero && ThumbLY == -Input::Thumb_State::Max)   return true;
        break;
    case Thumb::Before_Lower_Left:
        if (ThumbLX == -Input::Thumb_State::Mid && ThumbLY == -Input::Thumb_State::Max)   return true;
        break;
    case Thumb::Lower_Left:
        if (ThumbLX == -Input::Thumb_State::Max && ThumbLY == -Input::Thumb_State::Max)   return true;
        break;
    case Thumb::After_Lower_Left:
        if (ThumbLX == -Input::Thumb_State::Max && ThumbLY == -Input::Thumb_State::Mid)   return true;
        break;
    case Thumb::Left:
        if (ThumbLX == -Input::Thumb_State::Max && ThumbLY == Input::Thumb_State::Zero)   return true;
        break;
    case Thumb::Before_Upper_Left:
        if (ThumbLX == -Input::Thumb_State::Max && ThumbLY == Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Upper_Left:
        if (ThumbLX == -Input::Thumb_State::Max && ThumbLY == Input::Thumb_State::Max)    return true;
        break;
    case Thumb::After_Upper_Left:
        if (ThumbLX == -Input::Thumb_State::Mid && ThumbLY == Input::Thumb_State::Max)    return true;
        break;
    case Thumb::Little_Up:
        if (ThumbLX == Input::Thumb_State::Zero && ThumbLY == Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Little_Right:
        if (ThumbLX == Input::Thumb_State::Mid && ThumbLY == Input::Thumb_State::Zero)    return true;
        break;
    case Thumb::Little_Down:
        if (ThumbLX == Input::Thumb_State::Zero && ThumbLY == -Input::Thumb_State::Mid)   return true;
        break;
    case Thumb::Little_Left:
        if (ThumbLX == -Input::Thumb_State::Mid && ThumbLY == Input::Thumb_State::Zero)   return true;
        break;
    case Thumb::Little_Upper_Right:
        if (ThumbLX == Input::Thumb_State::Mid && ThumbLY == Input::Thumb_State::Mid)     return true;
        break;
    case Thumb::Little_Lower_Right:
        if (ThumbLX == Input::Thumb_State::Mid && ThumbLY == -Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Little_Lower_Left:
        if (ThumbLX == -Input::Thumb_State::Mid && ThumbLY == -Input::Thumb_State::Mid)   return true;
        break;
    case Thumb::Little_Upper_Left:
        if (ThumbLX == -Input::Thumb_State::Mid && ThumbLY == Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Roughly_Up:
        if (ThumbLY == Input::Thumb_State::Mid || ThumbLY == Input::Thumb_State::Max)     return true;
        break;
    case Thumb::Roughly_Right:
        if (ThumbLX == Input::Thumb_State::Mid || ThumbLX == Input::Thumb_State::Max)     return true;
        break;
    case Thumb::Roughly_Down:
        if (ThumbLY == -Input::Thumb_State::Mid || ThumbLY == -Input::Thumb_State::Max)   return true;
        break;
    case Thumb::Roughly_Left:
        if (ThumbLX == -Input::Thumb_State::Mid || ThumbLX == -Input::Thumb_State::Max)   return true;
        break;
    }
    return false;
}

// 右スティックを倒している時、各方向にTRUEを返す
bool Input::GetRightThumb(int  RightThumb)
{
    switch (RightThumb)
    {
    case Thumb::Not:
        if (ThumbRX == Input::Thumb_State::Zero && ThumbRY == Input::Thumb_State::Zero)   return true;
        break;
    case Thumb::Up:
        if (ThumbRX == Input::Thumb_State::Zero && ThumbRY == Input::Thumb_State::Max)    return true;
        break;
    case Thumb::Before_Upper_Right:
        if (ThumbRX == Input::Thumb_State::Mid && ThumbRY == Input::Thumb_State::Max)     return true;
        break;
    case Thumb::Upper_Right:
        if (ThumbRX == Input::Thumb_State::Max && ThumbRY == Input::Thumb_State::Max)     return true;
        break;
    case Thumb::After_Upper_Right:
        if (ThumbRX == Input::Thumb_State::Max && ThumbRY == Input::Thumb_State::Mid)     return true;
        break;
    case Thumb::Right:
        if (ThumbRX == Input::Thumb_State::Max && ThumbRY == Input::Thumb_State::Zero)    return true;
        break;
    case Thumb::Before_Lower_Right:
        if (ThumbRX == Input::Thumb_State::Max && ThumbRY == -Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Lower_Right:
        if (ThumbRX == Input::Thumb_State::Max && ThumbRY == -Input::Thumb_State::Max)    return true;
        break;
    case Thumb::After_Lower_Right:
        if (ThumbRX == Input::Thumb_State::Mid && ThumbRY == -Input::Thumb_State::Max)    return true;
        break;
    case Thumb::Down:
        if (ThumbRX == Input::Thumb_State::Zero && ThumbRY == -Input::Thumb_State::Max)   return true;
        break;
    case Thumb::Before_Lower_Left:
        if (ThumbRX == -Input::Thumb_State::Mid && ThumbRY == -Input::Thumb_State::Max)   return true;
        break;
    case Thumb::Lower_Left:
        if (ThumbRX == -Input::Thumb_State::Max && ThumbRY == -Input::Thumb_State::Max)   return true;
        break;
    case Thumb::After_Lower_Left:
        if (ThumbRX == -Input::Thumb_State::Max && ThumbRY == -Input::Thumb_State::Mid)   return true;
        break;
    case Thumb::Left:
        if (ThumbRX == -Input::Thumb_State::Max && ThumbRY == Input::Thumb_State::Zero)   return true;
        break;
    case Thumb::Before_Upper_Left:
        if (ThumbRX == -Input::Thumb_State::Max && ThumbRY == Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Upper_Left:
        if (ThumbRX == -Input::Thumb_State::Max && ThumbRY == Input::Thumb_State::Max)    return true;
        break;
    case Thumb::After_Upper_Left:
        if (ThumbRX == -Input::Thumb_State::Mid && ThumbRY == Input::Thumb_State::Max)    return true;
        break;
    case Thumb::Little_Up:
        if (ThumbRX == Input::Thumb_State::Zero && ThumbRY == Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Little_Right:
        if (ThumbRX == Input::Thumb_State::Mid && ThumbRY == Input::Thumb_State::Zero)    return true;
        break;
    case Thumb::Little_Down:
        if (ThumbRX == Input::Thumb_State::Zero && ThumbRY == -Input::Thumb_State::Mid)   return true;
        break;
    case Thumb::Little_Left:
        if (ThumbRX == -Input::Thumb_State::Mid && ThumbRY == Input::Thumb_State::Zero)   return true;
        break;
    case Thumb::Little_Upper_Right:
        if (ThumbRX == Input::Thumb_State::Mid && ThumbRY == Input::Thumb_State::Mid)     return true;
        break;
    case Thumb::Little_Lower_Right:
        if (ThumbRX == Input::Thumb_State::Mid && ThumbRY == -Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Little_Lower_Left:
        if (ThumbRX == -Input::Thumb_State::Mid && ThumbRY == -Input::Thumb_State::Mid)   return true;
        break;
    case Thumb::Little_Upper_Left:
        if (ThumbRX == -Input::Thumb_State::Mid && ThumbRY == Input::Thumb_State::Mid)    return true;
        break;
    case Thumb::Roughly_Up:
        if (ThumbRY == Input::Thumb_State::Mid || ThumbRY == Input::Thumb_State::Max)     return true;
        break;
    case Thumb::Roughly_Right:
        if (ThumbRX == Input::Thumb_State::Mid || ThumbRX == Input::Thumb_State::Max)     return true;
        break;
    case Thumb::Roughly_Down:
        if (ThumbRY == -Input::Thumb_State::Mid || ThumbRY == -Input::Thumb_State::Max)   return true;
        break;
    case Thumb::Roughly_Left:
        if (ThumbRX == -Input::Thumb_State::Mid || ThumbRX == -Input::Thumb_State::Max)   return true;
        break;
    }
    return false;
}