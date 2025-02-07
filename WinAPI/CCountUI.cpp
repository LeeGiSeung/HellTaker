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
	// �� �����ӿ� ���� ��� ����
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
		100,                    // ���� ����
		0,                     // ���� �� (0���� �ڵ� ����)
		0,                     // ���� ����
		0,                     // ���� ���� ����
		FW_NORMAL,				// ���� �β�
		FALSE,                 // ����� ����
		FALSE,                 // ���� ����
		FALSE,                 // ��Ҽ� ����
		ANSI_CHARSET,          // ���� ����
		OUT_DEFAULT_PRECIS,    // ��� ���е�
		CLIP_DEFAULT_PRECIS,   // Ŭ���� ���е�
		DEFAULT_QUALITY,       // ��� ǰ��
		DEFAULT_PITCH | FF_SWISS, // �۲� ������ �� �۲� �йи�
		L"CrimsonPro-Medium"   // �۲� �̸�
	);

	HFONT hOldFont = (HFONT)SelectObject(dc, hFont);

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	SetGraphicsMode(dc, GM_ADVANCED);
	SetBkMode(dc, TRANSPARENT); // ����� �������� ����

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	COLORREF textColor = RGB(255, 255, 255); // R, G, B �� ����
	SetTextColor(dc, textColor); // DC�� �ؽ�Ʈ ���� ����

	if (CountUI == COUNT_UI_LEFT) {
		SetBkMode(dc, TRANSPARENT); // ��� ��� ����

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
			text = std::to_wstring(cur_count); // cur_count�� ���ڿ��� ��ȯ
		}

		int length = text.length(); // ���ڿ� ���� ���
		

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

		int length = text.length(); // ���ڿ� ���� ���

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

	SelectObject(dc, hOldFont); // ���� ��Ʈ ����
	DeleteObject(hFont); // ��Ʈ �޸� ����
	DeleteObject(hOldFont);
	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	ReleaseDC(hwnd, dc);
	
}

