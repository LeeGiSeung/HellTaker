#pragma once
#include "CObj.h"

class CCollider;
class CTexture;
class CFlipbookPlayer;
class CFSM;
class CSound;
class CThorn;

enum DIRECTION;

class CMonster :
    public CObj
{
private:
    tMonInfo    m_Info;

    int         m_Dir;
    float       m_Speed;
    Vec2        m_InitPos;
    float       m_Dist;

    CFlipbookPlayer* m_FlipbookPlayer;
    CTexture*   m_Tex;
    CCollider*  m_Collider;
    CFSM*       m_FSM;

    bool MonsterHitFlipbook;

    int DeathSound = 0;
    CSound*     Monster_Die_Sound_1;
    CSound*     Monster_Die_Sound_2;
    CSound*     Monster_Die_Sound_3;
    bool MONSTER_MOVING_CHECK;

    DIRECTION Move_Direction;
    float Moving_TickPos;
    Vec2 Moving_CurPos;
    Vec2 Moving_GoalPos;
    Vec2 Moving_MovePos;

public:
    void SetSpeed(float _Speed) { m_Speed = _Speed; }
    void SetDistance(float _Dist) { m_Dist = _Dist; }
    void CreateMonsterFlipbook();
    void CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame);

    void IFINPLACETHORNUP();
    void IFNextPointUpThorn();
    CThorn* m_Target_Thorn = nullptr;
    void SetSound(int _SelectDeathSound);
    void Move(int Dir);
    const tMonInfo& GetMonInfo() { return m_Info; }

    float x_offset;
    float y_offset;
    void SetOffset(float _x, float _y) { x_offset = _x; y_offset = _y; };

public:
    virtual void Begin() override;
    virtual void Tick() override;            
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider) override;

public:
    CMonster();
    void SetSound();
    ~CMonster();
};

