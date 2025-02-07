#include "pch.h"
#include "CFlipbookPlayer.h"

#include "CTimeMgr.h"
#include "CFlipbook.h"
#include "CKeyMgr.h"

#include "CEngine.h"
#include "CSprite.h"
#include "CTexture.h"
#include "CAssetMgr.h"

CFlipbookPlayer::CFlipbookPlayer()
	: CComponent(COMPONENT_TYPE::FLIPBOOKPLAYER)
	, m_CurFlipbook(nullptr)
	, m_SpriteIdx(0)
	, m_FPS(0.f)
	, m_Time(0.f)
	, m_Repeat(false)
	, m_Finish(false)
	, m_Tex(nullptr)
{
}

CFlipbookPlayer::~CFlipbookPlayer()
{
}
 
void CFlipbookPlayer::FinalTick()
{
	// ���� ������� Flipbook �� ������ ��
	if (nullptr == m_CurFlipbook)
	{
		return;
	}

	if (m_Finish)
	{	
		// �ݺ� ����ϱ�� ������ �ٽ� 0 �� ��������Ʈ�� �ε����� �����Ѵ�.
		if (m_Repeat)
			Reset();

		// �ѹ� ����� ������(m_Finish), �ݺ� �����尡 �ƴ϶��
		// ������ �������� �����ϵ��� �Ѵ�.
		else
			return;
	}	

	// FPS �� ���� �ð�üũ
	m_Time += DT;
	if (1.f / m_FPS <= m_Time)
	{
		m_Time -= 1.f / m_FPS;
		++m_SpriteIdx;

		// ������ Sprite �� �����ߴٸ�
		if (m_CurFlipbook->GetMaxSpriteCount() <= m_SpriteIdx)
		{
			// Finish ���� On
			m_Finish = true;
			--m_SpriteIdx;
		}
	}
}

void CFlipbookPlayer::Render(float _Yoffset, float _Xoffset, float _scale)
{
	if (nullptr == m_CurFlipbook)
		return;

	CSprite* Sprite = m_CurFlipbook->GetSprite(m_SpriteIdx);
	
	// Sprite �� ȭ�鿡 �׸���.
	HDC hBackDC = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = GetOwner()->GetRenderPos();

	m_Tex = Sprite->GetAtlas();

	float b = vPos.x - (m_Tex->GetWidth()) / 2.f + _Xoffset;
	float a = vPos.y - (m_Tex->GetHeight()) / 2.f + _Yoffset;

	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;



	AlphaBlend(
		hBackDC
		, vPos.x - (m_Tex->GetWidth()) / 2.f + _Xoffset
		, vPos.y - (m_Tex->GetHeight()) / 2.f + _Yoffset
		, m_Tex->GetWidth() * _scale
		, m_Tex->GetHeight() * _scale
		, m_Tex->GetDC()
		, 0
		, 0
		, m_Tex->GetWidth()
		, m_Tex->GetHeight()
		, blend);
	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	ReleaseDC(hwnd, hBackDC);
	//DeleteObject(hfont);

}

void CFlipbookPlayer::CenterRender(float _Yoffset, float _Xoffset, float scale)
{
	if (nullptr == m_CurFlipbook)
		return;

	CSprite* Sprite = m_CurFlipbook->GetSprite(m_SpriteIdx);

	// Sprite �� ȭ�鿡 �׸���.
	HDC hBackDC = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = GetOwner()->GetRenderPos();

	m_Tex = Sprite->GetAtlas();

	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(
		hBackDC,
		1920.f / 2.f - m_Tex->GetWidth()/2.f + _Xoffset,
		1080.f / 2.f - m_Tex->GetHeight() / 2.f + _Yoffset,
		m_Tex->GetWidth() * scale,  // ����� �ʺ� ������ ����
		m_Tex->GetHeight() * scale, // ����� ���̿� ������ ����
		m_Tex->GetDC(),
		0,
		0,
		m_Tex->GetWidth(),
		m_Tex->GetHeight(),
		blend
	);
	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	ReleaseDC(hwnd, hBackDC);
}

void CFlipbookPlayer::Fire_Render(float x_offset, float y_offset, float scale)
{
	if (nullptr == m_CurFlipbook)
		return;

	CSprite* Sprite = m_CurFlipbook->GetSprite(m_SpriteIdx);

	// Sprite �� ȭ�鿡 �׸���.
	HDC hBackDC = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = GetOwner()->GetRenderPos();

	m_Tex = Sprite->GetAtlas();

	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(
		hBackDC,
		vPos.x - (m_Tex->GetWidth() * scale) / 2.f + x_offset,
		vPos.y - (m_Tex->GetHeight() * scale) / 2.f + y_offset,
		m_Tex->GetWidth() * scale,  // ����� �ʺ� ������ ����
		m_Tex->GetHeight() * scale, // ����� ���̿� ������ ����
		m_Tex->GetDC(),
		0,
		0,
		m_Tex->GetWidth(),
		m_Tex->GetHeight(),
		blend
	);
	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	ReleaseDC(hwnd, hBackDC);
	//DeleteObject(hfont);
}

void CFlipbookPlayer::FullRender()
{
	if (nullptr == m_CurFlipbook)
		return;

	CSprite* Sprite = m_CurFlipbook->GetSprite(m_SpriteIdx);

	// Sprite �� ȭ�鿡 �׸���.
	HDC hBackDC = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = GetOwner()->GetRenderPos();
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	m_Tex = Sprite->GetAtlas();

	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(
		hBackDC
		, 0
		, vResolution.y - m_Tex->GetHeight()
		, m_Tex->GetWidth()
		, m_Tex->GetHeight()
		, m_Tex->GetDC()
		, 0
		, 0
		, m_Tex->GetWidth()
		, m_Tex->GetHeight()
		, blend);
	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	ReleaseDC(hwnd, hBackDC);
	//DeleteObject(hfont);
}

void CFlipbookPlayer::Inplace_Render(Vec2 _Pos, float _Yoffset, float _Xoffset)
{
	if (nullptr == m_CurFlipbook)
		return;

	CSprite* Sprite = m_CurFlipbook->GetSprite(m_SpriteIdx);

	// Sprite �� ȭ�鿡 �׸���.
	HDC hBackDC = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = _Pos;

	m_Tex = Sprite->GetAtlas();

	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	float scale = 1.f;

	AlphaBlend(
		hBackDC,
		vPos.x - (m_Tex->GetWidth() * scale) / 2.f + _Xoffset,
		vPos.y - (m_Tex->GetHeight() * scale) / 2.f + _Yoffset,
		m_Tex->GetWidth() * scale,  // ����� �ʺ� ������ ����
		m_Tex->GetHeight() * scale, // ����� ���̿� ������ ����
		m_Tex->GetDC(),
		0,
		0,
		m_Tex->GetWidth(),
		m_Tex->GetHeight(),
		blend
	);
	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	ReleaseDC(hwnd, hBackDC);
	//DeleteObject(hfont);
}

//Vec2 LeftTop = Vec2(vPos.x - (Sprite->GetSlice().x / 2) + Sprite->GetOffset().x, vPos.y - (Sprite->GetSlice().y / 2) + Sprite->GetOffset().y);

//TransparentBlt(hBackDC
//	, vPos.x - (Sprite->GetSlice().x / 2) + Sprite->GetOffset().x
//	, vPos.y - (Sprite->GetSlice().y / 2) + Sprite->GetOffset().y
//	, Sprite->GetSlice().x
//	, Sprite->GetSlice().y
//	, Sprite->GetAtlas()->GetDC()
//	, Sprite->GetLeftTop().x
//	, Sprite->GetLeftTop().y
//	, Sprite->GetSlice().x
//	, Sprite->GetSlice().y
//	, RGB(255, 0, 255));

//m_Tex = CAssetMgr::GetInst()->LoadTexture(L"Character", L"Texture\\TX_GlowScene_2.png");