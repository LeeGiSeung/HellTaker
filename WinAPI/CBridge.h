#pragma once
#include "CObj.h"

class CSound;
class CTexture;
class CBridge :
    public CObj
{
    CTexture* m_Bridge;
    CTexture* m_LeftOutLine;
    CTexture* m_RightOutLine;


public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;


    bool LoopSoundPlay = false;
    bool MoveBirdge = false;
    CSound* boss_machine_loop = nullptr;
    float elapsedTime = 0.f;

    float x_offset;
    float y_offset;
    void SetOffset(float _x, float _y) { x_offset = _x; y_offset = _y; };

public:
    CBridge();
    void SetSound();
    ~CBridge();
};

