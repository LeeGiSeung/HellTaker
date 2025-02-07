#include "CObj.h"

class CFlipbookPlayer;

class CGear :
    public CObj
{
    CFlipbookPlayer* m_FlipbookPlayer;

public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void Render() override;

    int gear;
    bool GearTurn;

    void CreateFireFlipbook();
    void CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame);
    float x_offset;
    float y_offset;
    void SetOffset(float _x, float _y) { x_offset = _x; y_offset = _y; };

public:
    CGear();
    ~CGear();
};
