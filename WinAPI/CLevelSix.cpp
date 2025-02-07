#include "pch.h"
#include "CLevelSix.h"
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

CLevelSix::CLevelSix()
{
}

CLevelSix::~CLevelSix()
{
}

void CLevelSix::Init()
{
    CKey* pKey = new CKey;
    pKey->SetPos(950.f, 350.f);
    pKey->SetScale(100.f, 100.f);
    pKey->SetOffset(0.f, 30.f);
    AddObject(pKey, LAYER_TYPE::KEY);

    CKeybox* pKeybox = new CKeybox;
    pKeybox->SetPos(1050.f, 750.f);
    pKeybox->SetScale(100.f, 100.f);
    AddObject(pKeybox, LAYER_TYPE::KEYBOX);

    // Monster 생성
    CMonster* pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(750.f, 550.f);
    pMonster->SetScale(100.f, 100.f);
    pMonster->SetOffset(0.f, 30.f);
    pMonster->SetDistance(200.f);
    pMonster->SetSpeed(300.f);
    pMonster->SetSound(1);
    AddObject(pMonster, LAYER_TYPE::MONSTER);

    pMonster = new CMonster;
    pMonster->SetName(L"Monster");
    pMonster->SetPos(1150.f, 650.f);
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

    CRock* pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_0");
    pRock1->SetPos(750.f, 250.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_1");
    pRock1->SetPos(850.f, 250.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_2");
    pRock1->SetPos(1150.f, 750.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_3");
    pRock1->SetPos(950.f, 250.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_4");
    pRock1->SetPos(850.f, 450.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_5");
    pRock1->SetPos(950.f, 550.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_8");
    pRock1->SetPos(1050.f, 550.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    pRock1 = new CRock;
    pRock1->SetName(L"Rock");
    pRock1->SetRock(L"boxExport_9");
    pRock1->SetPos(950.f, 650.f);
    pRock1->SetScale(100.f, 100.f);
    AddObject(pRock1, LAYER_TYPE::Rock);

    CThorn* pThorn = new CThorn;
    pThorn->SetThorn(THORN_DOWN);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(750.f, 450.f);
    pThorn->SetOffset(-10.f, 5.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

    pThorn = new CThorn;
    pThorn->SetThorn(THORN_DOWN);
    pThorn->SetName(L"Thorn");
    pThorn->SetPos(850.f, 450.f);
    pThorn->SetOffset(-10.f, 5.f);
    pThorn->SetScale(100.f, 100.f);
    AddObject(pThorn, LAYER_TYPE::THORN);

}

void CLevelSix::Begin()
{
    //Add Object Reset할 오브젝트 추가
    Init();

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
    pWall->SetPos(850.f, 550.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(650.f, 250.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(650.f, 150.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(750.f, 50.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(850.f, 50.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(950.f, 50.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1050.f, 150.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1050.f, 250.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1050.f, 350.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1150.f, 350.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1150.f, 450.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1250.f, 450.f);
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
    pWall->SetPos(1250.f, 650.f);
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

    pWall = new CWall;
    pWall->SetPos(1250.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1250.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1150.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(1050.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(950.f, 850.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(950.f, 750.f);
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
    pWall->SetPos(650.f, 750.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(650.f, 650.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(650.f, 550.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(950.f, 950.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(550.f, 450.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    pWall = new CWall;
    pWall->SetPos(650.f, 450.f);
    pWall->SetScale(100.f, 100.f);
    pWall->SetWallSize(100.f, 100.f);
    AddObject(pWall, LAYER_TYPE::WALL);

    CDemon* pDemon = new CDemon;
    pDemon->SetName(L"Demon");
    pDemon->SetDemon(AZAZEL);
    pDemon->SetPos(1150.f, 850.f);
    pDemon->SetScale(100.f, 100.f);
    AddObject(pDemon, LAYER_TYPE::DEMON);

    //Player 생성
    CPlayer* pObject = new CPlayer;
    pObject->SetName(L"Player");
    pObject->SetPos(850.f, 150.f);
    pObject->SetStartPos(850.f, 150.f);
    pObject->SetOffset(0.f, 30.f);
    pObject->SetScale(100.f, 100.f);
    pObject->SetInitDir(0);
    pObject->SetPlayerMoveCount(43);
    pObject->CurLevel = STAGE_5;
    AddObject(pObject, LAYER_TYPE::PLAYER);

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::AZAZEL,
L"dialogueBG_hell",
        L"az_idle",
        L"세상에, 신이시여! 멀쩡히 살아있는 인간이 지옥에서 뭘 하고",
        L"있는 거에요? 별일을 다보네",
L"",
L"",
0,
1,
0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::CHOICE_CUTSCENE,
DEMON_TYPE::AZAZEL,
L"dialogueBG_hell",
        L"az_idle",
        L"세상에, 신이시여! 멀쩡히 살아있는 인간이 지옥에서 뭘 하고",
        L"있는 거에요? 별일을 다보네",
        L"악마를 찾고 있어.",
        L"천사를 찾고 있어",
1,
2,
3
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::SUCESS_CUTSCENE,
DEMON_TYPE::AZAZEL,
L"dialogueBG_hell",
        L"az_note",
        L"당신도요? 잠깐, 제가 맞춰볼래요. 현대 죄악에 관한 이론?",
        L"아니면 악마학? 저랑 힘을 합치는게 좋을거 같아요.",
L"",
L"",
0,
1,
0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::AZAZEL,
L"dialogueBG_hell",
L"az_idle",
        L"여기서는 찾기 힘들거에요. 운 좋게도, 제가 더 좋은 곳을 알고 있죠",
        L"자, 꽉 잡아요.",
L"",
L"",
0,
4,
0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::AZAZEL,
L"공백",
L"공백",
        L"거짓말을 해서 천국 가는 일이 가능한지 누가 알았겠어요.",
        L"",
L"",
L"",
0,
5,
0
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::DIE_CUTSCENE,
DEMON_TYPE::AZAZEL,
L"cutscene_0000_Layer-197-copy-2",
L"공백",
        L"악마가 가득한 하렘과는 작별 인사를 해야겠네요.",
        L"",
L"",
L"",
0,
1,
0
        });

    //pObject->TalkCutScene[0].push_back({
    //    CUTSCENE_TYPE::TALK_CUTSCENE,
    //    DEMON_TYPE::AZAZEL,
    //    L"dialogueBG_hell",
    //    L"az_idle",
    //    L"세상에, 신이시여! 멀쩡히 살아있는 인간이 지옥에서 뭘 하고",
    //    L"있는 거에요? 별일을 다보네",
    //    1,
    // });

    //pObject->TalkCutScene[0].push_back({
    //    CUTSCENE_TYPE::CHOICE_CUTSCENE,
    //    DEMON_TYPE::AZAZEL,
    //    L"dialogueBG_hell",
    //    L"az_idle",
    //    L"악마를 찾고 있어.",
    //    L"천사를 찾고 있어",
    //    1,
    //    });

    //pObject->TalkCutScene[0].push_back({
    //    CUTSCENE_TYPE::SUCESS_CUTSCENE,
    //    DEMON_TYPE::AZAZEL,
    //    L"dialogueBG_hell",
    //    L"az_note",
    //    L"당신도요? 잠깐, 제가 맞춰볼래요. 현대 죄악에 관한 이론?",
    //    L"아니면 악마학? 저랑 힘을 합치는게 좋을거 같아요.",
    //    1,
    //    });

    //pObject->TalkCutScene[0].push_back({
    //    CUTSCENE_TYPE::DIE_CUTSCENE,
    //    DEMON_TYPE::AZAZEL,
    //    L"dialogueBG_hell",
    //    L"az_idle",
    //    L"여기서는 찾기 힘들거예요. 운 좋게도, 제가 더 좋은 곳을 알고 있죠",
    //    L"자, 꽉 잡아요.",
    //    1,
    //    });

    pObject->diemessage = L"";
    pObject->diemessage2 = L"";

    CBackground* pBackground = new CBackground;
    pBackground->SetPos(0.f, 0.f);
    pBackground->SetBackgroundMap(L"chapterBG_6");
    AddObject(pBackground, LAYER_TYPE::BACKGROUND);

    //TileMap Object 추가
    //CMap* pTileMap = new CMap;
    //pTileMap->SetPos(Vec2(0.f, 0.f));
    //wstring FilePath = CPathMgr::GetContentPath();
    //pTileMap->GetTileMap()->LoadTileMap(FilePath + L"TileMap\\Temp.tile");
    //AddObject(pTileMap, LAYER_TYPE::TILE);

    CFireBase* pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(650.f, 265.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    CFire* pFire = new CFire;
    pFire->SetPos(Vec2(650.f, 265.f));
    pFire->SetOffset(7.f, -100.f);
    AddObject(pFire, LAYER_TYPE::FIRE);

    pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(1162.f, 320.f));
    pFireBase->SetOffset(5.f, -60.f);
    pFireBase->SetFireBase(0);
    AddObject(pFireBase, LAYER_TYPE::FIREBASE);

    pFire = new CFire;
    pFire->SetPos(Vec2(1162.f, 320.f));
    pFire->SetOffset(7.f, -100.f);
    AddObject(pFire, LAYER_TYPE::FIRE);

    pFireBase = new CFireBase;
    pFireBase->SetPos(Vec2(1060.f, 260.f));
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

void CLevelSix::Render()
{
    CLevel::Render();
}

void CLevelSix::End()
{
    DeleteAllObject();
}
