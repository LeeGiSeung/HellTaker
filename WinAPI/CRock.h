#pragma once
#include "CObj.h"

class CTexture;
class CCollider;
class CFlipbookPlayer;

enum DIRECTION;

class CRock :
    public CObj
{
private:
    CTexture*   m_Tex;
    Vec2        m_InitPos;
    CCollider*  m_HitBox;

    bool ROCK_MOVING_CHECK;

    CFlipbookPlayer* m_FlipbookMOVEVFXPlayer;

    DIRECTION Move_Direction;
    float Moving_TickPos;
    Vec2 Moving_CurPos;
    Vec2 Moving_GoalPos;
    Vec2 Moving_MovePos;

    bool VFX_MOVE_RENDER;
    Vec2 MoveVFXRenderPos;

public:
    void SetRock(const wstring& _Pngname);
    void CreatePlayerFlipbook();
    void CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame);
public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;
    void Move(int Dir);
    float x_offset;
    float y_offset;
    void SetOffset(float _x, float _y) { x_offset = _x; y_offset = _y; };
public:
    CRock();
    ~CRock();
};

