#include "pch.h"
#include "CDemon.h"
#include "CCollider.h"
#include "CAssetMgr.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CPlayer.h"
#include "CSprite.h"
#include "CTimeMgr.h"
#include "CEngine.h"

//FlipBook 이미지 생성
#include "CFlipbookPlayer.h"
#include "CTexture.h"
#include "CFlipbook.h"

//enum VFX {
//	LOVEPLOSION
//};

CDemon::CDemon()
	:m_HitBox(nullptr)
	, m_FlipbookPlayer(nullptr)
	, m_Target(nullptr)
	, DemonNUM(DEMON_END)
	, m_DetectRange(100.f)
{

	m_HitBox = new CCollider;
	m_HitBox->SetName(L"HitBox_01");
	m_HitBox->SetScale(Vec2(100.f, 100.f));
	m_HitBox->SetOffset(Vec2(0.f, 0.f));
	AddComponent(m_HitBox);

	CreatePlayerFlipbook();

}

CDemon::~CDemon()
{
}


void CDemon::Begin()
{
	if (DemonNUM == PANDEMONICA) {
		m_FlipbookPlayer->Play(PANDEMONICA, 15.f, true);
	}
	else if (DemonNUM == AZAZEL) {
		m_FlipbookPlayer->Play(AZAZEL, 15.f, true);
	}
	else if (DemonNUM == MODEUS) {
		m_FlipbookPlayer->Play(MODEUS, 15.f, true);
	}
	else if (DemonNUM == CERBERUS) {
		m_FlipbookPlayer->Play(CERBERUS, 15.f, true);
	}
	else if (DemonNUM == MALINA) {
		m_FlipbookPlayer->Play(MALINA, 15.f, true);
	}
	else if (DemonNUM == LUCY) {
		m_FlipbookPlayer->Play(LUCY, 15.f, true);
	}
	else if (DemonNUM == POLICE) {
		m_FlipbookPlayer->Play(POLICE, 15.f, true);
	}
	else if (DemonNUM == JUDGMENT) {
		m_FlipbookPlayer->Play(JUDGMENT, 15.f, true);
	}
	else if (DemonNUM == JUSTICE) {
		m_FlipbookPlayer->Play(JUSTICE, 15.f, true);
	}
	else if (DemonNUM == ZDRADA) {
		m_FlipbookPlayer->Play(ZDRADA, 15.f, true);
	}
	else if (DemonNUM == LUCY_HOME) {
		m_FlipbookPlayer->Play(LUCY_HOME, 15.f, true);
	}
	m_FlipbookDemonVFXPlayer->Play(LOVEPLOSION, 10.f, false);
}

//float DPos[4][2] = { {-100.f},{0.f } }, { {100.f},{0.f} }, { 0.f,-100.f }, { 0.f,100.f }};
float DPosX[4] = { -90.f,90.f,0.f,0.f };
float DPosY[4] = { 0.f,0.f,-90.f,90.f };

float LHDPosX[4] = { -180.f,180.f,0.f,0.f };
float LHDPosY[4] = { 0.f,0.f,-180.f,180.f };

void CDemon::Tick()
{
	if (dir == 0) {
		TickPos += 0.1f;
	}
	else {
		TickPos -= 0.1f;
	}

	if (TickPos >= 10) {
		dir = 1;
	}
	else if (TickPos <= 0) {
		dir = 0;
	}

	if (clearLevel) {
		kisstime += DT;
		if (kisstime > 2.5f) {
			m_FlipbookPlayer->Play(LOVEPLOSION, 10.f, false);
			clearLevel = false;
		}
	}

	if (kisstime > 2.5f && m_FlipbookPlayer->IsFinish()) {
		DeleteObject(this);
	}

	m_DetectRange = 100.f;
	m_Target = nullptr;
	CurPos = GetPos();
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
	CPlayer* cp = dynamic_cast<CPlayer*>(vecPlayer[0]);

	Vec2 vMonPos = cp->GetPos();

	for (int i = 0; i < 4; i++) {

		Vec2 nCurPos = CurPos;
		if (cp->CurLevel == STAGE_7) {
			nCurPos.x += LHDPosX[i];
			nCurPos.y += LHDPosY[i];
		}
		else {
			nCurPos.x += DPosX[i];
			nCurPos.y += DPosY[i];
		}


		float Dist = (nCurPos - vMonPos).Length();

		// 최소거리가 갱신된 경우
		if (Dist <= m_DetectRange)
		{
			vMonPos;
			nCurPos;
			m_DetectRange = Dist;
			m_Target = cp;
		}
		//Player를 찾았을때
		if (m_Target != nullptr) {
			CPlayer* cp = dynamic_cast<CPlayer*>(m_Target);
			if (cp->CurLevel == LEVEL_CHECK::STAGE_HOME) {
				if (!DemonTalk) {
					DemonTalk = true;
					cp->TalkPartCheck = true;
					m_Target = nullptr;
				}
			}
			else {
				if (cp->m_FlipbookPlayer->IsFinish() && cp->SuccessLevel == false) {
					cp->TalkPartCheck = true;
					m_Target = nullptr;
				}
			}
		}
	}

}

void CDemon::Render()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
	CPlayer* cp = dynamic_cast<CPlayer*>(vecPlayer[0]);

	//부모 렌더
	//CObj::Render();
	if (cp->CurLevel != STAGE_8) {
		m_FlipbookPlayer->Render(10.f + y_offset, x_offset);
		if (kisstime > 2.5f) {
			m_FlipbookPlayer->Render();
		}

		if (cp->SuccessLevel == false) {
			HDC dc = CEngine::GetInst()->GetSecondDC();

			Vec2 vPos = GetRenderPos();
			Vec2 vScale = GetScale();

			BLENDFUNCTION blend = {};

			blend.BlendOp = AC_SRC_OVER;
			blend.BlendFlags = 0;
			blend.SourceConstantAlpha = 255;
			blend.AlphaFormat = AC_SRC_ALPHA;

			wchar_t filePath[100] = {};
			wchar_t textureName[100] = {};
			// 각 프레임에 대한 경로 생성

			swprintf_s(filePath, 100, L"Texture\\lovesign.png");
			swprintf_s(textureName, 100, L"lovesign");


			CTexture* m_Tex = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				, (vPos.x - (m_Tex->GetWidth()) / 2.f) + x_offset - 45.f
				, (vPos.y - (m_Tex->GetHeight()) / 2.f) + y_offset + TickPos - 30.f
				, m_Tex->GetWidth()
				, m_Tex->GetHeight()
				, m_Tex->GetDC()
				, 0, 0
				, m_Tex->GetWidth()
				, m_Tex->GetHeight()
				, blend);

			HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
			ReleaseDC(hwnd, dc);
		}
	}
	

}

void CDemon::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void CDemon::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void CDemon::EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void CDemon::CreatePlayerFlipbook()
{
	//azazel_0
	//CreatePngFlipbook(L"PANDEMONICA", L"pandemonica", 12);
	//CreatePngFlipbook(L"AZAZEL", L"azazel", 12);
	//CreatePngFlipbook(L"MODEUS", L"modeus", 12);
	//CreatePngFlipbook(L"CERBERUS", L"cerberus_finalModel", 12);
	//CreatePngFlipbook(L"JUDGMENT", L"judgement_finalModel", 12);
	//CreatePngFlipbook(L"JUSTICE", L"justice_finalModel", 12);
	//CreatePngFlipbook(L"LUCY", L"lucy_finalModel", 12);
	//CreatePngFlipbook(L"LUCY_HOME", L"lucyH_finalModel", 12);
	//CreatePngFlipbook(L"MALINA", L"malina_finalModel", 12);
	//CreatePngFlipbook(L"ZDRADA", L"zdrada_finalModel", 12);
	//CreatePngFlipbook(L"LOVEPLOSION", L"lovePlosion", 15);

	m_FlipbookDemonVFXPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_FlipbookDemonVFXPlayer->AddFlipbook(LOVEPLOSION, CAssetMgr::GetInst()->LoadFlipbook(L"LOVEPLOSION", L"Flipbook\\LOVEPLOSION.flip"));

	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_FlipbookPlayer->AddFlipbook(MODEUS, CAssetMgr::GetInst()->LoadFlipbook(L"MODEUS", L"Flipbook\\MODEUS.flip"));
	m_FlipbookPlayer->AddFlipbook(PANDEMONICA, CAssetMgr::GetInst()->LoadFlipbook(L"PANDEMONICA_IDLE", L"Flipbook\\PANDEMONICA_IDLE.flip"));
	m_FlipbookPlayer->AddFlipbook(AZAZEL, CAssetMgr::GetInst()->LoadFlipbook(L"AZAZEL_IDLE", L"Flipbook\\AZAZEL_IDLE.flip"));
	m_FlipbookPlayer->AddFlipbook(CERBERUS, CAssetMgr::GetInst()->LoadFlipbook(L"CERBERUS", L"Flipbook\\CERBERUS.flip"));
	m_FlipbookPlayer->AddFlipbook(JUDGMENT, CAssetMgr::GetInst()->LoadFlipbook(L"JUDGMENT", L"Flipbook\\JUDGMENT.flip"));
	m_FlipbookPlayer->AddFlipbook(JUSTICE, CAssetMgr::GetInst()->LoadFlipbook(L"JUSTICE", L"Flipbook\\JUSTICE.flip"));
	m_FlipbookPlayer->AddFlipbook(LUCY, CAssetMgr::GetInst()->LoadFlipbook(L"LUCY", L"Flipbook\\LUCY.flip"));
	m_FlipbookPlayer->AddFlipbook(LUCY_HOME, CAssetMgr::GetInst()->LoadFlipbook(L"LUCY_HOME", L"Flipbook\\LUCY_HOME.flip"));
	m_FlipbookPlayer->AddFlipbook(MALINA, CAssetMgr::GetInst()->LoadFlipbook(L"MALINA", L"Flipbook\\MALINA.flip"));
	m_FlipbookPlayer->AddFlipbook(ZDRADA, CAssetMgr::GetInst()->LoadFlipbook(L"ZDRADA", L"Flipbook\\ZDRADA.flip"));
	m_FlipbookPlayer->AddFlipbook(LOVEPLOSION, CAssetMgr::GetInst()->LoadFlipbook(L"LOVEPLOSION", L"Flipbook\\LOVEPLOSION.flip"));
}

void CDemon::CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame)
{
	// Sprite 생성하기
	for (int i = 0; i < MaxFrame; i++)
	{
		wchar_t filePath[100] = {};
		wchar_t textureName[100] = {};
		// 각 프레임에 대한 경로 생성
		swprintf_s(filePath, 100, L"Texture\\%s_%d.png", _Pngname.c_str(), i);
		swprintf_s(textureName, 100, L"%s_%d", _Pngname.c_str(), i);

		CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		CSprite* pSprite = new CSprite;

		// _RightBot를 그대로 넘기지 않고 크기로 사용해야 합니다.
		int a = pAtlas->GetWidth();
		int b = pAtlas->GetHeight();
		int c = 0;

		Vec2 spriteSize = Vec2(static_cast<float>(pAtlas->GetWidth()), static_cast<float>(pAtlas->GetHeight()));
		Vec2 spritePosition = Vec2(0.0f, 0.0f); // 원하는 위치로 설정, 예를 들어 (0,0)
		pSprite->Create(pAtlas, spritePosition, spriteSize);

		// Key를 만들 때, wstring을 미리 생성 후 사용
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, L"%s_%d", _FlipbookName.c_str(), i);  // 여기서 형식 문자열을 분리하여 사용
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

	// Flipbook 생성하기
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

