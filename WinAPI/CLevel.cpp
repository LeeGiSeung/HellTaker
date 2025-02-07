#include "pch.h"
#include "CLevel.h"

#include "CObj.h"
#include "CSound.h"
#include "CAssetMgr.h"
#include "CEngine.h"
#include "CLevelMgr.h"
#include "CPlayer.h"
#include "CSoundMgr.h"

CLevel::CLevel()
	: RestartCutscene(false)
	, m_FlipbookPlayer(nullptr)
{

}

CLevel::~CLevel()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		Delete_Vector(m_vecObjects[i]);
	}
}

void CLevel::Begin()
{
	pBGM = CAssetMgr::GetInst()->LoadSound(L"MainBGM", L"Sound\\Vitality.wav");
	pJudmentBGM = CAssetMgr::GetInst()->LoadSound(L"MainBossBGM", L"Sound\\Judment.wav");
	Apropos = CAssetMgr::GetInst()->LoadSound(L"Apropos", L"Sound\\Apropos.wav");
	pHomeBGM = CAssetMgr::GetInst()->LoadSound(L"pHomeBGM", L"Sound\\Home.wav");

	if (stage != LEVEL_CHECK::BOSS_0 && stage != LEVEL_CHECK::STAGE_LOBBY && stage != LEVEL_CHECK::STAGE_HOME) {

		if (pBGM != nullptr) {
			CurBGM = pBGM;
			SetBGMVolume();
			if (stage == LEVEL_CHECK::STAGE_0) {
				CurBGM->PlayToBGM(true);
			}
		}

	}
	else if (stage == LEVEL_CHECK::BOSS_0) {

		if (nullptr != pJudmentBGM)
		{
			CurBGM = pJudmentBGM;
			SetBGMVolume();
			CurBGM->PlayToBGM(true);
		}


	}
	else if (stage == LEVEL_CHECK::STAGE_LOBBY) {

		if (nullptr != Apropos)
		{
			CurBGM = Apropos;
			SetBGMVolume();
			CurBGM->PlayToBGM(true);
		}

	}
	else if (stage == LEVEL_CHECK::STAGE_HOME) {

		if (nullptr != pHomeBGM)
		{
			CurBGM = pHomeBGM;
			SetBGMVolume();
			CurBGM->PlayToBGM(true);
		}

	}
	int a = 0;
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_vecObjects[i].size(); ++j)
		{
			m_vecObjects[i][j]->Begin();
		}
	}
}

void CLevel::SetBGMVolume()
{
	//맨 처음
	int MusicIndex = CSoundMgr::GetInst()->MusicIndex;

	if (MusicIndex == 0) {
		CurBGM->SetVolume(50.f);
	}
	else if (MusicIndex == 1) {
		CurBGM->SetVolume(30.f);
	}
	else if (MusicIndex == 2) {
		CurBGM->SetVolume(10.f);
	}

}

void CLevel::Tick()
{
	SetBGMVolume();

	// 이전프레임에 등록된 충돌체들 등록 해제
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		m_vecCollider[i].clear();
	}

	// 레벨 안에 있는 물체들에게 Tick 호출
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_vecObjects[i].size(); ++j)
		{
			m_vecObjects[i][j]->Tick();
		}
	}
}

void CLevel::FinalTick()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_vecObjects[i].size(); ++j)
		{
			m_vecObjects[i][j]->FinalTick();
		}
	}
}

void CLevel::Render()
{

	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		vector<CObj*>& vecObjects = m_vecObjects[i];
		vector<CObj*>::iterator iter = vecObjects.begin();
		for (; iter != vecObjects.end(); )
		{
			if ((*iter)->IsDead())
			{
				iter = vecObjects.erase(iter);
			}
			else
			{
				(*iter)->Render();
				++iter;
			}
		}			
	}
}

void CLevel::Init()
{

}

void CLevel::AddObject(CObj* _Object, LAYER_TYPE _Type)
{
	m_vecObjects[(UINT)_Type].push_back(_Object);
	_Object->m_LayerType = _Type; // 오브젝트의 소속 레이어를 알려줌
}


CObj* CLevel::FindObjectByName(LAYER_TYPE _Layer, const wstring& _Name)
{
	vector<CObj*>& vec = m_vecObjects[(UINT)_Layer];
	
	for (size_t i = 0; i < vec.size(); ++i)
	{
		if (vec[i]->GetName() == _Name)
			return vec[i];
	}

	return nullptr;
}

void CLevel::DeleteObject(int _LayerIdx)
{	
	for (size_t i = 0; i < m_vecObjects[_LayerIdx].size(); ++i)
	{
		if (m_vecObjects[_LayerIdx][i]->IsDead())
			continue;

		delete m_vecObjects[_LayerIdx][i];
	}	

	m_vecObjects[_LayerIdx].clear();
}

void CLevel::DeleteAllObject()
{
	for (int i = 0; i < (int)LAYER_TYPE::END; ++i)
	{
		DeleteObject(i);
	}
}