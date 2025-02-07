#pragma once
#include "CLevel.h"
class CLevelFour :
    public CLevel
{
    void Init() override;

    virtual void Begin() override;
    virtual void Render() override;
    virtual void End() override;

public:
    CLevelFour();
    ~CLevelFour();
};

