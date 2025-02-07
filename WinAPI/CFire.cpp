#include "pch.h"
#include "CFire.h"
#include "CEngine.h"
#include "CAssetMgr.h"
#include "CCollider.h"

#include "CLevel.h"
#include "CLevelMgr.h"
#include "CFlipbookPlayer.h"
#include "CSprite.h"
#include "CTexture.h"
#include "CFlipbook.h"

enum FIRE_STATE
{
	FIRE,
	WHITE_FIRE
};

CFire::CFire()
	:m_FlipbookPlayer(nullptr)
{
	CreateFireFlipbook();
}

CFire::~CFire()
{
}


void CFire::Begin()
{
	if (white) {
		m_FlipbookPlayer->Play(WHITE_FIRE, 15.f, true);
	}
	else {
		m_FlipbookPlayer->Play(FIRE, 15.f, true);
	}

}

void CFire::Tick()
{
}

void CFire::Render()
{
	HDC dc = CEngine::GetInst()->GetSecondDC();
	if (white) {
		if (use) {
			wchar_t filePath[100] = {};
			wchar_t textureName[100] = {};

			Vec2 vPos = GetRenderPos();

			BLENDFUNCTION blend = {};

			blend.BlendOp = AC_SRC_OVER;
			blend.BlendFlags = 0;
			blend.SourceConstantAlpha = 255;
			blend.AlphaFormat = AC_SRC_ALPHA;

			swprintf_s(filePath, 100, L"Texture\\sinPyre0001.png");
			swprintf_s(textureName, 100, L"sinPyre0001");
			CTexture* front = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				, this->GetPos().x - 130.f
				, this->GetPos().y + 20.f + 30.f
				, front->GetWidth() 
				, front->GetHeight()
				, front->GetDC()
				, 0, 0
				, front->GetWidth()
				, front->GetHeight()
				, blend);
			m_FlipbookPlayer->Render();
		}
		else {
			wchar_t filePath[100] = {};
			wchar_t textureName[100] = {};
			Vec2 vPos = GetRenderPos();

			BLENDFUNCTION blend = {};

			blend.BlendOp = AC_SRC_OVER;
			blend.BlendFlags = 0;
			blend.SourceConstantAlpha = 255;
			blend.AlphaFormat = AC_SRC_ALPHA;

			swprintf_s(filePath, 100, L"Texture\\sinPyre0002.png");
			swprintf_s(textureName, 100, L"sinPyre0002");
			CTexture* front = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				, this->GetPos().x - 130.f
				, this->GetPos().y + 20.f + 30.f
				, front->GetWidth()
				, front->GetHeight()
				, front->GetDC()
				, 0, 0
				, front->GetWidth()
				, front->GetHeight()
				, blend);
		}

	}
	else {
		m_FlipbookPlayer->Fire_Render(x_offset, y_offset);
	}
	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	ReleaseDC(hwnd, dc);
	//DeleteObject(hfont);
}

void CFire::CreateFireFlipbook()
{
	//CreatePngFlipbook(L"FIRE", L"fire", 12);
	//CreatePngFlipbook(L"WHITE_FIRE", L"WhiteFire", 12);
	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);

	m_FlipbookPlayer->AddFlipbook(FIRE, CAssetMgr::GetInst()->LoadFlipbook(L"FIRE", L"Flipbook\\FIRE.flip"));
	m_FlipbookPlayer->AddFlipbook(WHITE_FIRE, CAssetMgr::GetInst()->LoadFlipbook(L"WHITE_FIRE", L"Flipbook\\WHITE_FIRE.flip"));
}

void CFire::CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame)
{
	// Sprite �����ϱ�
	for (int i = 0; i < MaxFrame; i++)
	{
		wchar_t filePath[100] = {};
		wchar_t textureName[100] = {};
		// �� �����ӿ� ���� ��� ����
		swprintf_s(filePath, 100, L"Texture\\%s_%d.png", _Pngname.c_str(), i);
		/*swprintf_s(textureName, 100, L"assets100V%d", i);*/
		swprintf_s(textureName, 100, L"%s_%d", _Pngname.c_str(), i);

		CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		CSprite* pSprite = new CSprite;

		// _RightBot�� �״�� �ѱ��� �ʰ� ũ��� ����ؾ� �մϴ�.
		int a = pAtlas->GetWidth();
		int b = pAtlas->GetHeight();
		int c = 0;

		Vec2 spriteSize = Vec2(static_cast<float>(pAtlas->GetWidth()), static_cast<float>(pAtlas->GetHeight()));
		Vec2 spritePosition = Vec2(0.0f, 0.0f); // ���ϴ� ��ġ�� ����, ���� ��� (0,0)
		pSprite->Create(pAtlas, spritePosition, spriteSize);

		// Key�� ���� ��, wstring�� �̸� ���� �� ���
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, L"%s_%d", _FlipbookName.c_str(), i);  // ���⼭ ���� ���ڿ��� �и��Ͽ� ���
		CAssetMgr::GetInst()->AddSprite(Key, pSprite);

		wstring strSavePath = L"Sprite\\";
		strSavePath += pSprite->GetKey();
		pSprite->Save(strSavePath);
	}


	for (int i = 0; i < MaxFrame; ++i)
	{
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
		wstring Path = L"Sprite\\";
		Path += Key;
		CAssetMgr::GetInst()->LoadSprite(Key, Path + L".sprite");
	}

	// Flipbook �����ϱ�
	CFlipbook* pFlipbook = new CFlipbook;

	for (int i = 0; i < MaxFrame; ++i)
	{
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
		pFlipbook->AddSprite(CAssetMgr::GetInst()->FindSprite(Key));
	}

	CAssetMgr::GetInst()->AddFlipbook(_FlipbookName, pFlipbook);
	wstring Path = L"Flipbook\\";
	pFlipbook->Save(Path + _FlipbookName);
}

