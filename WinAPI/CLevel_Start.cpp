#include "pch.h"
#include "CLevel_Start.h"

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

CLevel_Start::CLevel_Start()
{
    CLevel::stage = LEVEL_CHECK::STAGE_0;
}

CLevel_Start::~CLevel_Start()
{

}

void CLevel_Start::Begin()
{
    
    //Add Object Reset할 오브젝트 추가
    Init();

    //Player 생성
    CPlayer* pObject = new CPlayer;
    pObject->SetName(L"Player");
    pObject->SetPos(1150.f, 250.f);
    pObject->SetStartPos(1150.f, 250.f);
    pObject->SetScale(100.f, 100.f);
    pObject->SetInitDir(0);
    pObject->SetPlayerMoveCount(23);
    pObject->CurLevel = STAGE_0;
    pObject->SetOffset(0.f, 30.f);
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
        DEMON_TYPE::PANDEMONICA,
        L"dialogueBG_hell",
        L"pand_idle",
        L"지옥 고객 서비스 센터의 판데모니카입니다.",
        L"무엇을 도와드릴까요?",
        L"",
        L"",
        0,
        1,
        0
     });

    pObject->NewTalkCutScene[0].push_back({
        CUTSCENE_TYPE::CHOICE_CUTSCENE,
        DEMON_TYPE::PANDEMONICA,
        L"dialogueBG_hell",
        L"pand_idle",
        L"지옥 고객 서비스 센터의 판데모니카입니다.",
        L"무엇을 도와드릴까요?",
        L"우리 집에 한번 오면 알게 될거야.",
        L"오히려 '그 쪽'을 도와줘야 할 판인데?",
        0,
        2,
        3
    });

    pObject->NewTalkCutScene[0].push_back({
        CUTSCENE_TYPE::SUCESS_CUTSCENE,
        DEMON_TYPE::PANDEMONICA,
        L"dialogueBG_hell",
        L"pand_flust",
        L"그래주면 좋겠네요. 지금 커피 한잔이 너무 마시고 싶은데.",
        L"지금 제정신이 아니에요.",
        L"",
        L"",
        0,
        0,
        0    
    });

    pObject->NewTalkCutScene[0].push_back({
    CUTSCENE_TYPE::DIE_CUTSCENE,
    DEMON_TYPE::PANDEMONICA,
    L"dialogueBG_hell",
    L"pand_idle",
    L"지옥을 살아서 나갈 생각을 한거야? 망상도 심하셔라.",
    L"",
    L"",
    L"",
    0,
    0,
    0      
});

    /*pObject->TalkCutScene[0].push_back({
        CUTSCENE_TYPE::TALK_CUTSCENE,
        DEMON_TYPE::PANDEMONICA,
        L"dialogueBG_hell",
        L"pand_idle",
        L"지옥 고객 서비스 센터의 판데모니카입니다.",
        L"무엇을 도와드릴까요?",
        1,
     });

    pObject->TalkCutScene[0].push_back({
        CUTSCENE_TYPE::CHOICE_CUTSCENE,
        DEMON_TYPE::PANDEMONICA,
        L"dialogueBG_hell",
        L"pand_idle",
        L"우리 집에 한번 오면 알게 될거야.",
        L"오히려 '그 쪽'을 도와줘야 할 판인데?",
        0,
    });

    pObject->TalkCutScene[0].push_back({
        CUTSCENE_TYPE::SUCESS_CUTSCENE,
        DEMON_TYPE::PANDEMONICA,
        L"dialogueBG_hell",
        L"pand_flust",
        L"그래주면 좋겠네요. 지금 커피 한잔이 너무 마시고 싶은데.",
        L"지금 제정신이 아니에요.",
        1,
    });

    pObject->TalkCutScene[0].push_back({
        CUTSCENE_TYPE::DIE_CUTSCENE,
        DEMON_TYPE::PANDEMONICA,
        L"dialogueBG_hell",
        L"pand_idle",
        L"지옥을 살아서 나갈 생각을 한거야? 망상도 심하셔라.",
        L"",
        1,
        });*/

    pObject->diemessage = L"그녀의 전문적인 친절함이 담긴 손길로 당신의 얼굴을 잡고";
    pObject->diemessage2 = L"목을 비틀어 버렸습니다.";

    CBackground* pBackground = new CBackground;
    pBackground->SetBackgroundMap(L"chapterBG_1");
    AddObject(pBackground, LAYER_TYPE::BACKGROUND);

    //TileMap Object 추가
    //CMap* pTileMap = new CMap;
    //pTileMap->SetPos(Vec2(0.f, 0.f));
    //wstring FilePath = CPathMgr::GetContentPath();
    //pTileMap->GetTileMap()->LoadTileMap(FilePath + L"TileMap\\Temp.tile");
    //AddObject(pTileMap, LAYER_TYPE::TILE);

    CFireBase* pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(950.f ,260.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(1);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(660.f ,370.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    CFire* pFire = new CFire;
    pFire->SetPos(Vec2(660.f, 370.f));
    pFire->SetOffset(7.f, -100.f);
    AddObject(pFire, LAYER_TYPE::FIRE);

    pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(550.f, 660.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(1);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(1260.f ,610.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    pFire = new CFire;
    pFire->SetPos(Vec2(1260.f, 610.f));
    pFire->SetOffset(7.f, -100.f);
    AddObject(pFire, LAYER_TYPE::FIRE);

    CCountUI* CUI = new CCountUI;
    CUI->SetCountUI(COUNT_UI_LEFT);
    AddObject(CUI, LAYER_TYPE::COUNTUI);

    CUI = new CCountUI;
    CUI->SetCountUI(COUNT_UI_RIGHT);
    AddObject(CUI, LAYER_TYPE::COUNTUI);

    CWall* pWall = new CWall;
    pWall->SetPos(1100.f, 150.f);
    pWall->SetScale(200.f, 100.f);
    pWall->SetWallSize(200.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(850.f, 250.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(950.f, 250.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(750.f, 250.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(650.f, 400.f);
    pWall->SetScale(100.f, 200.f);
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
    pWall->SetPos(550.f, 750.f);
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
    pWall->SetPos(650.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(750.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(850.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(950.f, 850.f);
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
    pWall->SetPos(1250.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1350.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);


    pWall = new CWall;
    pWall->SetPos(1250.f, 350.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1250.f, 450.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1250.f, 250.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1250.f, 550.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1250.f, 650.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1150.f, 450.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1150.f, 550.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    //pWall = new CWall;
    //pWall->SetPos(1350.f, 700.f);
    //pWall->SetScale(100.f, 200.f);
    //pWall->SetWallSize(100.f, 200.f);
    //AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(950.f, 550.f);
    pWall->SetScale(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1050.f, 550.f);
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

void CLevel_Start::Render()
{
    CLevel::Render();

    //글씨
    //TextOut(CEngine::GetInst()->GetSecondDC(), 10, 10, L"Start Level", wcslen(L"Start Level"));
}

void CLevel_Start::End()
{
    DeleteAllObject();
}

void CLevel_Start::Init()
{

    // Monster 생성
    CMonster* pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(1050.f, 450.f);
    pMonster->SetScale(100.f, 100.f);
    pMonster->SetDistance(200.f);
    pMonster->SetOffset(0.f, 30.f);
    pMonster->SetSpeed(300.f);
    pMonster->SetSound(1);
    AddObject(pMonster, LAYER_TYPE::MONSTER);

    CMonster* pMonster2 = new CMonster;
    pMonster2->SetName(L"Monster");
    pMonster2->SetPos(950.f, 350.f);
    pMonster2->SetScale(100.f, 100.f);
    pMonster2->SetDistance(200.f);
    pMonster2->SetOffset(0.f, 30.f);
    pMonster2->SetSpeed(300.f);
    pMonster2->SetSound(2);
    AddObject(pMonster2, LAYER_TYPE::MONSTER);

    CMonster* pMonster3 = new CMonster;
    pMonster3->SetName(L"Monster");
    pMonster3->SetPos(850.f, 450.f);
    pMonster3->SetScale(100.f, 100.f);
    pMonster3->SetDistance(200.f);
    pMonster3->SetSpeed(300.f);
    pMonster3->SetOffset(0.f, 30.f);
    pMonster3->SetSound(3);
    AddObject(pMonster3, LAYER_TYPE::MONSTER);

    CRock* pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_0");
    pRock1->SetPos(750.f, 650.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    CRock* pRock2 = new CRock;
    pRock2->SetName(L"Rock");
    pRock2->SetRock(L"boxExport_1");
    pRock2->SetPos(750.f, 750.f);
    pRock2->SetScale(100.f, 100.f);
    AddObject(pRock2, LAYER_TYPE::Rock);

    CRock* pRock4 = new CRock;
    pRock4->SetRock(L"boxExport_3");
    pRock4->SetName(L"Rock");
    pRock4->SetPos(1050.f, 650.f);
    pRock4->SetScale(100.f, 100.f);
    AddObject(pRock4, LAYER_TYPE::Rock);

    CRock* pRock3 = new CRock;
    pRock3->SetRock(L"boxExport_2");
    pRock3->SetName(L"Rock");
    pRock3->SetPos(950.f, 750.f);
    pRock3->SetScale(100.f, 100.f);
    AddObject(pRock3, LAYER_TYPE::Rock);

    CDemon* pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(PANDEMONICA);
    pDemon->SetPos(1250.f, 750.f);
    pDemon->SetScale(100.f, 100.f);
    AddObject(pDemon, LAYER_TYPE::DEMON);

    //CDemon* pDemon1 = new CDemon;
    //pDemon1->SetName(L"Demon1");
    //pDemon1->SetDemon(AZAZEL_IDLE);
    //pDemon1->SetPos(1150.f, 750.f);
    //pDemon1->SetScale(100.f, 100.f);
    //AddObject(pDemon1, LAYER_TYPE::DEMON);
}