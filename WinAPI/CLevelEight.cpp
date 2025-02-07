#include "pch.h"
#include "CLevelEight.h"

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

CLevelEight::CLevelEight()
{
}

CLevelEight::~CLevelEight()
{
}

void CLevelEight::Init()
{

    // Monster 생성
    CMonster* pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(950.f, 1550.f);
    pMonster->SetScale(100.f, 100.f);
    pMonster->SetOffset(0.f, 10.f);
    pMonster->SetDistance(200.f);
    pMonster->SetSpeed(300.f);
    pMonster->SetSound(1);
    AddObject(pMonster, LAYER_TYPE::MONSTER);

    pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(950.f, 1450.f);
    pMonster->SetScale(100.f, 100.f);
    pMonster->SetDistance(200.f);
    pMonster->SetOffset(0.f, 10.f);
    pMonster->SetSpeed(300.f);
    pMonster->SetSound(1);
    AddObject(pMonster, LAYER_TYPE::MONSTER);

    pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(950.f, 1350.f);
    pMonster->SetScale(100.f, 100.f);
    pMonster->SetDistance(200.f);
    pMonster->SetOffset(0.f, 10.f);
    pMonster->SetSpeed(300.f);
    pMonster->SetSound(1);
    AddObject(pMonster, LAYER_TYPE::MONSTER);

    pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(950.f, 1250.f);
    pMonster->SetScale(100.f, 100.f);
    pMonster->SetDistance(200.f);
    pMonster->SetOffset(0.f, 10.f);
    pMonster->SetSpeed(300.f);
    pMonster->SetSound(1);
    AddObject(pMonster, LAYER_TYPE::MONSTER);

    pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(950.f, 1150.f);
    pMonster->SetScale(100.f, 100.f);
    pMonster->SetDistance(200.f);
    pMonster->SetOffset(0.f, 10.f);
    pMonster->SetSpeed(300.f);
    pMonster->SetSound(1);
    AddObject(pMonster, LAYER_TYPE::MONSTER);

    pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(950.f, 1050.f);
    pMonster->SetScale(100.f, 100.f);
    pMonster->SetDistance(200.f);
    pMonster->SetOffset(0.f, 10.f);
    pMonster->SetSpeed(300.f);
    pMonster->SetSound(1);
    AddObject(pMonster, LAYER_TYPE::MONSTER);

    pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(950.f, 950.f);
    pMonster->SetScale(100.f, 100.f);
    pMonster->SetDistance(200.f);
    pMonster->SetOffset(0.f, 10.f);
    pMonster->SetSpeed(300.f);
    pMonster->SetSound(1);
    AddObject(pMonster, LAYER_TYPE::MONSTER);

    pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(950.f, 850.f);
    pMonster->SetScale(100.f, 100.f);
    pMonster->SetDistance(200.f);
    pMonster->SetOffset(0.f, 10.f);
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

 
}

void CLevelEight::Begin()
{
    //Add Object Reset할 오브젝트 추가
    Init();

    CWall* pWall = new CWall;
    pWall->SetPos(950.f, 750.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1050.f, 750.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1150.f, 750.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1150.f, 650.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(850.f, 750.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(750.f, 750.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(750.f, 650.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    CDemon* pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(LUCY);
    pDemon->SetPos(950.f, 650.f);
    pDemon->SetOffset(0.f, -30.f);
    pDemon->SetScale(100.f, 100.f);
    AddObject(pDemon, LAYER_TYPE::DEMON);

    //Player 생성
    CPlayer* pObject = new CPlayer;
    pObject->SetName(L"Player");
    pObject->SetPos(950.f, 1650.f);
    pObject->SetStartPos(950.f, 1650.f);
    pObject->SetScale(100.f, 100.f);
    pObject->SetOffset(0.f, 10.f);
    pObject->SetInitDir(0);
    pObject->SetPlayerMoveCount(12);
    pObject->CurLevel = STAGE_7;
    AddObject(pObject, LAYER_TYPE::PLAYER);

    pObject->NewTalkCutScene[0].push_back({
    CUTSCENE_TYPE::TALK_CUTSCENE,
        DEMON_TYPE::LUCY,
        L"dialogueBG_throne2",
        L"LH_idle",
        L"드디어 만나네. 내가 준비한 시험을 통과했으니 그 만한",
    L"자격은 있어 보여",
L"",
L"",
0,
1,
0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
    DEMON_TYPE::LUCY,
    L"dialogueBG_throne2",
    L"LH_idle",
    L"내게 영혼을 바치면 내가 가장 아끼는 노예로 써주마",
L"",
L"",
L"",
0,
2,
0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::CHOICE_CUTSCENE,
        DEMON_TYPE::LUCY,
        L"dialogueBG_throne2",
        L"LH_idle",
        L"내게 영혼을 바치면 내가 가장 아끼는 노예로 써주마",
        L"",
        L"예, 여왕 폐하!",
        L"사양하겠어. 대신 내 하렘에 들어와라",

0,
3,
7
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_throne2",
        L"LH_angry",
        L"도대체 뭘 하려는 거지? 악마들을 네가 원하는 대로 다룰 수",
        L"있을거라 생각하는 거냐?",
L"",
L"",
0,
4,
0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::CHOICE_CUTSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_throne2",
        L"LH_angry",
        L"도대체 뭘 하려는 거지? 악마들을 네가 원하는 대로 다룰 수",
        L"있을거라 생각하는 거냐?",
L"나를 주인님이라 불러라. 그리고 입을 열기전에 허락부터 받도록",
L"커피, 턴제 전략 게임 그리고 초콜릿 팬케이크 정도는 줄 수 있지.",
0,
5,
8
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_throne2",
        L"LH_angry",
        L"진짜로? 그게 다야? 여기까지 와서 고작 팬케이크로 내 마음을",
        L"사겠다고?",
L"",
L"",
0,
6,
0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::SUCESS_CUTSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_throne2",
        L"LH_happy",
        L"내가 팬케이크를 좋아하는걸 다행으로 여겨라.",
        L"",
L"",
L"",
0,
0,
0
        });

    pObject->NewTalkCutScene[0].push_back({
        CUTSCENE_TYPE::DIE_CUTSCENE,
        DEMON_TYPE::LUCY,
        L"dialogueBG_throne2",
        L"LH_idle",
        L"탐욕에 빠진 작은 영혼 같으니...",
        L"",
L"",
L"",
0,
1,
0
        });


    pObject->NewTalkCutScene[0].push_back({
    CUTSCENE_TYPE::DIE_CUTSCENE,
    DEMON_TYPE::LUCY,
    L"dialogueBG_throne2",
    L"LH_idle",
    L"이런.. 자기 분수에 맞는 교육이 필요한 것 같네.",
    L"",
L"",
L"",
0,
1,
0
        });
    //pObject->TalkCutScene[0].push_back({
    //    CUTSCENE_TYPE::TALK_CUTSCENE,
    //    DEMON_TYPE::LUCY,
    //    L"dialogueBG_throne2",
    //    L"LH_idle",
    //    L"내게 영혼을 바치면 내가 가장 아끼는 노예로 써주마",
    //    L"",
    //    1,
    //    });

    //pObject->TalkCutScene[0].push_back({
    //    CUTSCENE_TYPE::CHOICE_CUTSCENE,
    //    DEMON_TYPE::LUCY,
    //    L"dialogueBG_throne2",
    //    L"LH_idle",
    //    L"예, 여왕 폐하!",
    //    L"사양하겠어. 대신 내 하렘에 들어와라",
    //    0,
    //    });

    //pObject->TalkCutScene[0].push_back({
    //    CUTSCENE_TYPE::SUCESS_CUTSCENE,
    //    DEMON_TYPE::LUCY,
    //    L"dialogueBG_throne2",
    //    L"LH_happy",
    //    L"내가 팬케이크를 좋아하는걸 다행으로 여겨라",
    //    L"",
    //    1,
    //    });

    //pObject->TalkCutScene[0].push_back({
    //    CUTSCENE_TYPE::DIE_CUTSCENE,
    //    DEMON_TYPE::LUCY,
    //    L"dialogueBG_throne2",
    //    L"LH_idle",
    //    L"탐욕에 빠진 작은 영혼 같으니...",
    //    L"",
    //    1,
    //    });

    pObject->diemessage = L"무릎을 꿇자마자 그녀가 당신의 이마에 입맞춤을 합니다.";
    pObject->diemessage2 = L"입술이 닿자마자 당신의 삶은 녹아내려 사라집니다.";

    CBackground* pBackground = new CBackground;
    pBackground->SetPos(0.f, 0.f);
    pBackground->SetBackgroundMap(L"chapterBG_9");
    AddObject(pBackground, LAYER_TYPE::BACKGROUND);

    //TileMap Object 추가
    //CMap* pTileMap = new CMap;
    //pTileMap->SetPos(Vec2(0.f, 0.f));
    //wstring FilePath = CPathMgr::GetContentPath();
    //pTileMap->GetTileMap()->LoadTileMap(FilePath + L"TileMap\\TempEight.tile");
    //AddObject(pTileMap, LAYER_TYPE::TILE);

    CFireBase* pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(755.f, 1660.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    CFire* pFire = new CFire;
    pFire->SetPos(Vec2(755.f, 1660.f));
    pFire->SetOffset(7.f, -100.f);
    AddObject(pFire, LAYER_TYPE::FIRE);

    pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(1155.f, 1660.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    pFire = new CFire;
    pFire->SetPos(Vec2(1155.f, 1660.f));
    pFire->SetOffset(7.f, -100.f);
    AddObject(pFire, LAYER_TYPE::FIRE);

    pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(755.f, 1460.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    pFire = new CFire;
    pFire->SetPos(Vec2(755.f, 1460.f));
    pFire->SetOffset(7.f, -100.f);
    AddObject(pFire, LAYER_TYPE::FIRE);

    pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(755.f, 1260.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    pFire = new CFire;
    pFire->SetPos(Vec2(755.f, 1260.f));
    pFire->SetOffset(7.f, -100.f);
    AddObject(pFire, LAYER_TYPE::FIRE);

    pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(755.f, 1060.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    pFire = new CFire;
    pFire->SetPos(Vec2(755.f, 1060.f));
    pFire->SetOffset(7.f, -100.f);
    AddObject(pFire, LAYER_TYPE::FIRE);

    pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(1155.f, 1460.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    pFire = new CFire;
    pFire->SetPos(Vec2(1155.f, 1460.f));
    pFire->SetOffset(7.f, -100.f);
    AddObject(pFire, LAYER_TYPE::FIRE);

    pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(1155.f, 1260.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    pFire = new CFire;
    pFire->SetPos(Vec2(1155.f, 1260.f));
    pFire->SetOffset(7.f, -100.f);
    AddObject(pFire, LAYER_TYPE::FIRE);

    pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(1155.f, 1060.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    pFire = new CFire;
    pFire->SetPos(Vec2(1155.f, 1060.f));
    pFire->SetOffset(7.f, -100.f);
    AddObject(pFire, LAYER_TYPE::FIRE);

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

void CLevelEight::Render()
{
    CLevel::Render();
}

void CLevelEight::End()
{
    DeleteAllObject();
}
