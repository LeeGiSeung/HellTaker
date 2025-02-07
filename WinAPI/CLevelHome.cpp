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

    //Add Object Reset�� ������Ʈ �߰�
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

    //Player ����
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
    L"����",
    L"����",
    L"�׸��Ͽ� ����� ������ ���� ����.",
    L"",
    L"",
    L"",
    0,
    1,
    0,
    L"�׸��Ͽ�"
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::NULLNAME,
L"����",
L"cutscene_0005_Layer-196",
L"�Ǹ����� �������� ������ �����Ծ�.",
L"�׸��� ������Ŀ��� �˷����� ����.",
L"",
L"",
0,
2,
0,
L"�׸���������Ŀ��"
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::NULLNAME,
L"����",
L"cutscene_0006_Group-6-copy-3",
    L"������ ���� ���� ���� ���̴�.",
    L"�и� ª��, �� ������ �����ϸ�.",
L"",
L"",
0,
3,
0,
L"�����������ʴ�"
        });

    pObject->NewTalkCutScene[0].push_back({
CUTSCENE_TYPE::NEXTINDEXSCENE,
DEMON_TYPE::NULLNAME,
L"����",
L"cutscene_0007_Group-6-copy-6",
L"������ ��� ��ư��� ���̶� ����� ��.",
L"�׷��� �� ������ŭ�� ���°� ������.",
L"",
L"",
0,
4,
0,
L"��������¹�"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_home",
L"LW_pc",
L"������ũ �� �� �� �ϼ��̴�.",
L"",
L"",
L"",
0,
1,
0,
L"������ũ���Ǵ�"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_home",
L"LW_yum",
L"�׸��� ���ƾƾ� ���־�....",
L"",
L"",
L"",
0,
2,
0,
L"�����־�"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::HELLTAKER,
L"dialogueBG_home",
L"man_pc",
L"�����༭ ����",
L"",
L"",
L"",
0,
3,
0,
L"�����༭����"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_home",
L"LW_unsure",
L"���ｺ����. �� �͵� �ƴϿ���",
L"",
L"",
L"",
0,
4,
0,
L"���͵��ƴϿ���"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_home",
L"LW_unsure",
L"�׳����� ��, �װ� ��� �Ź� ��� ���������� ������",
L"�𸣰ھ�",
L"",
L"",
0,
5,
0,
L"����̷��Ծ��"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_home",
L"LW_unsure",
L"��� ������ũ�� �׷��� �������� �÷� ����������",
L"�ñ��ϰ�. ���� �����̶� ���� �� ����.",
L"",
L"",
0,
6,
0,
L"���������ũ����������"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::HELLTAKER,
L"dialogueBG_home",
L"man_pc",
L"��������.",
L"",
L"",
L"",
0,
7,
0,
L"��������"
        });

    pObject->NewTalkCutScene[1].push_back({
CUTSCENE_TYPE::NEXTINDEXSCENE,
DEMON_TYPE::LUCY,
L"dialogueBG_home",
L"LW_talk",
L"�� �׷��ðھ�. �ֵ����� ������ũ�� ������.",
L"",
L"",
L"",
0,
8,
0,
L"�Ʊ׷��ðھ�"
            });

        pObject->NewTalkCutScene[2].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::HELLTAKER,
L"dialogueBG_home",
L"man_pc",
L"���� ������ũ.",
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
    L"�����ֳ�. �� �ϳ��� �����.",
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
    L"���غ�",
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
    L"�ֵ� ���δ� ����� ���۶󽺸� �ȹ��´ٴµ�, �� �׷��ž�?",
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
    L"�� ������ ���� ����� �ͱ�.",
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
    L"�� ����? ���� ����̶� �� �ǵ�.",
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
    L"�� ������ �̷���. �� ��⵵ �ѹ� ����?",
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
L"������ ������...",
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
L"����, ����. ���� �ֵ��̶� �̹� ���� �ߴ� ���̾�.",
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
L"�� ������ �������� �ȳ����� �� ������ ���󰣴ٰ�.",
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
L"�����̴�! �� ����.",
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
L"�����̴�! �� ����.",
L"",
L"����.",
L"���� �ʱ�.",
1,
2,
2
            });

        pObject->NewTalkCutScene[3].push_back({
CUTSCENE_TYPE::TALK_CUTSCENE,
DEMON_TYPE::HELLTAKER,
L"dialogueBG_home",
L"man_pc",
L"������ũ ��Ű���?",
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
L"��, ���׿�. �׷��� ��� ���� ���߰ڽ��ϴ�.",
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
L"����",
L"����",
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
L"����",
L"cutscene_0008_Group-5",
L"�׷��� ������Ŀ�� �̾߱�� ���� ���ϴ�.",
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
L"����",
L"cutscene_0008_Group-5",
L"�̻� ����� ģ�� ���������� �����̼��̿����ϴ�.",
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

    // Platform Object �߰�
    //CObj* pPlatform = new CPlatform;
    //pPlatform->SetPos(0, 200);
    //AddObject(pPlatform, LAYER_TYPE::TILE);

    // �浹 ����
    CCollisionMgr::GetInst()->CollisionCheckClear();
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
    CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::Rock);
    //CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::TILE);

    // Camera ȿ��
    //CCamera::GetInst()->PostProcessEffect(HEART, 0.5f);  

    // �θ� CLevel �� Begin ȣ��
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
