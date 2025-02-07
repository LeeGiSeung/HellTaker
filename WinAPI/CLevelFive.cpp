#include "pch.h"
#include "CLevelFive.h"
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

CLevelFive::CLevelFive()
{
}

CLevelFive::~CLevelFive()
{

}

void CLevelFive::Init()
{
    CKey* pKey = new CKey;
    pKey->SetPos(1250.f, 850.f);
    pKey->SetOffset(10.f, 30.f);
    pKey->SetScale(100.f, 100.f);
    AddObject(pKey, LAYER_TYPE::KEY);

    CKeybox* pKeybox = new CKeybox;
    pKeybox->SetPos(1050.f, 350.f);
    pKeybox->SetScale(100.f, 100.f);
    AddObject(pKeybox, LAYER_TYPE::KEYBOX);

    // Monster 생성
    CMonster* pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(750.f, 650.f);
    pMonster->SetScale(100.f, 100.f);
    pMonster->SetOffset(0.f, 30.f);
    pMonster->SetDistance(200.f);
    pMonster->SetSpeed(300.f);
    pMonster->SetSound(1);
    AddObject(pMonster, LAYER_TYPE::MONSTER);

    //CMonster* pMonster3 = new CMonster;
    //pMonster3->SetName(L"Monster");
    //pMonster3->SetPos(1050.f, 650.f);
    //pMonster3->SetScale(100.f, 100.f);
    //pMonster3->SetDistance(200.f);
    //pMonster3->SetSpeed(300.f);
    //pMonster3->SetSound(3);
    //AddObject(pMonster3, LAYER_TYPE::MONSTER);

    CThorn* pThorn = new CThorn;
    pThorn->SetThorn(THORN_DOWN);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(750.f, 750.f);
    pThorn->SetOffset(-10.f, 5.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    CRock* pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_0");
    pRock1->SetPos(950.f, 650.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_1");
    pRock1->SetPos(1050.f, 650.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_2");
    pRock1->SetPos(1150.f, 650.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_3");
    pRock1->SetPos(1150.f, 450.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_4");
    pRock1->SetPos(1150.f, 350.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_5");
    pRock1->SetPos(1250.f, 650.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_DOWN);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(950.f, 750.f);
    pThorn->SetOffset(-10.f, 5.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_DOWN);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(950.f, 450.f);
    pThorn->SetOffset(-10.f, 5.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_DOWN);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(1050.f, 550.f);
    pThorn->SetOffset(-10.f, 5.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_DOWN);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(1250.f, 750.f);
    pThorn->SetOffset(-10.f, 5.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_DOWN);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(1250.f, 550.f);
    pThorn->SetOffset(-10.f, 5.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);
}

void CLevelFive::Begin()
{
    //Add Object Reset할 오브젝트 추가
    Init();

    CWall* pWall = new CWall;
    pWall->SetPos(650.f, 350.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(650.f, 450.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(650.f, 550.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(650.f, 650.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(650.f, 750.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(650.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);


    pWall = new CWall;
    pWall->SetPos(750.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);


    pWall = new CWall;
    pWall->SetPos(850.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);


    pWall = new CWall;
    pWall->SetPos(950.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);


    pWall = new CWall;
    pWall->SetPos(1050.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);


    pWall = new CWall;
    pWall->SetPos(1150.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1150.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1250.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 750.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 650.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 550.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 450.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 350.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 250.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 150.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1250.f, 150.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1250.f, 250.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1150.f, 150.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1050.f, 150.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(950.f, 150.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(950.f, 250.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(850.f, 150.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(850.f, 250.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(850.f, 350.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(750.f, 350.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(850.f, 450.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(850.f, 550.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(850.f, 650.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);


    CDemon* pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(ZDRADA);
    pDemon->SetPos(1150.f, 250.f);
    pDemon->SetScale(100.f, 100.f);
    AddObject(pDemon, LAYER_TYPE::DEMON);

    //Player 생성
    CPlayer* pObject = new CPlayer;
    pObject->SetName(L"Player");
    pObject->SetPos(750.f, 450.f);
    pObject->SetStartPos(750.f, 450.f);
    pObject->SetScale(100.f, 100.f);
    pObject->SetOffset(0.f, 30.f);
    pObject->SetInitDir(0);
    pObject->SetPlayerMoveCount(23);
    pObject->CurLevel = STAGE_4;
    AddObject(pObject, LAYER_TYPE::PLAYER);

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::ZDRADA,
L"dialogueBG_hell",
L"z_idle",
        L"야. 너 하렘 만든다면서? 껴줘.",
        L"어디서 놀다온 사람이냐 넌?",
L"",
L"",
0,
1,
0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::CHOICE_CUTSCENE,
DEMON_TYPE::ZDRADA,
L"dialogueBG_hell",
L"z_idle",
        L"야. 너 하렘 만든다면서? 껴줘.",
        L"어디서 놀다온 사람이냐 넌?",
        L"잠깐. 왠지 후회할거 같은데.",
        L"여기엔 하렘 따윈 없어. 오직 턴제 전투 게임 뿐이지.",
1,
2,
3
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::SUCESS_CUTSCENE,
DEMON_TYPE::ZDRADA,
L"dialogueBG_hell",
L"z_laugh",
        L"거 안됐네, 어차피 낄 생각이였어. 어디 막을 수 있으면 막아봐.",
        L"",
L"",
L"",
0,
1,
0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::DIE_CUTSCENE,
DEMON_TYPE::ZDRADA,
L"dialogueBG_hell",
L"z_idle",
        L"정말 끔직하네. 내가 그 고통을 끝내줄게",
        L"",
L"",
L"",
0,
1,
0
        });


    //pObject->TalkCutScene[0].push_back({
    //    CUTSCENE_TYPE::TALK_CUTSCENE,
    //    DEMON_TYPE::ZDRADA,
    //    L"dialogueBG_hell",
    //    L"z_idle",
    //    L"야. 너 하렘 만든다면서? 껴줘.",
    //    L"어디서 놀다온 사람이냐 넌?",
    //    1,
    //    });

    //pObject->TalkCutScene[0].push_back({
    //    CUTSCENE_TYPE::CHOICE_CUTSCENE,
    //    DEMON_TYPE::ZDRADA,
    //    L"dialogueBG_hell",
    //    L"z_idle",
    //    L"잠깐. 웬지 후회할거 같은데.",
    //    L"여기엔 하렘 따윈 없어. 오직 턴제 전투 게임 뿐이지.",
    //    1,
    //    });

    //pObject->TalkCutScene[0].push_back({
    //    CUTSCENE_TYPE::SUCESS_CUTSCENE,
    //    DEMON_TYPE::ZDRADA,
    //    L"dialogueBG_hell",
    //    L"z_laugh",
    //    L"거 안됐네, 어차피 낄 생각이였어. 어디 막을 수 있으면 막아봐.",
    //    L"",
    //    1,
    //    });

    //pObject->TalkCutScene[0].push_back({
    //    CUTSCENE_TYPE::DIE_CUTSCENE,
    //    DEMON_TYPE::ZDRADA,
    //    L"dialogueBG_hell",
    //    L"z_idle",
    //    L"정말 끔직하네. 내가 그 고통을 끝내줄게",
    //    L"",
    //    1,
    //    });

    pObject->diemessage = L"시야가 흐릿해지기 시작하더니, 갈비뼈 사이로 칼 한자루가";
    pObject->diemessage2 = L"깊게 박힌 것을 보고 눈 앞이 깜깜해졌습니다.";

    CBackground* pBackground = new CBackground;
    pBackground->SetPos(40.f, 40.f);
    pBackground->SetBackgroundMap(L"chapterBG_5");
    AddObject(pBackground, LAYER_TYPE::BACKGROUND);

    //TileMap Object 추가
    //CMap* pTileMap = new CMap;
    //pTileMap->SetPos(Vec2(0.f, 0.f));
    //wstring FilePath = CPathMgr::GetContentPath();
    //pTileMap->GetTileMap()->LoadTileMap(FilePath + L"TileMap\\Temp.tile");
    //AddObject(pTileMap, LAYER_TYPE::TILE);

    CFireBase* pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(645.f, 650.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    CFire* pFire = new CFire;
    pFire->SetPos(Vec2(645.f, 650.f));
    pFire->SetOffset(7.f, -100.f);
    AddObject(pFire, LAYER_TYPE::FIRE);

    pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(845.f, 605.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    pFire = new CFire;
    pFire->SetPos(Vec2(845.f, 605.f));
    pFire->SetOffset(7.f, -100.f);
    AddObject(pFire, LAYER_TYPE::FIRE);

    pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(1350.f, 650.f));
    pFireBase->SetOffset(5.f, 40.f);
    pFireBase->SetFireBase(1);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    //pFireBase = new CFireBase;
    //pFireBase->SetPos(Vec2(745.f, 650.f));
    //pFireBase->SetFireBase(0);
    //AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    //pFire = new CFire;
    //pFire->SetPos(Vec2(745.f, 650.f));
    //pFire->SetOffset(3.f, -40.f);
    //AddObject(pFire, LAYER_TYPE::FIRE);

    CCountUI* CUI = new CCountUI;
    CUI->SetCountUI(COUNT_UI_LEFT);
    AddObject(CUI, LAYER_TYPE::COUNTUI);

    CUI = new CCountUI;
    CUI->SetCountUI(COUNT_UI_RIGHT);
    AddObject(CUI, LAYER_TYPE::COUNTUI);

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

void CLevelFive::Render()
{
    CLevel::Render();
}

void CLevelFive::End()
{
    DeleteAllObject();
}

