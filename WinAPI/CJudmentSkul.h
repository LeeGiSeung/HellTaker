#pragma once
#include "CObj.h"
class CJudmentSkul :
    public CObj
{
public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

    int Under;
    int dir;

public:
    CJudmentSkul();
    ~CJudmentSkul();
};

