
#include "pch.h"
#include "CMonster.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CCollider.h"

#include "CAssetMgr.h"
#include "CTexture.h"
#include "CFSM.h"
#include "CSprite.h"
#include "CFlipbook.h"
#include "CFlipbookPlayer.h"

#include "CIdleState.h"
#include "CTraceState.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CSound.h"
#include "CPlayer.h"
#include "CThorn.h"

enum MONSTER_ANIM_STATE
{
	IDLE,
	HIT,
	DEATH
};

enum DIRECTION {
	D_LEFT,
	D_RIGHT,
	D_UP,
	D_DOWN,
	D_END
};

CMonster::CMonster()
	: m_Dir(1)
	, m_Speed(300.f)
	, m_Dist(100.f)
	, m_Collider(nullptr)
	, m_FSM(nullptr)
	, m_FlipbookPlayer(nullptr)
	, Monster_Die_Sound_1(nullptr)
	, Monster_Die_Sound_2(nullptr)
	, Monster_Die_Sound_3(nullptr)
	, MONSTER_MOVING_CHECK(false)
	, Move_Direction(D_END)
	, Moving_TickPos(5.f)
	, Moving_CurPos({ 0.f,0.f })
	, Moving_GoalPos({ 0.f,0.f })
	, Moving_MovePos({ 0.f,0.f })
{

	Monster_Die_Sound_1 = CAssetMgr::GetInst()->LoadSound(L"Monster_Die_Sound_1", L"Sound\\enemy_die_01.wav");
	if (nullptr != Monster_Die_Sound_1)
	{
		Monster_Die_Sound_1->SetVolume(20.f);
	}
	Monster_Die_Sound_2 = CAssetMgr::GetInst()->LoadSound(L"Monster_Die_Sound_2", L"Sound\\enemy_die_02.wav");
	if (nullptr != Monster_Die_Sound_2)
	{
		Monster_Die_Sound_2->SetVolume(20.f);
	}
	Monster_Die_Sound_3 = CAssetMgr::GetInst()->LoadSound(L"Monster_Die_Sound_3", L"Sound\\enemy_die_03.wav");
	if (nullptr != Monster_Die_Sound_3)
	{
		Monster_Die_Sound_3->SetVolume(20.f);
	}

	CreateMonsterFlipbook();

	// Collider 컴포넌트 추가
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(100.f, 100.f));

	// 몬스터 스탯
	m_Info.MaxHP = 100.f;
	m_Info.CurHP = 100.f;
	m_Info.AttRange = 100.f;
	m_Info.DetectRange = 200.f;
	m_Info.Speed = 100.f;

	// FSM 컴포넌트 추가
	m_FSM = (CFSM*)AddComponent(new CFSM);

	// FSM 에 상태 추가
	m_FSM->AddState(L"Idle", new CIdleState);
	m_FSM->AddState(L"Trace", new CTraceState);
}

void CMonster::SetSound()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
	CPlayer* cp = dynamic_cast<CPlayer*>(vecPlayer[0]);

	float a = 40.f;

	if (cp->SoundIndex == 0) {
		a = 50.f;
	}
	else if (cp->SoundIndex == 1) {
		a = 30.f;
	}
	else if (cp->SoundIndex == 2) {
		a = 10.f;
	}

	if (nullptr != Monster_Die_Sound_1)
	{
		Monster_Die_Sound_1->SetVolume(a);
	}
	if (nullptr != Monster_Die_Sound_2)
	{
		Monster_Die_Sound_2->SetVolume(a);
	}
	if (nullptr != Monster_Die_Sound_3)
	{
		Monster_Die_Sound_3->SetVolume(a);
	}
}

CMonster::~CMonster()
{

}

void CMonster::Begin()
{
	m_FSM->ChangeState(L"Idle");
	m_InitPos = GetPos();

	m_FlipbookPlayer->Play(IDLE, 15.f, true);

}

void CMonster::Tick()
{
	IFINPLACETHORNUP();
	SetSound();
	if (m_FlipbookPlayer->IsFinish()) {
		m_FlipbookPlayer->Play(IDLE, 15.f, true);
		MonsterHitFlipbook = false;
	}

	if (MONSTER_MOVING_CHECK) {
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
			MONSTER_MOVING_CHECK = false;
			Moving_MovePos = { 0.f,0.f };
			Moving_CurPos = { 0.f,0.f };
			Moving_GoalPos = { 0.f,0.f };
		}
	}
}

void CMonster::Render()
{
	//CObj::Render();
	HDC dc = CEngine::GetInst()->GetSecondDC();

	m_FlipbookPlayer->Render(y_offset + 10.f, x_offset);
	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	ReleaseDC(hwnd, dc);

}



void CMonster::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player")
	{
	//ChangeLevel(LEVEL_TYPE::EDITOR);
	}
}

void CMonster::CreateMonsterFlipbook()
{
	//CreatePngFlipbook(L"ASSETS100V_IDLE", L"assets100V", 12);
	//CreatePngFlipbook(L"HIT", L"MonsterDamaged", 6);

	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);

	m_FlipbookPlayer->AddFlipbook(IDLE, CAssetMgr::GetInst()->LoadFlipbook(L"ASSETS100V_IDLE", L"Flipbook\\ASSETS100V_IDLE.flip"));
	m_FlipbookPlayer->AddFlipbook(HIT, CAssetMgr::GetInst()->LoadFlipbook(L"HIT", L"Flipbook\\HIT.flip"));
}

void CMonster::CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame)
{
	// Sprite 생성하기
	for (int i = 0; i < MaxFrame; i++)
	{
		wchar_t filePath[100] = {};
		wchar_t textureName[100] = {};
		// 각 프레임에 대한 경로 생성
		swprintf_s(filePath, 100, L"Texture\\%s_%d.png", _Pngname.c_str(), i);
		/*swprintf_s(textureName, 100, L"assets100V%d", i);*/
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

void CMonster::SetSound(int _SelectDeathSound)
{
	DeathSound = _SelectDeathSound;
}

void CMonster::Move(int Dir)
{
	float m_DetectRange = 80.f;
	CObj* m_Target = nullptr;

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecMon = pCurLevel->GetObjects(LAYER_TYPE::MONSTER);
	const vector<CObj*>& vecRock = pCurLevel->GetObjects(LAYER_TYPE::Rock);
	const vector<CObj*>& vecWall = pCurLevel->GetObjects(LAYER_TYPE::WALL);
	const vector<CObj*>& vecThorn = pCurLevel->GetObjects(LAYER_TYPE::THORN);
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

		if (vMonPos.x == GetPos().x && vMonPos.x == GetPos().y) {
			continue;
		}

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

	for (size_t i = 0; i < vecWall.size(); ++i)
	{

		Vec2 vMonPos = vecWall[i]->GetPos(); // 몬스터의 위치

		//if (vMonPos.x == GetPos().x && vMonPos.x == GetPos().y) {
		//	continue;
		//}

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

	for (size_t i = 0; i < vecThorn.size(); ++i)
	{

		Vec2 vMonPos = vecThorn[i]->GetPos(); // 몬스터의 위치
		//가만히에서 가시가 돋아날 경우
		CThorn* th = dynamic_cast<CThorn*>(vecThorn[i]);
		//지금 잘못된게 가시를 찾을 수 없는건 맞아 왜냐하면 가시의 위치가 플레이어가 이동할 곳에 없으니까
		//그래서 m_Target_Thorn에 들어왔는데 CheckStatThorn은 현재 같은 위치에 가시가 있는지 검사하는 거임
		//그래서 이동하고있는 플레이어와 가시는 같은 위치, 그래서 걸리는거
		//그럼 지금 플레이어가 이동하고 있다는걸 알고 있으면 걸리면 안됨
		float Dist = (vPos - vMonPos).Length();

		// 최소거리가 갱신된 경우
		if (Dist < MinDistance)
		{
			MinDistance = Dist;
			m_Target_Thorn = th;
		}
	}

	m_FlipbookPlayer->Play(HIT, 15.f, false);

	//m_Target이 몬스터, 돌을 거쳐서 가장 가까운 위치에 있는 것임
	//부딪힌 타겟이 없으면 이동 할 수 있음
	if (m_Target == nullptr) {
		Moving_CurPos = GetPos();
		MONSTER_MOVING_CHECK = true;

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
		IFNextPointUpThorn();
	}
	else {
		if (DeathSound == 1) Monster_Die_Sound_1->Play(false);
		else if (DeathSound == 2) Monster_Die_Sound_2->Play(false);
		else if (DeathSound == 3) Monster_Die_Sound_3->Play(false);
		DeleteObject(this);
	}
}

void CMonster::IFINPLACETHORNUP()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecMon = pCurLevel->GetObjects(LAYER_TYPE::PLAYER);
	const vector<CObj*>& vecThorn = pCurLevel->GetObjects(LAYER_TYPE::THORN);
	CPlayer* cp = dynamic_cast<CPlayer*>(vecMon[0]);

	if (cp->PlayerMove) {
		for (size_t i = 0; i < vecThorn.size(); ++i) {
			Vec2 vMonPos = vecThorn[i]->GetPos(); // 몬스터의 위치
			//가만히에서 가시가 돋아날 경우
			CThorn* th = dynamic_cast<CThorn*>(vecThorn[i]);
			if (th->CheckStayMonsterThorn()) {
				if (DeathSound == 1) Monster_Die_Sound_1->Play(false);
				else if (DeathSound == 2) Monster_Die_Sound_2->Play(false);
				else if (DeathSound == 3) Monster_Die_Sound_3->Play(false);
				DeleteObject(this);
			}
		}
	}
}

void CMonster::IFNextPointUpThorn()
{
	if (m_Target_Thorn != nullptr) {
		CThorn* th = dynamic_cast<CThorn*>(m_Target_Thorn);
		if (th->ThornNUM == 0) {
			if (DeathSound == 1) Monster_Die_Sound_1->Play(false);
			else if (DeathSound == 2) Monster_Die_Sound_2->Play(false);
			else if (DeathSound == 3) Monster_Die_Sound_3->Play(false);
			DeleteObject(this);
		}
	}
}
