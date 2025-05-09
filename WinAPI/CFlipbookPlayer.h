#pragma once
#include "CComponent.h"

class CFlipbook;
class CTexture;

class CFlipbookPlayer :
    public CComponent
{
private:

    vector<CFlipbook*>  m_vecFlipbook;  // Flipbook 목록
    CFlipbook*          m_CurFlipbook;  // 현재 재생중인 Flipbook

    CTexture*           m_Tex;
    float               m_FPS;          // Flipbook 재생속도
    float               m_Time;         // 누적시간
    bool                m_Repeat;       // 반복재생인지 아닌지
    bool                m_Finish;       // 재생이 끝났는지 체크

public:
    int                 m_SpriteIdx;    // 현재 재생중인 Flipbook 에서, 화면에 노출중인 Sprite 인덱스
    void AddFlipbook(CFlipbook* _Flipbook) { m_vecFlipbook.push_back(_Flipbook); }
    void AddFlipbook(int _idx, CFlipbook* _Flipbook)
    {
        if (m_vecFlipbook.size() <= _idx)
        {
            m_vecFlipbook.resize(_idx + 1);
        }

        m_vecFlipbook[_idx] = _Flipbook;
    }

    void Play(int _FlipbookIdx, float _FPS, bool _Repeat)
    {
        m_CurFlipbook = m_vecFlipbook[_FlipbookIdx];
        m_SpriteIdx = 0;
        m_FPS = _FPS;
        m_Repeat = _Repeat;
        m_Finish = false;
        m_Time = 0.f;
    }

    bool IsFinish() { return m_Finish; }

    void Reset()
    {
        m_Finish = false;
        m_SpriteIdx = 0;        
    }


public:
    virtual void FinalTick() override;
    void Render(float _Yoffset = 40.f, float _Xoffset = 0.f, float _scale = 1.f);
    void CenterRender(float _Yoffset = 0.f, float _Xoffset = 0.f,float scale = 1.f);
    void Fire_Render(float x_offset = 0.f, float y_offset = 0.f, float scale = 0.58f);
    void FullRender();
    void Inplace_Render(Vec2 _Pos, float _Yoffset = 0.f, float _Xoffset = 0.f);

public:
    CFlipbookPlayer();
    ~CFlipbookPlayer();
};

