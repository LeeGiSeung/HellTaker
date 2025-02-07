#include "pch.h"
#include "CCountUI.h"
#include "CEngine.h"
#include "CAssetMgr.h"
#include "CCollider.h"

#include "CLevel.h"
#include "CLevelMgr.h"
#include "CPlayer.h"

CCountUI::CCountUI()
	:m_Tex(nullptr)
	,CountUI(0)
{
}

CCountUI::~CCountUI()
{
}


void CCountUI::SetCountUI(int _UI)
{
	CountUI = _UI;

	wchar_t filePath[100] = {};
	wchar_t textureName[100] = {};
	// 각 프레임에 대한 경로 생성
	if (CountUI == COUNT_UI_LEFT) {
		swprintf_s(filePath, 100, L"Texture\\mainUIexport_fUI0001.png");
		swprintf_s(textureName, 100, L"mainUIexport_fUI0001");
	}
	else if (CountUI == COUNT_UI_RIGHT) {
		swprintf_s(filePath, 100, L"Texture\\mainUIexport_fUI0001LEFT.png");
		swprintf_s(textureName, 100, L"mainUIexport_fUI0001LEFT");
	}

	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

	m_Tex = pAtlas;
}

void CCountUI::Begin()
{
}

void CCountUI::Tick()
{
}

void CCountUI::Render()
{
	HDC dc = CEngine::GetInst()->GetSecondDC();
	HFONT hFont = CreateFont(
		100,                    // 글자 높이
		0,                     // 글자 폭 (0으로 자동 설정)
		0,                     // 글자 각도
		0,                     // 글자 기준 각도
		FW_NORMAL,				// 글자 두께
		FALSE,                 // 기울임 여부
		FALSE,                 // 밑줄 여부
		FALSE,                 // 취소선 여부
		ANSI_CHARSET,          // 문자 집합
		OUT_DEFAULT_PRECIS,    // 출력 정밀도
		CLIP_DEFAULT_PRECIS,   // 클리핑 정밀도
		DEFAULT_QUALITY,       // 출력 품질
		DEFAULT_PITCH | FF_SWISS, // 글꼴 가변폭 및 글꼴 패밀리
		L"CrimsonPro-Medium"   // 글꼴 이름
	);

	HFONT hOldFont = (HFONT)SelectObject(dc, hFont);

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	SetGraphicsMode(dc, GM_ADVANCED);
	SetBkMode(dc, TRANSPARENT); // 배경을 투명으로 설정

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	COLORREF textColor = RGB(255, 255, 255); // R, G, B 값 설정
	SetTextColor(dc, textColor); // DC에 텍스트 색상 설정

	if (CountUI == COUNT_UI_LEFT) {
		SetBkMode(dc, TRANSPARENT); // 배경 모드 설정

		wchar_t filePath[100] = {};
		wchar_t textureName[100] = {};

		swprintf_s(filePath, 100, L"Texture\\mainUIexport.png");
		swprintf_s(textureName, 100, L"mainUIexport");
		CTexture* front = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		AlphaBlend(dc
			, 0.f
			, 0.f
			, front->GetWidth()
			, front->GetHeight()
			, front->GetDC()
			, 0, 0
			, front->GetWidth()
			, front->GetHeight()
			, blend);

		AlphaBlend(dc,
			0,
			m_Tex->GetHeight() / 2.f + 50.f,
			m_Tex->GetWidth(),
			m_Tex->GetHeight(),
			m_Tex->GetDC(),
			0, 0,
			m_Tex->GetWidth(),
			m_Tex->GetHeight(),
			blend);

		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
		//CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
		CPlayer* cp = dynamic_cast<CPlayer*>(vecPlayer[0]);

		int cur_count = cp->GetPlayerMoveCount();
		std::wstring text;
		if (cur_count == 0) {
			text = L"X";
		}
		else {
			text = std::to_wstring(cur_count); // cur_count를 문자열로 변환
		}

		int length = text.length(); // 문자열 길이 계산
		

		TextOut(
			dc,
			150,
			m_Tex->GetHeight() + 50.f + 50.f,
			text.c_str(),
			length
		);
	}

	else if (CountUI == COUNT_UI_RIGHT) {
		wchar_t filePath[100] = {};
		wchar_t textureName[100] = {};

		swprintf_s(filePath, 100, L"Texture\\mainUIexportRIGHT.png");
		swprintf_s(textureName, 100, L"mainUIexportRIGHT");
		CTexture* front = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		AlphaBlend(dc
			, 1920.f - front->GetWidth() - 10.f
			, 0.f
			, front->GetWidth()
			, front->GetHeight()
			, front->GetDC()
			, 0, 0
			, front->GetWidth()
			, front->GetHeight()
			, blend);


		AlphaBlend(dc
			, 1920.f - m_Tex->GetWidth() - 10.f
			, m_Tex->GetHeight() / 2.f + 50.f
			, m_Tex->GetWidth()
			, m_Tex->GetHeight()
			, m_Tex->GetDC()
			, 0, 0
			, m_Tex->GetWidth()
			, m_Tex->GetHeight()
			, blend);


		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
		CPlayer* cp = dynamic_cast<CPlayer*>(vecPlayer[0]);

		std::wstring text;
		if (cp->CurLevel == STAGE_0) {
			text = L"I";
		}
		else if (cp->CurLevel == STAGE_1) {
			text = L"II";
		}
		else if (cp->CurLevel == STAGE_2) {
			text = L"III";
		}
		else if (cp->CurLevel == STAGE_3) {
			text = L"IV";
		}
		else if (cp->CurLevel == STAGE_4) {
			text = L"V";
		}
		else if (cp->CurLevel == STAGE_5) {
			text = L"VI";
		}
		else if (cp->CurLevel == STAGE_6) {
			text = L"VII";
		}
		else if (cp->CurLevel == STAGE_7) {
			text = L"VIII";
		}
		else if (cp->CurLevel == STAGE_8) {
			text = L"IX";
		}

		int length = text.length(); // 문자열 길이 계산

		if (text.size() == 1) {
			TextOut(
				dc,
				1920.f - 230.f,
				m_Tex->GetHeight() + 50.f +50.f,
				text.c_str(),
				length
			);
		}
		else if (text.size() == 2) {
			TextOut(
				dc,
				1920.f - 240.f,
				m_Tex->GetHeight() + 50.f + 50.f,
				text.c_str(),
				length
			);
		}
		else if (text.size() == 3) {
			TextOut(
				dc,
				1920.f - 250.f,
				m_Tex->GetHeight() + 50.f + 50.f,
				text.c_str(),
				length
			);
		}
		else if (text.size() == 4) {
			TextOut(
				dc,
				1920.f - 260.f,
				m_Tex->GetHeight() + 50.f + 50.f,
				text.c_str(),
				length
			);
		}

	}

	SelectObject(dc, hOldFont); // 이전 폰트 복원
	DeleteObject(hFont); // 폰트 메모리 해제
	DeleteObject(hOldFont);
	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	ReleaseDC(hwnd, dc);
	
}

