#pragma once
#include "CObj.h"

class CFlipbookPlayer;
class CSound;

class CThorn :
    public CObj
{
public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;
    void SetThorn(int _d) { ThornNUM = _d; }

    /*virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);*/

    float m_DetectRange;
    CFlipbookPlayer* m_FlipbookPlayer;
    CObj* m_Target;
    CCollider* m_HitBox;
    int ThornNUM;
    
    void ChangePlayerMove();

    bool PlayerMove;
    bool Hit;
    Vec2 CurPos;
    bool BOSS_CHECK = false;
    bool CheckStayThorn();
    bool CheckStayMonsterThorn();
    float x_offset;
    float y_offset;
    void SetOffset(float _x, float _y) { x_offset = _x; y_offset = _y; };
    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);

private:
    void CreatePlayerFlipbook();
    void CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame);
    CSound* pThorn_damage0;
    CSound* pThorn_damage1;
public:
    CThorn();
    ~CThorn();
};

