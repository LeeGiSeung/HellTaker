#include "pch.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLevel_Start.h"
#include "CLevel_Editor.h"
#include "CLevelTwo.h"
#include "CLevelThree.h"
#include "CLevelFour.h"
#include "CLevelFive.h"
#include "CLevelSix.h"
#include "CLevelSeven.h"
#include "CLevelEight.h"
#include "CLevelNine.h"
#include "CLevelBoss_0.h"
#include "CLevelHome.h"
#include "CLevelLobby.h"

CLevelMgr::CLevelMgr()
    : m_arrLevel{}
    , m_CurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
    Delete_Array(m_arrLevel);
}

void CLevelMgr::Init()
{
    //m_arrLevel[(UINT)LEVEL_TYPE::STAGE_1] = new CLevel_Editor;
	// 레벨 제작
    m_arrLevel[(UINT)LEVEL_TYPE::EDITOR] = new CLevel_Editor;
    m_arrLevel[(UINT)LEVEL_TYPE::STAGE_0] = new CLevel_Start;
    m_arrLevel[(UINT)LEVEL_TYPE::STAGE_1] = new CLevelTwo;
    m_arrLevel[(UINT)LEVEL_TYPE::STAGE_2] = new CLevelThree;
    m_arrLevel[(UINT)LEVEL_TYPE::STAGE_3] = new CLevelFour;
    m_arrLevel[(UINT)LEVEL_TYPE::STAGE_4] = new CLevelFive;
    m_arrLevel[(UINT)LEVEL_TYPE::STAGE_5] = new CLevelSix;
    m_arrLevel[(UINT)LEVEL_TYPE::STAGE_6] = new CLevelSeven;
    m_arrLevel[(UINT)LEVEL_TYPE::STAGE_7] = new CLevelEight;
    m_arrLevel[(UINT)LEVEL_TYPE::STAGE_8] = new CLevelNine;
    m_arrLevel[(UINT)LEVEL_TYPE::BOSS_0] = new CLevelBoss_0;
    m_arrLevel[(UINT)LEVEL_TYPE::STAGE_HOME] = new CLevelHome;
    m_arrLevel[(UINT)LEVEL_TYPE::STAGE_LOBBY] = new CLevelLobby;

    // 현재 레벨을 CLevel_Start 로 지정
    m_CurLevel = m_arrLevel[(UINT)LEVEL_TYPE::STAGE_LOBBY];
    m_CurLevel->Begin();
}

void CLevelMgr::Progress()
{
    if (nullptr == m_CurLevel)
        return;

    m_CurLevel->Tick();
    m_CurLevel->FinalTick();   
}

void CLevelMgr::Render()
{
    m_CurLevel->Render();
}

void CLevelMgr::ChangeLevel(LEVEL_TYPE _NextLevel)
{
    // 1. 현재 레벨과 변경하려는 레벨이 동일하면 아무일도 안일어난다.
    if (m_CurLevel == m_arrLevel[(UINT)_NextLevel])
        return;

    // 2. 현재 레벨에 End 를 호출시킨다.
    m_CurLevel->End();

    // 3. 변경 요청한 레벨을 현재 레벨로 지정한다.
    m_CurLevel = m_arrLevel[(UINT)_NextLevel];

    // 3. 변경된 레벨의 Begin 을 호출시킨다.
    m_CurLevel->Begin();
}

CObj* CLevelMgr::FindObjectByName(LAYER_TYPE _Layer, const wstring& _Name)
{
    if (nullptr == m_CurLevel)
        return nullptr;

    return m_CurLevel->FindObjectByName(_Layer, _Name);
}