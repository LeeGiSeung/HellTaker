#pragma once

#include "CObj.h"

class CFlipbookPlayer;
class CSound;
class CPlayer;

class CRestartCutScene :
    public CObj
{

private:
    CSound*             pTransSound;
    CPlayer*            cp;
    

    void CreatePlayerFlipbook();
    void CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame);
public:
    CFlipbookPlayer* m_FlipbookPlayer;
    bool                ReStartCutSceneEnd;
    CSound* Screen_Changer = nullptr;

    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

    void play();


public:
    CRestartCutScene();
    void SetSound();
    ~CRestartCutScene();
};

