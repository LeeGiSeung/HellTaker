#include "pch.h"
#include "CLevelTwo.h"

#include "CEngine.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CMissile.h"
#include "CPlatform.h"
#include "CMap.h"

#include "CCollisionMgr.h"
#include "CCollider.h"

#include "CTileMap.h"
#include "CPathMgr.h"
#include "CCamera.h"
#include "CBackground.h"
#include "CRock.h"
#include "CDemon.h"
#include "CKey.h"

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

CLevelTwo::CLevelTwo()
{
}

CLevelTwo::~CLevelTwo()
{
}

void CLevelTwo::Begin()
{

    //Add Object Reset할 오브젝트 추가
    Init();

    //Player 생성
    CPlayer* pObject = new CPlayer;
    pObject->SetName(L"Player");
    pObject->SetPos(650.f, 650.f);
    pObject->SetStartPos(650.f, 650.f);
    pObject->SetScale(100.f, 100.f);
    pObject->SetOffset(0.f, 30.f);
    pObject->SetInitDir(1);
    pObject->SetPlayerMoveCount(24);
    pObject->CurLevel = STAGE_1;
    AddObject(pObject, LAYER_TYPE::PLAYER);

    //struct CUTSCENE_DATA_NEW {
//    CUTSCENE_TYPE CutsceneType;
//    DEMON_TYPE DemonType;
//    wchar_t BackgroundTexture[100] = {};
//    wchar_t CharacterTexture[100] = {};
//    wchar_t DemonFirstText[100] = {};
//    wchar_t DemonSecondText[100] = {};
//    wchar_t HeroFirstText[100] = {};
//    wchar_t HeroSecondText[100] = {};
//    int DeathChoice;
//    int nextIndex;
//    int nextDeathIndex;
//};

    pObject->NewTalkCutScene[0].push_back({
        CUTSCENE_TYPE::TALK_CUTSCENE,
        DEMON_TYPE::MODEUS,
        L"dialogueBG_hell",
        L"mod_idle",
        L"너랑 나랑, 지금 당장 하자.",
        L"",
        L"",
        L"",
        0,
        1,
        0
        });

    pObject->NewTalkCutScene[0].push_back({
    CUTSCENE_TYPE::CHOICE_CUTSCENE,
    DEMON_TYPE::MODEUS,
    L"dialogueBG_hell",
    L"mod_idle",
    L"너랑 나랑, 지금 당장 하자.",
    L"",
    L"좋아. 물어볼 필요도 없지.",
    L"그럴 시간 없어. 여자들 모으느라 바빠",
    0,
    2,
    3
        });

    pObject->NewTalkCutScene[0].push_back({
    CUTSCENE_TYPE::SUCESS_CUTSCENE,
    DEMON_TYPE::MODEUS,
    L"dialogueBG_hell",
    L"mod_close",
    L"악마 하렘? 가여워라... 다들 네 영혼을 찢으려 들텐데, 이건 '꼭'",
    L"봐야겠다.",
    L"",
    L"",
    0,
    1,
    0
        });

    pObject->NewTalkCutScene[0].push_back({
    CUTSCENE_TYPE::DIE_CUTSCENE,
    DEMON_TYPE::MODEUS,
    L"dialogueBG_hell",
    L"mod_idle",
    L"다들 처음엔 그러더라... 그리고 결국 도망가려 하던데.",
    L"혹시 모르니, 다리를 부러뜨려 놔야겠다.",
    L"",
    L"",
    0,
    1,
    0
        });

    pObject->TalkCutScene[0].push_back({
        CUTSCENE_TYPE::TALK_CUTSCENE,
        DEMON_TYPE::MODEUS,
        L"dialogueBG_hell",
        L"mod_idle",
        L"너랑 나랑, 지금 당장 하자.",
        L"",
        1,
        });

    pObject->TalkCutScene[0].push_back({
        CUTSCENE_TYPE::CHOICE_CUTSCENE,
        DEMON_TYPE::MODEUS,
        L"dialogueBG_hell",
        L"mod_idle",
        L"좋아. 물어볼 필요도 없지.",
        L"그럴 시간 없어. 여자들 모으느라 바빠.",
        0,
        });

    pObject->TalkCutScene[0].push_back({
        CUTSCENE_TYPE::SUCESS_CUTSCENE,
        DEMON_TYPE::MODEUS,
        L"dialogueBG_hell",
        L"mod_close",
        L"악마 하렘? 가여워라... 다들 네 영혼을 찢으려 들텐데, 이건 '꼭'",
        L"봐야겠다.",
        1,
        });

    pObject->TalkCutScene[0].push_back({
        CUTSCENE_TYPE::DIE_CUTSCENE,
        DEMON_TYPE::MODEUS,
        L"dialogueBG_hell",
        L"mod_idle",
        L"다들 처음엔 그러더라... 그리고 결국 도망가려 하던데.",
        L"혹시 모르니, 다리를 부려뜨려 놔야겠다.",
        1,
        });

    pObject->diemessage = L"그녀는 쇠망치를 꺼내 들었습니다. 보기 좋게 끝날 것 같지는";
    pObject->diemessage2 = L"않네요.";

    CBackground* pBackground = new CBackground;
    pBackground->SetBackgroundMap(L"chapterBG_2");
    AddObject(pBackground, LAYER_TYPE::BACKGROUND);

    //TileMap Object 추가
    //CMap* pTileMap = new CMap;
    //pTileMap->SetPos(Vec2(0.f, 0.f));
    //wstring FilePath = CPathMgr::GetContentPath();
    //pTileMap->GetTileMap()->LoadTileMap(FilePath + L"TileMap\\Temp.tile");
    //AddObject(pTileMap, LAYER_TYPE::TILE);

    CFireBase* pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(1160.f, 210.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(1);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(650.f, 270.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    CFire* pFire = new CFire;
    pFire->SetPos(Vec2(650.f, 270.f));
    pFire->SetOffset(7.f, -100.f);
    AddObject(pFire, LAYER_TYPE::FIRE);

    pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(1365.f, 610.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    pFire = new CFire;
    pFire->SetPos(Vec2(1365.f, 610.f));
    pFire->SetOffset(7.f, -100.f);
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
    pWall->SetPos(1250.f, 250.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(200.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(850.f, 350.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(200.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1150.f, 250.f);
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
    pWall->SetPos(550.f, 750.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f, 650.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 300.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f, 650.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 300.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f, 550.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(650.f, 750.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(750.f, 750.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(850.f, 750.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(950.f, 750.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1050.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1150.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1250.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);


    pWall = new CWall;
    pWall->SetPos(1350.f, 350.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 450.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 250.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 550.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 650.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(850.f, 450.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(950.f, 450.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 700.f);
    pWall->SetScale(100.f, 200.f);
    pWall->SetWallSize(100.f, 200.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(950.f, 550.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(950.f, 650.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(850.f, 650.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(850.f, 550.f);
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

void CLevelTwo::Render()
{
    CLevel::Render();
}

void CLevelTwo::End()
{
    DeleteAllObject();
}

void CLevelTwo::Init()
{
    // 화면 해상도 
    //CKey* pKey = new CKey;
    //pKey->SetName(L"Key");
    //pKey->SetPos(1050.f, 250.f);
    //pKey->SetScale(100.f, 100.f);
    //AddObject(pKey, LAYER_TYPE::KEY);

    //CKeybox* pKeyBox = new CKeybox;
    //pKeyBox->SetName(L"KeyBox");
    //pKeyBox->SetPos(650.f, 650.f);
    //pKeyBox->SetScale(100.f, 100.f);
    //AddObject(pKeyBox, LAYER_TYPE::KEYBOX);

    // Monster 생성
    CMonster* pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(750.f, 350.f);
    pMonster->SetScale(100.f, 100.f);
    pMonster->SetDistance(200.f);
    pMonster->SetOffset(0.f, 30.f);
    pMonster->SetSpeed(300.f);
    pMonster->SetSound(1);
    AddObject(pMonster, LAYER_TYPE::MONSTER);

    CMonster* pMonster2 = new CMonster;
    pMonster2->SetName(L"Monster");
    pMonster2->SetPos(1250.f, 750.f);
    pMonster2->SetScale(100.f, 100.f);
    pMonster2->SetDistance(200.f);
    pMonster2->SetOffset(0.f, 30.f);
    pMonster2->SetSpeed(300.f);
    pMonster2->SetSound(2);
    AddObject(pMonster2, LAYER_TYPE::MONSTER);

    CMonster* pMonster3 = new CMonster;
    pMonster3->SetName(L"Monster");
    pMonster3->SetPos(1150.f, 650.f);
    pMonster3->SetScale(100.f, 100.f);
    pMonster3->SetDistance(200.f);
    pMonster3->SetOffset(0.f, 30.f);
    pMonster3->SetSpeed(300.f);
    pMonster3->SetSound(3);
    AddObject(pMonster3, LAYER_TYPE::MONSTER);

    CRock* pRock1 = new CRock;
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
    AddObject(pRock4, LAYER_TYPE::Rock);

    CThorn* pThorn = new CThorn;
    pThorn->SetThorn(THORN_UP);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(1050.f, 450.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_UP);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(1150.f, 450.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_UP);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(1150.f, 550.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_UP);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(1050.f, 350.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_UP);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(950.f, 350.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_UP);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(750.f, 450.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    CDemon* pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(MODEUS);
    pDemon->SetPos(1050.f, 750.f);
    pDemon->SetScale(100.f, 100.f);
    AddObject(pDemon, LAYER_TYPE::DEMON);

    //CDemon* pDemon1 = new CDemon;
    //pDemon1->SetName(L"Demon1");
    //pDemon1->SetDemon(AZAZEL_IDLE);
    //pDemon1->SetPos(1150.f, 750.f);
    //pDemon1->SetScale(100.f, 100.f);
    //AddObject(pDemon1, LAYER_TYPE::DEMON);
}

