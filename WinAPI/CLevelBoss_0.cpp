#include "pch.h"
#include "CLevelBoss_0.h"

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
#include "CBridge.h"
#include "CGear.h"
#include "CJudmentPiston.h"
#include "CJudmentCastle.h"
#include "CJudmentSkul.h"
#include "CBlackChain.h"
#include "CDamageChain.h"

#include "CLevel_Start.h"
#include "CLevelMgr.h"

CLevelBoss_0::CLevelBoss_0()
{
    CLevel::stage = LEVEL_CHECK::BOSS_0;
}

CLevelBoss_0::~CLevelBoss_0()
{

}

void CLevelBoss_0::Init()
{

}

void CLevelBoss_0::Begin()
{

    //Add Object Reset할 오브젝트 추가
    Init();

    CFire* pfire = new CFire;
    pfire->SetPos(500.f, 937.f + 50.f);
    pfire->white = true;
    pfire->num = 0;
    pfire->SetScale(100.f, 100.f);
    AddObject(pfire, LAYER_TYPE::FIRE);

    pfire = new CFire;
    pfire->SetPos(700.f, 937.f + 50.f);
    pfire->white = true;
    pfire->num = 1;
    pfire->SetScale(100.f, 100.f);
    AddObject(pfire, LAYER_TYPE::FIRE);

    pfire = new CFire;
    pfire->SetPos(1200.f, 937.f +50.f);
    pfire->white = true;
    pfire->num = 2;
    pfire->SetScale(100.f, 100.f);
    AddObject(pfire, LAYER_TYPE::FIRE);

    pfire = new CFire;
    pfire->SetPos(1400.f, 937.f + 50.f);
    pfire->white = true;
    pfire->num = 3;
    pfire->SetScale(100.f, 100.f);
    AddObject(pfire, LAYER_TYPE::FIRE);

    CWall* pWall = new CWall;
    pWall->SetPos(550.f, 250.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f, 350.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f, 450.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f, 550.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f, 650.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f, 750.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 250.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 350.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 450.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 550.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 650.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 750.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    //Player 생성
    CPlayer* pObject = new CPlayer;
    pObject->SetName(L"Player");
    pObject->SetPos(950.f, 650.f);
    pObject->SetStartPos(950.f, 650.f);
    pObject->SetScale(100.f, 100.f);
    pObject->SetOffset(-5.f, 30.f);
    pObject->SetInitDir(0);
    pObject->SetPlayerMoveCount(50);
    pObject->CurLevel = BOSS_0;
    pObject->TalkPartCheck = true;
    AddObject(pObject, LAYER_TYPE::PLAYER);

    CThorn* th = new CThorn;
    th->SetOffset(-20.f, 0.f);
    th->SetThorn(0);
    th->SetScale(100.f, 100.f);
    th->SetPos(650.f, 350.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetOffset(-20.f, 0.f);
    th->SetThorn(0);
    th->SetPos(750.f, 350.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetOffset(-20.f, 0.f);
    th->SetPos(850.f, 350.f);
    th->SetThorn(0);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetPos(950.f, 350.f);
    th->SetThorn(0);
    th->SetOffset(-20.f, 0.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetOffset(-20.f, 0.f);
    th->SetThorn(0);
    th->SetPos(1050.f, 350.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetOffset(-20.f, 0.f);
    th->SetThorn(0);
    th->SetPos(1150.f, 350.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetOffset(-20.f, 0.f);
    th->SetThorn(0);
    th->SetPos(1250.f, 350.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetOffset(-20.f, 0.f);
    th->SetScale(100.f, 100.f);
    th->SetPos(650.f, 250.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetOffset(-20.f, 0.f);
    th->SetPos(750.f, 250.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetOffset(-20.f, 0.f);
    th->SetPos(850.f, 250.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetPos(950.f, 250.f);
    th->SetOffset(-20.f, 0.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetOffset(-20.f, 0.f);
    th->SetPos(1050.f, 250.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetOffset(-20.f, 0.f);
    th->SetPos(1150.f, 250.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetOffset(-20.f, 0.f);
    th->SetPos(1250.f, 250.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetOffset(-20.f, 0.f);
    th->SetPos(650.f, 1050.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetPos(750.f, 1050.f);
    th->SetOffset(-20.f, 0.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetOffset(-20.f, 0.f);
    th->SetPos(850.f, 1050.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetOffset(-20.f, 0.f);
    th->SetPos(950.f, 1050.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetPos(1050.f, 1050.f);
    th->SetOffset(-20.f, 0.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetOffset(-20.f, 0.f);
    th->SetPos(1150.f, 1050.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetPos(1250.f, 1050.f);
    th->SetOffset(-20.f, 0.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetOffset(-20.f, 0.f);
    th->SetPos(650.f, 950.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetPos(750.f, 950.f);
    th->SetOffset(-20.f, 0.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetOffset(-20.f, 0.f);
    th->SetPos(850.f, 950.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetOffset(-20.f, 0.f);
    th->SetPos(950.f, 950.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetPos(1050.f, 950.f);
    th->SetOffset(-20.f, 0.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetOffset(-20.f, 0.f);
    th->SetPos(1150.f, 950.f);
    AddObject(th, LAYER_TYPE::THORN);

    th = new CThorn;
    th->SetScale(100.f, 100.f);
    th->SetPos(1250.f, 950.f);
    th->SetOffset(-20.f, 0.f);
    AddObject(th, LAYER_TYPE::THORN);

    //BRIDGE
    CBridge* pBridge = new CBridge;
    pBridge->SetPos(1920.f / 2.f, -200.f );
    AddObject(pBridge, LAYER_TYPE::BRIDGE);

    pBridge = new CBridge;
    pBridge->SetPos(1920.f / 2.f, 400.f);
    AddObject(pBridge, LAYER_TYPE::BRIDGE);

    pBridge = new CBridge;
    pBridge->SetPos(1920.f / 2.f, 1000.f);
    AddObject(pBridge, LAYER_TYPE::BRIDGE);

    CGear* pGear = new CGear;
    pGear->GearTurn = false;
    pGear->SetPos(200.f, 930.f);
    pGear->gear = 0;
    AddObject(pGear, LAYER_TYPE::GEAR);

    pGear = new CGear;
    pGear->SetPos(1720.f, 930.f);
    pGear->GearTurn = false;
    pGear->gear = 1;
    AddObject(pGear, LAYER_TYPE::GEAR);

    CJudmentPiston* pJud = new CJudmentPiston;
    pJud->SetPos(1740.f, 1210.f);
    pJud->Under = false;
    pJud->TurnPiston = false;
    AddObject(pJud, LAYER_TYPE::HIGH_PISTON);

    pJud = new CJudmentPiston;
    pJud->SetPos(1740.f, 1210.f);
    pJud->Under = true;
    pJud->TurnPiston = false;
    AddObject(pJud, LAYER_TYPE::HIGH_UNDER_PISTON);

    pJud = new CJudmentPiston;
    pJud->SetPos(180.f, 1210.f);
    pJud->Under = false;
    pJud->TurnPiston = false;
    AddObject(pJud, LAYER_TYPE::HIGH_PISTON);

    pJud = new CJudmentPiston;
    pJud->SetPos(180.f, 1210.f);
    pJud->Under = true;
    pJud->TurnPiston = false;
    AddObject(pJud, LAYER_TYPE::HIGH_UNDER_PISTON);

    pJud = new CJudmentPiston;
    pJud->SetPos(180.f, -70.f);
    pJud->Under = false;
    pJud->TurnPiston = false;
    AddObject(pJud, LAYER_TYPE::LOW_PISTON);

    pJud = new CJudmentPiston;
    pJud->SetPos(180.f, -70.f);
    pJud->Under = true;
    pJud->TurnPiston = false;
    AddObject(pJud, LAYER_TYPE::LOW_UNDER_PISTON);

    pJud = new CJudmentPiston;
    pJud->SetPos(1740.f, -70.f);
    pJud->Under = false;
    pJud->TurnPiston = false;
    AddObject(pJud, LAYER_TYPE::LOW_PISTON);

    pJud = new CJudmentPiston;
    pJud->SetPos(1740.f, -70.f);
    pJud->Under = true;
    pJud->TurnPiston = false;
    AddObject(pJud, LAYER_TYPE::LOW_UNDER_PISTON);


    CJudmentCastle* pCastle = new CJudmentCastle;
    pCastle->SetPos(1920.f / 2.f, 0.f);
    AddObject(pCastle, LAYER_TYPE::CASTLE);


    CJudmentSkul* pSkul = new CJudmentSkul;
    pSkul->Under = false;
    pSkul->dir = 0;
    pSkul->SetPos(180.f, 750.f);
    AddObject(pSkul, LAYER_TYPE::SKUL);

    pSkul = new CJudmentSkul;
    pSkul->Under = true;
    pSkul->SetPos(180.f, 750.f);
    AddObject(pSkul, LAYER_TYPE::UNDER_SKUL);

    pSkul = new CJudmentSkul;
    pSkul->Under = false;
    pSkul->dir = 1;
    pSkul->SetPos(1740.f, 750.f);
    AddObject(pSkul, LAYER_TYPE::SKUL);

    pSkul = new CJudmentSkul;
    pSkul->Under = true;
    pSkul->SetPos(1740.f, 750.f);
    AddObject(pSkul, LAYER_TYPE::UNDER_SKUL);



    CBlackChain* pChain = new CBlackChain;
    pChain->SetPos(1740.f, 1000.f);
    AddObject(pChain, LAYER_TYPE::CHAIN);

    pChain = new CBlackChain;
    pChain->SetPos(1740.f, 800.f);
    AddObject(pChain, LAYER_TYPE::CHAIN);

    pChain = new CBlackChain;
    pChain->SetPos(1740.f, 600.f);
    AddObject(pChain, LAYER_TYPE::CHAIN);

    pChain = new CBlackChain;
    pChain->SetPos(1740.f, 400.f);
    AddObject(pChain, LAYER_TYPE::CHAIN);

    pChain = new CBlackChain;
    pChain->SetPos(1740.f, 200.f);
    AddObject(pChain, LAYER_TYPE::CHAIN);

    pChain = new CBlackChain;
    pChain->SetPos(1740.f, 0.f);
    AddObject(pChain, LAYER_TYPE::CHAIN);

    pChain = new CBlackChain;
    pChain->SetPos(180.f, 1000.f);
    AddObject(pChain, LAYER_TYPE::CHAIN);

    pChain = new CBlackChain;
    pChain->SetPos(180.f, 800.f);
    AddObject(pChain, LAYER_TYPE::CHAIN);

    pChain = new CBlackChain;
    pChain->SetPos(180.f, 600.f);
    AddObject(pChain, LAYER_TYPE::CHAIN);

    pChain = new CBlackChain;
    pChain->SetPos(180.f, 400.f);
    AddObject(pChain, LAYER_TYPE::CHAIN);

    pChain = new CBlackChain;
    pChain->SetPos(180.f, 200.f);
    AddObject(pChain, LAYER_TYPE::CHAIN);

    pChain = new CBlackChain;
    pChain->SetPos(180.f, 0.f);
    AddObject(pChain, LAYER_TYPE::CHAIN);

    pObject->NewTalkCutScene[0].push_back({
       CUTSCENE_TYPE::TALK_CUTSCENE,
       DEMON_TYPE::QUESTION,
       L"공백",
       L"공백",
       L"이 침입자 녀석! 이제서야 널 찾았다.",
       L"",
       L"",
       L"",
       0,
       1,
       0
        });

    pObject->NewTalkCutScene[0].push_back({
   CUTSCENE_TYPE::TALK_CUTSCENE,
   DEMON_TYPE::QUESTION,
   L"dialogueBG_sin",
   L"공백",
   L"지금 여기서 편히 죽을 생각은 마",
   L"너랑 나랑, 아주 오랜 시간 동안 있어야 할테니까",
   L"",
   L"",
   0,
   2,
   0
        });

//    pObject->NewTalkCutScene[0].push_back({
//CUTSCENE_TYPE::TALK_CUTSCENE,
//DEMON_TYPE::QUESTION,
//L"dialogueBG_sin",
//L"공백",
//L"형벌의 기계에 불을 밝혀라! 고행은 반드시 치뤄져야 한다!",
//L"",
//L"",
//L"",
//0,
//3,
//0
//        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::NEXTINDEXSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim",
L"죄악의 기계에 시동을 걸어라! 시련을 피할 수는 없다!",
L"",
L"",
L"",
0,
3,
0,
L"죄악의기계에시동을"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"침입자야! 죄악의 기계가 마음에 드느냐!",
L"",
L"",
L"",
0,
1,
0,
L"죄악의기계가마음"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"이만 굴복하고 삼켜져라!",
L"",
L"",
L"",
0,
2,
0,
L"이만굴복하고"
});

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::CERBERUS,
L"dialogueBG_sin",
L"cer_idle",
L"안돼 잠깐! 포기하면 안돼! 우리를 데리고 나가야지!",
L"",
L"",
L"",
0,
3,
0,
L"안돼포기하지마"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::PANDEMONICA,
L"dialogueBG_sin",
L"pand_flust",
L"그리고 커피도 타주셔야죠...",
L"",
L"",
L"",
0,
4,
0,
L"그리고커피도"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_back",
L"희망은 버려라! 저 녀석의 운명은 이미 정해졌다!",
L"",
L"",
L"",
0,
5,
0,
L"희망을버려라"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_sin",
L"LH_angry",
L"이런 저지먼트, 이 녀석은 모르고 있겠지만, 내거야.",
L"그냥 내버려 놓을 순 없어?",
L"",
L"",
0,
6,
0,
L"내꺼야그냥내버려"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::NEXTINDEXSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_angry",
L"정숙해라! 이제 진짜 시작이다.",
L"",
L"",
L"",
0,
6,
0,
L"정숙하라"
        });

    pObject->NewTalkCutScene[2].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"j_laugh2",
L"너를 이곳으로 이끌었던 것들이 사슬이 되어, 너를 휘감지",
L"",
L"",
L"",
0,
1,
0,
L"사슬이되어너를휘감지"
        });


    pObject->NewTalkCutScene[2].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"j_laugh2",
L"너의 교만, 너의 탐욕, 그리고 욕정, 네 고통은 스스로 자초한거다.",
L"",
L"",
L"",
0,
2,
0,
L"스스로자초"
        });

    pObject->NewTalkCutScene[2].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_sin",
L"LH_angry",
L"그만! 고위 기소관, 즉시 물러날 것을 명한다.",
L"",
L"",
L"",
0,
3,
0,
L"그만고위귀소관"
        });

    pObject->NewTalkCutScene[2].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_angry",
L"그 어떤 권위도 형벌을 넘어 설 수 없다!",
L"",
L"",
L"",
0,
4,
0,
L"그어떤권위도"
        });

    pObject->NewTalkCutScene[2].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUSTICE,
L"dialogueBG_sin",
L"jus_idle",
L"저지먼트 계속해봐, 잘 나가는데?",
L"",
L"",
L"",
0,
5,
0,
L"저지먼트계속해봐"
        });

    pObject->NewTalkCutScene[2].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::AZAZEL,
L"dialogueBG_sin",
L"az_note",
L"그래요, 계속하세요. 이거 분명 A+ 받을 만한 소재에요.",
L"",
L"",
L"",
0,
6,
0,
L"그래요계속하세요"
        });


    pObject->NewTalkCutScene[2].push_back({
CUTSCENE_TYPE::NEXTINDEXSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_sin",
L"LH_rustled",
L"내가 지옥의 여왕일텐데! 왜 아무도 말귀를 안 처 들어?",
L"",
L"",
L"",
0,
7,
0,
L"내가지옥의"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"j_bindAnimNull",
L"진정 사실을 부수고 빠져 나갈 수 있을 것 같으냐?",
L"",
L"",
L"",
0,
1,
0,
L"진정사슬을부수고"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"j_bindAnimNull",
L"희망은 실망을, 그리고 실망은 절망을 낳는다.",
L"",
L"",
L"",
0,
2,
0,
L"희망은실망을"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"j_bindAnimNull",
L"그리고 절망의 사슬이 가장 즐거운 법이지.",
L"",
L"",
L"",
0,
3,
0,
L"그리고절망의사슬이"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::ZDRADA,
L"dialogueBG_sin",
L"z_idle",
L"하.. 말린카는 재수도 없지 기껏 찾은 겜스퍼거 친구가 죽게 생겼네.",
L"",
L"",
L"",
0,
4,
0,
L"재수도없지"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::MALINA,
L"dialogueBG_sin",
L"mal_puzzled",
L"내 운수가 이러니 쟤가 네크로폴리스를 하게 됐어.",
L"",
L"",
L"",
0,
5,
0,
L"내운수가"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::MODEUS,
L"dialogueBG_sin",
L"mod_idle",
L"차라리 나 혼자 독차지 할 걸...",
L"",
L"",
L"",
0,
6,
0,
L"차라리나혼자"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"그래! 네가 행한 모든 것들을 후회하라!",
L"",
L"",
L"",
0,
7,
0,
L"네가행한"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::CHOICE_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"그래! 네가 행한 모든 것들을 후회하라!",
L"",
L"네 헤어 스타일이 마음에 드는데.",
L"그 옷 끝내주는데! 10점 만점에 10점!",
2,
8,
8
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"거짓말! 기만으로 네 운명을 벗어날 수는 없다!",
L"",
L"",
L"",
0,
9,
0,
L"기만으로"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::CHOICE_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"거짓말! 기만으로 네 운명을 벗어날 수는 없다!",
L"",
L"알아. 그래서 지금 이렇게 솔직한 거지.",
L"그 손톱도 꽤 마음에 드는데!",
2,
10,
10
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"j_poseAnim (3)",
L"그래? 그렇다면, 고맙다! 라고 해야겠지?",
L"",
L"",
L"",
0,
11,
0,
L"그래"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::NEXTINDEXSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"j_flyAnim_4",
L"이제 다시 시련을 시작한다!",
L"",
L"",
L"",
0,
12,
0,
L"시련을"
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"진정한 고통이 시작되기 전에 남길 말이라도 있느냐?",
L"",
L"",
L"",
0,
1,
0,
L"진정한"
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::CHOICE_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"진정한 고통이 시작되기 전에 남길 말이라도 있느냐?",
L"",
L"너를 일찍 보지 못한게 가장 후회되는 군.",
L"너에게 벌을 받고 있는게 죄를 지을 가치가 있다고 생각해.",
2,
2,
2,
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"값싼 아부는 집어치워! 일을 어렵게 만들지 마!",
L"",
L"",
L"",
0,
3,
0,
L"값싼"
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::CHOICE_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"값싼 아부는 집어치워! 일을 어렵게 만들지 마!",
L"",
L"게다가, 이렇게 예쁜 눈이 또 있을까.",
L"내가 아까 머리 스타일 멋지다고 얘기 했었나?",
2,
4,
4
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_resign",
L"있잖아, 나도 별로 이러고 싶진 않은데. 하지만 이미 계약이",
L"확정됐어. 네 저주를 막을 수 없다고.",
L"",
L"",
0,
5,
0,
L"있잖아"
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_resign",
L"그래도... 네가 다시 지옥을 휘젓고 다니지만 않는다면 뒤로",
L"미룰 수는 있겠지.",
L"",
L"",
0,
6,
0,
L"그래도네가다시"
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_resign",
L"우리 운명은 정해져 있어. 난 너를 죽이고, 넌 시련을 받아야 하지.",
L"하지만 그게 꼭 오늘일 필요야 없어...",
L"",
L"",
0,
7,
0,
L"우리운명은"
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"그러니 운 좋은 줄 알고 내 눈 앞에서 사라져라!",
L"",
L"",
L"",
0,
8,
0,
L"그러니운좋은"
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"...",
L"",
L"",
L"",
0,
9,
0
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"... ...",
L"",
L"",
L"",
0,
10,
0
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"... ... ...",
L"",
L"",
L"",
0,
11,
0
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_angry",
L"가도 된다고 했잖아! 썩 사라져!",
L"",
L"",
L"",
0,
12,
0,
L"가도된다고"
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_angry",
L"뭐? 네 하렘에 들어오라고? 웃기지 마라!",
L"",
L"",
L"",
0,
13,
0,
L"네하렘으로"
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_resign",
L"고문으로 널 죽이려는 고통의 화신과 한 지붕 아래서",
L"살겠다고?",
L"",
L"",
0,
14,
0,
L"고문으로"
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::CHOICE_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_resign",
L"고문으로 널 죽이려는 고통의 화신과 한 지붕 아래서",
L"살겠다고?",
L"그것 말고 다른건 원하지 않아",
L"내 말 들어봐, 이미 내 하렘에 더 끔직한게 있다니까.",
2,
15,
15
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::SUCESS_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_shock",
L"뭐? 진심이야?",
L"",
L"",
L"",
0,
16,
0,
L"진심이야"
        });
    pObject->diemessage = L"시야가 흐릿해지기 시작하더니, 갈비뼈 사이로 칼 한자루가";
    pObject->diemessage2 = L"깊게 박힌 것을 보고 눈 앞이 깜깜해졌습니다.";

    CBackground* pBackground = new CBackground;
    pBackground->SetPos(0.f, 0.f);
    pBackground->SetBackgroundMap(L"공백");
    AddObject(pBackground, LAYER_TYPE::BACKGROUND);

    //TileMap Object 추가
    //CMap* pTileMap = new CMap;
    //pTileMap->SetPos(Vec2(0.f, 0.f));
    //wstring FilePath = CPathMgr::GetContentPath();
    //pTileMap->GetTileMap()->LoadTileMap(FilePath + L"TileMap\\Temp.tile");
    //AddObject(pTileMap, LAYER_TYPE::TILE);

    // Platform Object 추가
    //CObj* pPlatform = new CPlatform;
    //pPlatform->SetPos(500, 800);
    //AddObject(pPlatform, LAYER_TYPE::TILE);

    // 충돌 설정
    CCollisionMgr::GetInst()->CollisionCheckClear();
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::THORN);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::DAMAGE_CHAIN);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::TILE);

    // Camera 효과
    //CCamera::GetInst()->PostProcessEffect(HEART, 0.5f);  

    // 부모 CLevel 의 Begin 호출
    CLevel::Begin();

}

void CLevelBoss_0::Render()
{
    CLevel::Render();

}

void CLevelBoss_0::End()
{
    DeleteAllObject();
}

