#include "pch.h"
#include "CLevelSeven.h"

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
CLevelSeven::CLevelSeven()
{
}

CLevelSeven::~CLevelSeven()
{
}

void CLevelSeven::Init()
{
    CKey* pKey = new CKey;
    pKey->SetPos(800.f, 400.f);
    pKey->SetScale(100.f, 100.f);
    pKey->SetOffset(10.f, 30.f);
    AddObject(pKey, LAYER_TYPE::KEY);

    CKeybox* pKeybox = new CKeybox;
    pKeybox->SetPos(1100.f, 300.f);
    pKeybox->SetScale(100.f, 100.f);
    pKeybox->SetOffset(0.f, 10.f);
    AddObject(pKeybox, LAYER_TYPE::KEYBOX);

    // Monster 생성
    CMonster* pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(1000.f, 500.f);
    pMonster->SetScale(100.f, 100.f);
    pMonster->SetOffset(10.f, 30.f);
    pMonster->SetDistance(200.f);
    pMonster->SetSpeed(300.f);
    pMonster->SetSound(1);
    AddObject(pMonster, LAYER_TYPE::MONSTER);

    pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(900.f, 600.f);
    pMonster->SetScale(100.f, 100.f);
    pMonster->SetOffset(10.f, 30.f);
    pMonster->SetDistance(200.f);
    pMonster->SetSpeed(300.f);
    pMonster->SetSound(1);
    AddObject(pMonster, LAYER_TYPE::MONSTER);

    pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(700.f, 500.f);
    pMonster->SetScale(100.f, 100.f);
    pMonster->SetOffset(10.f, 30.f);
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

    CRock* pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_0");
    pRock1->SetPos(1000.f, 400.f);
    pRock1->SetOffset(0.f, 10.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_1");
    pRock1->SetPos(1200.f, 400.f);
    pRock1->SetOffset(0.f, 10.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_2");
    pRock1->SetPos(1100.f, 400.f);
    pRock1->SetOffset(0.f, 10.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_3");
    pRock1->SetPos(1100.f, 500.f);
    pRock1->SetOffset(0.f, 10.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_4");
    pRock1->SetPos(800.f, 500.f);
    pRock1->SetOffset(0.f, 10.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    CThorn* pThorn = new CThorn;
    pThorn->SetThorn(THORN_DOWN);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(1000.f, 700.f);
    pThorn->SetOffset(0, 10.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_UP);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(1000.f, 800.f);
    pThorn->SetOffset(-5, 20.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_DOWN);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(900.f, 800.f);
    pThorn->SetOffset(-5, 20.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_UP);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(800.f, 800.f);
    pThorn->SetOffset(-5, 20.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_DOWN);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(700.f, 800.f);
    pThorn->SetOffset(-5, 20.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_UP);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(700.f, 700.f);
    pThorn->SetOffset(-5, 20.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

}

void CLevelSeven::Begin()
{
    //Add Object Reset할 오브젝트 추가
    Init();

    CWall* pWall = new CWall;
    pWall->SetPos(1300.f, 400.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1300.f, 500.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1300.f, 600.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1300.f, 700.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1200.f, 700.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1100.f, 700.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1100.f, 800.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1100.f, 900.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1000.f, 900.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(900.f, 900.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(800.f, 900.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(700.f, 900.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(600.f, 900.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(600.f, 800.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(600.f, 700.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(600.f, 600.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(600.f, 500.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(600.f, 400.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(600.f, 300.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(700.f, 300.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(800.f, 300.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(900.f, 300.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);


    pWall = new CWall;
    pWall->SetPos(900.f, 200.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);


    pWall = new CWall;
    pWall->SetPos(900.f, 100.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);


    pWall = new CWall;
    pWall->SetPos(1000.f, 100.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1100.f, 100.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1200.f, 100.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1200.f, 200.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1300.f, 200.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1300.f, 300.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(800.f, 600.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(900.f, 700.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(900.f, 400.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(800.f, 700.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);


    CDemon* pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(JUSTICE);
    pDemon->SetPos(1000.f, 200.f);
    pDemon->SetScale(100.f, 100.f);
    AddObject(pDemon, LAYER_TYPE::DEMON);

    //Player 생성
    CPlayer* pObject = new CPlayer;
    pObject->SetName(L"Player");
    pObject->SetPos(1200.f, 600.f);
    pObject->SetStartPos(1200.f, 600.f);
    pObject->SetScale(100.f, 100.f);
    pObject->SetInitDir(0);
    pObject->SetPlayerMoveCount(32);
    pObject->SetOffset(0.f, 30.f);
    pObject->CurLevel = STAGE_6;
    AddObject(pObject, LAYER_TYPE::PLAYER);

    pObject->NewTalkCutScene[0].push_back({
        CUTSCENE_TYPE::TALK_CUTSCENE,
        DEMON_TYPE::JUSTICE,
        L"dialogueBG_hell",
        L"jus_curious",
        L"오, 방금 그 퍼즐을 푼거야? 대단한데?",
        L"",
 L"",
 L"",
 0,
 1,
 0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::CHOICE_CUTSCENE,
DEMON_TYPE::JUSTICE,
L"dialogueBG_hell",
        L"jus_curious",
        L"오, 방금 그 퍼즐을 푼거야? 대단한데?",
        L"",
        L"푸는데 힘 좀 썼지. 같이 하렘에 낄 생각 있나?",
        L"그냥 공략 보면서 왔지. 같이 하렘에 낄 생각 있나?",

2,
2,
3
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::SUCESS_CUTSCENE,
DEMON_TYPE::JUSTICE,
L"dialogueBG_hell",
        L"jus_idle",
        L"굳이 안물어봐도 되는데 말야. 파티라면 빠지는 법이 없거든.",
        L"",
L"",
L"",
0,
1,
0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::SUCESS_CUTSCENE,
DEMON_TYPE::JUSTICE,
L"dialogueBG_hell",
        L"jus_idle",
        L"나라도 충분히 그랬을 것 같네.",
        L"빠른게 좋은거 아니겠어?",
L"",
L"",
0,
1,
0
});

 /*   pObject->TalkCutScene[0].push_back({
        CUTSCENE_TYPE::TALK_CUTSCENE,
        DEMON_TYPE::JUSTICE,
        L"dialogueBG_hell",
        L"jus_curious",
        L"오, 방금 그 퍼즐을 푼거야? 대단한데?",
        L"",
        1,
        });

    pObject->TalkCutScene[0].push_back({
        CUTSCENE_TYPE::CHOICE_CUTSCENE,
        DEMON_TYPE::JUSTICE,
        L"dialogueBG_hell",
        L"jus_curious",
        L"푸는데 힘 좀 썼지. 같이 하렘에 낄 생각 있나?",
        L"그냥 공략 보면서 왔지. 같이 하렘에 낄 생각 있나?",
        1,
        });

    pObject->TalkCutScene[0].push_back({
        CUTSCENE_TYPE::SUCESS_CUTSCENE,
        DEMON_TYPE::JUSTICE,
        L"dialogueBG_hell",
        L"jus_idle",
        L"굳이 안물어봐도 되는데 말야. 파티라면 빠지는 법이 없거든.",
        L"",
        1,
        });

    pObject->TalkCutScene[0].push_back({
        CUTSCENE_TYPE::DIE_CUTSCENE,
        DEMON_TYPE::JUSTICE,
        L"dialogueBG_hell",
        L"jus_idle",
        L"나라도 충분히 그랬을 것 같네.",
        L"빠른게 좋은거 아니겠어?",
        1,
        });*/

    pObject->diemessage = L"시야가 흐릿해지기 시작하더니, 갈비뼈 사이로 칼 한자루가";
    pObject->diemessage2 = L"깊게 박힌 것을 보고 눈 앞이 깜깜해졌습니다.";

    CBackground* pBackground = new CBackground;
    pBackground->SetPos(0.f, 0.f);
    pBackground->SetBackgroundMap(L"chapterBG_7");
    AddObject(pBackground, LAYER_TYPE::BACKGROUND);

    //TileMap Object 추가
    //CMap* pTileMap = new CMap;
    //pTileMap->SetPos(Vec2(50.f, 50.f));
    //wstring FilePath = CPathMgr::GetContentPath();
    //pTileMap->GetTileMap()->LoadTileMap(FilePath + L"TileMap\\Temp.tile");
    //AddObject(pTileMap, LAYER_TYPE::TILE);

    CFireBase* pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(1315.f, 270.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    CFire* pFire = new CFire;
    pFire->SetPos(Vec2(1315.f, 270.f));
    pFire->SetOffset(7.f, -100.f);
    AddObject(pFire, LAYER_TYPE::FIRE);

    pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(1210.f, 215.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(1);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(595.f, 715.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    pFire = new CFire;
    pFire->SetPos(Vec2(595.f, 715.f));
    pFire->SetOffset(7.f, -100.f);
    AddObject(pFire, LAYER_TYPE::FIRE);



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

void CLevelSeven::Render()
{
    CLevel::Render();
}

void CLevelSeven::End()
{
    DeleteAllObject();
}


