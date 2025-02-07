#pragma once
#include "CLevel.h"

class CObj;
class CPlayer;

class CLevelTwo :
    public CLevel
{
    void Init() override;

    virtual void Begin() override;
    virtual void Render() override;
    virtual void End() override;


public:
    CLevelTwo();
    ~CLevelTwo();
};

