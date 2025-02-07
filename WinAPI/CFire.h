#pragma once
#include "CObj.h"

class CFlipbookPlayer;

class CFire :
    public CObj
{
    CFlipbookPlayer* m_FlipbookPlayer;

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;
    
    bool white = false;
    bool use = true;
    int num;

    void CreateFireFlipbook();
    void CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame);
    float x_offset;
    float y_offset;
    void SetOffset(float _x, float _y) { x_offset = _x; y_offset = _y; };

public:
    CFire();
    ~CFire();
};

