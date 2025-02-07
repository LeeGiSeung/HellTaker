#pragma once
#include "CObj.h"

class CFlipbookPlayer;
class CSound;

class CJudmentPiston :
    public CObj
{
    CFlipbookPlayer* m_FlipbookPlayer;

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

    int TurnPiston = true;
    float elapsedTime = 0.0f;
    float MovePos;
    int Under;
    float Curtime;

    CSound* boss_machine_loop = nullptr;
    bool LoopSoundPlay = false;
    void CreateFireFlipbook();
    void CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame);
    float x_offset;
    float y_offset;
    void SetOffset(float _x, float _y) { x_offset = _x; y_offset = _y; };

public:
    CJudmentPiston();
    ~CJudmentPiston();
};

