#pragma once
#include "CLevel.h"

class CObj;
class CPlayer;

class CLevel_Start :
    public CLevel
{
public:

    void Init() override;

    virtual void Begin() override;
    virtual void Render() override;
    virtual void End() override;

public:
    CLevel_Start();
    ~CLevel_Start();

};

