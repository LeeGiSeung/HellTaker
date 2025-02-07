#pragma once
#include "CObj.h"

class CCollider;
class CTexture;
class CFlipbookPlayer;
class CFSM;
class CSound;

class CKey :
    public CObj
{

public:
    CFlipbookPlayer* m_FlipbookPlayer;
    CCollider* m_Collider;

    CSound* KeyPickUpSound;

    bool GetKey;

    void CreateMonsterFlipbook();
    void CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame);

    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;

    float x_offset;
    float y_offset;
    void SetOffset(float _x, float _y) { x_offset = _x; y_offset = _y; };
public:
    CKey();
    void SetSound();
    ~CKey();

};

