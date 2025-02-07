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
	// ���� ����
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

    // ���� ������ CLevel_Start �� ����
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
    // 1. ���� ������ �����Ϸ��� ������ �����ϸ� �ƹ��ϵ� ���Ͼ��.
    if (m_CurLevel == m_arrLevel[(UINT)_NextLevel])
        return;

    // 2. ���� ������ End �� ȣ���Ų��.
    m_CurLevel->End();

    // 3. ���� ��û�� ������ ���� ������ �����Ѵ�.
    m_CurLevel = m_arrLevel[(UINT)_NextLevel];

    // 3. ����� ������ Begin �� ȣ���Ų��.
    m_CurLevel->Begin();
}

CObj* CLevelMgr::FindObjectByName(LAYER_TYPE _Layer, const wstring& _Name)
{
    if (nullptr == m_CurLevel)
        return nullptr;

    return m_CurLevel->FindObjectByName(_Layer, _Name);
}