#pragma once
#include "CObj.h"

class CCollider;
class CTexture;
class CFlipbookPlayer;
class CFSM;
class CSound;

class CKeybox :
    public CObj
{

private:
    CTexture* m_Tex;
    CCollider* m_HitBox;
    CFlipbookPlayer* m_FlipbookPlayer;
    CSound* KeyBoxSound;
    CCollider* m_Collider;

    bool openbox;

public:
    void CreateKeyBoxFlipbook();
    void CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame);
    float x_offset;
    float y_offset;
    void SetOffset(float _x, float _y) { x_offset = _x; y_offset = _y; };

    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

public:
    CKeybox();
    void SetSound();
    ~CKeybox();
};

