#pragma once
#include "CLevel.h"
class CLevelBoss_0 :
    public CLevel
{
    void Init() override;

    virtual void Begin() override;
    virtual void Render() override;
    virtual void End() override;

public:
    CLevelBoss_0();
    ~CLevelBoss_0();
};

