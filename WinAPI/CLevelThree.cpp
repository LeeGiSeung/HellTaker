#include "pch.h"
#include "CLevelThree.h"

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

CLevelThree::CLevelThree()
{
}

CLevelThree::~CLevelThree()
{

}

void CLevelThree::Init()
{
    CKey* pKey = new CKey;
    pKey->SetPos(650.f, 750.f);
    pKey->SetScale(100.f, 100.f);
    AddObject(pKey, LAYER_TYPE::KEY);

    CKeybox* pKeybox = new CKeybox;
    pKeybox->SetPos(1250.f, 350.f);
    pKeybox->SetScale(100.f, 100.f);
    AddObject(pKeybox, LAYER_TYPE::KEYBOX);

    // Monster 생성
    CMonster* pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(1150.f, 850.f);
    pMonster->SetScale(100.f, 100.f);
    pMonster->SetOffset(0.f, 30.f);
    pMonster->SetDistance(200.f);
    pMonster->SetSpeed(300.f);
    pMonster->SetSound(1);
    AddObject(pMonster, LAYER_TYPE::MONSTER);

    CMonster* pMonster3 = new CMonster;
    pMonster3->SetName(L"Monster");
    pMonster3->SetPos(1050.f, 650.f);
    pMonster3->SetScale(100.f, 100.f);
    pMonster3->SetDistance(200.f);
    pMonster3->SetOffset(0.f, 30.f);
    pMonster3->SetSpeed(300.f);
    pMonster3->SetSound(3);
    AddObject(pMonster3, LAYER_TYPE::MONSTER);

    /*CRock* pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_0");
    pRock1->SetPos(1150.f, 450.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    CRock* pRock2 = new CRock;
    pRock2->SetName(L"Rock");
    pRock2->SetRock(L"boxExport_1");
    pRock2->SetPos(1050.f, 450.f);
    pRock2->SetScale(100.f, 100.f);
    AddObject(pRock2, LAYER_TYPE::Rock);

    CRock* pRock4 = new CRock;
    pRock4->SetRock(L"boxExport_3");
    pRock4->SetName(L"Rock");
    pRock4->SetPos(1250.f, 450.f);
    pRock4->SetScale(100.f, 100.f);
    AddObject(pRock4, LAYER_TYPE::Rock);*/

    CThorn* pThorn = new CThorn;
    pThorn->SetThorn(THORN_UP);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(1050.f, 450.f);
    pThorn->SetOffset(-10.f, 5.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_UP);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(950.f, 450.f);
    pThorn->SetOffset(-10.f, 5.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_UP);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(1050.f, 550.f);
    pThorn->SetOffset(-10.f, 5.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_UP);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(850.f, 550.f);
    pThorn->SetOffset(-10.f, 5.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_UP);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(1150.f, 650.f);
    pThorn->SetOffset(-10.f, 5.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_UP);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(1250.f, 650.f);
    pThorn->SetOffset(-10.f, 5.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_UP);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(1050.f, 750.f);
    pThorn->SetOffset(-10.f, 5.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_UP);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(850.f, 750.f);
    pThorn->SetOffset(-10.f, 5.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);
}

void CLevelThree::Begin()
{
    //Add Object Reset할 오브젝트 추가
    Init();

    CDemon* pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(CERBERUS);
    pDemon->SetPos(1150.f, 250.f);
    pDemon->SetScale(100.f, 100.f);
    AddObject(pDemon, LAYER_TYPE::DEMON);

    pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(CERBERUS);
    pDemon->SetPos(1050.f, 250.f);
    pDemon->SetScale(100.f, 100.f);
    AddObject(pDemon, LAYER_TYPE::DEMON);

    pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(CERBERUS);
    pDemon->SetPos(950.f, 250.f);
    pDemon->SetScale(100.f, 100.f);
    AddObject(pDemon, LAYER_TYPE::DEMON);

    //Player 생성
    CPlayer* pObject = new CPlayer;
    pObject->SetName(L"Player");
    pObject->SetPos(1350.f, 450.f);
    pObject->SetStartPos(1350.f, 450.f);
    pObject->SetScale(100.f, 100.f);
    pObject->SetOffset(0.f, 30.f);
    pObject->SetInitDir(0);
    pObject->SetPlayerMoveCount(32);
    pObject->CurLevel = STAGE_2;
    AddObject(pObject, LAYER_TYPE::PLAYER);

    pObject->NewTalkCutScene[0].push_back({
    CUTSCENE_TYPE::TALK_CUTSCENE,
    DEMON_TYPE::CERBERUS,
    L"dialogueBG_hell",
    L"cer_idle",
    L"인간이야? 진짜 인간? 제발 같이 데려가줘. 응?",
    L"",
    L"",
    L"",
    0,
    1,
    0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::CHOICE_CUTSCENE,
DEMON_TYPE::CERBERUS,
L"dialogueBG_hell",
L"cer_idle",
    L"인간이야? 진짜 인간? 제발 같이 데려가줘. 응?",
    L"",
L"좋아. 물어볼 필요도 없지.",
L"잠깐, 일이 너무 쉽게 흘러가는데. 좀 물어봐야겠어.",
1,
2,
3
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::SUCESS_CUTSCENE,
DEMON_TYPE::CERBERUS,
L"dialogueBG_hell",
L"cer_happy",
L"좋아! 드디어! 필멸자들의 세계를 타락시키자!",
L"",
L"",
L"",
0,
1,
0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::DIE_CUTSCENE,
DEMON_TYPE::CERBERUS,
L"dialogueBG_hell",
L"cer_idle",
L"지옥문을 건너려면 인간이 필요해서 그래.",
L"어차피 한 몸일 필요도 없잖아?",
L"",
L"",
0,
1,
0
});
    //pObject->TalkCutScene[0].push_back({
    //    CUTSCENE_TYPE::TALK_CUTSCENE,
    //    DEMON_TYPE::CERBERUS,
    //    L"dialogueBG_hell",
    //    L"cer_idle",
    //    L"인간이야? 진짜 인간? 제발 같이 데려가줘. 응?",
    //    L"",
    //    1,
    //    });

    //pObject->TalkCutScene[0].push_back({
    //    CUTSCENE_TYPE::CHOICE_CUTSCENE,
    //    DEMON_TYPE::CERBERUS,
    //    L"dialogueBG_hell",
    //    L"cer_idle",
    //    L"좋아. 물어볼 필요도 없지.",
    //    L"잠깐, 일이 너무 쉽게 흘러가는데. 좀 물어봐야겠어.",
    //    1,
    //    });

    //pObject->TalkCutScene[0].push_back({
    //    CUTSCENE_TYPE::SUCESS_CUTSCENE,
    //    DEMON_TYPE::CERBERUS,
    //    L"dialogueBG_hell",
    //    L"cer_happy",
    //    L"좋아! 드디어! 필멸자들의 세계를 타락시키자!",
    //    L"",
    //    1,
    //    });

    //pObject->TalkCutScene[0].push_back({
    //    CUTSCENE_TYPE::DIE_CUTSCENE,
    //    DEMON_TYPE::CERBERUS,
    //    L"dialogueBG_hell",
    //    L"cer_idle",
    //    L"지옥문을 건너려면 인간이 필요해서 그래.",
    //    L"어차피 한 몸일 필요도 없잖아?",
    //    1,
    //    });

    pObject->diemessage = L"그녀들은 송곳니 소리와 함께 개처럼 날뛰기 시작했습니다. 마치 귀여운 개처럼";
    pObject->diemessage2 = L"다같이 달려들어 당신에게 심장마비를 선사해주었네요.";

    CBackground* pBackground = new CBackground;
    pBackground->SetPos(40.f,40.f);
    pBackground->SetBackgroundMap(L"chapterBG_3");
    AddObject(pBackground, LAYER_TYPE::BACKGROUND);

    //TileMap Object 추가
    //CMap* pTileMap = new CMap;
    //pTileMap->SetPos(Vec2(0.f, 0.f));
    //wstring FilePath = CPathMgr::GetContentPath();
    //pTileMap->GetTileMap()->LoadTileMap(FilePath + L"TileMap\\Temp.tile");
    //AddObject(pTileMap, LAYER_TYPE::TILE);

    CFireBase* pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(1350.f, 350.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    CFire* pFire = new CFire;
    pFire->SetPos(Vec2(1350.f, 350.f));
    pFire->SetOffset(7.f, -100.f);
    AddObject(pFire, LAYER_TYPE::FIRE);

    pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(745.f, 650.f));
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    pFire = new CFire;
    pFire->SetPos(Vec2(745.f, 650.f));
    pFire->SetOffset(3.f, -40.f);
    AddObject(pFire, LAYER_TYPE::FIRE);

    CCountUI* CUI = new CCountUI;
    CUI->SetCountUI(COUNT_UI_LEFT);
    AddObject(CUI, LAYER_TYPE::COUNTUI);

    CUI = new CCountUI;
    CUI->SetCountUI(COUNT_UI_RIGHT);
    AddObject(CUI, LAYER_TYPE::COUNTUI);

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

    pWall = new CWall;
    pWall->SetPos(1350.f, 150.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(200.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f,750.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(200.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(650.f, 650.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(200.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(200.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(750.f, 750.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(200.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(200.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1150.f, 350.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(200.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1150.f, 550.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(200.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1150.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(200.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1050.f, 150.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(200.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(850.f, 150.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(950.f, 150.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(750.f, 150.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f, 450.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 200.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(650.f, 350.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 200.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(850.f, 350.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 200.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1050.f, 350.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 200.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(850.f, 250.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 200.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(650.f, 250.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 200.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f, 650.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f, 550.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 300.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 300.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(650.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(750.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(850.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(950.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1050.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1150.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1250.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 350.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1450.f, 450.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 250.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1450.f, 550.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 650.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(750.f, 450.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(950.f, 350.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 700.f);
    pWall->SetScale(100.f, 200.f);
    pWall->SetWallSize(100.f, 200.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(750.f, 650.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(950.f, 550.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(950.f, 750.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1150.f, 750.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(750.f, 550.f);
    pWall->SetScale(100.f, 100.f);
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

void CLevelThree::Render()
{
    CLevel::Render();
}

void CLevelThree::End()
{
    DeleteAllObject();
}

