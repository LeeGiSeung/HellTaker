#pragma once
#include "CObj.h"

class CFlipbookPlayer;
class CSound;

class CDeathP :
    public CObj
{
private:
    CFlipbookPlayer* m_FlipbookPlayer;
    CSound* pTransSound;

    int m_SpriteIdx;
   

    void CreatePlayerFlipbook();
    void CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame);
public:
    bool    CDeathEnd;
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

public:
    CDeathP();
    void SetSound();
    ~CDeathP();
};

