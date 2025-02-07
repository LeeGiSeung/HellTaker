#pragma once
#include "CObj.h"

class CTexture;

class CCountUI :
    public CObj
{
    CTexture* m_Tex;
    int CountUI;

public:
    void SetCountUI(int _UI);

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;


public:
    CCountUI();
    ~CCountUI();
};

