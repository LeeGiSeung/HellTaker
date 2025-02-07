#include "pch.h"
#include "CThorn.h"
#include "CCollider.h"
#include "CAssetMgr.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CPlayer.h"
#include "CSprite.h"
#include "CEngine.h"
#include "CTexture.h"
#include "CSound.h"
#include "CMonster.h"

//FlipBook 이미지 생성
#include "CFlipbookPlayer.h"
#include "CTexture.h"
#include "CFlipbook.h"

CThorn::CThorn()
	: m_DetectRange(50.f)
	, m_FlipbookPlayer(nullptr)
	, m_Target(nullptr)
	, m_HitBox(nullptr)
	, PlayerMove(false)
	, Hit(false)
	, pThorn_damage0(nullptr)
	, pThorn_damage1(nullptr)
{
	//spikes_damage_01
	//spikes_damage_02

	pThorn_damage0 = CAssetMgr::GetInst()->LoadSound(L"pThorn_damage0", L"Sound\\spikes_damage_01.wav");
	if (nullptr != pThorn_damage0)
	{
		pThorn_damage0->SetVolume(20.f);
	}
	pThorn_damage1 = CAssetMgr::GetInst()->LoadSound(L"pThorn_damage1", L"Sound\\spikes_damage_02.wav");
	if (nullptr != pThorn_damage1)
	{
		pThorn_damage1->SetVolume(20.f);
	}

	m_HitBox = new CCollider;
	m_HitBox->SetName(L"HitBox_01");
	m_HitBox->SetScale(Vec2(100.f, 100.f));
	m_HitBox->SetOffset(Vec2(0.f, 0.f));
	AddComponent(m_HitBox);

	CreatePlayerFlipbook();
}

CThorn::~CThorn()
{
}

void CThorn::Begin()
{
	if (ThornNUM == THORN_UP) {
		m_FlipbookPlayer->Play(THORN_UP, 30.f, false);
	}
	else if (ThornNUM == THORN_DOWN) {
		m_FlipbookPlayer->Play(THORN_DOWN, 30.f, false);
	}
}

void CThorn::Tick()
{
	//CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	//const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
	//CPlayer* cp = dynamic_cast<CPlayer*>(vecPlayer[0]);

	//if (cp->CurLevel == LEVEL_CHECK::BOSS_0) {
	//	if (m_FlipbookPlayer->IsFinish() && BOSS_CHECK) {
	//		if (ThornNUM == THORN_DOWN) {
	//			ThornNUM = THORN_UP;
	//		}
	//		else {
	//			ThornNUM = THORN_DOWN;
	//		}
	//		BOSS_CHECK = false;
	//	}
	//}

	//현재 가시가 끝났으면 반대 가시로 다시 시작해야함
	//if (PlayerMove == true) {
	//if (m_FlipbookPlayer->IsFinish()) {
	//	if (ThornNUM == THORN_UP) {
	//		m_FlipbookPlayer->Play(THORN_DOWN, 15.f, true);
	//	}
	//	else if (ThornNUM == THORN_DOWN) {
	//		m_FlipbookPlayer->Play(THORN_UP, 15.f, true);
	//	}
	//}

	//CurPos = GetPos();
	//CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	//const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
	//CPlayer* cp = dynamic_cast<CPlayer*>(vecPlayer[0]);
	//Vec2 vMonPos = cp->GetPos(); // 플레이어의 위치

	//Vec2 nCurPos = CurPos;

	//float Dist = (nCurPos - vMonPos).Length();

	//// 최소거리가 갱신된 경우
	//// 0도 포함힌거임
	//if (Dist < m_DetectRange && cp->m_FlipbookPlayer->IsFinish() && ThornNUM == THORN_UP)
	//{
	//	pThorn_damage0->Play();
	//	m_DetectRange = Dist;
	//	m_Target = cp;
	//}

	//if (m_Target != nullptr && Hit == true) {
	//	Hit = false;
	//}
	////아직 처맞지 않았을때
	//else if (m_Target != nullptr && Hit == false) {
	//	cp->PlayerMove_Count--;
	//	//처 맞았으니까 변경
	//	Hit = true;
	//}
}

void CThorn::Render()
{
	//부모 렌더
	//CObj::Render();

	if (PlayerMove) {
		m_FlipbookPlayer->Render(10.f + y_offset, 10.f + x_offset);
	}

	else {
		CTexture* m_Tex;
		wchar_t filePath[100] = {};
		wchar_t textureName[100] = {};

		if (ThornNUM == THORN_DOWN) {
			swprintf_s(filePath, 100, L"Texture\\ThornDown_0.png");
			swprintf_s(textureName, 100, L"ThornDown_0");
		}
		else if (ThornNUM == THORN_UP) {
			swprintf_s(filePath, 100, L"Texture\\ThornUp_0.png");
			swprintf_s(textureName, 100, L"ThornUp_0");
		}

		CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		m_Tex = pAtlas;

		HDC dc = CEngine::GetInst()->GetSecondDC();

		Vec2 vPos = GetRenderPos();
		Vec2 vScale = GetScale();

		BLENDFUNCTION blend = {};

		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		int a = m_Tex->GetWidth();
		int b = m_Tex->GetHeight();
		float c = vPos.x + m_Tex->GetWidth() / 2.f;
		float d = vPos.y + m_Tex->GetHeight() / 2.f;

		AlphaBlend(dc
			, vPos.x - m_Tex->GetWidth() / 2.f + 10.f + x_offset
			, vPos.y - m_Tex->GetHeight() / 2.f + 10.f + y_offset
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

void CThorn::ChangePlayerMove()
{
	PlayerMove = true;

	if (m_FlipbookPlayer->IsFinish() && ThornNUM == THORN_UP) {
		m_FlipbookPlayer->Play(THORN_UP, 30.f, false);
		ThornNUM = THORN_DOWN;
		//PlayerMove = false;
	}
	if (m_FlipbookPlayer->IsFinish() && ThornNUM == THORN_DOWN) {
		m_FlipbookPlayer->Play(THORN_DOWN, 30.f, false);
		ThornNUM = THORN_UP;
		//PlayerMove = false;
	}
}

bool CThorn::CheckStayThorn()
{
	m_DetectRange = 10.f;
	m_Target = nullptr;

	CurPos = GetPos();
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
	CPlayer* cp = dynamic_cast<CPlayer*>(vecPlayer[0]);

	Vec2 vMonPos = cp->GetPos(); // 플레이어의 위치

	Vec2 nCurPos = CurPos;

	float Dist = (nCurPos - vMonPos).Length();

	// 최소거리가 갱신된 경우
	// 0도 포함힌거임
	if (Dist < m_DetectRange && ThornNUM == THORN_UP)
	{
		cp->PlayerMove_Count--;
		pThorn_damage0->Play();
		m_DetectRange = Dist;
		m_Target = cp;
		return true;
	}

	////아직 처맞지 않았을때
	//else if (m_Target != nullptr) {
	//	//cp->PlayerMove_Count--;
	//}
	return false;

}

bool CThorn::CheckStayMonsterThorn()
{
	m_DetectRange = 10.f;
	m_Target = nullptr;

	CurPos = GetPos();
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::MONSTER);
	CMonster* cp = dynamic_cast<CMonster*>(vecPlayer[0]);

	Vec2 vMonPos = cp->GetPos(); // 플레이어의 위치

	Vec2 nCurPos = CurPos;

	float Dist = (nCurPos - vMonPos).Length();

	// 최소거리가 갱신된 경우
	// 0도 포함힌거임
	if (Dist < m_DetectRange && ThornNUM == THORN_UP)
	{
		return true;
	}

	////아직 처맞지 않았을때
	//else if (m_Target != nullptr) {
	//	//cp->PlayerMove_Count--;
	//}
	return false;
}

void CThorn::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player") {
		CPlayer* cp = dynamic_cast<CPlayer*>(_OtherObject);
		cp->PlayerDie();
	}
}

void CThorn::CreatePlayerFlipbook()
{
	//CreatePngFlipbook(L"THORN_UP", L"ThornUp", 5);
	//CreatePngFlipbook(L"THORN_DOWN", L"ThornDown", 4);

	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);

	m_FlipbookPlayer->AddFlipbook(THORN_UP, CAssetMgr::GetInst()->LoadFlipbook(L"THORN_UP", L"Flipbook\\THORN_UP.flip"));
	m_FlipbookPlayer->AddFlipbook(THORN_DOWN, CAssetMgr::GetInst()->LoadFlipbook(L"THORN_DOWN", L"Flipbook\\THORN_DOWN.flip"));

}

void CThorn::CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame)
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

