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

    //Add Object Reset�� ������Ʈ �߰�
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

    //Player ����
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
       L"����",
       L"����",
       L"�� ħ���� �༮! �������� �� ã�Ҵ�.",
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
   L"����",
   L"���� ���⼭ ���� ���� ������ ��",
   L"�ʶ� ����, ���� ���� �ð� ���� �־�� ���״ϱ�",
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
//L"����",
//L"������ ��迡 ���� ������! ������ �ݵ�� ġ������ �Ѵ�!",
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
L"�˾��� ��迡 �õ��� �ɾ��! �÷��� ���� ���� ����!",
L"",
L"",
L"",
0,
3,
0,
L"�˾��Ǳ�迡�õ���"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"ħ���ھ�! �˾��� ��谡 ������ �����!",
L"",
L"",
L"",
0,
1,
0,
L"�˾��Ǳ�谡����"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"�̸� �����ϰ� ��������!",
L"",
L"",
L"",
0,
2,
0,
L"�̸������ϰ�"
});

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::CERBERUS,
L"dialogueBG_sin",
L"cer_idle",
L"�ȵ� ���! �����ϸ� �ȵ�! �츮�� ������ ��������!",
L"",
L"",
L"",
0,
3,
0,
L"�ȵ�����������"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::PANDEMONICA,
L"dialogueBG_sin",
L"pand_flust",
L"�׸��� Ŀ�ǵ� Ÿ�ּž���...",
L"",
L"",
L"",
0,
4,
0,
L"�׸���Ŀ�ǵ�"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_back",
L"����� ������! �� �༮�� ����� �̹� ��������!",
L"",
L"",
L"",
0,
5,
0,
L"�����������"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_sin",
L"LH_angry",
L"�̷� ������Ʈ, �� �༮�� �𸣰� �ְ�����, ���ž�.",
L"�׳� ������ ���� �� ����?",
L"",
L"",
0,
6,
0,
L"�����߱׳ɳ�����"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::NEXTINDEXSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_angry",
L"�����ض�! ���� ��¥ �����̴�.",
L"",
L"",
L"",
0,
6,
0,
L"�����϶�"
        });

    pObject->NewTalkCutScene[2].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"j_laugh2",
L"�ʸ� �̰����� �̲����� �͵��� �罽�� �Ǿ�, �ʸ� �ְ���",
L"",
L"",
L"",
0,
1,
0,
L"�罽�̵Ǿ�ʸ��ְ���"
        });


    pObject->NewTalkCutScene[2].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"j_laugh2",
L"���� ����, ���� Ž��, �׸��� ����, �� ������ ������ �����ѰŴ�.",
L"",
L"",
L"",
0,
2,
0,
L"����������"
        });

    pObject->NewTalkCutScene[2].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_sin",
L"LH_angry",
L"�׸�! ���� ��Ұ�, ��� ������ ���� ���Ѵ�.",
L"",
L"",
L"",
0,
3,
0,
L"�׸������ͼҰ�"
        });

    pObject->NewTalkCutScene[2].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_angry",
L"�� � ������ ������ �Ѿ� �� �� ����!",
L"",
L"",
L"",
0,
4,
0,
L"�׾������"
        });

    pObject->NewTalkCutScene[2].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUSTICE,
L"dialogueBG_sin",
L"jus_idle",
L"������Ʈ ����غ�, �� �����µ�?",
L"",
L"",
L"",
0,
5,
0,
L"������Ʈ����غ�"
        });

    pObject->NewTalkCutScene[2].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::AZAZEL,
L"dialogueBG_sin",
L"az_note",
L"�׷���, ����ϼ���. �̰� �и� A+ ���� ���� ���翡��.",
L"",
L"",
L"",
0,
6,
0,
L"�׷������ϼ���"
        });


    pObject->NewTalkCutScene[2].push_back({
CUTSCENE_TYPE::NEXTINDEXSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_sin",
L"LH_rustled",
L"���� ������ �������ٵ�! �� �ƹ��� ���͸� �� ó ���?",
L"",
L"",
L"",
0,
7,
0,
L"����������"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"j_bindAnimNull",
L"���� ����� �μ��� ���� ���� �� ���� �� ������?",
L"",
L"",
L"",
0,
1,
0,
L"�����罽���μ���"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"j_bindAnimNull",
L"����� �Ǹ���, �׸��� �Ǹ��� ������ ���´�.",
L"",
L"",
L"",
0,
2,
0,
L"������Ǹ���"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"j_bindAnimNull",
L"�׸��� ������ �罽�� ���� ��ſ� ������.",
L"",
L"",
L"",
0,
3,
0,
L"�׸��������ǻ罽��"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::ZDRADA,
L"dialogueBG_sin",
L"z_idle",
L"��.. ����ī�� ����� ���� �ⲯ ã�� �׽��۰� ģ���� �װ� �����.",
L"",
L"",
L"",
0,
4,
0,
L"���������"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::MALINA,
L"dialogueBG_sin",
L"mal_puzzled",
L"�� ����� �̷��� ���� ��ũ���������� �ϰ� �ƾ�.",
L"",
L"",
L"",
0,
5,
0,
L"�������"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::MODEUS,
L"dialogueBG_sin",
L"mod_idle",
L"���� �� ȥ�� ������ �� ��...",
L"",
L"",
L"",
0,
6,
0,
L"���󸮳�ȥ��"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"�׷�! �װ� ���� ��� �͵��� ��ȸ�϶�!",
L"",
L"",
L"",
0,
7,
0,
L"�װ�����"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::CHOICE_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"�׷�! �װ� ���� ��� �͵��� ��ȸ�϶�!",
L"",
L"�� ��� ��Ÿ���� ������ ��µ�.",
L"�� �� �����ִµ�! 10�� ������ 10��!",
2,
8,
8
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"������! �⸸���� �� ����� ��� ���� ����!",
L"",
L"",
L"",
0,
9,
0,
L"�⸸����"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::CHOICE_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"������! �⸸���� �� ����� ��� ���� ����!",
L"",
L"�˾�. �׷��� ���� �̷��� ������ ����.",
L"�� ���鵵 �� ������ ��µ�!",
2,
10,
10
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"j_poseAnim (3)",
L"�׷�? �׷��ٸ�, ����! ��� �ؾ߰���?",
L"",
L"",
L"",
0,
11,
0,
L"�׷�"
        });

    pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::NEXTINDEXSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"j_flyAnim_4",
L"���� �ٽ� �÷��� �����Ѵ�!",
L"",
L"",
L"",
0,
12,
0,
L"�÷���"
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"������ ������ ���۵Ǳ� ���� ���� ���̶� �ִ���?",
L"",
L"",
L"",
0,
1,
0,
L"������"
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::CHOICE_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"������ ������ ���۵Ǳ� ���� ���� ���̶� �ִ���?",
L"",
L"�ʸ� ���� ���� ���Ѱ� ���� ��ȸ�Ǵ� ��.",
L"�ʿ��� ���� �ް� �ִ°� �˸� ���� ��ġ�� �ִٰ� ������.",
2,
2,
2,
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"���� �ƺδ� ����ġ��! ���� ��ư� ������ ��!",
L"",
L"",
L"",
0,
3,
0,
L"����"
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::CHOICE_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"���� �ƺδ� ����ġ��! ���� ��ư� ������ ��!",
L"",
L"�Դٰ�, �̷��� ���� ���� �� ������.",
L"���� �Ʊ� �Ӹ� ��Ÿ�� �����ٰ� ��� �߾���?",
2,
4,
4
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_resign",
L"���ݾ�, ���� ���� �̷��� ���� ������. ������ �̹� �����",
L"Ȯ���ƾ�. �� ���ָ� ���� �� ���ٰ�.",
L"",
L"",
0,
5,
0,
L"���ݾ�"
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_resign",
L"�׷���... �װ� �ٽ� ������ ������ �ٴ����� �ʴ´ٸ� �ڷ�",
L"�̷� ���� �ְ���.",
L"",
L"",
0,
6,
0,
L"�׷����װ��ٽ�"
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_resign",
L"�츮 ����� ������ �־�. �� �ʸ� ���̰�, �� �÷��� �޾ƾ� ����.",
L"������ �װ� �� ������ �ʿ�� ����...",
L"",
L"",
0,
7,
0,
L"�츮�����"
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"J_introAnim_6",
L"�׷��� �� ���� �� �˰� �� �� �տ��� �������!",
L"",
L"",
L"",
0,
8,
0,
L"�׷��Ͽ�����"
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
L"���� �ȴٰ� ���ݾ�! �� �����!",
L"",
L"",
L"",
0,
12,
0,
L"�����ȴٰ�"
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_angry",
L"��? �� �Ϸ��� �������? ������ ����!",
L"",
L"",
L"",
0,
13,
0,
L"���Ϸ�����"
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_resign",
L"������ �� ���̷��� ������ ȭ�Ű� �� ���� �Ʒ���",
L"��ڴٰ�?",
L"",
L"",
0,
14,
0,
L"������"
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::CHOICE_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_resign",
L"������ �� ���̷��� ������ ȭ�Ű� �� ���� �Ʒ���",
L"��ڴٰ�?",
L"�װ� ���� �ٸ��� ������ �ʾ�",
L"�� �� ����, �̹� �� �Ϸ��� �� �����Ѱ� �ִٴϱ�.",
2,
15,
15
        });

    pObject->NewTalkCutScene[4].push_back({
CUTSCENE_TYPE::SUCESS_CUTSCENE,
DEMON_TYPE::JUDGMENT,
L"dialogueBG_sin",
L"judg_shock",
L"��? �����̾�?",
L"",
L"",
L"",
0,
16,
0,
L"�����̾�"
        });
    pObject->diemessage = L"�þ߰� �帴������ �����ϴ���, ����� ���̷� Į ���ڷ簡";
    pObject->diemessage2 = L"��� ���� ���� ���� �� ���� �����������ϴ�.";

    CBackground* pBackground = new CBackground;
    pBackground->SetPos(0.f, 0.f);
    pBackground->SetBackgroundMap(L"����");
    AddObject(pBackground, LAYER_TYPE::BACKGROUND);

    //TileMap Object �߰�
    //CMap* pTileMap = new CMap;
    //pTileMap->SetPos(Vec2(0.f, 0.f));
    //wstring FilePath = CPathMgr::GetContentPath();
    //pTileMap->GetTileMap()->LoadTileMap(FilePath + L"TileMap\\Temp.tile");
    //AddObject(pTileMap, LAYER_TYPE::TILE);

    // Platform Object �߰�
    //CObj* pPlatform = new CPlatform;
    //pPlatform->SetPos(500, 800);
    //AddObject(pPlatform, LAYER_TYPE::TILE);

    // �浹 ����
    CCollisionMgr::GetInst()->CollisionCheckClear();
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::THORN);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::DAMAGE_CHAIN);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::TILE);

    // Camera ȿ��
    //CCamera::GetInst()->PostProcessEffect(HEART, 0.5f);  

    // �θ� CLevel �� Begin ȣ��
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

