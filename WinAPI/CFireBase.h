#pragma once
#include "CObj.h"

class CTexture;
class CFlipbookPlayer;

class CFireBase :
    public CObj
{
    CFlipbookPlayer* m_FlipbookPlayer;
    CTexture* m_Tex;

    int FLAMBASENum;

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

    void SetFireBase(int _FlamBase) { FLAMBASENum = _FlamBase; };

    float x_offset;
    float y_offset;
    void SetOffset(float _x, float _y) { x_offset = _x; y_offset = _y; };

public:
    CFireBase();
    ~CFireBase();
    
};

