#pragma once
#include "CObj.h"

class CFlipbookPlayer;
class CSound;
class CPlayer;

class CSuccess :
    public CObj
{
private:
    CSound* SUCCESS_Sound;
    CPlayer* cp;


    void CreatePlayerFlipbook();
    void CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame);
public:
    CFlipbookPlayer*    m_FlipbookPlayer;
    bool                SuccessEnd;
    bool                SuccessStart = false;

    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

    CSuccess();
    void NewFunction();
    ~CSuccess();
};

