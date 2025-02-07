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

    //Player 생성
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
L"공백",
        L"당신은 주변이 심연으로 둘러쌓인 것을 알아차립니다.",
        L"[ENTER]를 눌러 계속하기.",
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
        L"환영하네 인간이여. 너무 놀라지 말게나.",
        L"자네의 친구 베엘제붑일세.",
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
L"새 게임",
L"나가기",
0,
8,
3      });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::BEEL_FLY,
L"dialogueBG_abyss",
L"BEEL_FLY",
        L"또 헬테이커의 이야기를 듣고 싶다고? 흥미롭군...",
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
        L"혹시 말이야, 나레이터가 필요하지는 않나?",
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
L"공백",
L"공백",
        L"내게 허락만 해준다면... 그거 참 영광이겠군",
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
L"공백",
        L"어느날 당신은 원대한 꿈을 가지고 일어났습니다.",
        L"여악마들이 가득한 하렘을 만드는 것이 꿈이죠.",
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
L"공백",
        L"하지만, 당신은 이 꿈이 쉽지 않다는 것을 알고 있었습니다.",
        L"그리고 목숨을 잃을 만한 위태로운 상황이 닥칠 것도요.",
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
L"공백",
        L"여악마들이 관련된 일이라면, 그만한 댓가가 따를 수 밖에 없지.",
        L"라고 말하며, 당신은 지옥으로 여정을 떠나기 시작합니다.",
L"",
L"",
0,
9,
0
        });

    CCollisionMgr::GetInst()->CollisionCheckClear();
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::Rock);

    // 부모 CLevel 의 Begin 호출
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

