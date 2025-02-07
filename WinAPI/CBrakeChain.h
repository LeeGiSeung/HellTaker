#pragma once
#include "CObj.h"

class CTexture;
class CSound;

class CBrakeChain :
    public CObj
{
public:

    int hp = 60;
    int alpha = 255;
    bool alphaincr = false;;

    CTexture* m_Tex;
    CSound* boss_big_chain_show_02 = nullptr;
    CSound* boss_big_chain_show_01 = nullptr;

    bool ShowSound = false;
    int dir;

    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

    float x_offset = 0.f;
    float y_offset = 0.f;
    void SetOffset(float _x, float _y) { x_offset = _x; y_offset = _y; };

public:
    CBrakeChain();
    void SetSound();
    ~CBrakeChain();
};

