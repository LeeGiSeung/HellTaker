#include "pch.h"
#include "CLevelLobby.h"
#include "CEngine.h"
#include "CCollisionMgr.h"
#include "CCollider.h"

#include "CTileMap.h"
#include "CPathMgr.h"
#include "CCamera.h"
#include "CBackground.h"
#include "CRock.h"
#include "CDemon.h"
#include "CKey.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CMissile.h"
#include "CPlatform.h"
#include "CMap.h"

#include "CAssetMgr.h"
#include "CSound.h"
#include "CRestartCutScene.h"
#include "CWall.h"
#include "CThorn.h"
#include "CFireBase.h"
#include "CFire.h"
#include "CCountUI.h"
#include "CKeybox.h"

#include "CLevel_Start.h"
#include "CLevelMgr.h"
CLevelLobby::CLevelLobby()
{
    CLevel::stage = LEVEL_CHECK::STAGE_LOBBY;
}

CLevelLobby::~CLevelLobby()
{
}

void CLevelLobby::Init()
{
}

void CLevelLobby::Begin()
{

    //Player ����
    CPlayer* pObject = new CPlayer;
    pObject->SetName(L"Player");
    pObject->SetPos(750.f, 450.f);
    pObject->SetStartPos(750.f, 450.f);
    pObject->SetScale(100.f, 100.f);
    pObject->SetOffset(0.f, 30.f);
    pObject->SetInitDir(0);
    pObject->TalkPartCheck = true;
    pObject->SetPlayerMoveCount(50);
    pObject->CurLevel = STAGE_LOBBY;
    AddObject(pObject, LAYER_TYPE::PLAYER);

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::NULLNAME,
L"dialogueBG_abyss",
L"����",
        L"����� �ֺ��� �ɿ����� �ѷ����� ���� �˾������ϴ�.",
        L"[ENTER]�� ���� ����ϱ�.",
L"",
L"",
0,
1,
0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::BEEL_FLY,
L"dialogueBG_abyss",
L"beel_fly",
        L"ȯ���ϳ� �ΰ��̿�. �ʹ� ����� ���Գ�.",
        L"�ڳ��� ģ�� ���������ϼ�.",
        L"",
        L"",
0,
2,
0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::CHOICE_CUTSCENE,
DEMON_TYPE::BEEL_FLY,
L"dialogueBG_abyss",
L"beel_fly",
L"",
L"",
L"�� ����",
L"������",
0,
8,
3      });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::BEEL_FLY,
L"dialogueBG_abyss",
L"BEEL_FLY",
        L"�� ������Ŀ�� �̾߱⸦ ��� �ʹٰ�? ��̷ӱ�...",
        L"",
L"",
L"",
0,
4,
0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::BEEL_FLY,
L"dialogueBG_abyss",
L"BEEL_FLY",
        L"Ȥ�� ���̾�, �������Ͱ� �ʿ������� �ʳ�?",
        L"",
L"",
L"",
0,
5,
0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::NULLNAME,
L"����",
L"����",
        L"���� ����� ���شٸ�... �װ� �� �����̰ڱ�",
        L"",
L"",
L"",
0,
6,
0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::NULLNAME,
L"cutscene_0002_Group-2",
L"����",
        L"����� ����� ������ ���� ������ �Ͼ���ϴ�.",
        L"���Ǹ����� ������ �Ϸ��� ����� ���� ������.",
L"",
L"",
0,
7,
0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::NULLNAME,
L"cutscene_0003_Group-3-copy-2",
L"����",
        L"������, ����� �� ���� ���� �ʴٴ� ���� �˰� �־����ϴ�.",
        L"�׸��� ����� ���� ���� ���·ο� ��Ȳ�� ��ĥ �͵���.",
L"",
L"",
0,
8,
0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::NEXT_LEVELSCENE,
DEMON_TYPE::NULLNAME,
L"cutscene_0004_Layer-273-copy",
L"����",
        L"���Ǹ����� ���õ� ���̶��, �׸��� �񰡰� ���� �� �ۿ� ����.",
        L"��� ���ϸ�, ����� �������� ������ ������ �����մϴ�.",
L"",
L"",
0,
9,
0
        });

    CCollisionMgr::GetInst()->CollisionCheckClear();
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::Rock);

    // �θ� CLevel �� Begin ȣ��
    CLevel::Begin();
}

void CLevelLobby::Render()
{
    CLevel::Render();
}

void CLevelLobby::End()
{
    DeleteAllObject();
}

