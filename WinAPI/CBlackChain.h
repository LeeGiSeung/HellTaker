#pragma once
#include "CObj.h"
class CBlackChain :
    public CObj
{
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

public:
    CBlackChain();
    ~CBlackChain();
};

