#pragma once
#include "CObj.h"

class CTexture;
enum DIRECTION;

class CWall :
    public CObj
{
private:
    CCollider* m_HitBox;
    Vec2 WallSize;

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

    void SetWallSize(float _WallSizeX, float _WallSizeY) 
    { 
        WallSize.x = _WallSizeX;
        WallSize.y = _WallSizeY;
    }

public:
    CWall();
    ~CWall();
};

