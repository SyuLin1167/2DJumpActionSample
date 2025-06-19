#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>

/// <summary>
/// ゲームの操作に必要なキー
/// </summary>
static struct KeyType
{
    const int ESCAPE = KEY_INPUT_ESCAPE;    //エスケープキー
    const int E = KEY_INPUT_E;              //Eキー
    const int M = KEY_INPUT_M;              //Mキー
    const int A = KEY_INPUT_A;              //Aキー
    const int D = KEY_INPUT_D;              //Dキー
    const int LEFT = KEY_INPUT_LEFT;        //左キー
    const int RIGHT = KEY_INPUT_RIGHT;      //右キー
}keyType;


/// <summary>
/// ループ制御用キー一覧
/// </summary>
const static std::vector<int> KEYS = {
    keyType.ESCAPE,
    keyType.E,
    keyType.M,
    keyType.A,
    keyType.D,
    keyType.LEFT,
    keyType.RIGHT,
};