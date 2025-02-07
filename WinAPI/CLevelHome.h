#pragma once
#include "CLevel.h"
class CLevelHome :
    public CLevel
{
    void Init() override;

    virtual void Begin() override;
    virtual void Render() override;
    virtual void End() override;

public:
    CLevelHome();
    ~CLevelHome();
};

