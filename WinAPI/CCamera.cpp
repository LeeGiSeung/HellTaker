#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CObj.h"

#include "CAssetMgr.h"
#include "CTexture.h"
#include "CEngine.h"
#include "CSelectGDI.h"

CCamera::CCamera()
	: m_Target(nullptr)
	, m_Duration(0.f)
	, m_Amplitude(0.f)
	, m_Frequency(0.f)
	, m_Time(0.f)
	, m_Dir(0.2f)
	, m_bOscillation(false)
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	m_CamTex = CAssetMgr::GetInst()->CreateTexture(L"CameraTex", (UINT)vResolution.x, (UINT)vResolution.y);
	m_CamTex1 = CAssetMgr::GetInst()->CreateTexture(L"CameraTex1", (UINT)vResolution.x, (UINT)vResolution.y);

	// m_CamTex1 전체를 red 색으로 채운다.
	//HBRUSH hPrev = (HBRUSH)SelectObject(m_CamTex1->GetDC(), CEngine::GetInst()->GetBrush(BRUSH_TYPE::RED));
	//Rectangle(m_CamTex1->GetDC(), -1, -1, (int)vResolution.x + 1, (int)vResolution.y + 1);
	//SelectObject(m_CamTex1->GetDC(), hPrev);
}

CCamera::~CCamera()
{
}

void CCamera::Init()
{
	Vec2 Resolution = CEngine::GetInst()->GetResolution();
	//Vec2 Resolution = CEngine::GetInst()->GetResolution();
	//m_LookAt = Resolution / 2.f;
	m_LookAt = Vec2(1920 / 2.f, 1080 / 2.f);

	m_Offset = Vec2(0.f, 0.f);
}

void CCamera::Tick()
{
	Vec2 Resolution = CEngine::GetInst()->GetResolution();
	m_Diff = (m_LookAt + m_Offset) - (Resolution / 2.f);

	if (KEY_PRESSED(KEY::W))
		m_LookAt.y -= DT * 500.f;
	if (KEY_PRESSED(KEY::S))
		m_LookAt.y += DT * 500.f;
	if (KEY_PRESSED(KEY::A))
		m_LookAt.x -= DT * 500.f;
	if (KEY_PRESSED(KEY::D))
		m_LookAt.x += DT * 500.f;

	if (m_Target)
	{
		m_LookAt = m_Target->GetPos();
	}
	else {
		m_LookAt = Vec2(1920/2.f,1080/2.f);
	}
	
	// 카메라 진동 효과
	Oscillation();
}

void CCamera::Render()
{
	if (m_CamEffectList.empty())
		return;

	tCamEffect& effect = m_CamEffectList.front();

	// 진행률
	float NormalizedAge = Saturate(effect.Time / effect.Duration);
	int Alpha = 0;
	CTexture* pTex = nullptr;

	// FADE_IN : 점점 밝아진다		255 -> 0
	// FADE_OUT : 점점 어두워진다		0 -> 255

	if (FADE_IN == effect.Effect)
	{
		Alpha = (int)(255.f * (1.f - NormalizedAge));
		pTex = m_CamTex;
	}
	else if (FADE_OUT == effect.Effect)
	{
		Alpha = (int)(255.f * NormalizedAge);
		pTex = m_CamTex;
	}
	else if (HEART == effect.Effect)
	{
		NormalizedAge *= 2.f;

		if (NormalizedAge <= 1.f)
		{
			Alpha = (int)(150.f * NormalizedAge);
		}
		else
		{
			NormalizedAge -= 1.f;
			Alpha = (int)(150.f * (1.f - NormalizedAge));			
		}

		pTex = m_CamTex1;
	}

	// 후처리 효과시간이 만료되면 기능을 Off 한다.
	effect.Time += DT;
	if (effect.Duration <= effect.Time)
	{
		m_CamEffectList.pop_front();
	}

	HDC dc = CEngine::GetInst()->GetSecondDC();
	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = Alpha; // 추가 알파블렌드
	blend.AlphaFormat = 0;

	AlphaBlend(dc
		, 0.f, 0.f
		, pTex->GetWidth()
		, pTex->GetHeight()
		, pTex->GetDC()
		, 0, 0
		, pTex->GetWidth()
		, pTex->GetHeight()
		, blend);

	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	ReleaseDC(hwnd, dc);
	//DeleteObject(hfont);
}

void CCamera::Oscillation()
{
	if (false == m_bOscillation)
		return;

	// 진폭과 속도 조정 (작게 설정)
	float SpeedX = m_Amplitude * 5.f * m_Frequency;  // x축 속도 조정
	float SpeedY = m_Amplitude * 5.f * m_Frequency;  // y축 속도 조정

	// x축, y축 각각 흔들림 적용
	m_Offset.x += SpeedX * m_DirX * DT;
	m_Offset.y += SpeedY * m_DirY * DT;

	// x축 흔들림 진폭 초과 시 방향 전환
	if (m_Amplitude < fabs(m_Offset.x))
	{
		m_Offset.x = m_Amplitude * m_DirX;
		m_DirX *= -1.f;
		m_Offset.x += m_DirX * (m_Amplitude - fabs(m_Offset.x));
	}

	// y축 흔들림 진폭 초과 시 방향 전환
	if (m_Amplitude < fabs(m_Offset.y))
	{
		m_Offset.y = m_Amplitude * m_DirY;
		m_DirY *= -1.f;
		m_Offset.y += m_DirY * (m_Amplitude - fabs(m_Offset.y));
	}

	// 시간 경과 확인 및 진동 종료
	m_Time += DT;
	if (m_Duration <= m_Time)
	{
		m_bOscillation = false;
		m_Offset = Vec2(0.f, 0.f);
	}

	//if (false == m_bOscillation)
	//	return;

	//float Speed = m_Amplitude * 50.f * m_Frequency;
	//m_Offset.y += Speed * m_Dir * DT;
	//
	//// 만약 진폭크기를 넘어서버리면, 방향을 전환한다.
	//if (m_Amplitude < fabs(m_Offset.y))
	//{
	//	// 진폭 최대치로 설정
	//	m_Offset.y = m_Amplitude * m_Dir; 

	//	// 방향 전환
	//	m_Dir *= -1.f;				

	//	// 초과량을 전환된 방향쪽으로 전진시킴
	//	m_Offset.y +=  m_Dir * (m_Amplitude - fabs(m_Offset.y)); 
	//}

	//m_Time += DT;

	//if (m_Duration <= m_Time)
	//{
	//	m_bOscillation = false;
	//	m_Offset = Vec2(0.f, 0.f);
	//}	
}