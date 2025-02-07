#include "pch.h"
#include "CRock.h"
#include "CEngine.h"
#include "CAssetMgr.h"
#include "CCollider.h"

#include "CLevel.h"
#include "CLevelMgr.h"

#include "CFlipbookPlayer.h"
#include "CTexture.h"
#include "CFlipbook.h"
#include "CSprite.h"

enum DIRECTION {
	D_LEFT,
	D_RIGHT,
	D_UP,
	D_DOWN,
	D_END
};

CRock::CRock()
	:m_Tex(nullptr)
	,m_HitBox(nullptr)
	,ROCK_MOVING_CHECK(false)
	, Move_Direction(D_END)
	, Moving_TickPos(5.f)
	, Moving_CurPos({0.f,0.f})
	, Moving_GoalPos({ 0.f,0.f })
	, Moving_MovePos({ 0.f,0.f })
	, m_FlipbookMOVEVFXPlayer(nullptr)
	, VFX_MOVE_RENDER(false)
	, MoveVFXRenderPos({ 0.f,0.f })
{
	m_HitBox = new CCollider;
	m_HitBox->SetName(L"Rock");
	m_HitBox->SetScale(Vec2(100.f, 100.f));
	m_HitBox->SetOffset(Vec2(0.f, 0.f));
	AddComponent(m_HitBox);
	CreatePlayerFlipbook();

}

CRock::~CRock()
{
}

void CRock::SetRock(const wstring& _Pngname)
{
	wchar_t filePath[100] = {};
	wchar_t textureName[100] = {};
	// 각 프레임에 대한 경로 생성
	swprintf_s(filePath, 100, L"Texture\\%s.png", _Pngname.c_str());
	swprintf_s(textureName, 100, L"%s", _Pngname.c_str());

	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

	m_Tex = pAtlas;
}

void CRock::CreatePlayerFlipbook()
{
	//CreatePngFlipbook(L"MOVE_VFX_1", L"Move_vfx1", 3);
	//CreatePngFlipbook(L"MOVE_VFX_2", L"Move_vfx2", 3);
	//CreatePngFlipbook(L"MOVE_VFX_3", L"Move_vfx3", 3);

	////MOVE
	m_FlipbookMOVEVFXPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);

	m_FlipbookMOVEVFXPlayer->AddFlipbook(MOVE_VFX_1, CAssetMgr::GetInst()->LoadFlipbook(L"MOVE_VFX_1", L"Flipbook\\MOVE_VFX_1.flip"));
	m_FlipbookMOVEVFXPlayer->AddFlipbook(MOVE_VFX_2, CAssetMgr::GetInst()->LoadFlipbook(L"MOVE_VFX_2", L"Flipbook\\MOVE_VFX_2.flip"));
	m_FlipbookMOVEVFXPlayer->AddFlipbook(MOVE_VFX_3, CAssetMgr::GetInst()->LoadFlipbook(L"MOVE_VFX_3", L"Flipbook\\MOVE_VFX_3.flip"));


}

void CRock::CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame)
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

void CRock::Begin()
{

}

void CRock::Tick()
{

	if (m_FlipbookMOVEVFXPlayer->IsFinish()) {
		VFX_MOVE_RENDER = false;
		MoveVFXRenderPos = { 0.f,0.f };
	}

	if (ROCK_MOVING_CHECK) {
	//	//현재위치가 아직 목표위치에 도달하지 않았을때

		if (Move_Direction == D_LEFT) {
			if (abs(Moving_CurPos.x) != abs(Moving_GoalPos.x)) {
				Moving_CurPos.x -= Moving_TickPos;
				SetPos(Moving_CurPos);
			}
		}
		else if (Move_Direction == D_RIGHT) {
			if (abs(Moving_CurPos.x) != abs(Moving_GoalPos.x)) {
				Moving_CurPos.x += Moving_TickPos;
				SetPos(Moving_CurPos);
			}
		}
		else if (Move_Direction == D_UP) {
			if (abs(Moving_CurPos.y) > abs(Moving_GoalPos.y)) {
				Moving_CurPos.y -= Moving_TickPos;
				SetPos(Moving_CurPos);
			}
		}
		else if (Move_Direction == D_DOWN) {
			if (abs(Moving_CurPos.y) < abs(Moving_GoalPos.y)) {
				Moving_CurPos.y += Moving_TickPos;
				SetPos(Moving_CurPos);
			}
		}

		else {
			ROCK_MOVING_CHECK = false;
			Moving_MovePos = { 0.f,0.f };
			Moving_CurPos = { 0.f,0.f };
			Moving_GoalPos = { 0.f,0.f };
		}
	}
}

void CRock::Render()
{
	//부모 렌더
	//CObj::Render();

	if (VFX_MOVE_RENDER) {
		m_FlipbookMOVEVFXPlayer->Inplace_Render(MoveVFXRenderPos, 40.f);
	}

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
		, (vPos.x - (m_Tex->GetWidth()) / 2.f) + 5.f + x_offset
		, (vPos.y - (m_Tex->GetHeight()) / 2.f) + 30.f + y_offset
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

void CRock::Move(int Dir)
{
	float m_DetectRange = 90.f;
	CObj* m_Target = nullptr;

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecMon = pCurLevel->GetObjects(LAYER_TYPE::MONSTER);
	const vector<CObj*>& vecRock = pCurLevel->GetObjects(LAYER_TYPE::Rock);
	const vector<CObj*>& vecWall = pCurLevel->GetObjects(LAYER_TYPE::WALL);
	const vector<CObj*>& vecDemon = pCurLevel->GetObjects(LAYER_TYPE::DEMON);
	const vector<CObj*>& vecKeyBox = pCurLevel->GetObjects(LAYER_TYPE::KEYBOX);

	// 본인과 가장 가까운 대상(돌, 몬스터)를 타겟으로 지정한다.
	Vec2 vPos = GetPos();

	if (Dir == D_LEFT) {
		vPos += Vec2(-100.f, 0.f);
	}
	if (Dir == D_RIGHT) {
		vPos += Vec2(100.f, 0.f);
	}
	if (Dir == D_UP) {
		vPos += Vec2(0.f, -100.f);
	}
	if (Dir == D_DOWN) {
		vPos += Vec2(0.f, 100.f);
	}

	float MinDistance = m_DetectRange;

	for (size_t i = 0; i < vecMon.size(); ++i)
	{
		if (vecMon[i]->IsDead())
			continue;

		Vec2 vMonPos = vecMon[i]->GetPos(); // 몬스터의 위치

		Vec2 a = vPos;
		Vec2 b = vMonPos;

		float Dist = (vPos - vMonPos).Length();

		// 최소거리가 갱신된 경우
		if (Dist <= MinDistance)
		{
			MinDistance = Dist;
			m_Target = vecMon[i];
		}
	}

	for (size_t i = 0; i < vecDemon.size(); ++i)
	{

		Vec2 vMonPos = vecDemon[i]->GetPos(); // 몬스터의 위치

		Vec2 a = vPos;
		Vec2 b = vMonPos;

		float Dist = (vPos - vMonPos).Length();

		// 최소거리가 갱신된 경우
		if (Dist <= MinDistance)
		{
			MinDistance = Dist;
			m_Target = vecDemon[i];
		}
	}

	for (size_t i = 0; i < vecWall.size(); ++i)
	{

		Vec2 vMonPos = vecWall[i]->GetPos(); // 몬스터의 위치

		Vec2 a = vPos;
		Vec2 b = vMonPos;

		float Dist = (vPos - vMonPos).Length();

		// 최소거리가 갱신된 경우
		if (Dist <= MinDistance)
		{
			MinDistance = Dist;
			m_Target = vecWall[i];
		}
	}

	for (size_t i = 0; i < vecRock.size(); ++i)
	{

		Vec2 vMonPos = vecRock[i]->GetPos(); // 돌의 위치
		float Dist = (vPos - vMonPos).Length();

		// 최소거리가 갱신된 경우
		if (Dist <= MinDistance)
		{
			MinDistance = Dist;
			m_Target = vecRock[i];
		}
	}

	for (size_t i = 0; i < vecKeyBox.size(); ++i)
	{

		Vec2 vMonPos = vecKeyBox[i]->GetPos(); // 돌의 위치
		float Dist = (vPos - vMonPos).Length();

		// 최소거리가 갱신된 경우
		if (Dist <= MinDistance)
		{
			MinDistance = Dist;
			m_Target = vecKeyBox[i];
		}
	}

	//m_Target이 몬스터, 돌을 거쳐서 가장 가까운 위치에 있는 것임
	//부딪힌 타겟이 없으면 이동 할 수 있음
	if (m_Target == nullptr) {
		Moving_CurPos = GetPos();
		ROCK_MOVING_CHECK = true;

		if (VFX_MOVE_RENDER == false) {
			MoveVFXRenderPos = GetRenderPos();
			m_FlipbookMOVEVFXPlayer->Play(MOVE_VFX_2, 10.f, false);
			VFX_MOVE_RENDER = true;
		}

		if (Dir == D_LEFT) {
			Move_Direction = D_LEFT;
			Moving_MovePos = Vec2(-100.f, 0.f);
			Moving_GoalPos = Moving_CurPos + Moving_MovePos;
		}
		else if (Dir == D_RIGHT) {
			Move_Direction = D_RIGHT;
			Moving_MovePos = Vec2(100.f, 0.f);
			Moving_GoalPos = Moving_CurPos + Moving_MovePos;
		}
		else if (Dir == D_UP) {
			Move_Direction = D_UP;
			Moving_MovePos = Vec2(0.f, -100.f);
			Moving_GoalPos = Moving_CurPos + Moving_MovePos;
		}
		else if (Dir == D_DOWN) {
			Move_Direction = D_DOWN;
			Moving_MovePos = Vec2(0.f, +100.f);
			Moving_GoalPos = Moving_CurPos + Moving_MovePos;
		}
	}
}

