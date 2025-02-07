#pragma once
#include "CObj.h"

class CCollider;
class CFlipbookPlayer;

class CDemon :
    public CObj
{
public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;
    void SetDemon(int _d) { DemonNUM = _d; }

    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);

    float m_DetectRange;
    CFlipbookPlayer* m_FlipbookPlayer;
    CFlipbookPlayer* m_FlipbookDemonVFXPlayer = nullptr;
    CObj* m_Target;
    CCollider* m_HitBox;
    int DemonNUM;
    
    bool DemonTalk = false;
    float kisstime;
    bool clearLevel = false;

    Vec2 CurPos;
    
    float TickPos;
    bool dir = false;
    float x_offset;
    float y_offset;
    void SetOffset(float _x, float _y) { x_offset = _x; y_offset = _y; };

private:
    void CreatePlayerFlipbook();
    void CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame);


public:
    CDemon();
    ~CDemon();

};

