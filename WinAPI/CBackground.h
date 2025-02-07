#pragma once
#include "CObj.h"

class CTexture;

class CBackground :
    public CObj
{
private:
    CTexture* m_Tex;


public:
    void SetBackgroundMap(const wstring& _Pngname);

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

public:
    CBackground();
    ~CBackground();
};

