#pragma once
#include "CObj.h"

class CFlipbookPlayer;
class CSound;

class CDamageChain :
    public CObj
{

public:

    class CCollider* m_Collider;
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;


    void CreatePlayerFlipbook();
    void CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame);


    CSound* ChainBlink_1 = nullptr;
    CSound* ChainBlink_2 = nullptr;
    CSound* ChainBlink_3 = nullptr;
    CSound* ChainBlink_4 = nullptr;
    CSound* pPlayer_damage = nullptr;

    int Chaindir = 0;
    int SelectChainBlinkSound = 0;
    int SelectChainBlick = 0;

    CFlipbookPlayer* m_FlipbookChainPlayer;

    float x_offset = 0.f;
    float y_offset = 0.f;
    void SetOffset(float _x, float _y) { x_offset = _x; y_offset = _y; };
    void SetChainSound(int _sound) { SelectChainBlick = _sound; }
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    float animationProgress;
    bool DeleteChain;
    bool HitChain;
    bool ChainSound;
public:
    CDamageChain();
    void SetSound();
    ~CDamageChain();
};

