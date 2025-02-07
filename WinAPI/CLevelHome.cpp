#include "pch.h"
#include "CLevelHome.h"

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
#include "CSound.h"
#include "CSoundMgr.h"

#include "CLevel_Start.h"
#include "CLevelMgr.h"

CLevelHome::CLevelHome()
{
    CLevel::stage = LEVEL_CHECK::STAGE_HOME;
}

CLevelHome::~CLevelHome()
{

}

void CLevelHome::Init()
{

}

void CLevelHome::Begin()
{

    //Add Object Reset할 오브젝트 추가
    Init();

    CDemon* pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(CERBERUS);
    pDemon->SetPos(250.f, 550.f);
    pDemon->SetScale(100.f, 100.f);
    pDemon->DemonTalk = true;
    AddObject(pDemon, LAYER_TYPE::DEMON);

    pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(CERBERUS);
    pDemon->SetPos(250.f, 650.f);
    pDemon->SetScale(100.f, 100.f);
    pDemon->DemonTalk = true;
    AddObject(pDemon, LAYER_TYPE::DEMON);

    pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(CERBERUS);
    pDemon->DemonTalk = true;
    pDemon->SetPos(250.f, 450.f);
    pDemon->SetScale(100.f, 100.f);
    AddObject(pDemon, LAYER_TYPE::DEMON);

    pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(LUCY_HOME);
    pDemon->SetPos(1350.f, 450.f);
    pDemon->SetScale(100.f, 100.f);
    AddObject(pDemon, LAYER_TYPE::DEMON);

    pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(JUSTICE);
    pDemon->SetPos(1250.f, 450.f);
    pDemon->SetScale(100.f, 100.f);
    AddObject(pDemon, LAYER_TYPE::DEMON);

    pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(MODEUS);
    pDemon->DemonTalk = true;
    pDemon->SetPos(1650.f, 550.f);
    pDemon->SetScale(100.f, 100.f);
    AddObject(pDemon, LAYER_TYPE::DEMON);

    pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(MALINA);
    pDemon->DemonTalk = true;
    pDemon->SetPos(750.f, 550.f);
    pDemon->SetScale(100.f, 100.f);
    AddObject(pDemon, LAYER_TYPE::DEMON);

    pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(ZDRADA);
    pDemon->SetPos(750.f, 150.f);
    pDemon->DemonTalk = true;
    pDemon->SetScale(100.f, 100.f);
    AddObject(pDemon, LAYER_TYPE::DEMON);

    pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(AZAZEL);
    pDemon->SetPos(350.f, 150.f);
    pDemon->DemonTalk = true;
    pDemon->SetScale(100.f, 100.f);
    AddObject(pDemon, LAYER_TYPE::DEMON);

    pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(JUDGMENT);
    pDemon->DemonTalk = true;
    pDemon->SetPos(550.f, 550.f);
    pDemon->SetScale(100.f, 100.f);
    AddObject(pDemon, LAYER_TYPE::DEMON);

    pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(POLICE);
    pDemon->SetPos(350.f, 850.f);
    pDemon->SetScale(100.f, 100.f);
    AddObject(pDemon, LAYER_TYPE::DEMON);

    //Player 생성
    CPlayer* pObject = new CPlayer;
    pObject->SetName(L"Player");
    pObject->SetPos(1450.f, 250.f);
    pObject->SetStartPos(1450.f, 250.f);
    pObject->SetScale(100.f, 100.f);
    pObject->SetOffset(0.f, 30.f);
    pObject->SetInitDir(0);
    pObject->TalkPartCheck = true;
    pObject->SetPlayerMoveCount(200);
    pObject->CurLevel = STAGE_HOME;
    AddObject(pObject, LAYER_TYPE::PLAYER);

    pObject->NewTalkCutScene[0].push_back({
    CUTSCENE_TYPE::TALK_CUTSCENE,
    DEMON_TYPE::NULLNAME,
    L"공백",
    L"공백",
    L"그리하여 당신의 여정은 끝이 났다.",
    L"",
    L"",
    L"",
    0,
    1,
    0,
    L"그리하여"
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::NULLNAME,
L"공백",
L"cutscene_0005_Layer-196",
L"악마들을 지옥에서 무사히 데려왔어.",
L"그리고 헬테이커라고 알려지게 됐지.",
L"",
L"",
0,
2,
0,
L"그리고헬테이커로"
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::NULLNAME,
L"공백",
L"cutscene_0006_Group-6-copy-3",
    L"하지만 쉽지 않은 삶일 터이니.",
    L"분명 짧고, 또 고난으로 가득하리.",
L"",
L"",
0,
3,
0,
L"하지만쉽지않는"
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::NEXTINDEXSCENE,
DEMON_TYPE::NULLNAME,
L"공백",
L"cutscene_0007_Group-6-copy-6",
L"하지만 어떻게 살아가든 삶이란 고달픈 법.",
L"그러니 그 순간만큼은 즐기는게 낫겠지.",
L"",
L"",
0,
4,
0,
L"삶은고달픈법"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_home",
L"LW_pc",
L"팬케이크 한 판 더 완성이다.",
L"",
L"",
L"",
0,
1,
0,
L"팬케이크한판더"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_home",
L"LW_yum",
L"그리고 차아아암 맛있어....",
L"",
L"",
L"",
0,
2,
0,
L"참맛있어"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::HELLTAKER,
L"dialogueBG_home",
L"man_pc",
L"도와줘서 고마워",
L"",
L"",
L"",
0,
3,
0,
L"도와줘서고마워"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_home",
L"LW_unsure",
L"새삼스럽게. 별 것도 아니였어",
L"",
L"",
L"",
0,
4,
0,
L"별것도아니였어"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_home",
L"LW_unsure",
L"그나저나 참, 네가 어떻게 매번 얇게 구워내는지 아직도",
L"모르겠어",
L"",
L"",
0,
5,
0,
L"어떻게이렇게얇게"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_home",
L"LW_unsure",
L"어떻게 팬케이크를 그렇게 공중으로 올려 뒤집는지도",
L"궁금하고. 무슨 마법이라도 쓰는 것 같아.",
L"",
L"",
0,
6,
0,
L"어떻게팬케이크를공중으로"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::HELLTAKER,
L"dialogueBG_home",
L"man_pc",
L"경험이지.",
L"",
L"",
L"",
0,
7,
0,
L"경험이지"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::NEXTINDEXSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_home",
L"LW_talk",
L"아 그러시겠어. 애들한테 팬케이크나 나눠줘.",
L"",
L"",
L"",
0,
8,
0,
L"아그러시겠어"
            });

        pObject->NewTalkCutScene[2].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::HELLTAKER,
L"dialogueBG_home",
L"man_pc",
L"여기 팬케이크.",
L"",
L"",
L"",
0,
1,
0
            });

        pObject->NewTalkCutScene[2].push_back({
    CUTSCENE_TYPE::TALK_CUTSCENE,
    DEMON_TYPE::JUSTICE,
    L"dialogueBG_home",
    L"jus_pc",
    L"끝내주네. 뭐 하나만 물어보자.",
    L"",
    L"",
    L"",
    0,
    2,
    0
            });

        pObject->NewTalkCutScene[2].push_back({
    CUTSCENE_TYPE::TALK_CUTSCENE,
    DEMON_TYPE::HELLTAKER,
    L"dialogueBG_home",
    L"man_pc",
    L"말해봐",
    L"",
    L"",
    L"",
    0,
    3,
    0
            });

        pObject->NewTalkCutScene[2].push_back({
    CUTSCENE_TYPE::TALK_CUTSCENE,
    DEMON_TYPE::JUSTICE,
    L"dialogueBG_home",
    L"jus_pc",
    L"애들 말로는 절대로 선글라스를 안벗는다는데, 왜 그런거야?",
    L"",
    L"",
    L"",
    0,
    4,
    0
            });

        pObject->NewTalkCutScene[2].push_back({
    CUTSCENE_TYPE::TALK_CUTSCENE,
    DEMON_TYPE::HELLTAKER,
    L"dialogueBG_home",
    L"man_pc",
    L"그 질문은 나도 물어보고 싶군.",
    L"",
    L"",
    L"",
    0,
    5,
    0
            });

        pObject->NewTalkCutScene[2].push_back({
    CUTSCENE_TYPE::TALK_CUTSCENE,
    DEMON_TYPE::JUSTICE,
    L"dialogueBG_home",
    L"jus_blind",
    L"나 말야? 나는 장님이라 쓴 건데.",
    L"",
    L"",
    L"",
    0,
    6,
    0
            });

        pObject->NewTalkCutScene[2].push_back({
    CUTSCENE_TYPE::TALK_CUTSCENE,
    DEMON_TYPE::JUSTICE,
    L"dialogueBG_home",
    L"jus_idle",
    L"내 사정은 이렇고. 네 얘기도 한번 들어볼까?",
    L"",
    L"",
    L"",
    0,
    7,
    0
            });

        pObject->NewTalkCutScene[2].push_back({
CUTSCENE_TYPE::NEXTINDEXSCENE,
DEMON_TYPE::HELLTAKER,
L"dialogueBG_home",
L"man_pc2",
L"다음에 언젠가...",
L"",
L"",
L"",
0,
8,
0
            });

        pObject->NewTalkCutScene[2].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUSTICE,
L"dialogueBG_home",
L"jus_curious",
L"에이, 거참. 여자 애들이랑 이미 내기 했단 말이야.",
L"",
L"",
L"",
0,
8,
0
            });

        pObject->NewTalkCutScene[2].push_back({
CUTSCENE_TYPE::NEXTINDEXSCENE,
DEMON_TYPE::JUSTICE,
L"dialogueBG_home",
L"jus_pc",
L"네 눈에서 레이저가 안나가면 내 만원이 날라간다고.",
L"",
L"",
L"",
0,
9,
0
            });

        pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::POLICE,
L"dialogueBG_home",
L"police_1",
L"경찰이다! 문 열어.",
L"",
L"",
L"",
0,
1,
0
            });

        pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::CHOICE_CUTSCENE,
DEMON_TYPE::POLICE,
L"dialogueBG_home",
L"police_1",
L"경찰이다! 문 열어.",
L"",
L"열기.",
L"열지 않기.",
1,
2,
2
            });

        pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::HELLTAKER,
L"dialogueBG_home",
L"man_pc",
L"팬케이크 어떠신가요?",
L"",
L"",
L"",
0,
3,
0
            });

        pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::POLICE,
L"dialogueBG_home",
L"police_2",
L"어, 고맙네요. 그런데 몇가지 여쭤 봐야겠습니다.",
L"",
L"",
L"",
0,
4,
0
            });

        pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::NULLNAME,
L"공백",
L"공백",
L"...",
L"",
L"",
L"",
0,
5,
0
            });

        pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::NULLNAME,
L"공백",
L"cutscene_0008_Group-5",
L"그렇게 헬테이커의 이야기는 끝이 납니다.",
L"",
L"",
L"",
0,
6,
0
            });

        pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::NEXT_LEVELSCENE,
DEMON_TYPE::NULLNAME,
L"공백",
L"cutscene_0008_Group-5",
L"이상 당신의 친구 베엘제붑의 나레이션이였습니다.",
L"",
L"",
L"",
0,
7,
0
            });
    CBackground* pBackground = new CBackground;
    pBackground->SetPos(0.f, -10.f);
    pBackground->SetBackgroundMap(L"Home07");
    AddObject(pBackground, LAYER_TYPE::BACKGROUND);

    CWall* pWall = new CWall;
    pWall->SetPos(1150.f, 150.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(200.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1250.f, 150.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(200.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    // Platform Object 추가
    //CObj* pPlatform = new CPlatform;
    //pPlatform->SetPos(0, 200);
    //AddObject(pPlatform, LAYER_TYPE::TILE);

    // 충돌 설정
    CCollisionMgr::GetInst()->CollisionCheckClear();
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::Rock);
    //CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::TILE);

    // Camera 효과
    //CCamera::GetInst()->PostProcessEffect(HEART, 0.5f);  

    // 부모 CLevel 의 Begin 호출
    CLevel::Begin();
}

void CLevelHome::Render()
{
    CLevel::Render();
}

void CLevelHome::End()
{
    DeleteAllObject();
}
