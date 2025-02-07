#pragma once
#include "CObj.h"

class CJudmentCastle :
    public CObj
{

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

public:
    CJudmentCastle();
    ~CJudmentCastle();
};

