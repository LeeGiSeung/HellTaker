#include "pch.h"
#include "CPlayer.h"

#include "CCamera.h"
#include "CAssetMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CTaskMgr.h"
#include "CDbgRender.h"

#include "CMissile.h"
#include "CLevelMgr.h"
#include "CLevel.h"

#include "CMonster.h"
#include "CCollider.h"
#include "CFlipbookPlayer.h"
#include "CGuidedMissile.h"
#include "CLevel_Start.h"

#include "CGear.h"
#include "CJudmentSkul.h"
#include "CJudmentPiston.h"
#include "CEngine.h"
#include "CTexture.h"
#include "CFlipbook.h"
#include "CSprite.h"
#include "CRigidBody.h"
#include "CSound.h"
#include "CRestartCutScene.h"
#include "CDeathP.h"
#include "CRock.h"
#include "CThorn.h"
#include "CKeybox.h"
#include "CDemon.h"
#include "CKey.h"
#include "CBridge.h"
#include "CDialogueDeath.h"
#include "CDamageChain.h"
#include "CSuccess.h"
#include "CFire.h"
#include <functional>
#include "CBrakeChain.h"
#include "CSoundMgr.h"

enum PLAYER_ANIM_STATE
{
	IDLE_LEFT,
	IDLE_RIGHT,
	MOVE_LEFT,
	MOVE_RIGHT,
	KICK_LEFT,
	KICK_RIGHT,
	SMILE

};

enum DIRECTION {
	D_LEFT,
	D_RIGHT,
	D_UP,
	D_DOWN,
	D_END
};

enum SEE {
	S_LEFT,
	S_RIGHT
};

CPlayer::CPlayer()
	: m_Speed(200.f)
	, m_AttSpeed(10.f)
	, m_AccTime(0.f)
	, Pressed(false)
	, m_HitBox(nullptr)
	, m_FlipbookPlayer(nullptr)
	, m_FlipbookVFXPlayer(nullptr)
	, m_FlipbookMOVEVFXPlayer(nullptr)
	, m_FlipbookCutSceneBooperPlayer(nullptr)
	, m_FlipbookCutSceneDeathPlayer(nullptr)
	, m_FlipbookCutSceneSucessPlayer(nullptr)
	, pCharacter_Enemy_Kick(nullptr)
	, pCharacter_Rock_Kick(nullptr)
	, m_Restart(nullptr)
	, PLAYER_COLLISION_CHECK(false)
	, m_Target(nullptr)
	, m_Target_Thorn(nullptr)
	, m_DetectRange(100.f)
	, PLAYER_MOVING_CHECK(false)
	, Moving_TickPos(20.f)
	, Moving_CurPos({ 0.f,0.f })
	, Moving_GoalPos({ 0.f,0.f })
	, Moving_MovePos({ 0.f,0.f })
	, MoveVFXRenderPos({ 0.f,0.f })
	, Move_Direction(D_END)
	, PlayerMove_Count(0)
	, Init_PlayerMove_Count(0)
	, Die(false)
	, pThorn_damage0(nullptr)
	, pThorn_damage1(nullptr)
	, PlayerMove(false)
	, VFX_HUGE_RENDER(false)
	, VFX_KICK_RENDER(false)
	, VFX_MOVE_RENDER(false)
	, KeyBox_Key(false)
	, TalkPartCheck(false)
	, Dialogue_start(nullptr)
	, Dialogue_Success(nullptr)
	, Dialogue_Start(nullptr)
	, Dialogue_Booper(nullptr)
	, Dialogue_Next(nullptr)
	, CurLevel(false)
{
	// Collider 컴포넌트 추가
	m_HitBox = new CCollider;
	m_HitBox->SetName(L"HitBox_01");
	m_HitBox->SetScale(Vec2(90.f, 80.f));
	m_HitBox->SetOffset(Vec2(0.f, 20.f));
	AddComponent(m_HitBox);

	CreateSound();

	CreatePlayerFlipbook();

}

void CPlayer::CreateSound()
{

	float a = 40.f;
	SoundIndex = CSoundMgr::GetInst()->SoundIndex;
	if (SoundIndex == 0) {
		ActorVolume = 60.f;
		a = 50.f;
	}
	else if (SoundIndex == 1) {
		ActorVolume = 40.f;
		a = 30.f;
	}
	else if (SoundIndex == 2) {
		ActorVolume = 20.f;
		a = 10.f;
	}

	pCharacter_Move = CAssetMgr::GetInst()->LoadSound(L"Character_move", L"Sound\\character_move_01.wav");
	if (nullptr != pCharacter_Move)
	{
		pCharacter_Move->SetVolume(a);
	}
	pCharacter_Enemy_Kick = CAssetMgr::GetInst()->LoadSound(L"Character_Enemy_Kick", L"Sound\\enemy_kick_03.wav");
	if (nullptr != pCharacter_Enemy_Kick)
	{
		pCharacter_Enemy_Kick->SetVolume(a);
	}
	pCharacter_Rock_Kick = CAssetMgr::GetInst()->LoadSound(L"Character_Rock_Kick", L"Sound\\stone_kick_01.wav");
	if (nullptr != pCharacter_Rock_Kick)
	{
		pCharacter_Rock_Kick->SetVolume(a);
	}
	pThorn_damage0 = CAssetMgr::GetInst()->LoadSound(L"pThorn_damage0", L"Sound\\spikes_damage_01.wav");
	if (nullptr != pThorn_damage0)
	{
		pThorn_damage0->SetVolume(a);
	}
	pThorn_damage1 = CAssetMgr::GetInst()->LoadSound(L"pThorn_damage1", L"Sound\\spikes_damage_02.wav");
	if (nullptr != pThorn_damage1)
	{
		pThorn_damage1->SetVolume(a);
	}

	Dialogue_start = CAssetMgr::GetInst()->LoadSound(L"Dialogue_start", L"Sound\\dialogue_start_01.wav");
	if (nullptr != Dialogue_start)
	{
		Dialogue_start->SetVolume(a);
	}

	Dialogue_Success = CAssetMgr::GetInst()->LoadSound(L"Dialogue_Success", L"Sound\\dialogue_success_01.wav");
	if (nullptr != Dialogue_Success)
	{
		Dialogue_Success->SetVolume(a);
	}

	Dialogue_Booper = CAssetMgr::GetInst()->LoadSound(L"Dialogue_Booper", L"Sound\\dialogue_text_end_01.wav");
	if (nullptr != Dialogue_Booper)
	{
		Dialogue_Booper->SetVolume(a);
	}

	Dialogue_Next = CAssetMgr::GetInst()->LoadSound(L"Dialogue_Next", L"Sound\\dialogue_text_next.wav");
	if (nullptr != Dialogue_Next)
	{
		Dialogue_Next->SetVolume(a);
	}

	KissSound = CAssetMgr::GetInst()->LoadSound(L"KissSound", L"Sound\\succub_capture_01.wav");
	if (nullptr != KissSound)
	{
		KissSound->SetVolume(a);
	}

	boss_machine_end = CAssetMgr::GetInst()->LoadSound(L"boss_machine_end", L"Sound\\boss_machine_end.wav");
	if (nullptr != boss_machine_end)
	{
		boss_machine_end->SetVolume(a);
	}

	boss_machine_start = CAssetMgr::GetInst()->LoadSound(L"boss_machine_start", L"Sound\\boss_machine_start.wav");
	if (nullptr != boss_machine_start)
	{
		boss_machine_start->SetVolume(a);
	}

	boss_chain_kick_01L = CAssetMgr::GetInst()->LoadSound(L"boss_chain_kick_01L", L"Sound\\boss_chain_kick_01L.wav");
	if (nullptr != boss_chain_kick_01L)
	{
		boss_chain_kick_01L->SetVolume(a);
	}

	boss_chain_kick_02L = CAssetMgr::GetInst()->LoadSound(L"boss_chain_kick_02L", L"Sound\\boss_chain_kick_02L.wav");
	if (nullptr != boss_chain_kick_02L)
	{
		boss_chain_kick_02L->SetVolume(a);
	}

	boss_chain_kick_03L = CAssetMgr::GetInst()->LoadSound(L"boss_chain_kick_03L", L"Sound\\boss_chain_kick_03L.wav");
	if (nullptr != boss_chain_kick_03L)
	{
		boss_chain_kick_03L->SetVolume(a);
	}

	boss_chain_kick_01R = CAssetMgr::GetInst()->LoadSound(L"boss_chain_kick_01R", L"Sound\\boss_chain_kick_01R.wav");
	if (nullptr != boss_chain_kick_01R)
	{
		boss_chain_kick_01R->SetVolume(a);
	}

	boss_chain_kick_02R = CAssetMgr::GetInst()->LoadSound(L"boss_chain_kick_02R", L"Sound\\boss_chain_kick_02R.wav");
	if (nullptr != boss_chain_kick_02R)
	{
		boss_chain_kick_02R->SetVolume(a);
	}

	boss_chain_kick_03R = CAssetMgr::GetInst()->LoadSound(L"boss_chain_kick_03R", L"Sound\\boss_chain_kick_03R.wav");
	if (nullptr != boss_chain_kick_03R)
	{
		boss_chain_kick_03R->SetVolume(a);
	}

	boss_chain_break_01R = CAssetMgr::GetInst()->LoadSound(L"boss_chain_break_01R", L"Sound\\boss_chain_break_01R.wav");
	if (nullptr != boss_chain_break_01R)
	{
		boss_chain_break_01R->SetVolume(a);
	}

	boss_chain_break_01L = CAssetMgr::GetInst()->LoadSound(L"boss_chain_break_01L", L"Sound\\boss_chain_break_01L.wav");
	if (nullptr != boss_chain_break_01L)
	{
		boss_chain_break_01L->SetVolume(a);
	}

	lucifer_intro_vine_01 = CAssetMgr::GetInst()->LoadSound(L"lucifer_intro_vine_01", L"Sound\\lucifer_intro_vine_01.wav");
	if (nullptr != lucifer_intro_vine_01)
	{
		lucifer_intro_vine_01->SetVolume(a);
	}

	lucifer_intro_skeleton_01 = CAssetMgr::GetInst()->LoadSound(L"lucifer_intro_skeleton_01", L"Sound\\lucifer_intro_skeleton_01.wav");
	if (nullptr != lucifer_intro_skeleton_01)
	{
		lucifer_intro_skeleton_01->SetVolume(a);
	}

	lucifer_intro_dialogue_start_v2 = CAssetMgr::GetInst()->LoadSound(L"lucifer_intro_dialogue_start_v2", L"Sound\\lucifer_intro_dialogue_start_v2.wav");
	if (nullptr != lucifer_intro_dialogue_start_v2)
	{
		lucifer_intro_dialogue_start_v2->SetVolume(a);
	}

	judgement_chain_bind_01 = CAssetMgr::GetInst()->LoadSound(L"judgement_chain_bind_01", L"Sound\\judgement_chain_bind_01.wav");
	if (nullptr != judgement_chain_bind_01)
	{
		judgement_chain_bind_01->SetVolume(a);
	}

	judgement_spell_cast_01 = CAssetMgr::GetInst()->LoadSound(L"judgement_spell_cast_01", L"Sound\\judgement_spell_cast_01.wav");
	if (nullptr != judgement_spell_cast_01)
	{
		judgement_spell_cast_01->SetVolume(a);
	}

	judgement_chain_summon_01 = CAssetMgr::GetInst()->LoadSound(L"judgement_chain_summon_01", L"Sound\\judgement_chain_summon_01.wav");
	if (nullptr != judgement_chain_summon_01)
	{
		judgement_chain_summon_01->SetVolume(a);
	}

	button_menu_confirm_01 = CAssetMgr::GetInst()->LoadSound(L"button_menu_confirm_01", L"Sound\\button_menu_confirm_01.wav");
	if (nullptr != button_menu_confirm_01)
	{
		button_menu_confirm_01->SetVolume(a);
	}

	judgement_intro_start_01 = CAssetMgr::GetInst()->LoadSound(L"judgement_intro_start_01", L"Sound\\judgement_intro_start_01.wav");
	if (nullptr != judgement_intro_start_01)
	{
		judgement_intro_start_01->SetVolume(a);
	}
	
	judgement_intro_anim_01 = CAssetMgr::GetInst()->LoadSound(L"judgement_intro_anim_01", L"Sound\\judgement_intro_anim_01new2.wav");
	if (nullptr != judgement_intro_anim_01)
	{
		judgement_intro_anim_01->SetVolume(a);
	}
	boss_judgement_land_01 = CAssetMgr::GetInst()->LoadSound(L"boss_judgement_land_01", L"Sound\\boss_judgement_land_01.wav");
	if (nullptr != boss_judgement_land_01)
	{
		boss_judgement_land_01->SetVolume(a);
	}
}

CPlayer::~CPlayer()
{	
}

void CPlayer::Begin()
{
	if (CurLevel == LEVEL_CHECK::BOSS_0) {
		Moving_TickPos = 20.f;
		judgement_intro_start_01->Play();
	}
	else {
		Moving_TickPos = 5.f;
	}

	m_AccTime = 1.f / m_AttSpeed;

	if (Dir == S_RIGHT) {
		m_FlipbookPlayer->Play(IDLE_RIGHT, 15.f, true);
	}
	else if (Dir == S_LEFT) {
		m_FlipbookPlayer->Play(IDLE_LEFT, 15.f, true);
	}
	
	//m_FlipbookCutSceneDemonPlayer->Play(J_introAnim, 7.f, false);
	m_FlipbookCutSceneBooperPlayer->Play(BOOPER_CUTSCENE_FLIPBOOK, 20.f, true);
	m_FlipbookCutSceneDeathPlayer->Play(PLAYER_DEATH_CUTSCENE_FLIPBOOK, 10.f, false);
	m_FlipbookCutSceneSucessPlayer->Play(SUCESS_CUTSCENE_FLIPBOOK, 10.f, false);
	m_FlipbookCutSceneDemonPlayerRight->Play(mainUIexport_oUI_idleRIGHT, 15.f, true);
	m_FlipbookCutSceneLucyEye->Play(LUCY_FACE, 1.f, false);

	if (CurLevel == STAGE_7) {
		CCamera::GetInst()->SetTarget(this);
	}
	else {
		CCamera::GetInst()->SetTarget(nullptr);
	}
}

void CPlayer::Tick()
{
	MusicIndex = CSoundMgr::GetInst()->MusicIndex;
	SoundIndex = CSoundMgr::GetInst()->SoundIndex;

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::DAMAGE_CHAIN);

	Vec2 z = GetPos();
	int h = 0;
	if (KEY_TAP(ESC)) {
		TurnPauseMenu();
	}
	if (PauseMenu) {
		PauseLogic();
	}
	else {
		if (TalkPartCheck) {
			TALKCUTSCENE_LOGIC();
		}
		else {
			DEFAULT_LOGIC();
		}
	}
}

void CPlayer::PauseLogic()
{
	if (KEY_TAP(ENTER)) {
		if (PauseMenuFocusingNum == 0) {
			TurnPauseMenu();
		}
		else if (PauseMenuFocusingNum == 1) {
			if (CurLevel == LEVEL_CHECK::BOSS_0) {
				ChangeGodMode();
				TurnPauseMenu();
			}
			else {
				CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
				SuccessLevel = true;
				CutsceneTime = 0.f;
				TalkPartCheck = false;
				const vector<CObj*>& vecDemon = pCurLevel->GetObjects(LAYER_TYPE::DEMON);

				for (int i = 0; i < vecDemon.size(); i++) {
					CDemon* cd = dynamic_cast<CDemon*>(vecDemon[i]);
					cd->clearLevel = true;
				}
				if (CurLevel == LEVEL_CHECK::BOSS_0 && TalkCutSceneIndex == 4) {
					JudmentClear = true;
				}
				m_FlipbookPlayer->Play(SMILE, 5.f, false);

				KissSound->Play();
				TurnPauseMenu();
			}
		}
		else if (PauseMenuFocusingNum == 4) {
			ChangeLevel(LEVEL_TYPE::STAGE_LOBBY);
		}
	}
	if (KEY_TAP(UP)) {
		Dialogue_Next->Play();
		if ((PauseMenuFocusingNum - 1) % 5 < 0) {
			PauseMenuFocusingNum = 4;
		}
		else {
			PauseMenuFocusingNum = (PauseMenuFocusingNum - 1) % 5;
		}
	}
	else if (KEY_TAP(DOWN)) {
		Dialogue_Next->Play();
		PauseMenuFocusingNum = (PauseMenuFocusingNum + 1) % 5;
	}
	if (KEY_TAP(LEFT)) {
		Dialogue_Next->Play();
		if (PauseMenuFocusingNum == 2) {
			MusicIndex = CSoundMgr::GetInst()->MusicIndex;
			if (MusicIndex - 1 < 0) {
				MusicIndex = 2;
			}
			else {
				MusicIndex = (MusicIndex - 1) % 3;
			}
		}
		if (PauseMenuFocusingNum == 3) {
			SoundIndex = CSoundMgr::GetInst()->SoundIndex;
			if (SoundIndex - 1 < 0) {
				SoundIndex = 2;
			}
			else {
				SoundIndex = (SoundIndex - 1) % 3;
			}
		}
		CSoundMgr::GetInst()->SoundIndex = SoundIndex;
		CSoundMgr::GetInst()->MusicIndex = MusicIndex;
		CreateSound();
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		pCurLevel->SetBGMVolume();
	}
	if (KEY_TAP(RIGHT)) {
		Dialogue_Next->Play();
		if (PauseMenuFocusingNum == 2) {
			MusicIndex = CSoundMgr::GetInst()->MusicIndex;
			MusicIndex = (MusicIndex + 1) % 3;
		}
		if (PauseMenuFocusingNum == 3) {
			SoundIndex = CSoundMgr::GetInst()->SoundIndex;
			SoundIndex = (SoundIndex + 1) % 3;
		}
		CSoundMgr::GetInst()->SoundIndex = SoundIndex;
		CSoundMgr::GetInst()->MusicIndex = MusicIndex;
		CreateSound();
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		pCurLevel->SetBGMVolume();
	}
}

void CPlayer::ChangeGodMode()
{
	if (GodMode == false) {
		GodMode = true;
	}
	else if (GodMode == true) {
		GodMode = false;
	}

}

void CPlayer::TurnPauseMenu()
{
	if (PauseMenu == true) {
		if (PauseMenuFocusingNum != 1) {
			button_menu_confirm_01->Play();
		}
		PauseMenu = false;
	}
	else {
		PauseMenu = true;
	}

}

struct DATA {
	float PattonTimes;
	Vec2 ChainPos;
	int ChainDir;
};
std::vector<DATA> pattonTimes = { 
	{5.0f,{650.f,750.f},1},
	{5.6f,{750.f,750.f},1},
	{6.2f,{850.f,750.f},1},
	{6.8f,{950.f,750.f},1},
	{7.4f,{1050.f,750.f},1},
	{8.2f,{1250.f,750.f},1},
	{8.8f,{1150.f,750.f},1},
	{9.4f,{1050.f,750.f},1},
	{10.0f,{950.f,750.f},1},
	{10.6f,{850.f,750.f},1},
	{11.2f,{650.f,750.f},1},
	{11.8f,{850.f,750.f},1},
	{12.4f,{1050.f,750.f},1},
	{13.0f,{750.f,750.f},1},
	{13.0f,{1250.f,750.f},1},
	{13.6f,{650.f,750.f},1},
	{13.6f,{950.f,750.f},1},
	{14.2f,{850.f,750.f},1},
	{14.2f,{1150.f,750.f},1},
	{14.8f,{1050.f,750.f},1},
	{15.4f,{1250.f,750.f},1},
	{16.0f,{950.f,750.f},1},
	{16.6f,{650.f,750.f},1},
	{16.6f,{1250.f,750.f},1},
	{17.2f,{850.f,750.f},1},
	{17.2f,{1050.f,750.f},1},
	{17.8f,{750.f,750.f},1},
	{17.8f,{1150.f,750.f},1},
	{18.4f,{950.f,750.f},1},
	{18.4f,{1250.f,750.f},1},
	{18.4f,{650.f,750.f},1},
};
std::vector<DATA> pattonTimes1 = {
	{5.0f,{650.f,750.f},1},
	{5.0f,{950.f,750.f},1},
	{5.0f,{1250.f,750.f},1},
	{5.6f,{850.f,750.f},1},
	{5.6f,{1050.f,750.f},1},
	{6.2f,{950.f,750.f},1},
	{6.8f,{750.f,750.f},1},
	{6.8f,{1150.f,750.f},1},
	{7.4f,{650.f,750.f},1},
	{7.4f,{950.f,750.f},1},
	{7.4f,{1250.f,750.f},1},

	{8.2f,{0.f,750.f},0},
	{9.2f,{0.f,650.f},0},
	{10.2f,{0.f,450.f},0},
	{10.2f,{0.f,750.f},0},
	{11.2f,{0.f,600.f},0},
	{12.2f,{0.f,750.f},0},

	{13.2f,{650.f,750.f},1},
	{13.2f,{1250.f,750.f},1},
	{13.8f,{750.f,750.f},1},
	{13.8f,{1150.f,750.f},1},
	{14.4f,{950.f,750.f},1},

	{15.0f,{950.f,750.f},1},
	{15.0f,{850.f,750.f},1},
	{15.0f,{1050.f,750.f},1},

	{15.6f,{650.f,750.f},1},
	{15.6f,{850.f,750.f},1},
	{15.6f,{1050.f,750.f},1},
	{15.6f,{1250.f,750.f},1},

	{16.2f,{750.f,750.f},1},
	{16.2f,{950.f,750.f},1},
	{16.2f,{1150.f,750.f},1},

	{16.8f,{650.f,750.f},1},
	{16.8f,{1250.f,750.f},1},

	{17.4f,{850.f,750.f},1},
	{17.4f,{1050.f,750.f},1},

	{18.0f,{750.f,750.f},1},
	{18.0f,{950.f,750.f},1},
	{18.0f,{1150.f,750.f},1},

	{18.6f,{650.f,750.f},1},
	{18.6f,{1250.f,750.f},1},

	{19.2f,{650.f,750.f},1},
	{19.2f,{750.f,750.f},1},
	{19.2f,{950.f,750.f},1},
	{19.2f,{1150.f,750.f},1},
	{19.2f,{1250.f,750.f},1},

	{19.8f,{850.f,750.f},1},
	{19.8f,{1050.f,750.f},1},

	{20.4f,{750.f,750.f},1},
	{20.4f,{950.f,750.f},1},
	{20.4f,{1150.f,750.f},1},

	{21.4f,{650.f,750.f},1},
	{21.4f,{1250.f,750.f},1},

	{22.4f,{750.f,750.f},1},
	{22.4f,{1150.f,750.f},1},

	{23.4f,{850.f,750.f},1},
	{23.4f,{1050.f,750.f},1},

	{24.4f,{650.f,750.f},1},
	{24.4f,{1250.f,750.f},1},

	{25.4f,{750.f,750.f},1},
	{25.4f,{1150.f,750.f},1},

	{26.4f,{850.f,750.f},1},
	{26.4f,{1050.f,750.f},1},

	{27.4f,{650.f,750.f},1},
	{27.4f,{1250.f,750.f},1},

	{28.4f,{750.f,750.f},1},
	{28.4f,{1150.f,750.f},1},

	{29.4f,{850.f,750.f},1},
	{29.4f,{1050.f,750.f},1},

	{30.4f,{650.f,750.f},1},
	{30.4f,{1250.f,750.f},1},

	{31.4f,{750.f,750.f},1},
	{31.4f,{1150.f,750.f},1},

	{32.4f,{850.f,750.f},1},
	{32.4f,{1050.f,750.f},1},

	{ 33.4f,{650.f,750.f},1 },
	{ 33.4f,{1250.f,750.f},1 },

	{ 34.4f,{750.f,750.f},1 },
	{ 34.4f,{1150.f,750.f},1 },

	{ 35.4f,{850.f,750.f},1 },
	{ 35.4f,{1050.f,750.f},1 },
};
std::vector<DATA> pattonTimes2 = {
	{5.0f,{950.f,750.f},1},

	{5.6f,{850.f,750.f},1},
	{5.6f,{1050.f,750.f},1},

	{6.2f,{750.f,750.f},1},
	{6.2f,{1150.f,750.f},1},

	{6.8f,{1250.f,750.f},1},
	{6.8f,{650.f,750.f},1},

	{7.4f,{950.f,750.f},0},

	{8.0f,{950.f,650.f},0},
	{8.0f,{1250.f,750.f},1},
	{8.0f,{650.f,750.f},1},

	{8.6f,{950.f,450.f},0},

	{9.2f,{750.f,750.f},1},
	{9.2f,{1150.f,750.f},1},

	{9.8f,{950.f,550.f},0},

	{10.4f,{850.f,750.f},1},
	{10.4f,{1050.f,750.f},1},

	{11.0f,{950.f,450.f},0},
	{11.6f,{950.f,750.f},1},

	{12.2f,{950.f,750.f},1},
	{12.2f,{650.f,750.f},1},
	{12.2f,{1250.f,750.f},1},

	{12.8f,{750.f,750.f},1},
	{12.8f,{850.f,750.f},1},
	{12.8f,{1050.f,750.f},1},
	{12.8f,{1150.f,750.f},1},

	{13.4f,{950.f,600.f},0},

	{14.0f,{650.f,750.f},1},
	{14.0f,{1250.f,750.f},1},

	{14.6f,{950.f,750.f},0},
	{14.6f,{950.f,450.f},0},
	{14.6f,{950.f,750.f},1},

	{14.6f,{1050.f,750.f},1},
	{14.6f,{850.f,750.f},1},

	{15.2f,{1250.f,750.f},1},
	{15.2f,{650.f,750.f},1},
	{15.2f,{950.f,450.f},0},

	{15.8f,{1150.f,750.f},1},
	{15.8f,{750.f,750.f},1},

	{16.4f,{950.f,550.f},0},	
	{16.4f,{950.f,750.f},1},

	{17.0f,{950.f,750.f},1},
	{17.0f,{1050.f,750.f},1},
	{17.0f,{850.f,750.f},1},

	{17.6f,{1050.f,750.f},1},
	{17.6f,{850.f,750.f},1},
	{17.6f,{950.f,750.f},1},
	{17.6f,{1150.f,750.f},1},
	{17.6f,{750.f,750.f},1},

	{18.2f,{1250.f,750.f},1},
	{18.2f,{650.f,750.f},1},

	{18.8f,{1250.f,750.f},1},
	{18.8f,{650.f,750.f},1},
	{18.8f,{1150.f,750.f},1},
	{18.8f,{750.f,750.f},1},

	//반복
	{19.4f,{650.f,750.f},1},
	{19.4f,{750.f,750.f},1},
	{19.4f,{950.f,450.f},0},

	{20.4f,{950.f,750.f},0},
	{20.4f,{950.f,450.f},0},

	{21.4f,{1250.f,750.f},1},
	{21.4f,{1150.f,750.f},1},
	{21.4f,{950.f,750.f},0},

	{22.4f,{1250.f,750.f},1},
	{22.4f,{650.f,750.f},1},

	{23.4f,{650.f,750.f},1},
	{23.4f,{750.f,750.f},1},
	{23.4f,{950.f,450.f},0},

	{24.4f,{950.f,750.f},0},
	{24.4f,{950.f,450.f},0},

	{25.4f,{1250.f,750.f},1},
	{25.4f,{1150.f,750.f},1},
	{25.4f,{950.f,750.f},0},

	{26.4f,{1250.f,750.f},1},
	{26.4f,{650.f,750.f},1},

	{ 27.4f,{650.f,750.f},1 },
	{ 27.4f,{750.f,750.f},1 },
	{ 27.4f,{950.f,450.f},0 },

	{ 28.4f,{950.f,750.f},0 },
	{ 28.4f,{950.f,450.f},0 },

	{ 29.4f,{1250.f,750.f},1 },
	{ 29.4f,{1150.f,750.f},1 },
	{ 29.4f,{950.f,750.f},0 },

	{ 30.4f,{1250.f,750.f},1 },
	{ 30.4f,{650.f,750.f},1 },

	{ 31.4f,{650.f,750.f},1 },
	{ 31.4f,{750.f,750.f},1 },
	{ 31.4f,{950.f,450.f},0 },

	{32.4f,{950.f,750.f},0 },
	{ 32.4f,{950.f,450.f},0 },

	{ 33.4f,{1250.f,750.f},1 },
	{ 33.4f,{1150.f,750.f},1 },
	{ 33.4f,{950.f,750.f},0 },

	{ 34.4f,{1250.f,750.f},1 },
	{ 34.4f,{650.f,750.f},1 },

	{ 35.4f,{650.f,750.f},1 },
	{ 35.4f,{750.f,750.f},1 },
	{ 35.4f,{950.f,450.f},0 },

	{ 36.4f,{950.f,750.f},0 },
	{ 36.4f,{950.f,450.f},0 },

	{ 37.4f,{1250.f,750.f},1 },
	{ 37.4f,{1150.f,750.f},1 },
	{ 37.4f,{950.f,750.f},0 },

	{ 38.4f,{1250.f,750.f},1 },
	{ 38.4f,{650.f,750.f},1 },

};
std::vector<DATA> pattonTimes3 = {
	{5.0f,{950.f,750.f},1},
	{5.0f,{950.f,650.f},0},

	{5.6f,{950.f,700.f},0},
	{5.6f,{950.f,450.f},0},
	{5.6f,{850.f,750.f},1},
	{5.6f,{1050.f,750.f},1},

	{6.6f,{950.f,750.f},0},
	{6.6f,{950.f,450.f},0},
	{6.6f,{650.f,750.f},1},
	{6.6f,{1250.f,750.f},1},

	{7.6f,{950.f,550.f},0},
	{7.6f,{650.f,750.f},1},
	{7.6f,{950.f,750.f},1},

	{8.6f,{950.f,650.f},0},
	{8.6f,{750.f,750.f},1},
	{8.6f,{1050.f,750.f},1},

	{9.6f,{950.f,450.f},0},
	{9.6f,{850.f,750.f},1},
	{9.6f,{1150.f,750.f},1},

	{10.6f,{950.f,750.f},1},
	{10.6f,{1250.f,750.f},1},
	{10.6f,{950.f,750.f},0},

	{11.6f,{1250.f,750.f},1},
	{11.6f,{650.f,750.f},1},

	{12.6f,{1150.f,750.f},1},
	{12.6f,{750.f,750.f},1},

	{13.6f,{1050.f,750.f},1},
	{13.6f,{850.f,750.f},1},

	{14.6f,{950.f,750.f},1},

	{15.6f,{1050.f,750.f},1},
	{15.6f,{850.f,750.f},1},

	{16.6f,{1150.f,750.f},1},
	{16.6f,{750.f,750.f},1},

	{17.6f,{1250.f,750.f},1},
	{17.6f,{650.f,750.f},1},

	{18.6f,{1150.f,750.f},1},
	{18.6f,{750.f,750.f},1},

	{19.6f,{1050.f,750.f},1},
	{19.6f,{850.f,750.f},1},

	{20.6f,{950.f,750.f},1},

	{21.6f,{950.f,750.f},0},
	{21.6f,{950.f,450.f},0},
	{21.6f,{650.f,750.f},1},
	{21.6f,{1250.f,750.f},1},

	{22.6f,{950.f,650.f},0},
	{22.6f,{950.f,350.f},0},
	{22.6f,{750.f,750.f},1},
	{22.6f,{1150.f,750.f},1},

	{23.6f,{950.f,750.f},1},
	{23.6f,{950.f,650.f},0},

	{24.6f,{950.f,750.f},0},
	{24.6f,{950.f,450.f},0},
	{24.6f,{850.f,750.f},1},
	{24.6f,{1050.f,750.f},1},

	{25.6f,{950.f,450.f},0},
	{25.6f,{950.f,650.f},0},
	{25.6f,{950.f,750.f},1},

	{26.6f,{950.f,750.f},1},
	{26.6f,{1050.f,750.f},1},
	{26.6f,{850.f,750.f},1},

	{27.6f,{950.f,750.f},0},
	{27.6f,{950.f,450.f},0},
	{27.6f,{650.f,750.f},1},
	{27.6f,{1250.f,750.f},1},

	{28.6f,{950.f,650.f},0},
	{28.6f,{650.f,750.f},1},
	{28.6f,{750.f,750.f},1},
	{28.6f,{1150.f,750.f},1},
	{28.6f,{1250.f,750.f},1},

	{29.6f,{650.f,750.f},1},
	{29.6f,{750.f,750.f},1},
	{29.6f,{850.f,750.f},1},
	{29.6f,{1050.f,750.f},1},
	{29.6f,{1150.f,750.f},1},
	{29.6f,{1250.f,750.f},1},

	//반복
	{ 30.6f,{650.f,750.f},1 },
	{ 30.6f,{1250.f,750.f},1 },

	{ 31.6f,{950.f,750.f},0},
	{ 31.6f,{950.f,450.f},0 },

	{ 32.6f,{750.f,750.f},1 },
	{ 32.6f,{1150.f,750.f},1 },
	{ 32.6f,{950.f,650.f},0 },
	{ 32.6f,{950.f,450.f},0 },

	{ 33.6f,{850.f,750.f},1 },
	{ 33.6f,{1050.f,750.f},1 },
	{ 33.6f,{950.f,450.f},0 },
	{ 33.6f,{950.f,750.f},0 },

	{ 34.6f,{650.f,750.f},1 },
	{ 34.6f,{1250.f,750.f},1 },

	{ 35.6f,{950.f,750.f},0 },
	{ 35.6f,{950.f,450.f},0 },

	{ 36.6f,{750.f,750.f},1 },
	{ 36.6f,{1150.f,750.f},1 },
	{ 36.6f,{950.f,750.f},0 },
	{ 36.6f,{950.f,450.f},0 },

	{ 37.6f,{850.f,750.f},1 },
	{ 37.6f,{1050.f,750.f},1 },
	{ 37.6f,{950.f,500.f},0 },
	{ 37.6f,{950.f,750.f},0 },

	{ 38.6f,{650.f,750.f},1 },
	{ 38.6f,{1250.f,750.f},1 },

	{ 39.6f,{950.f,750.f},0 },
	{ 39.6f,{950.f,450.f},0 },

	{ 40.6f,{750.f,750.f},1 },
	{ 40.6f,{1150.f,750.f},1 },
	{ 40.6f,{950.f,650.f},0 },
	{ 40.6f,{950.f,450.f},0 },

	{ 41.6f,{850.f,750.f},1 },
	{ 41.6f,{1050.f,750.f},1 },
	{ 41.6f,{950.f,500.f},0 },
	{ 41.6f,{950.f,750.f},0 },

	{ 42.6f,{650.f,750.f},1 },
	{ 42.6f,{1250.f,750.f},1 },

	{ 43.6f,{950.f,750.f},0 },
	{ 43.6f,{950.f,450.f},0 },

	{ 44.6f,{750.f,750.f},1 },
	{ 44.6f,{1150.f,750.f},1 },
	{ 44.6f,{950.f,700.f},0 },
	{ 44.6f,{950.f,450.f},0 },

	{ 45.6f,{850.f,750.f},1 },
	{ 45.6f,{1050.f,750.f},1 },
	{ 45.6f,{950.f,500.f},0 },
	{ 45.6f,{950.f,750.f},0 },

	{ 46.6f,{650.f,750.f},1 },
	{ 46.6f,{1250.f,750.f},1 },

	{ 47.6f,{950.f,750.f},0 },
	{ 47.6f,{950.f,450.f},0 },

	{ 48.6f,{750.f,750.f},1 },
	{ 48.6f,{1150.f,750.f},1 },
	{ 48.6f,{950.f,650.f},0 },
	{ 48.6f,{950.f,400.f},0 },

	{ 49.6f,{850.f,750.f},1 },
	{ 49.6f,{1050.f,750.f},1 },
	{ 49.6f,{950.f,500.f},0 },
	{ 49.6f,{950.f,750.f},0 },

	{ 50.6f,{650.f,750.f},1 },
	{ 50.6f,{1250.f,750.f},1 },

	{ 51.6f,{950.f,750.f},0 },
	{ 51.6f,{950.f,450.f},0 },

	{ 52.6f,{750.f,750.f},1 },
	{ 52.6f,{1150.f,750.f},1 },
	{ 52.6f,{950.f,650.f},0 },
	{ 52.6f,{950.f,400.f},0 },

	{ 53.6f,{850.f,750.f},1 },
	{ 53.6f,{1050.f,750.f},1 },
	{ 53.6f,{950.f,500.f},0 },
	{ 53.6f,{950.f,750.f},0 },

	{ 54.6f,{650.f,750.f},1 },
	{ 54.6f,{1250.f,750.f},1 },

	{ 55.6f,{950.f,750.f},0 },
	{ 55.6f,{950.f,450.f},0 },

	{ 56.6f,{750.f,750.f},1 },
	{ 56.6f,{1150.f,750.f},1 },
	{ 56.6f,{950.f,650.f},0 },
	{ 56.6f,{950.f,450.f},0 },

	{ 57.6f,{850.f,750.f},1 },
	{ 57.6f,{1050.f,750.f},1 },
	{ 57.6f,{950.f,500.f},0 },
	{ 57.6f,{950.f,750.f},0 },

	{ 58.6f,{650.f,750.f},1 },
	{ 58.6f,{1250.f,750.f},1 },

	{ 59.6f,{950.f,750.f},0 },
	{ 59.6f,{950.f,450.f},0 },

	{ 60.6f,{750.f,750.f},1 },
	{ 60.6f,{1150.f,750.f},1 },
	{ 60.6f,{950.f,650.f},0 },
	{ 60.6f,{950.f,400.f},0 },

	{ 61.6f,{850.f,750.f},1 },
	{ 61.6f,{1050.f,750.f},1 },
	{ 61.6f,{950.f,500.f},0 },
	{ 61.6f,{950.f,750.f},0 },

	{ 62.6f,{650.f,750.f},1 },
	{ 62.6f,{1250.f,750.f},1 },

	{ 63.6f,{950.f,750.f},0 },
	{ 63.6f,{950.f,450.f},0 },

	{ 64.6f,{750.f,750.f},1 },
	{ 64.6f,{1150.f,750.f},1 },
	{ 64.6f,{950.f,650.f},0 },
	{ 64.6f,{950.f,400.f},0 },

	{ 65.6f,{850.f,750.f},1 },
	{ 65.6f,{1050.f,750.f},1 },
	{ 65.6f,{950.f,500.f},0 },
	{ 65.6f,{950.f,750.f},0 },

	{ 66.6f,{650.f,750.f},1 },
	{ 66.6f,{1250.f,750.f},1 },

	{ 67.6f,{950.f,750.f},0 },
	{ 67.6f,{950.f,450.f},0 },

	{ 68.6f,{750.f,750.f},1 },
	{ 68.6f,{1150.f,750.f},1 },
	{ 68.6f,{950.f,650.f},0 },
	{ 68.6f,{950.f,450.f},0 },

	{ 69.6f,{850.f,750.f},1 },
	{ 69.6f,{1050.f,750.f},1 },
	{ 69.6f,{950.f,500.f},0 },
	{ 69.6f,{950.f,750.f},0 },

};

//std::vector<DATA> pattonTimes3 = {
//	{5.0f,{950.f,750.f},1},
//	{5.0f,{950.f,650.f},0},
//
//	{5.6f,{950.f,650.f},0},
//	{5.6f,{950.f,450.f},0},
//	{5.6f,{850.f,750.f},1},
//	{5.6f,{1050.f,750.f},1},
//
//	{6.2f,{950.f,750.f},0},
//	{6.2f,{950.f,450.f},0},
//	{6.2f,{650.f,750.f},1},
//	{6.2f,{1250.f,750.f},1},
//
//	{6.8f,{950.f,550.f},0},
//	{6.8f,{650.f,750.f},1},
//	{6.8f,{950.f,750.f},1},
//
//	{7.4f,{950.f,650.f},0},
//	{7.4f,{750.f,750.f},1},
//	{7.4f,{1050.f,750.f},1},
//
//	{8.0f,{950.f,450.f},0},
//	{8.0f,{850.f,750.f},1},
//	{8.0f,{1150.f,750.f},1},
//
//	{8.6f,{950.f,750.f},1},
//	{8.6f,{1250.f,750.f},1},
//	{8.6f,{950.f,750.f},0},
//
//	{9.6f,{1250.f,750.f},1},
//	{9.6f,{650.f,750.f},1},
//
//	{10.2f,{1150.f,750.f},1},
//	{10.2f,{750.f,750.f},1},
//
//	{10.8f,{1050.f,750.f},1},
//	{10.8f,{850.f,750.f},1},
//
//	{11.4f,{950.f,750.f},1},
//
//	{12.0f,{1050.f,750.f},1},
//	{12.0f,{850.f,750.f},1},
//
//	{12.6f,{1150.f,750.f},1},
//	{12.6f,{750.f,750.f},1},
//
//	{13.2f,{1250.f,750.f},1},
//	{13.2f,{650.f,750.f},1},
//
//	{13.8f,{1150.f,750.f},1},
//	{13.8f,{750.f,750.f},1},
//
//	{14.4f,{1050.f,750.f},1},
//	{14.4f,{850.f,750.f},1},
//
//	{15.0f,{950.f,750.f},1},
//
//	{15.6f,{950.f,750.f},0},
//	{15.6f,{950.f,450.f},0},
//	{15.6f,{650.f,750.f},1},
//	{15.6f,{1250.f,750.f},1},
//
//	{16.2f,{950.f,650.f},0},
//	{16.2f,{950.f,450.f},0},
//	{16.2f,{750.f,750.f},1},
//	{16.2f,{1150.f,750.f},1},
//
//	{16.8f,{950.f,750.f},1},
//	{16.8f,{950.f,650.f},0},
//
//	{17.4f,{950.f,750.f},0},
//	{17.4f,{950.f,450.f},0},
//	{17.4f,{850.f,750.f},1},
//	{17.4f,{1050.f,750.f},1},
//
//	{18.0f,{950.f,450.f},0},
//	{18.0f,{950.f,650.f},0},
//	{18.0f,{950.f,750.f},1},
//
//	{18.6f,{950.f,750.f},1},
//	{18.6f,{1050.f,750.f},1},
//	{18.6f,{850.f,750.f},1},
//
//	{19.2f,{950.f,750.f},0},
//	{19.2f,{950.f,450.f},0},
//	{19.2f,{650.f,750.f},1},
//	{19.2f,{1250.f,750.f},1},
//
//	{19.8f,{950.f,650.f},0},
//	{19.8f,{650.f,750.f},1},
//	{19.8f,{750.f,750.f},1},
//	{19.8f,{1150.f,750.f},1},
//	{19.8f,{1250.f,750.f},1},
//
//	{20.4f,{650.f,750.f},1},
//	{20.4f,{750.f,750.f},1},
//	{20.4f,{850.f,750.f},1},
//	{20.4f,{1050.f,750.f},1},
//	{20.4f,{1150.f,750.f},1},
//	{20.4f,{1250.f,750.f},1},
//
//	//반복
//	{ 21.0f,{650.f,750.f},1 },
//	{ 21.0f,{1250.f,750.f},1 },
//
//	{ 22.0f,{950.f,750.f},0},
//	{ 22.0f,{950.f,450.f},0 },
//
//	{ 23.0f,{750.f,750.f},1 },
//	{ 23.0f,{1150.f,750.f},1 },
//	{ 23.0f,{950.f,650.f},0 },
//	{ 23.0f,{950.f,450.f},0 },
//
//	{ 24.0f,{850.f,750.f},1 },
//	{ 24.0f,{1050.f,750.f},1 },
//	{ 24.0f,{950.f,550.f},0 },
//	{ 24.0f,{950.f,750.f},0 },
//
//	{ 25.0f,{650.f,750.f},1 },
//	{ 25.0f,{1250.f,750.f},1 },
//
//	{ 26.0f,{950.f,750.f},0 },
//	{ 26.0f,{950.f,450.f},0 },
//
//	{ 27.0f,{750.f,750.f},1 },
//	{ 27.0f,{1150.f,750.f},1 },
//	{ 27.0f,{950.f,650.f},0 },
//	{ 27.0f,{950.f,450.f},0 },
//
//	{ 28.0f,{850.f,750.f},1 },
//	{ 28.0f,{1050.f,750.f},1 },
//	{ 28.0f,{950.f,550.f},0 },
//	{ 28.0f,{950.f,750.f},0 },
//
//	{ 29.0f,{650.f,750.f},1 },
//	{ 29.0f,{1250.f,750.f},1 },
//
//	{ 30.0f,{950.f,750.f},0 },
//	{ 30.0f,{950.f,450.f},0 },
//
//	{ 31.0f,{750.f,750.f},1 },
//	{ 31.0f,{1150.f,750.f},1 },
//	{ 31.0f,{950.f,650.f},0 },
//	{ 31.0f,{950.f,450.f},0 },
//
//	{ 32.0f,{850.f,750.f},1 },
//	{ 32.0f,{1050.f,750.f},1 },
//	{ 32.0f,{950.f,550.f},0 },
//	{ 32.0f,{950.f,750.f},0 },
//
//	{ 33.0f,{650.f,750.f},1 },
//	{ 33.0f,{1250.f,750.f},1 },
//
//	{ 34.0f,{950.f,750.f},0 },
//	{ 34.0f,{950.f,450.f},0 },
//
//	{ 35.0f,{750.f,750.f},1 },
//	{ 35.0f,{1150.f,750.f},1 },
//	{ 35.0f,{950.f,650.f},0 },
//	{ 35.0f,{950.f,450.f},0 },
//
//	{ 36.0f,{850.f,750.f},1 },
//	{ 36.0f,{1050.f,750.f},1 },
//	{ 36.0f,{950.f,550.f},0 },
//	{ 36.0f,{950.f,750.f},0 },
//
//	{ 37.0f,{650.f,750.f},1 },
//	{ 37.0f,{1250.f,750.f},1 },
//
//	{ 38.0f,{950.f,750.f},0 },
//	{ 38.0f,{950.f,450.f},0 },
//
//	{ 39.0f,{750.f,750.f},1 },
//	{ 39.0f,{1150.f,750.f},1 },
//	{ 39.0f,{950.f,650.f},0 },
//	{ 39.0f,{950.f,450.f},0 },
//
//	{ 40.0f,{850.f,750.f},1 },
//	{ 40.0f,{1050.f,750.f},1 },
//	{ 40.0f,{950.f,550.f},0 },
//	{ 40.0f,{950.f,750.f},0 },
//
//	{ 41.0f,{650.f,750.f},1 },
//	{ 41.0f,{1250.f,750.f},1 },
//
//	{ 42.0f,{950.f,750.f},0 },
//	{ 42.0f,{950.f,450.f},0 },
//
//	{ 43.0f,{750.f,750.f},1 },
//	{ 43.0f,{1150.f,750.f},1 },
//	{ 43.0f,{950.f,650.f},0 },
//	{ 43.0f,{950.f,450.f},0 },
//
//	{ 44.0f,{850.f,750.f},1 },
//	{ 44.0f,{1050.f,750.f},1 },
//	{ 44.0f,{950.f,550.f},0 },
//	{ 44.0f,{950.f,750.f},0 },
//
//	{ 45.0f,{650.f,750.f},1 },
//	{ 45.0f,{1250.f,750.f},1 },
//
//	{ 46.0f,{950.f,750.f},0 },
//	{ 46.0f,{950.f,450.f},0 },
//
//	{ 47.0f,{750.f,750.f},1 },
//	{ 47.0f,{1150.f,750.f},1 },
//	{ 48.0f,{950.f,650.f},0 },
//	{ 48.0f,{950.f,450.f},0 },
//
//	{ 49.0f,{850.f,750.f},1 },
//	{ 49.0f,{1050.f,750.f},1 },
//	{ 49.0f,{950.f,550.f},0 },
//	{ 49.0f,{950.f,750.f},0 },
//
//	{ 50.0f,{650.f,750.f},1 },
//	{ 50.0f,{1250.f,750.f},1 },
//
//	{ 51.0f,{950.f,750.f},0 },
//	{ 51.0f,{950.f,450.f},0 },
//
//	{ 52.0f,{750.f,750.f},1 },
//	{ 52.0f,{1150.f,750.f},1 },
//	{ 52.0f,{950.f,650.f},0 },
//	{ 52.0f,{950.f,450.f},0 },
//
//	{ 53.0f,{850.f,750.f},1 },
//	{ 53.0f,{1050.f,750.f},1 },
//	{ 53.0f,{950.f,550.f},0 },
//	{ 53.0f,{950.f,750.f},0 },
//
//	{ 54.0f,{650.f,750.f},1 },
//	{ 54.0f,{1250.f,750.f},1 },
//
//	{ 55.0f,{950.f,750.f},0 },
//	{ 55.0f,{950.f,450.f},0 },
//
//	{ 56.0f,{750.f,750.f},1 },
//	{ 56.0f,{1150.f,750.f},1 },
//	{ 56.0f,{950.f,650.f},0 },
//	{ 56.0f,{950.f,450.f},0 },
//
//	{ 57.0f,{850.f,750.f},1 },
//	{ 57.0f,{1050.f,750.f},1 },
//	{ 57.0f,{950.f,550.f},0 },
//	{ 57.0f,{950.f,750.f},0 },
//
//	{ 58.0f,{650.f,750.f},1 },
//	{ 58.0f,{1250.f,750.f},1 },
//
//	{ 59.0f,{950.f,750.f},0 },
//	{ 59.0f,{950.f,450.f},0 },
//
//	{ 60.0f,{750.f,750.f},1 },
//	{ 60.0f,{1150.f,750.f},1 },
//	{ 60.0f,{950.f,650.f},0 },
//	{ 60.0f,{950.f,450.f},0 },
//
//	{ 61.0f,{850.f,750.f},1 },
//	{ 61.0f,{1050.f,750.f},1 },
//	{ 61.0f,{950.f,550.f},0 },
//	{ 61.0f,{950.f,750.f},0 },
//
//};

bool checkPatton[100] = { false };
int curPattonIndex = 0;
void CPlayer::DEFAULT_LOGIC()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	Vec2 CurPos = GetPos();

	m_Target = nullptr;
	m_Target_Thorn = nullptr;

	FlipBookMGR();
	
	if (PLAYER_MOVING_CHECK) {
		Moving_CurPos = GetPos();
		//현재위치가 아직 목표위치에 도달하지 않았을때
		if (Move_Direction == D_LEFT) {
			if (MoveDistance < 100.f ) {
				Moving_CurPos.x -= Moving_TickPos;
				MoveDistance += Moving_TickPos;
				SetPos(Moving_CurPos);

			}
			if (MoveDistance == 100.f) {
				PLAYER_MOVING_CHECK = false;
				MoveDistance = 0.f;
			}
		}
		else if (Move_Direction == D_RIGHT) {
			if (MoveDistance < 100.f) {

				Moving_CurPos.x += Moving_TickPos;
				MoveDistance += Moving_TickPos;
				SetPos(Moving_CurPos);

			}
			if (MoveDistance == 100.f) {
				PLAYER_MOVING_CHECK = false;
				MoveDistance = 0.f;
			}
		}
		else if (Move_Direction == D_UP) {
			if (MoveDistance < 100.f) {

				Moving_CurPos.y -= Moving_TickPos;
				MoveDistance += Moving_TickPos;
				SetPos(Moving_CurPos);

			}
			if (MoveDistance == 100.f) {
				PLAYER_MOVING_CHECK = false;
				MoveDistance = 0.f;
			}
		}
		else if (Move_Direction == D_DOWN) {
			if (MoveDistance < 100.f) {

				Moving_CurPos.y += Moving_TickPos;
				MoveDistance += Moving_TickPos;
				SetPos(Moving_CurPos);

			}
			if (MoveDistance == 100.f) {
				PLAYER_MOVING_CHECK = false;
				MoveDistance = 0.f;
				Vec2 CurPos = GetPos();
				int a = 0;
			}
		}
	}
	if (!PLAYER_MOVING_CHECK) {
		if (KEY_TAP(LEFT))
		{
			PLAYER_COLLISION_CHECK = true;
			CurPos.x -= 100.f;
			Move_Direction = D_LEFT;
		}
		if (KEY_TAP(RIGHT))
		{
			PLAYER_COLLISION_CHECK = true;
			CurPos.x += 100.f;
			Move_Direction = D_RIGHT;
		}
		if (KEY_TAP(UP))
		{
			PLAYER_COLLISION_CHECK = true;
			CurPos.y -= 100.f;
			Move_Direction = D_UP;
		}
		if (KEY_TAP(DOWN))
		{
			PLAYER_COLLISION_CHECK = true;
			CurPos.y += 100.f;
			Move_Direction = D_DOWN;
		}
	}

	if (KEY_TAP(R))
	{
		Die = false;

		CRestartCutScene* pResetCutScene = new CRestartCutScene;
		CreateObject(pResetCutScene, LAYER_TYPE::CUTSCENE);

		SetPos(GetStartPos());
		ResetObject();

		BreakChainSummon0 = false;
		//TalkPartCheck = true;
		bossStartSound = false;
		CurCutSceneIndex = 0;
		CurTime = 0.f;
		SkulMoveDistance = 0.f;
		PistonMoveDistance = 0.f;
		CheckStartPiston = false;
		CheckStartSkul = false;
		CheckStartBridge = false;
		CheckEndPiston = false;
		CheckEndSkul = false;
		bossEndSound = false;
		SpawnJudmentThorn = false;
		curPattonIndex = 0;
		memset(checkPatton, false, sizeof(checkPatton));
	}

	if (Die || JudmentPlayerHealth <= 0) {

		PlayerDie();
		ResetObject();
	}

	//보스전이 아닐경우
	if (CurLevel != BOSS_0) {
		if (PLAYER_COLLISION_CHECK) {

			PlayerMove = false;
			//uncheckDemon = false;

			if (CurLevel != STAGE_1 && CurLevel != STAGE_2 && CurLevel != STAGE_3) {
				const vector<CObj*>& vecTHORN = pCurLevel->GetObjects(LAYER_TYPE::THORN);
				for (int i = 0; i < vecTHORN.size(); i++) {
					CThorn* pThorn = dynamic_cast<CThorn*>(vecTHORN[i]);
					pThorn->ChangePlayerMove();
				}
			}

			if (PlayerMove_Count > 0) {
				PlayerMove_Count--;
			}
			else if (PlayerMove_Count <= 0) {
				Die = true;
			}
			const vector<CObj*>& vecMon = pCurLevel->GetObjects(LAYER_TYPE::MONSTER);
			const vector<CObj*>& vecRock = pCurLevel->GetObjects(LAYER_TYPE::Rock);
			const vector<CObj*>& vecWall = pCurLevel->GetObjects(LAYER_TYPE::WALL);
			const vector<CObj*>& vecThorn = pCurLevel->GetObjects(LAYER_TYPE::THORN);
			const vector<CObj*>& vecKeyBox = pCurLevel->GetObjects(LAYER_TYPE::KEYBOX);

			// 본인과 가장 가까운 대상(돌, 몬스터)를 타겟으로 지정한다.
			Vec2 vPos = CurPos;
			int a = 0;
			float MinDistance = m_DetectRange;

			if (m_Target == nullptr) {
				for (size_t i = 0; i < vecKeyBox.size(); ++i)
				{

					Vec2 vMonPos = vecKeyBox[i]->GetPos(); // 몬스터의 위치

					Vec2 a = vPos;
					Vec2 b = vMonPos;

					float Dist = (vPos - vMonPos).Length();

					// 최소거리가 갱신된 경우
					if (Dist < MinDistance)
					{
						MinDistance = Dist;
						m_Target = vecKeyBox[i];
					}
				}
			}

			if (m_Target == nullptr) {
				for (size_t i = 0; i < vecMon.size(); ++i)
				{
					if (vecMon[i]->IsDead())
						continue;

					Vec2 vMonPos = vecMon[i]->GetPos(); // 몬스터의 위치

					Vec2 a = vPos;
					Vec2 b = vMonPos;

					float Dist = (vPos - vMonPos).Length();

					// 최소거리가 갱신된 경우
					if (Dist < MinDistance)
					{
						MinDistance = Dist;
						m_Target = vecMon[i];
					}
				}
			}

			if (m_Target == nullptr) {
				for (size_t i = 0; i < vecWall.size(); ++i)
				{

					Vec2 vMonPos = vecWall[i]->GetPos(); // 몬스터의 위치

					Vec2 a = vPos;
					Vec2 b = vMonPos;

					float Dist = (vPos - vMonPos).Length();

					// 최소거리가 갱신된 경우
					if (Dist < MinDistance)
					{
						MinDistance = Dist;
						m_Target = vecWall[i];
					}
				}
			}

			if (m_Target == nullptr) {
				for (size_t i = 0; i < vecRock.size(); ++i)
				{

					Vec2 vMonPos = vecRock[i]->GetPos(); // 몬스터의 위치
					float Dist = (vPos - vMonPos).Length();

					// 최소거리가 갱신된 경우
					if (Dist < MinDistance)
					{
						MinDistance = Dist;
						m_Target = vecRock[i];
					}
				}
			}

			for (size_t i = 0; i < vecThorn.size(); ++i)
			{

				Vec2 vMonPos = vecThorn[i]->GetPos(); // 몬스터의 위치
				//가만히에서 가시가 돋아날 경우
				CThorn* th = dynamic_cast<CThorn*>(vecThorn[i]);
				//지금 잘못된게 가시를 찾을 수 없는건 맞아 왜냐하면 가시의 위치가 플레이어가 이동할 곳에 없으니까
				//그래서 m_Target_Thorn에 들어왔는데 CheckStatThorn은 현재 같은 위치에 가시가 있는지 검사하는 거임
				//그래서 이동하고있는 플레이어와 가시는 같은 위치, 그래서 걸리는거
				//그럼 지금 플레이어가 이동하고 있다는걸 알고 있으면 걸리면 안됨
				float Dist = (vPos - vMonPos).Length();

				// 최소거리가 갱신된 경우
				if (Dist < MinDistance)
				{
					MinDistance = Dist;
					m_Target_Thorn = vecThorn[i];
				}
			}

			//m_Target이 몬스터, 돌을 거쳐서 가장 가까운 위치에 있는 것임

			//부딪힌 타겟이 없거나 Keybox가 존재할 경우
			if (m_Target == nullptr) {

				//VFX_KICK_RENDER 초기화함
				//VFX_KICK_RENDER = false;
				PlayerMove = true;

				//이동 할 수 있으니 현재 위치에서 MoveVFX 실행 가능
				UsePlayerMoveVFXFlipbook();

				//다음 위치에 가시가 돋아날 경우 데미지 
				IFNextPointUpThorn();

				//좌표 기반 이동 실행
				if (!Die) {
					MoveLogic();
				}
			}
			else {
				LAYER_TYPE m_Target_LayerType = m_Target->GetLayerType();

				//다음이 상자인데 키를 가지고 있으면 타겟이 있더라도 움직일 수 있음
				if (m_Target_LayerType == LAYER_TYPE::KEYBOX && KeyBox_Key) {
					MoveLogic();
				}
				else {
					//이동 할 수 없고 상자도 아닌 것들에 대한 로직 실행
					Check_In_Place_Motion(m_Target_LayerType);
				}
			}
		IFINPLACETHORNUP(vecThorn);
		PLAYER_COLLISION_CHECK = false;
		}
			//PlayerMove
	}
	//보스전일 경우
	else {

		if (JudmentPlayerHealth < 4) {
			if (JudmentPlayerHealth == 3) {
				const vector<CObj*>& vecBridge = pCurLevel->GetObjects(LAYER_TYPE::FIRE);
				for (int i = 0; i < vecBridge.size(); i++) {
					CFire* cf = dynamic_cast<CFire*>(vecBridge[i]);
					if (cf->num == 0) {
						cf->use = false;
					}
				}
			}
			if (JudmentPlayerHealth == 2) {
				const vector<CObj*>& vecBridge = pCurLevel->GetObjects(LAYER_TYPE::FIRE);
				for (int i = 0; i < vecBridge.size(); i++) {
					CFire* cf = dynamic_cast<CFire*>(vecBridge[i]);
					if (cf->num == 1) {
						cf->use = false;
					}
				}
			}
			if (JudmentPlayerHealth == 1) {
				const vector<CObj*>& vecBridge = pCurLevel->GetObjects(LAYER_TYPE::FIRE);
				for (int i = 0; i < vecBridge.size(); i++) {
					CFire* cf = dynamic_cast<CFire*>(vecBridge[i]);
					if (cf->num == 2) {
						cf->use = false;
					}
				}
			}
		}
		
		if (!MoveBridgePattonDone && !JudmentClear) {
			CurTime += DT;
			if (2.f < CurTime && !CheckStartPiston) {
				StartPiston(pCurLevel);
				if (!bossStartSound) {
					bossStartSound = true;
					boss_machine_start->Play();
				}
			}
			else if (2.7f < CurTime && !CheckStartSkul) {
				MoveSkul(pCurLevel);
			}
			else if (3.f < CurTime && !CheckStartBridge) {
				CheckStartBridge = true;
				const vector<CObj*>& vecBridge = pCurLevel->GetObjects(LAYER_TYPE::BRIDGE);

				for (int i = 0; i < vecBridge.size(); i++) {
					CBridge* jud = dynamic_cast<CBridge*>(vecBridge[i]);
					jud->MoveBirdge = true;
				}
				PistonMoveDistance = 0.f;
				SkulMoveDistance = 0.f;

			}
			//1페이즈
			if (TalkCutSceneIndex == 1) {
				for (size_t i = 0; i < pattonTimes.size(); ++i) {
					if (curPattonIndex == i && CurTime >= pattonTimes[i].PattonTimes && !checkPatton[i]) {
						// pDamageChain 객체 생성 및 초기화
						pDamageChain = new CDamageChain;
						pDamageChain->SetPos(pattonTimes[i].ChainPos);
						pDamageChain->SetScale(100.f, 100.f);
						pDamageChain->Chaindir = pattonTimes[i].ChainDir;
						pDamageChain->SelectChainBlick = ChainSound;
						CreateObject(pDamageChain, LAYER_TYPE::DAMAGE_CHAIN);
						UpIndex = true;
						// Patton 체크 및 인덱스 증가
					}
				}

				if (21.f < CurTime && !BreakChainSummon0) {
					BreakChainSummon0 = true;

					//CBrakeChain* Bch1 = new CBrakeChain;
					//Bch1->SetPos(550.f, 450.f);
					//Bch1->SetOffset(-102.f, -420.f);
					//Bch1->SetScale(100.f, 100.f);
					//Bch1->dir = 0;
					//CreateObject(Bch1, LAYER_TYPE::BROKE_CHAIN);

					CBrakeChain* Bch = new CBrakeChain;
					Bch->SetPos(550.f, 750.f);
					Bch->SetOffset(-102.f, -393.f);
					Bch->SetScale(100.f, 130.f);
					Bch->dir = 0;
					CreateObject(Bch, LAYER_TYPE::BROKE_CHAIN);

					CBrakeChain* Bch2 = new CBrakeChain;
					Bch2->SetPos(1350.f, 450.f);
					Bch2->SetOffset(90.f, -420.f);
					Bch2->SetScale(100.f, -420.f);
					Bch2->dir = 1;
					CreateObject(Bch2, LAYER_TYPE::BROKE_CHAIN);

					//CBrakeChain* Bch3 = new CBrakeChain;
					//Bch3->SetPos(1350.f, 750.f);
					//Bch3->SetOffset(90.f, -393.f);
					//Bch3->SetScale(100.f, 100.f);
					//Bch3->dir = 1;
					//CreateObject(Bch3, LAYER_TYPE::BROKE_CHAIN);

				}
			}

			if (TalkCutSceneIndex == 2) {
				for (size_t i = 0; i < pattonTimes1.size(); ++i) {
					if (curPattonIndex == i && CurTime >= pattonTimes1[i].PattonTimes && !checkPatton[i]) {
						// pDamageChain 객체 생성 및 초기화
						pDamageChain = new CDamageChain;
						pDamageChain->SetPos(pattonTimes1[i].ChainPos);
						pDamageChain->SetScale(100.f, 100.f);
						pDamageChain->Chaindir = pattonTimes1[i].ChainDir;
						pDamageChain->SelectChainBlick = ChainSound;
						CreateObject(pDamageChain, LAYER_TYPE::DAMAGE_CHAIN);
						UpIndex = true;
						// Patton 체크 및 인덱스 증가
					}
				}
				if (21.f < CurTime && !BreakChainSummon0) {
					BreakChainSummon0 = true;

					//CBrakeChain* Bch1 = new CBrakeChain;
					//Bch1->SetPos(550.f, 450.f);
					//Bch1->SetOffset(-102.f, -420.f);
					//Bch1->SetScale(100.f, 100.f);
					//Bch1->dir = 0;
					//CreateObject(Bch1, LAYER_TYPE::BROKE_CHAIN);

					CBrakeChain* Bch = new CBrakeChain;
					Bch->SetPos(550.f, 750.f);
					Bch->SetOffset(-102.f, -393.f);
					Bch->SetScale(100.f, 130.f);
					Bch->dir = 0;
					CreateObject(Bch, LAYER_TYPE::BROKE_CHAIN);

					CBrakeChain* Bch2 = new CBrakeChain;
					Bch2->SetPos(1350.f, 450.f);
					Bch2->SetOffset(90.f, -420.f);
					Bch2->SetScale(100.f, -420.f);
					Bch2->dir = 1;
					CreateObject(Bch2, LAYER_TYPE::BROKE_CHAIN);

					//CBrakeChain* Bch3 = new CBrakeChain;
					//Bch3->SetPos(1350.f, 750.f);
					//Bch3->SetOffset(90.f, -393.f);
					//Bch3->SetScale(100.f, 100.f);
					//Bch3->dir = 1;
					//CreateObject(Bch3, LAYER_TYPE::BROKE_CHAIN);

				}
			}

			if (TalkCutSceneIndex == 3) {
				for (size_t i = 0; i < pattonTimes2.size(); ++i) {
					if (curPattonIndex == i && CurTime >= pattonTimes2[i].PattonTimes && !checkPatton[i]) {
						// pDamageChain 객체 생성 및 초기화
						pDamageChain = new CDamageChain;
						pDamageChain->SetPos(pattonTimes2[i].ChainPos);
						pDamageChain->SetScale(100.f, 100.f);
						pDamageChain->Chaindir = pattonTimes2[i].ChainDir;
						pDamageChain->SelectChainBlick = ChainSound;
						CreateObject(pDamageChain, LAYER_TYPE::DAMAGE_CHAIN);
						UpIndex = true;
						// Patton 체크 및 인덱스 증가
					}
				}
				if (21.f < CurTime && !BreakChainSummon0) {
					BreakChainSummon0 = true;

					CBrakeChain* Bch1 = new CBrakeChain;
					Bch1->SetPos(550.f, 450.f);
					Bch1->SetOffset(-102.f, -420.f);
					Bch1->SetScale(100.f, 100.f);
					Bch1->dir = 0;
					CreateObject(Bch1, LAYER_TYPE::BROKE_CHAIN);

					//CBrakeChain* Bch = new CBrakeChain;
					//Bch->SetPos(550.f, 750.f);
					//Bch->SetOffset(-102.f, -393.f);
					//Bch->SetScale(100.f, 130.f);
					//Bch->dir = 0;
					//CreateObject(Bch, LAYER_TYPE::BROKE_CHAIN);

					//CBrakeChain* Bch2 = new CBrakeChain;
					//Bch2->SetPos(1350.f, 450.f);
					//Bch2->SetOffset(90.f, -420.f);
					//Bch2->SetScale(100.f, -420.f);
					//Bch2->dir = 1;
					//CreateObject(Bch2, LAYER_TYPE::BROKE_CHAIN);

					CBrakeChain* Bch3 = new CBrakeChain;
					Bch3->SetPos(1350.f, 750.f);
					Bch3->SetOffset(90.f, -393.f);
					Bch3->SetScale(100.f, 100.f);
					Bch3->dir = 1;
					CreateObject(Bch3, LAYER_TYPE::BROKE_CHAIN);

				}
			}

			if (TalkCutSceneIndex == 4) {
				for (size_t i = 0; i < pattonTimes3.size(); ++i) {
					if (curPattonIndex == i && CurTime >= pattonTimes3[i].PattonTimes && !checkPatton[i]) {
						// pDamageChain 객체 생성 및 초기화
						pDamageChain = new CDamageChain;
						pDamageChain->SetPos(pattonTimes3[i].ChainPos);
						pDamageChain->SetScale(100.f, 100.f);
						pDamageChain->Chaindir = pattonTimes3[i].ChainDir;
						pDamageChain->SelectChainBlick = ChainSound;
						CreateObject(pDamageChain, LAYER_TYPE::DAMAGE_CHAIN);
						UpIndex = true;
						// Patton 체크 및 인덱스 증가
					}
				}
				if (21.f < CurTime && !BreakChainSummon0) {
					BreakChainSummon0 = true;

					CBrakeChain* Bch1 = new CBrakeChain;
					Bch1->SetPos(550.f, 450.f);
					Bch1->SetOffset(-102.f, -420.f);
					Bch1->SetScale(100.f, 100.f);
					Bch1->dir = 0;
					CreateObject(Bch1, LAYER_TYPE::BROKE_CHAIN);

					CBrakeChain* Bch = new CBrakeChain;
					Bch->SetPos(550.f, 750.f);
					Bch->SetOffset(-102.f, -393.f);
					Bch->SetScale(100.f, 130.f);
					Bch->dir = 0;
					CreateObject(Bch, LAYER_TYPE::BROKE_CHAIN);

					CBrakeChain* Bch2 = new CBrakeChain;
					Bch2->SetPos(1350.f, 450.f);
					Bch2->SetOffset(90.f, -420.f);
					Bch2->SetScale(100.f, -420.f);
					Bch2->dir = 1;
					CreateObject(Bch2, LAYER_TYPE::BROKE_CHAIN);

					CBrakeChain* Bch3 = new CBrakeChain;
					Bch3->SetPos(1350.f, 750.f);
					Bch3->SetOffset(90.f, -393.f);
					Bch3->SetScale(100.f, 100.f);
					Bch3->dir = 1;
					CreateObject(Bch3, LAYER_TYPE::BROKE_CHAIN);

				}
			}

			if (20.f < CurTime && !CheckEndPiston) {
				if (!bossEndSound) {
					bossEndSound = true;
					boss_machine_end->Play();
				}

				InplacePiston(pCurLevel);

			}
			if (20.5f < CurTime && !CheckEndSkul) {
				InplaceSkul(pCurLevel);
			}

			if (24.f < CurTime && BreakChainSummon0) {
				const vector<CObj*>& vecDamageChain = pCurLevel->GetObjects(LAYER_TYPE::BROKE_CHAIN);
				if (vecDamageChain.size() == 0 && TalkCutSceneIndex == 4){

					CDemon* pDemon = new CDemon;
					pDemon->SetPos(1920 / 2.f - 10.f, 130.f);
					pDemon->SetDemon(JUDGMENT);
					pDemon->SetScale(100.f, 100.f);
					CreateObject(pDemon, LAYER_TYPE::DEMON);

					//TalkCutSceneIndex += 1;
					BreakChainSummon0 = false;
					TalkPartCheck = true;
					Dialogue_start->Play();
					bossStartSound = false;
					CurCutSceneIndex = 0;
					CurTime = 0.f;
					SkulMoveDistance = 0.f;
					PistonMoveDistance = 0.f;
					CheckStartPiston = false;
					CheckStartSkul = false;
					CheckStartBridge = false;
					CheckEndPiston = false;
					CheckEndSkul = false;
					bossEndSound = false;
					SpawnJudmentThorn = false;
					curPattonIndex = 0;
					memset(checkPatton, false, sizeof(checkPatton));

				}
				else if(vecDamageChain.size() == 0){
					if (TalkCutSceneIndex == 1) {
						if (!JudmentJump) {
							m_FlipbookJudmentJump->Play(judgement_jump, 15.f, false);
							boss_judgement_land_01->Play();
							JudmentJump = true;
							CCamera::GetInst()->Oscillation(0.2, 15, 15);
						}
						if (m_FlipbookJudmentJump->IsFinish()) {
							JudmentJumpTime += DT;
							if (JudmentJumpTime >= 1.f) {
								BreakChainSummon0 = false;
								TalkPartCheck = true;
								Dialogue_start->Play();
								bossStartSound = false;
								CurCutSceneIndex = 0;
								CurTime = 0.f;
								SkulMoveDistance = 0.f;
								PistonMoveDistance = 0.f;
								CheckStartPiston = false;
								CheckStartSkul = false;
								CheckStartBridge = false;
								CheckEndPiston = false;
								CheckEndSkul = false;
								bossEndSound = false;
								SpawnJudmentThorn = false;
								curPattonIndex = 0;
								memset(checkPatton, false, sizeof(checkPatton));
							}
						}
					}
					else {
						BreakChainSummon0 = false;
						TalkPartCheck = true;
						Dialogue_start->Play();
						bossStartSound = false;
						CurCutSceneIndex = 0;
						CurTime = 0.f;
						SkulMoveDistance = 0.f;
						PistonMoveDistance = 0.f;
						CheckStartPiston = false;
						CheckStartSkul = false;
						CheckStartBridge = false;
						CheckEndPiston = false;
						CheckEndSkul = false;
						bossEndSound = false;
						SpawnJudmentThorn = false;
						curPattonIndex = 0;
						memset(checkPatton, false, sizeof(checkPatton));
					}
					//TalkCutSceneIndex += 1;
				}
			}

			if (UpIndex) {
				ChainSound = (ChainSound + 1) % 4 + 1;
				checkPatton[curPattonIndex] = true;
				curPattonIndex++;
				UpIndex = false;
			}

		

		}

		if (PLAYER_COLLISION_CHECK) {
			PlayerMove = false;
			float MinDistance = 100.f;

			Vec2 vPos = CurPos;
			const vector<CObj*>& vecWall = pCurLevel->GetObjects(LAYER_TYPE::WALL);
			const vector<CObj*>& vecBreakChain = pCurLevel->GetObjects(LAYER_TYPE::BROKE_CHAIN);

			for (size_t i = 0; i < vecBreakChain.size(); ++i)
			{

				Vec2 vMonPos = vecBreakChain[i]->GetPos(); // 몬스터의 위치

				Vec2 a = vPos;
				Vec2 b = vMonPos;

				float Dist = (vPos - vMonPos).Length();

				// 최소거리가 갱신된 경우
				if (Dist < MinDistance)
				{
					MinDistance = Dist;
					m_Target = vecBreakChain[i];
				}
			}

			if (m_Target == nullptr) {
				for (size_t i = 0; i < vecWall.size(); ++i)
				{

					Vec2 vMonPos = vecWall[i]->GetPos(); // 몬스터의 위치

					Vec2 a = vPos;
					Vec2 b = vMonPos;

					float Dist = (vPos - vMonPos).Length();

					// 최소거리가 갱신된 경우
					if (Dist < MinDistance)
					{
						MinDistance = Dist;
						m_Target = vecWall[i];
					}
				}
			}

			//부딪힌 타겟이 없거나 Keybox가 존재할 경우
			if (m_Target == nullptr) {

				//VFX_KICK_RENDER 초기화함
				//VFX_KICK_RENDER = false;
				PlayerMove = true;

				//이동 할 수 있으니 현재 위치에서 MoveVFX 실행 가능
				UsePlayerMoveVFXFlipbook();

				//다음 위치에 가시가 돋아날 경우 데미지 
				IFNextPointUpThorn();

				//좌표 기반 이동 실행
				MoveLogic();

			}
			else {
				LAYER_TYPE m_Target_LayerType = m_Target->GetLayerType();
				Check_In_Place_Motion(m_Target_LayerType);
			}
			PLAYER_COLLISION_CHECK = false;
		}
	}
}

void CPlayer::FlipBookMGR()
{
	if (m_FlipbookVFXPlayer->IsFinish()) {
		VFX_HUGE_RENDER = false;
		VFX_KICK_RENDER = false;
	}
	if (m_FlipbookMOVEVFXPlayer->IsFinish()) {
		VFX_MOVE_RENDER = false;
		MoveVFXRenderPos = { 0.f,0.f };
	}
	if (m_FlipbookPlayer->IsFinish() && SuccessLevel) {
		if (RestartCutsceneStart) {
			RestartCutsceneStart = false;
			CRestartCutScene* pResetCutScene = new CRestartCutScene;
			CreateObject(pResetCutScene, LAYER_TYPE::CUTSCENE);

		}
		else if (RestartCutsceneEnd == true) {
			if (CurLevel == STAGE_0) {
				ChangeLevel(LEVEL_TYPE::STAGE_1);
			}
			else if (CurLevel == STAGE_1) {
				ChangeLevel(LEVEL_TYPE::STAGE_2);
			}
			else if (CurLevel == STAGE_2) {
				ChangeLevel(LEVEL_TYPE::STAGE_3);
			}
			else if (CurLevel == STAGE_3) {
				ChangeLevel(LEVEL_TYPE::STAGE_4);
			}
			else if (CurLevel == STAGE_4) {
				ChangeLevel(LEVEL_TYPE::STAGE_5);
			}
			else if (CurLevel == STAGE_5) {
				ChangeLevel(LEVEL_TYPE::STAGE_6);
			}
			else if (CurLevel == STAGE_6) {
				ChangeLevel(LEVEL_TYPE::STAGE_7);
			}
			else if (CurLevel == STAGE_7) {
				ChangeLevel(LEVEL_TYPE::STAGE_8);
			}
			else if (CurLevel == STAGE_8) {
				ChangeLevel(LEVEL_TYPE::BOSS_0);
			}
			else if (CurLevel == BOSS_0) {
				ChangeLevel(LEVEL_TYPE::STAGE_HOME);
			}
			else if (CurLevel == STAGE_HOME) {
				ChangeLevel(LEVEL_TYPE::STAGE_LOBBY);
			}

		}
	}
	if (m_FlipbookPlayer->IsFinish()) {
		if (Dir == S_RIGHT) {
			m_FlipbookPlayer->Play(IDLE_RIGHT, 15.f, true);
		}
		else if (Dir == S_LEFT) {
			m_FlipbookPlayer->Play(IDLE_LEFT, 15.f, true);
		}
	}
}

void CPlayer::InplaceSkul(CLevel* pCurLevel)
{
	SkulMoveDistance += 20.f;

	const vector<CObj*>& vecSKUL = pCurLevel->GetObjects(LAYER_TYPE::SKUL);
	const vector<CObj*>& vecUNDERSKUL = pCurLevel->GetObjects(LAYER_TYPE::UNDER_SKUL);

	for (int i = 0; i < vecSKUL.size(); i++) {
		CJudmentSkul* jud = dynamic_cast<CJudmentSkul*>(vecSKUL[i]);
		Vec2 ps = jud->GetPos();
		jud->SetPos(ps.x, ps.y + 15.f);
	}
	for (int i = 0; i < vecUNDERSKUL.size(); i++) {
		CJudmentSkul* jud = dynamic_cast<CJudmentSkul*>(vecUNDERSKUL[i]);
		Vec2 ps = jud->GetPos();
		jud->SetPos(ps.x, ps.y + 15.f);
	}
	const vector<CObj*>& vecHighPiston = pCurLevel->GetObjects(LAYER_TYPE::HIGH_PISTON);
	const vector<CObj*>& vecHighUnderPiston = pCurLevel->GetObjects(LAYER_TYPE::HIGH_UNDER_PISTON);

	for (int i = 0; i < vecHighPiston.size(); i++) {
		CJudmentPiston* jud = dynamic_cast<CJudmentPiston*>(vecHighPiston[i]);
		jud->SetPos(jud->GetPos().x, jud->GetPos().y + 10.f);
	}

	for (int i = 0; i < vecHighUnderPiston.size(); i++) {
		CJudmentPiston* jud = dynamic_cast<CJudmentPiston*>(vecHighUnderPiston[i]);
		jud->SetPos(jud->GetPos().x, jud->GetPos().y + 10.f);
	}

	if (SkulMoveDistance == 400.f) {
		CCamera::GetInst()->Oscillation(0.2, 15, 15);
		CheckEndSkul = true;
		const vector<CObj*>& vecBridge = pCurLevel->GetObjects(LAYER_TYPE::BRIDGE);

		for (int i = 0; i < vecBridge.size(); i++) {
			CBridge* jud = dynamic_cast<CBridge*>(vecBridge[i]);
			jud->MoveBirdge = false;
		}
		const vector<CObj*>& pGearVec = pCurLevel->GetObjects(LAYER_TYPE::GEAR);
		for (int i = 0; i < pGearVec.size(); i++) {
			CGear* gear = dynamic_cast<CGear*>(pGearVec[i]);
			gear->GearTurn = false;
		}
	}
}

void CPlayer::InplacePiston(CLevel* pCurLevel)
{
	PistonMoveDistance += 20.f;
	const vector<CObj*>& vecHIGHPiston = pCurLevel->GetObjects(LAYER_TYPE::HIGH_PISTON);
	const vector<CObj*>& vecHIGHUnderPiston = pCurLevel->GetObjects(LAYER_TYPE::HIGH_UNDER_PISTON);

	for (int i = 0; i < vecHIGHPiston.size(); i++) {
		CJudmentPiston* jud = dynamic_cast<CJudmentPiston*>(vecHIGHPiston[i]);
		jud->SetPos(jud->GetPos().x, jud->GetPos().y - 10.f);
	}

	for (int i = 0; i < vecHIGHUnderPiston.size(); i++) {
		CJudmentPiston* jud = dynamic_cast<CJudmentPiston*>(vecHIGHUnderPiston[i]);
		jud->SetPos(jud->GetPos().x, jud->GetPos().y - 10.f);
	}

	if (PistonMoveDistance == 400.f) {
		CCamera::GetInst()->Oscillation(0.2, 15, 15);
		CheckEndPiston = true;
	}
}

void CPlayer::MoveSkul(CLevel* pCurLevel)
{
	SkulMoveDistance += 20.f;

	const vector<CObj*>& vecSKUL = pCurLevel->GetObjects(LAYER_TYPE::SKUL);
	const vector<CObj*>& vecUNDERSKUL = pCurLevel->GetObjects(LAYER_TYPE::UNDER_SKUL);

	for (int i = 0; i < vecSKUL.size(); i++) {
		CJudmentSkul* jud = dynamic_cast<CJudmentSkul*>(vecSKUL[i]);
		Vec2 ps = jud->GetPos();
		jud->SetPos(ps.x, ps.y - 15.f);
	}
	for (int i = 0; i < vecUNDERSKUL.size(); i++) {
		CJudmentSkul* jud = dynamic_cast<CJudmentSkul*>(vecUNDERSKUL[i]);
		Vec2 ps = jud->GetPos();
		jud->SetPos(ps.x, ps.y - 15.f);
	}
	const vector<CObj*>& vecLOWPiston = pCurLevel->GetObjects(LAYER_TYPE::LOW_PISTON);
	const vector<CObj*>& vecLOWUnderPiston = pCurLevel->GetObjects(LAYER_TYPE::LOW_UNDER_PISTON);

	for (int i = 0; i < vecLOWPiston.size(); i++) {
		CJudmentPiston* jud = dynamic_cast<CJudmentPiston*>(vecLOWPiston[i]);
		jud->SetPos(jud->GetPos().x, jud->GetPos().y - 20.f);
	}

	for (int i = 0; i < vecLOWUnderPiston.size(); i++) {
		CJudmentPiston* jud = dynamic_cast<CJudmentPiston*>(vecLOWUnderPiston[i]);
		jud->SetPos(jud->GetPos().x, jud->GetPos().y - 20.f);
	}

	if (SkulMoveDistance == 400.f) {
		CCamera::GetInst()->Oscillation(0.2, 15, 15);
		CheckStartSkul = true;
		const vector<CObj*>& pGearVec = pCurLevel->GetObjects(LAYER_TYPE::GEAR);
		for (int i = 0; i < pGearVec.size(); i++) {
			CGear* gear = dynamic_cast<CGear*>(pGearVec[i]);
			gear->GearTurn = true;
		}
	}

}

void CPlayer::StartPiston(CLevel* pCurLevel)
{
	PistonMoveDistance += 20.f;
	const vector<CObj*>& vecHIGHPiston = pCurLevel->GetObjects(LAYER_TYPE::HIGH_PISTON);
	const vector<CObj*>& vecHIGHUnderPiston = pCurLevel->GetObjects(LAYER_TYPE::HIGH_UNDER_PISTON);
	const vector<CObj*>& vecLOWPiston = pCurLevel->GetObjects(LAYER_TYPE::LOW_PISTON);
	const vector<CObj*>& vecLOWUnderPiston = pCurLevel->GetObjects(LAYER_TYPE::LOW_UNDER_PISTON);

	for (int i = 0; i < vecLOWPiston.size(); i++) {
		CJudmentPiston* jud = dynamic_cast<CJudmentPiston*>(vecLOWPiston[i]);
		jud->SetPos(jud->GetPos().x, jud->GetPos().y + 20.f);
	}

	for (int i = 0; i < vecLOWUnderPiston.size(); i++) {
		CJudmentPiston* jud = dynamic_cast<CJudmentPiston*>(vecLOWUnderPiston[i]);
		jud->SetPos(jud->GetPos().x, jud->GetPos().y + 20.f);
	}

	if (PistonMoveDistance == 400.f) {
		CCamera::GetInst()->Oscillation(0.2, 15, 15);
		CheckStartPiston = true;
	}
}

void CPlayer::StopPiston(CLevel* pCurLevel)
{
	const vector<CObj*>& vecHIGHPiston = pCurLevel->GetObjects(LAYER_TYPE::HIGH_PISTON);
	const vector<CObj*>& vecHIGHUnderPiston = pCurLevel->GetObjects(LAYER_TYPE::HIGH_UNDER_PISTON);
	const vector<CObj*>& vecLOWPiston = pCurLevel->GetObjects(LAYER_TYPE::LOW_PISTON);
	const vector<CObj*>& vecLOWUnderPiston = pCurLevel->GetObjects(LAYER_TYPE::LOW_UNDER_PISTON);

	for (int i = 0; i < vecHIGHPiston.size(); i++) {
		CJudmentPiston* jud = dynamic_cast<CJudmentPiston*>(vecHIGHPiston[i]);
		jud->TurnPiston = false;
	}

	for (int i = 0; i < vecHIGHUnderPiston.size(); i++) {
		CJudmentPiston* jud = dynamic_cast<CJudmentPiston*>(vecHIGHUnderPiston[i]);
		jud->TurnPiston = false;
	}
}

void CPlayer::TALKCUTSCENE_LOGIC()
{

	CutsceneTime += DT;

	//flipbookplayer
	if (wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText, L"죄악의 기계에 시동을 걸어라! 시련을 피할 수는 없다!") == 0 && !check) {
		if (!j_introsound && CutsceneTime > 0.2f) {
			judgement_intro_anim_01->Play();
			j_introsound = true;
			m_FlipbookCutSceneDemonPlayer->Play(J_introAnim, 10.f, false);
			j_animintro = true;
			check = true;
			CSound* SIDONG = CAssetMgr::GetInst()->LoadSound(L"voice", L"Sound\\죄악의기계에시동을.wav");
			if (nullptr != SIDONG)
			{
				SIDONG->SetVolume(ActorVolume);
				SIDONG->Play();
			}
		}

		//if (CutsceneTime > 0.3f) {

		//}
	}
	else if (wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText, L"드디어 만나네. 내가 준비한 시험을 통과했으니 그 만한") == 0 && !check) {
		if (CutsceneTime > 0.2f) {
			m_FlipbookCutSceneDemonPlayer->Play(LH_swirl, 8.f, false);
			lucifer_intro_vine_01->Play();
			check = true;
		}
	}
	else if (wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText, L"그리고 절망의 사슬이 가장 즐거운 법이지.") == 0 && !check) {
		if (CutsceneTime > 0.5f) {
			judgement_chain_bind_01->Play();
			m_FlipbookCutSceneDemonPlayer->Play(j_bindAnim, 10.f, false);
			Judment_bind = true;

			std::wstring voiceName = NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].Voice;

			// 문자열 버퍼에 파일 경로 포맷팅
			wchar_t soundPath[256];
			swprintf_s(soundPath, L"Sound\\%s.wav", voiceName.c_str());

			// CSound 객체 로드
			voice = CAssetMgr::GetInst()->LoadSound(soundPath, soundPath);

			if (nullptr != voice)
			{
				voice->SetVolume(ActorVolume);
				voice->Play();
			}

			check = true;
		}
	}
	else if (wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText, L"희망은 실망을, 그리고 실망은 절망을 낳는다.") == 0 && !check) {
		if (CutsceneTime > 0.4f) {
			judgement_chain_summon_01->Play();
			j_bindAnimNull = true;
			check = true;

			std::wstring voiceName = NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].Voice;

			// 문자열 버퍼에 파일 경로 포맷팅
			wchar_t soundPath[256];
			swprintf_s(soundPath, L"Sound\\%s.wav", voiceName.c_str());

			// CSound 객체 로드
			voice = CAssetMgr::GetInst()->LoadSound(soundPath, soundPath);

			if (nullptr != voice)
			{
				voice->SetVolume(ActorVolume);
				voice->Play();
			}

		}
	}
	else if (wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText, L"이제 다시 시련을 시작한다!") == 0 && !check) {
		if (CutsceneTime > 0.2f) {
			m_FlipbookCutSceneDemonPlayer->Play(j_flyAnim, 20.f, false);
			judgement_spell_cast_01->Play();
			j_fly = true;
			std::wstring voiceName = NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].Voice;

			// 문자열 버퍼에 파일 경로 포맷팅
			wchar_t soundPath[256];
			swprintf_s(soundPath, L"Sound\\%s.wav", voiceName.c_str());

			// CSound 객체 로드
			voice = CAssetMgr::GetInst()->LoadSound(soundPath, soundPath);

			if (nullptr != voice)
			{
				voice->SetVolume(ActorVolume);
				voice->Play();
			}

			check = true;
		}
	}
	else if (wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText, L"뭐? 진심이야?") == 0 && !check) {
		if (CutsceneTime > 0.5f) {
			// 문자열 버퍼에 파일 경로 포맷팅
			std::wstring voiceName = NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].Voice;
			wchar_t soundPath[256];
			swprintf_s(soundPath, L"Sound\\%s.wav", voiceName.c_str());

			// CSound 객체 로드
			voice = CAssetMgr::GetInst()->LoadSound(soundPath, soundPath);

			if (nullptr != voice)
			{
				voice->SetVolume(ActorVolume);
				voice->Play();
			}
			m_FlipbookCutSceneDemonPlayer->Play(mainUIexport_oUI_idle, 15.f, true);
			j_Success = true;
			check = true;
		}
	}
	else if (wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText, L"드디어 만나네. 내가 준비한 시험을 통과했으니 그 만한") == 0 && m_FlipbookCutSceneLucyEye->IsFinish() && !lucy_facecheck) {
		if (CutsceneTime > 4.5f) {
			lucifer_intro_skeleton_01->Play();
			lucy_facecheck = true;
		}
	}
	else if(wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].Voice, L"NO") == 1 && !check){
		std::wstring voiceName = NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].Voice;

		// 문자열 버퍼에 파일 경로 포맷팅
		wchar_t soundPath[256];
		swprintf_s(soundPath, L"Sound\\%s.wav", voiceName.c_str());

		// CSound 객체 로드
		voice = CAssetMgr::GetInst()->LoadSound(soundPath, soundPath);

		if (nullptr != voice)
		{
			voice->SetVolume(ActorVolume);
			voice->Play();
		}
		check = true;
	}

	//대화 파트
	if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].CutsceneType == CUTSCENE_TYPE::TALK_CUTSCENE) {
		if (KEY_TAP(ENTER)) {
			Dialogue_Booper->Play();
			CurCutSceneIndex = NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].nextIndex;
			int a = 0;
			CutsceneTime = 0.f;
			check = false;
			j_bindAnimNull = false;
			if (voice != nullptr) {
				voice->Stop();
			}

		}
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].CutsceneType == CUTSCENE_TYPE::SUCESS_CUTSCENE) {
		if (!SuccessStart) {
			CSuccess* Cs = new CSuccess;
			CreateObject(Cs, LAYER_TYPE::SUCCESS);
			SuccessStart = true;
		}
		if (SuccessEnd && KEY_TAP(ENTER)) {
			if (voice != nullptr) {
				voice->Stop();
			}
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
			const vector<CObj*>& vecPlayer = pCurLevel->GetObjects(LAYER_TYPE::SUCCESS);
			CSuccess* cp = dynamic_cast<CSuccess*>(vecPlayer[0]);
			DeleteObject(cp);
			SuccessLevel = true;
			CutsceneTime = 0.f;
			TalkPartCheck = false;
			const vector<CObj*>& vecDemon = pCurLevel->GetObjects(LAYER_TYPE::DEMON);

			for (int i = 0; i < vecDemon.size(); i++) {
				CDemon* cd = dynamic_cast<CDemon*>(vecDemon[i]);
				cd->clearLevel = true;
			}
			if (CurLevel == LEVEL_CHECK::BOSS_0 && TalkCutSceneIndex == 4) {
				JudmentClear = true;
			}
			m_FlipbookPlayer->Play(SMILE, 5.f, false);

			if (voice != nullptr) {
				voice->Stop();
			}
			KissSound->Play();
		}
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].CutsceneType == CUTSCENE_TYPE::DIE_CUTSCENE) {
		if (KEY_TAP(ENTER)) {
			CurCutSceneIndex = 0;
			TalkPartCheck = false;
			CDialogueDeath* pDia = new CDialogueDeath;
			pDia->SetScale(100.f, 100.f);
			CreateObject(pDia, LAYER_TYPE::CUTSCENE);
			uncheckDemon = true;
			SetPos(GetStartPos());
			ResetObject();
			CutsceneTime = 0.f;
			check = false;
			lucy_facecheck = false;
			CutsceneTime = 0.f;
			if (voice != nullptr) {
				voice->Stop();
			}
		}
	}
	//선택 파트
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].CutsceneType == CUTSCENE_TYPE::CHOICE_CUTSCENE) {
		if (KEY_TAP(UP)) {
			Dialogue_Next->Play();
			if (FocusChoice == 1) {
				FocusChoice = 0;
			}
		}
		else if (KEY_TAP(DOWN)) {
			Dialogue_Next->Play();
			if (FocusChoice == 0) {
				FocusChoice = 1;
			}
		}
		else if (KEY_TAP(ENTER)) {
			CutsceneTime = 0.f;
			Dialogue_Booper->Play();
			//죽음을 선택 했을때
			if (wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].HeroSecondText, L"나가기") == 0 && FocusChoice == 1) {
				PostQuitMessage(0);
			}
			else if (FocusChoice == NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DeathChoice) {
				if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::POLICE) {
					TalkPartCheck = false;
				}
				else {
					CurCutSceneIndex = NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].nextDeathIndex;
				}
			}
			else {
				//죽음을 선택하지 않으면 다음 index로 넘어감
				CurCutSceneIndex = NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].nextIndex;
			}
			if (voice != nullptr) {
				voice->Stop();
			}
		}
	}
	//다음 컷신으로
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].CutsceneType == CUTSCENE_TYPE::NEXTINDEXSCENE) {
		if (KEY_TAP(ENTER)) {
			CurCutSceneIndex = 0;
			TalkCutSceneIndex += 1;
			CutsceneTime = 0.f;
			check = false;
			TalkPartCheck = false;
			if (voice != nullptr) {
				voice->Stop();
			}
		}
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].CutsceneType == CUTSCENE_TYPE::NEXT_LEVELSCENE) {
		if (KEY_TAP(ENTER)) {
			if (voice != nullptr) {
				voice->Stop();
			}
			if (CurLevel == STAGE_0) {
				ChangeLevel(LEVEL_TYPE::STAGE_1);
			}
			else if (CurLevel == STAGE_1) {
				ChangeLevel(LEVEL_TYPE::STAGE_2);
			}
			else if (CurLevel == STAGE_2) {
				ChangeLevel(LEVEL_TYPE::STAGE_3);
			}
			else if (CurLevel == STAGE_3) {
				ChangeLevel(LEVEL_TYPE::STAGE_4);
			}
			else if (CurLevel == STAGE_4) {
				ChangeLevel(LEVEL_TYPE::STAGE_5);
			}
			else if (CurLevel == STAGE_5) {
				ChangeLevel(LEVEL_TYPE::STAGE_6);
			}
			else if (CurLevel == STAGE_6) {
				ChangeLevel(LEVEL_TYPE::STAGE_7);
			}
			else if (CurLevel == STAGE_7) {
				ChangeLevel(LEVEL_TYPE::STAGE_8);
			}
			else if (CurLevel == STAGE_8) {
				ChangeLevel(LEVEL_TYPE::BOSS_0);
			}
			else if (CurLevel == BOSS_0) {
				ChangeLevel(LEVEL_TYPE::STAGE_HOME);
			}
			else if (CurLevel == STAGE_HOME) {
				ChangeLevel(LEVEL_TYPE::STAGE_LOBBY);
			}
			else if (CurLevel == STAGE_LOBBY) {
				ChangeLevel(LEVEL_TYPE::STAGE_0);
			}
		}
	}
}

void CPlayer::ResetObject()
{
	PlayerMove_Count = Init_PlayerMove_Count;
	lucy_facecheck = false;
	Die = false;
	KeyBox_Key = false;
	DeleteAllObject();
	RespownObject();
}

void CPlayer::DeleteAllObject()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	const vector<CObj*>& vecMon = pCurLevel->GetObjects(LAYER_TYPE::MONSTER);
	const vector<CObj*>& vecRock = pCurLevel->GetObjects(LAYER_TYPE::Rock);
	const vector<CObj*>& vecThorn = pCurLevel->GetObjects(LAYER_TYPE::THORN);
	const vector<CObj*>& vecKeyBox = pCurLevel->GetObjects(LAYER_TYPE::KEYBOX);
	const vector<CObj*>& vecKey = pCurLevel->GetObjects(LAYER_TYPE::KEY);

	for (size_t i = 0; i < vecKeyBox.size(); ++i)
	{
		DeleteObject(vecKeyBox[i]);
	}

	for (size_t i = 0; i < vecMon.size(); ++i)
	{
		DeleteObject(vecMon[i]);
	}

	for (size_t i = 0; i < vecRock.size(); ++i)
	{
		DeleteObject(vecRock[i]);
	}
	if (CurLevel != LEVEL_CHECK::BOSS_0) {
		for (size_t i = 0; i < vecThorn.size(); ++i)
		{
			DeleteObject(vecThorn[i]);
		}
	}

	for (size_t i = 0; i < vecKey.size(); ++i)
	{
		DeleteObject(vecKey[i]);
	}
}

void CPlayer::RespownObject()
{
	if (CurLevel == STAGE_0) {

		// Monster 생성
		CMonster* pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(1050.f, 450.f);
		pMonster->SetScale(100.f, 100.f);
		pMonster->SetDistance(200.f);
		pMonster->SetOffset(0.f, 30.f);
		pMonster->SetSpeed(300.f);
		pMonster->SetSound(1);
		CreateObject(pMonster, LAYER_TYPE::MONSTER);

		CMonster* pMonster2 = new CMonster;
		pMonster2->SetName(L"Monster");
		pMonster2->SetPos(950.f, 350.f);
		pMonster2->SetScale(100.f, 100.f);
		pMonster2->SetDistance(200.f);
		pMonster2->SetOffset(0.f, 30.f);
		pMonster2->SetSpeed(300.f);
		pMonster2->SetSound(2);
		CreateObject(pMonster2, LAYER_TYPE::MONSTER);

		CMonster* pMonster3 = new CMonster;
		pMonster3->SetName(L"Monster");
		pMonster3->SetPos(850.f, 450.f);
		pMonster3->SetScale(100.f, 100.f);
		pMonster3->SetDistance(200.f);
		pMonster3->SetSpeed(300.f);
		pMonster3->SetOffset(0.f, 30.f);
		pMonster3->SetSound(3);
		CreateObject(pMonster3, LAYER_TYPE::MONSTER);

		CRock* pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_0");
		pRock1->SetPos(750.f, 650.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		CRock* pRock2 = new CRock;
		pRock2->SetName(L"Rock");
		pRock2->SetRock(L"boxExport_1");
		pRock2->SetPos(750.f, 750.f);
		pRock2->SetScale(100.f, 100.f);
		CreateObject(pRock2, LAYER_TYPE::Rock);

		CRock* pRock4 = new CRock;
		pRock4->SetRock(L"boxExport_3");
		pRock4->SetName(L"Rock");
		pRock4->SetPos(1050.f, 650.f);
		pRock4->SetScale(100.f, 100.f);
		CreateObject(pRock4, LAYER_TYPE::Rock);

		CRock* pRock3 = new CRock;
		pRock3->SetRock(L"boxExport_2");
		pRock3->SetName(L"Rock");
		pRock3->SetPos(950.f, 750.f);
		pRock3->SetScale(100.f, 100.f);
		CreateObject(pRock3, LAYER_TYPE::Rock);
	}

	else if (CurLevel == STAGE_1) {
		CMonster* pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(750.f, 350.f);
		pMonster->SetScale(100.f, 100.f);
		pMonster->SetOffset(0.f, 30.f);
		pMonster->SetDistance(200.f);
		pMonster->SetSpeed(300.f);
		pMonster->SetSound(1);
		CreateObject(pMonster, LAYER_TYPE::MONSTER);

		CMonster* pMonster2 = new CMonster;
		pMonster2->SetName(L"Monster");
		pMonster2->SetPos(1250.f, 750.f);
		pMonster2->SetOffset(0.f, 30.f);
		pMonster2->SetScale(100.f, 100.f);
		pMonster2->SetDistance(200.f);
		pMonster2->SetSpeed(300.f);
		pMonster2->SetSound(2);
		CreateObject(pMonster2, LAYER_TYPE::MONSTER);

		CMonster* pMonster3 = new CMonster;
		pMonster3->SetName(L"Monster");
		pMonster3->SetPos(1150.f, 650.f);
		pMonster3->SetScale(100.f, 100.f);
		pMonster3->SetDistance(200.f);
		pMonster3->SetSpeed(300.f);
		pMonster3->SetOffset(0.f, 30.f);
		pMonster3->SetSound(3);
		CreateObject(pMonster3, LAYER_TYPE::MONSTER);

		CRock* pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_0");
		pRock1->SetPos(1150.f, 450.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		CRock* pRock2 = new CRock;
		pRock2->SetName(L"Rock");
		pRock2->SetRock(L"boxExport_1");
		pRock2->SetPos(1050.f, 450.f);
		pRock2->SetScale(100.f, 100.f);
		CreateObject(pRock2, LAYER_TYPE::Rock);

		CRock* pRock4 = new CRock;
		pRock4->SetRock(L"boxExport_3");
		pRock4->SetName(L"Rock");
		pRock4->SetPos(1250.f, 450.f);
		pRock4->SetScale(100.f, 100.f);
		CreateObject(pRock4, LAYER_TYPE::Rock);

		CThorn* pThorn = new CThorn;
		pThorn->SetThorn(THORN_UP);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(1050.f, 450.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_UP);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(1150.f, 450.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_UP);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(1150.f, 550.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_UP);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(1050.f, 350.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_UP);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(950.f, 350.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_UP);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(750.f, 450.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);
	}
	else if (CurLevel == STAGE_2) {
		CKey* pKey = new CKey;
		pKey->SetPos(650.f, 750.f);
		pKey->SetScale(100.f, 100.f);
		CreateObject(pKey, LAYER_TYPE::KEY);

		CKeybox* pKeybox = new CKeybox;
		pKeybox->SetPos(1250.f, 350.f);
		pKeybox->SetScale(100.f, 100.f);
		CreateObject(pKeybox, LAYER_TYPE::KEYBOX);

		// Monster 생성
		CMonster* pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(1150.f, 850.f);
		pMonster->SetScale(100.f, 100.f);
		pMonster->SetDistance(200.f);
		pMonster->SetOffset(0.f, 30.f);
		pMonster->SetSpeed(300.f);
		pMonster->SetSound(1);
		CreateObject(pMonster, LAYER_TYPE::MONSTER);

		CMonster* pMonster3 = new CMonster;
		pMonster3->SetName(L"Monster");
		pMonster3->SetPos(1050.f, 650.f);
		pMonster3->SetScale(100.f, 100.f);
		pMonster3->SetDistance(200.f);
		pMonster3->SetOffset(0.f, 30.f);
		pMonster3->SetSpeed(300.f);
		pMonster3->SetSound(3);
		CreateObject(pMonster3, LAYER_TYPE::MONSTER);

		CThorn* pThorn = new CThorn;
		pThorn->SetThorn(THORN_UP);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(1050.f, 450.f);
		pThorn->SetOffset(-10.f, 5.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_UP);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(950.f, 450.f);
		pThorn->SetOffset(-10.f, 5.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_UP);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(1050.f, 550.f);
		pThorn->SetOffset(-10.f, 5.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_UP);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(850.f, 550.f);
		pThorn->SetOffset(-10.f, 5.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_UP);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(1150.f, 650.f);
		pThorn->SetOffset(-10.f, 5.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_UP);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(1250.f, 650.f);
		pThorn->SetOffset(-10.f, 5.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_UP);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(1050.f, 750.f);
		pThorn->SetOffset(-10.f, 5.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_UP);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(850.f, 750.f);
		pThorn->SetOffset(-10.f, 5.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);
	}
	else if (CurLevel == STAGE_3) {
		CKey* pKey = new CKey;
		pKey->SetPos(850.f, 350.f);
		pKey->SetScale(100.f, 100.f);
		CreateObject(pKey, LAYER_TYPE::KEY);

		CKeybox* pKeybox = new CKeybox;
		pKeybox->SetPos(1150.f, 450.f);
		pKeybox->SetScale(100.f, 100.f);
		CreateObject(pKeybox, LAYER_TYPE::KEYBOX);

		// Monster 생성
		//CMonster* pMonster = new CMonster;
		//pMonster->SetName(L"Monster");
		//pMonster->SetPos(1150.f, 850.f);
		//pMonster->SetScale(100.f, 100.f);
		//pMonster->SetDistance(200.f);
		//pMonster->SetSpeed(300.f);
		//pMonster->SetSound(1);
		//AddObject(pMonster, LAYER_TYPE::MONSTER);

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
		pRock1->SetPos(650.f, 550.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_1");
		pRock1->SetPos(750.f, 450.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetRock(L"boxExport_3");
		pRock1->SetName(L"Rock");
		pRock1->SetPos(750.f, 650.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_4");
		pRock1->SetPos(850.f, 550.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_5");
		pRock1->SetPos(850.f, 750.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_6");
		pRock1->SetPos(950.f, 450.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_7");
		pRock1->SetPos(950.f, 650.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_8");
		pRock1->SetPos(1050.f, 350.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_9");
		pRock1->SetPos(1050.f, 550.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_10");
		pRock1->SetPos(1050.f, 750.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_0");
		pRock1->SetPos(1150.f, 550.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_1");
		pRock1->SetPos(1150.f, 650.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_2");
		pRock1->SetPos(1250.f, 650.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		CThorn* pThorn = new CThorn;
		pThorn->SetThorn(THORN_UP);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(850.f, 450.f);
		pThorn->SetOffset(-10.f, 5.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_UP);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(950.f, 450.f);
		pThorn->SetOffset(-10.f, 5.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);
	}
	else if (CurLevel == STAGE_4) {
		CKey* pKey = new CKey;
		pKey->SetPos(1250.f, 850.f);
		pKey->SetScale(100.f, 100.f);
		pKey->SetOffset(10.f, 30.f);
		CreateObject(pKey, LAYER_TYPE::KEY);

		CKeybox* pKeybox = new CKeybox;
		pKeybox->SetPos(1050.f, 350.f);
		pKeybox->SetScale(100.f, 100.f);
		CreateObject(pKeybox, LAYER_TYPE::KEYBOX);

		// Monster 생성
		CMonster* pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(750.f, 650.f);
		pMonster->SetScale(100.f, 100.f);
		pMonster->SetOffset(0.f, 30.f);
		pMonster->SetDistance(200.f);
		pMonster->SetSpeed(300.f);
		pMonster->SetSound(1);
		CreateObject(pMonster, LAYER_TYPE::MONSTER);

		//CMonster* pMonster3 = new CMonster;
		//pMonster3->SetName(L"Monster");
		//pMonster3->SetPos(1050.f, 650.f);
		//pMonster3->SetScale(100.f, 100.f);
		//pMonster3->SetDistance(200.f);
		//pMonster3->SetSpeed(300.f);
		//pMonster3->SetSound(3);
		//CreateObject(pMonster3, LAYER_TYPE::MONSTER);

		CThorn* pThorn = new CThorn;
		pThorn->SetThorn(THORN_DOWN);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(750.f, 750.f);
		pThorn->SetOffset(-10.f, 5.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		CRock* pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_0");
		pRock1->SetPos(950.f, 650.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_1");
		pRock1->SetPos(1050.f, 650.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_2");
		pRock1->SetPos(1150.f, 650.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_3");
		pRock1->SetPos(1150.f, 450.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_4");
		pRock1->SetPos(1150.f, 350.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_5");
		pRock1->SetPos(1250.f, 650.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_DOWN);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(950.f, 750.f);
		pThorn->SetOffset(-10.f, 5.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_DOWN);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(950.f, 450.f);
		pThorn->SetOffset(-10.f, 5.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_DOWN);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(1050.f, 550.f);
		pThorn->SetOffset(-10.f, 5.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_DOWN);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(1250.f, 750.f);
		pThorn->SetOffset(-10.f, 5.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_DOWN);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(1250.f, 550.f);
		pThorn->SetOffset(-10.f, 5.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);
	}
	else if (CurLevel == STAGE_5) {
		CKey* pKey = new CKey;
		pKey->SetPos(950.f, 350.f);
		pKey->SetOffset(0.f, 30.f);
		pKey->SetScale(100.f, 100.f);
		CreateObject(pKey, LAYER_TYPE::KEY);

		CKeybox* pKeybox = new CKeybox;
		pKeybox->SetPos(1050.f, 750.f);
		pKeybox->SetScale(100.f, 100.f);
		CreateObject(pKeybox, LAYER_TYPE::KEYBOX);

		// Monster 생성
		CMonster* pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(750.f, 550.f);
		pMonster->SetScale(100.f, 100.f);
		pMonster->SetDistance(200.f);
		pMonster->SetSpeed(300.f);
		pMonster->SetOffset(0.f, 30.f);
		pMonster->SetSound(1);
		CreateObject(pMonster, LAYER_TYPE::MONSTER);

		pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(1150.f, 650.f);
		pMonster->SetScale(100.f, 100.f);
		pMonster->SetDistance(200.f);
		pMonster->SetSpeed(300.f);
		pMonster->SetOffset(0.f, 30.f);
		pMonster->SetSound(1);
		CreateObject(pMonster, LAYER_TYPE::MONSTER);

		//CMonster* pMonster3 = new CMonster;
		//pMonster3->SetName(L"Monster");
		//pMonster3->SetPos(1050.f, 650.f);
		//pMonster3->SetScale(100.f, 100.f);
		//pMonster3->SetDistance(200.f);
		//pMonster3->SetSpeed(300.f);
		//pMonster3->SetSound(3);
		//CreateObject(pMonster3, LAYER_TYPE::MONSTER);

		CRock* pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_0");
		pRock1->SetPos(750.f, 250.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_1");
		pRock1->SetPos(850.f, 250.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_2");
		pRock1->SetPos(1150.f, 750.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_3");
		pRock1->SetPos(950.f, 250.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_4");
		pRock1->SetPos(850.f, 450.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_5");
		pRock1->SetPos(950.f, 550.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_8");
		pRock1->SetPos(1050.f, 550.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_9");
		pRock1->SetPos(950.f, 650.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		CThorn* pThorn = new CThorn;
		pThorn->SetThorn(THORN_DOWN);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(750.f, 450.f);
		pThorn->SetOffset(-10.f, 5.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_DOWN);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(850.f, 450.f);
		pThorn->SetOffset(-10.f, 5.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);
	}
	else if (CurLevel == STAGE_6) {
		CKey* pKey = new CKey;
		pKey->SetPos(800.f, 400.f);
		pKey->SetScale(100.f, 100.f);
		pKey->SetOffset(10.f, 30.f);
		CreateObject(pKey, LAYER_TYPE::KEY);

		CKeybox* pKeybox = new CKeybox;
		pKeybox->SetPos(1100.f, 300.f);
		pKeybox->SetScale(100.f, 100.f);
		pKeybox->SetOffset(0.f, 10.f);
		CreateObject(pKeybox, LAYER_TYPE::KEYBOX);

		// Monster 생성
		CMonster* pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(1000.f, 500.f);
		pMonster->SetScale(100.f, 100.f);
		pMonster->SetDistance(200.f);
		pMonster->SetOffset(10.f, 30.f);
		pMonster->SetSpeed(300.f);
		pMonster->SetSound(1);
		CreateObject(pMonster, LAYER_TYPE::MONSTER);

		pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(900.f, 600.f);
		pMonster->SetScale(100.f, 100.f);
		pMonster->SetDistance(200.f);
		pMonster->SetOffset(10.f, 30.f);
		pMonster->SetSpeed(300.f);
		pMonster->SetSound(1);
		CreateObject(pMonster, LAYER_TYPE::MONSTER);

		pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(700.f, 500.f);
		pMonster->SetScale(100.f, 100.f);
		pMonster->SetDistance(200.f);
		pMonster->SetSpeed(300.f);
		pMonster->SetOffset(10.f, 30.f);
		pMonster->SetSound(1);
		CreateObject(pMonster, LAYER_TYPE::MONSTER);

		//CMonster* pMonster3 = new CMonster;
		//pMonster3->SetName(L"Monster");
		//pMonster3->SetPos(1050.f, 650.f);
		//pMonster3->SetScale(100.f, 100.f);
		//pMonster3->SetDistance(200.f);
		//pMonster3->SetSpeed(300.f);
		//pMonster3->SetSound(3);
		//CreateObject(pMonster3, LAYER_TYPE::MONSTER);

		CRock* pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_0");
		pRock1->SetPos(1000.f, 400.f);
		pRock1->SetOffset(0.f, 10.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_1");
		pRock1->SetPos(1200.f, 400.f);
		pRock1->SetOffset(0.f, 10.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_2");
		pRock1->SetPos(1100.f, 400.f);
		pRock1->SetOffset(0.f, 10.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_3");
		pRock1->SetPos(1100.f, 500.f);
		pRock1->SetOffset(0.f, 10.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_4");
		pRock1->SetPos(800.f, 500.f);
		pRock1->SetOffset(0.f, 10.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		CThorn* pThorn = new CThorn;
		pThorn->SetThorn(THORN_DOWN);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(1000.f, 700.f);
		pThorn->SetOffset(0, 10.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_UP);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(1000.f, 800.f);
		pThorn->SetOffset(-5, 20.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_DOWN);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(900.f, 800.f);
		pThorn->SetOffset(-5, 20.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_UP);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(800.f, 800.f);
		pThorn->SetOffset(-5, 20.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_DOWN);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(700.f, 800.f);
		pThorn->SetOffset(-5, 20.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);

		pThorn = new CThorn;
		pThorn->SetThorn(THORN_UP);
		pThorn->SetName(L"Thorn");
		pThorn->SetPos(700.f, 700.f);
		pThorn->SetOffset(-5, 20.f);
		pThorn->SetScale(100.f, 100.f);
		CreateObject(pThorn, LAYER_TYPE::THORN);
	}
	else if (CurLevel == STAGE_7) {
		// Monster 생성
		CMonster* pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(950.f, 1550.f);
		pMonster->SetScale(100.f, 100.f);
		pMonster->SetOffset(0.f, 10.f);
		pMonster->SetDistance(200.f);
		pMonster->SetSpeed(300.f);
		pMonster->SetSound(1);
		CreateObject(pMonster, LAYER_TYPE::MONSTER);

		pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(950.f, 1450.f);
		pMonster->SetScale(100.f, 100.f);
		pMonster->SetDistance(200.f);
		pMonster->SetOffset(0.f, 10.f);
		pMonster->SetSpeed(300.f);
		pMonster->SetSound(1);
		CreateObject(pMonster, LAYER_TYPE::MONSTER);

		pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(950.f, 1350.f);
		pMonster->SetScale(100.f, 100.f);
		pMonster->SetDistance(200.f);
		pMonster->SetOffset(0.f, 10.f);
		pMonster->SetSpeed(300.f);
		pMonster->SetSound(1);
		CreateObject(pMonster, LAYER_TYPE::MONSTER);

		pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(950.f, 1250.f);
		pMonster->SetScale(100.f, 100.f);
		pMonster->SetDistance(200.f);
		pMonster->SetOffset(0.f, 10.f);
		pMonster->SetSpeed(300.f);
		pMonster->SetSound(1);
		CreateObject(pMonster, LAYER_TYPE::MONSTER);

		pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(950.f, 1150.f);
		pMonster->SetScale(100.f, 100.f);
		pMonster->SetDistance(200.f);
		pMonster->SetOffset(0.f, 10.f);
		pMonster->SetSpeed(300.f);
		pMonster->SetSound(1);
		CreateObject(pMonster, LAYER_TYPE::MONSTER);

		pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(950.f, 1050.f);
		pMonster->SetScale(100.f, 100.f);
		pMonster->SetDistance(200.f);
		pMonster->SetOffset(0.f, 10.f);
		pMonster->SetSpeed(300.f);
		pMonster->SetSound(1);
		CreateObject(pMonster, LAYER_TYPE::MONSTER);

		pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(950.f, 950.f);
		pMonster->SetScale(100.f, 100.f);
		pMonster->SetDistance(200.f);
		pMonster->SetOffset(0.f, 10.f);
		pMonster->SetSpeed(300.f);
		pMonster->SetSound(1);
		CreateObject(pMonster, LAYER_TYPE::MONSTER);

		pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(950.f, 850.f);
		pMonster->SetScale(100.f, 100.f);
		pMonster->SetDistance(200.f);
		pMonster->SetOffset(0.f, 10.f);
		pMonster->SetSpeed(300.f);
		pMonster->SetSound(1);
		CreateObject(pMonster, LAYER_TYPE::MONSTER);
	}
	else if (CurLevel == STAGE_8) {
		CKey* pKey = new CKey;
		pKey->SetPos(1350.f, 650.f);
		pKey->SetScale(100.f, 100.f);
		pKey->SetOffset(10.f, 30.f);
		CreateObject(pKey, LAYER_TYPE::KEY);

		CKeybox* pKeybox = new CKeybox;
		pKeybox->SetPos(950.f, 450.f);
		pKeybox->SetOffset(10.f, 10.f);
		pKeybox->SetScale(100.f, 100.f);
		CreateObject(pKeybox, LAYER_TYPE::KEYBOX);

		//CMonster* pMonster3 = new CMonster;
		//pMonster3->SetName(L"Monster");
		//pMonster3->SetPos(1050.f, 650.f);
		//pMonster3->SetScale(100.f, 100.f);
		//pMonster3->SetDistance(200.f);
		//pMonster3->SetSpeed(300.f);
		//pMonster3->SetSound(3);
		//CreateObject(pMonster3, LAYER_TYPE::MONSTER);

		CRock* pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_0");
		pRock1->SetOffset(5.f, 10.f);
		pRock1->SetPos(850.f, 450.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_1");
		pRock1->SetOffset(5.f, 10.f);
		pRock1->SetPos(1050.f, 450.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_2");
		pRock1->SetPos(850.f, 550.f);
		pRock1->SetOffset(5.f, 10.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_3");
		pRock1->SetPos(850.f, 650.f);
		pRock1->SetScale(100.f, 100.f);
		pRock1->SetOffset(5.f, 10.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_4");
		pRock1->SetPos(950.f, 650.f);
		pRock1->SetOffset(5.f, 10.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_5");
		pRock1->SetPos(1050.f, 650.f);
		pRock1->SetScale(100.f, 100.f);
		pRock1->SetOffset(5.f, 10.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_6");
		pRock1->SetPos(1150.f, 750.f);
		pRock1->SetOffset(5.f, 10.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_7");
		pRock1->SetPos(1250.f, 750.f);
		pRock1->SetOffset(5.f, 10.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_8");
		pRock1->SetPos(1150.f, 850.f);
		pRock1->SetScale(100.f, 100.f);
		pRock1->SetOffset(5.f, 10.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_9");
		pRock1->SetPos(850.f, 750.f);
		pRock1->SetOffset(5.f, 10.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_10");
		pRock1->SetPos(750.f, 750.f);
		pRock1->SetOffset(5.f, 10.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_0");
		pRock1->SetPos(650.f, 750.f);
		pRock1->SetOffset(5.f, 10.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_1");
		pRock1->SetPos(650.f, 550.f);
		pRock1->SetScale(100.f, 100.f);
		pRock1->SetOffset(5.f, 10.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_2");
		pRock1->SetPos(550.f, 650.f);
		pRock1->SetOffset(5.f, 10.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

		pRock1 = new CRock;
		pRock1->SetName(L"Rock");
		pRock1->SetRock(L"boxExport_3");
		pRock1->SetPos(850.f, 850.f);
		pRock1->SetOffset(5.f, 10.f);
		pRock1->SetScale(100.f, 100.f);
		CreateObject(pRock1, LAYER_TYPE::Rock);

	}
	else if (CurLevel == STAGE_HOME) {

	}

}

void CPlayer::Check_In_Place_Motion(LAYER_TYPE m_Target_LayerType)
{
	VFX_KICK_RENDER = true;
	//발차기

	if (m_Target_LayerType == LAYER_TYPE::MONSTER) {
		CMonster* monsterTarget = static_cast<CMonster*>(m_Target);
		monsterTarget->Move(Move_Direction);
		pCharacter_Enemy_Kick->Play(false);
		m_FlipbookVFXPlayer->Play(KICK_VFX_1, 30.f, false);
	}
	else if (m_Target_LayerType == LAYER_TYPE::Rock) {
		CRock* rockTarget = static_cast<CRock*>(m_Target);
		rockTarget->Move(Move_Direction);
		pCharacter_Rock_Kick->Play(false);
		m_FlipbookVFXPlayer->Play(KICK_VFX_1, 30.f, false);
	}

	//키가 없으면 KEYBOX는 벽하고 동일 취급
	else if (m_Target_LayerType == LAYER_TYPE::WALL || m_Target_LayerType == LAYER_TYPE::KEYBOX) {
		pCharacter_Rock_Kick->Play(false);
		m_FlipbookVFXPlayer->Play(KICK_VFX_1, 30.f, false);
	}
	else if (m_Target_LayerType == LAYER_TYPE::BROKE_CHAIN) {
		CBrakeChain* monsterTarget = static_cast<CBrakeChain*>(m_Target);
		m_FlipbookVFXPlayer->Play(KICK_VFX_1, 30.f, false);

		if (monsterTarget->dir == 0) {
			if (kickchainsoundindex_Left == 0) {
				boss_chain_kick_01L->Play();
			}
			else if (kickchainsoundindex_Left == 1) {
				boss_chain_kick_02L->Play();
			}
			else if (kickchainsoundindex_Left == 2) {
				boss_chain_kick_03L->Play();
			}
			kickchainsoundindex_Left = (kickchainsoundindex_Left + 1) % 3;
		}
		else if (monsterTarget->dir == 1) {
			if (kickchainsoundindex_Right == 0) {
				boss_chain_kick_01R->Play();
			}
			else if (kickchainsoundindex_Right == 1) {
				boss_chain_kick_02R->Play();
			}
			else if (kickchainsoundindex_Right == 2) {
				boss_chain_kick_03R->Play();
			}
			kickchainsoundindex_Right = (kickchainsoundindex_Right + 1) % 3;
		}

		if (monsterTarget->hp - 10 == 0) {
			if (monsterTarget->dir == 0) {
				boss_chain_break_01L->Play();
			}
			else {
				boss_chain_break_01R->Play();
			}
		}

		monsterTarget->hp -= 10;
	}

	if (Move_Direction == D_LEFT) {
		Dir = S_LEFT;
	}
	else if (Move_Direction == D_RIGHT) {
		Dir = S_RIGHT;
	}

	if (Dir == S_RIGHT) {
		m_FlipbookPlayer->Play(KICK_RIGHT, 15.f, false);
	}
	else if (Dir == S_LEFT) {
		m_FlipbookPlayer->Play(KICK_LEFT, 15.f, false);
	}
}

void CPlayer::IFINPLACETHORNUP(const std::vector<CObj*>& vecThorn)
{
	if (!PlayerMove) {
		for (size_t i = 0; i < vecThorn.size(); ++i) {
			Vec2 vMonPos = vecThorn[i]->GetPos(); // 몬스터의 위치
			//가만히에서 가시가 돋아날 경우
			CThorn* th = dynamic_cast<CThorn*>(vecThorn[i]);
			if (th->CheckStayThorn()) {
				m_FlipbookVFXPlayer->Play(HUGE_VFX_1, 15.f, false);
				VFX_HUGE_RENDER = true;
			}
		}
	}
}

void CPlayer::HugeCamera()
{
	CCamera::GetInst()->Oscillation(0.01, 3, 5);
}

void CPlayer::IFNextPointUpThorn()
{
	if (m_Target_Thorn != nullptr) {
		CThorn* th = dynamic_cast<CThorn*>(m_Target_Thorn);
		if (th->ThornNUM == 0) {
			if (PlayerMove_Count > 0) {
				m_FlipbookVFXPlayer->Play(HUGE_VFX_2, 15.f, false);
				VFX_HUGE_RENDER = true;
				pThorn_damage0->Play();
				PlayerMove_Count--;
			}
		}
	}
}

void CPlayer::UsePlayerMoveVFXFlipbook()
{
	if (VFX_MOVE_RENDER == false) {

		MoveVFXRenderPos = GetRenderPos();
		m_FlipbookMOVEVFXPlayer->Play(MOVE_VFX_1, 10.f, false);
		VFX_MOVE_RENDER = true;
	}
}

void CPlayer::MoveLogic()
{
	Vec2 z = GetPos();

	PLAYER_MOVING_CHECK = true;

	//이동 수정
	if (Move_Direction == D_LEFT) {
		Dir = S_LEFT;
		m_FlipbookPlayer->Play(MOVE_LEFT, 20.f, true);
		Moving_MovePos = Vec2(-100.f, 0.f);
	}
	else if (Move_Direction == D_RIGHT) {
		Dir = S_RIGHT;
		m_FlipbookPlayer->Play(MOVE_RIGHT, 20.f, true);
		Moving_MovePos = Vec2(100.f, 0.f);
	}
	else if (Move_Direction == D_UP) {
		if (Dir == S_LEFT) {
			m_FlipbookPlayer->Play(MOVE_LEFT, 20.f, true);
		}
		else if (Dir == S_RIGHT) {
			m_FlipbookPlayer->Play(MOVE_RIGHT, 20.f, true);
		}
		Moving_MovePos = Vec2(0.f, -100.f);
		int a = 0;
	}
	else if (Move_Direction == D_DOWN) {
		if (Dir == S_LEFT) {
			m_FlipbookPlayer->Play(MOVE_LEFT, 20.f, true);
		}
		else if (Dir == S_RIGHT) {
			m_FlipbookPlayer->Play(MOVE_RIGHT, 20.f, true);
		}
		Moving_MovePos = Vec2(0.f, 100.f);
		int a = 0;
	}
	pCharacter_Move->Play(false);
	
}

void CPlayer::PlayHugeVFX()
{
	VFX_HUGE_RENDER = true;
	m_FlipbookVFXPlayer->Play(HUGE_VFX_1, 15.f, false);
}

//렌더링
void CPlayer::Render()
{
	//BOSS 스테이지 저지먼트 점프가 실행 될 수 있을 경우

	if (TalkPartCheck) {
		TALKCUTSCENE_RENDER();
	}
	else {
		DEFAULT_RENDER();
	}
	if (PauseMenu)
	{

		Vec2 vPos = CEngine::GetInst()->GetResolution();
		Vec2 vResolution = CEngine::GetInst()->GetResolution();
		Vec2 vScale = GetScale();
		HDC dc = CEngine::GetInst()->GetSecondDC();

		// 색상과 투명도 설정
		COLORREF color = RGB(2, 2, 27);
		BYTE alpha = 128;  // 투명도 (0 = 완전 투명, 255 = 불투명)

		// 사각형에 채울 브러시와 비트맵 생성
		HBITMAP hBitmap = CreateCompatibleBitmap(dc, vScale.x, vScale.y);
		HDC hMemDC = CreateCompatibleDC(dc);
		SelectObject(hMemDC, hBitmap);
		HBRUSH hBrush = CreateSolidBrush(color);
		SelectObject(hMemDC, hBrush);

		// 사각형 그리기
		PatBlt(hMemDC, 0, 0, vScale.x, vScale.y, PATCOPY);

		// AlphaBlend 함수로 투명도 적용하여 화면에 그리기
		BLENDFUNCTION blendFunc = { AC_SRC_OVER, 0, alpha, 0 };
		AlphaBlend(dc, 0, vResolution.y - 1080.f, 1920.f, 2000.f, hMemDC, 0, 0, vScale.x, vScale.y, blendFunc);

		// 리소스 정리
		SelectObject(dc, hBrush); // 이전 브러시 복원
		DeleteObject(hBrush);
		DeleteObject(hBitmap);
		DeleteDC(hMemDC);

		HFONT hFont = CreateFont(
			60,                    // 글자 높이
			0,                     // 글자 폭 (0으로 자동 설정)
			0,                     // 글자 각도
			0,                     // 글자 기준 각도
			FW_BOLD,			   // 글자 두께
			FALSE,                 // 기울임 여부
			FALSE,                 // 밑줄 여부
			FALSE,                 // 취소선 여부
			ANSI_CHARSET,          // 문자 집합
			OUT_DEFAULT_PRECIS,    // 출력 정밀도
			CLIP_DEFAULT_PRECIS,   // 클리핑 정밀도
			DEFAULT_QUALITY,       // 출력 품질
			DEFAULT_PITCH | FF_SWISS, // 글꼴 가변폭 및 글꼴 패밀리
			L"CrimsonPro-Medium"   // 글꼴 이름
		);

		HFONT hOldFont = (HFONT)SelectObject(dc, hFont);

		SetGraphicsMode(dc, GM_ADVANCED);
		SetBkMode(dc, TRANSPARENT);

		COLORREF textColor = RGB(229, 76, 80);
		SetTextColor(dc, textColor);

		std::wstring text = L"● 일시정지 메뉴 ●";

		// 중앙 정렬을 위해 텍스트 가로 길이 계산
		SIZE textSize;
		GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);

		float textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬
		float textPosY = 150.f;

		TextOut(
			dc,
			textPosX,
			textPosY,
			text.c_str(),
			text.length()
		);

		DeleteObject(hFont);

		CTexture* m_Tex = new CTexture;

		wchar_t filePath[100] = {};
		wchar_t textureName[100] = {};

		BLENDFUNCTION blend = {};

		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		swprintf_s(filePath, 100, L"Texture\\ritBorder.png");
		swprintf_s(textureName, 100, L"ritBorder");

		CTexture* bchain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		AlphaBlend(dc
			, vResolution.x / 2.f - bchain->GetWidth()
			, (vResolution.y - bchain->GetHeight()) / 2.f - 140.f + 200.f
			, bchain->GetWidth()
			, bchain->GetHeight()
			, bchain->GetDC()
			, 0, 0
			, bchain->GetWidth()
			, bchain->GetHeight()
			, blend);

		swprintf_s(filePath, 100, L"Texture\\ritBorderRIGHT.png");
		swprintf_s(textureName, 100, L"ritBorderRIGHT");

		bchain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		AlphaBlend(dc
			, vResolution.x / 2.f
			, (vResolution.y - bchain->GetHeight()) / 2.f - 140.f + 200.f
			, bchain->GetWidth()
			, bchain->GetHeight()
			, bchain->GetDC()
			, 0, 0
			, bchain->GetWidth()
			, bchain->GetHeight()
			, blend);

		//swprintf_s(filePath, 100, L"Texture\\NonChoiceButton.png");
		//swprintf_s(textureName, 100, L"NonChoiceButton");
		
		//################## chocie
		hFont = CreateFont(
			40,                    // 글자 높이
			0,                     // 글자 폭 (0으로 자동 설정)
			0,                     // 글자 각도
			0,                     // 글자 기준 각도
			FW_BOLD,			   // 글자 두께
			FALSE,                 // 기울임 여부
			FALSE,                 // 밑줄 여부
			FALSE,                 // 취소선 여부
			ANSI_CHARSET,          // 문자 집합
			OUT_DEFAULT_PRECIS,    // 출력 정밀도
			CLIP_DEFAULT_PRECIS,   // 클리핑 정밀도
			DEFAULT_QUALITY,       // 출력 품질
			DEFAULT_PITCH | FF_SWISS, // 글꼴 가변폭 및 글꼴 패밀리
			L"CrimsonPro-Medium"   // 글꼴 이름
		);

		hOldFont = (HFONT)SelectObject(dc, hFont);

		SetGraphicsMode(dc, GM_ADVANCED);
		SetBkMode(dc, TRANSPARENT);

		// 중앙 정렬을 위해 텍스트 가로 길이 계산

		float gamestart = 230.f;
		float puzzle = 330.f;
		float music = 430.f;
		float sound = 570.f;
		float main = 710.f;
	
		if (PauseMenuFocusingNum == 0) {

			swprintf_s(filePath, 100, L"Texture\\ChoiceButton.png");
			swprintf_s(textureName, 100, L"ChoiceButton");

			bchain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				, 660.f
				, gamestart
				, bchain->GetWidth() * 0.6f
				, bchain->GetHeight()
				, bchain->GetDC()
				, 0, 0
				, bchain->GetWidth()
				, bchain->GetHeight()
				, blend);

			textColor = RGB(255, 255, 255);
			SetTextColor(dc, textColor);
			text = L"게임 재개";
			GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
			textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬
			TextOut(
				dc,
				textPosX,
				gamestart + 20.f,
				text.c_str(),
				text.length()
			);
		}
		else {
			swprintf_s(filePath, 100, L"Texture\\NonChoiceButton.png");
			swprintf_s(textureName, 100, L"NonChoiceButton");

			bchain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				, 710.f
				, gamestart
				, bchain->GetWidth() * 0.5f
				, bchain->GetHeight() * 0.8
				, bchain->GetDC()
				, 0, 0
				, bchain->GetWidth()
				, bchain->GetHeight()
				, blend);

			textColor = RGB(191, 166, 174);
			SetTextColor(dc, textColor);
			text = L"게임 재개";
			GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
			textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬
			TextOut(
				dc,
				textPosX,
				gamestart + 20.f,
				text.c_str(),
				text.length()
			);
		}

		if (PauseMenuFocusingNum == 1) {
			swprintf_s(filePath, 100, L"Texture\\ChoiceButton.png");
			swprintf_s(textureName, 100, L"ChoiceButton");

			bchain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				, 660.f
				, puzzle
				, bchain->GetWidth() * 0.6f
				, bchain->GetHeight()
				, bchain->GetDC()
				, 0, 0
				, bchain->GetWidth()
				, bchain->GetHeight()
				, blend);

			textColor = RGB(255, 255, 255);
			SetTextColor(dc, textColor);
			if (CurLevel != LEVEL_CHECK::BOSS_0) {
				text = L"퍼즐 건너뛰기";
			}
			else {
				text = L"God Mode";
			}
			GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
			textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬
			TextOut(
				dc,
				textPosX,
				puzzle + 20.f,
				text.c_str(),
				text.length()
			);

		}
		else {
			swprintf_s(filePath, 100, L"Texture\\NonChoiceButton.png");
			swprintf_s(textureName, 100, L"NonChoiceButton");

			bchain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				, 710.f
				, puzzle
				, bchain->GetWidth() * 0.5f
				, bchain->GetHeight() * 0.8
				, bchain->GetDC()
				, 0, 0
				, bchain->GetWidth()
				, bchain->GetHeight()
				, blend);

			textColor = RGB(191, 166, 174);
			SetTextColor(dc, textColor);
			if (CurLevel != LEVEL_CHECK::BOSS_0) {
				text = L"퍼즐 건너뛰기";
			}
			else {
				text = L"God Mode";
			}
			GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
			textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬
			TextOut(
				dc,
				textPosX,
				puzzle + 20.f,
				text.c_str(),
				text.length()
			);
		}

		if (PauseMenuFocusingNum == 2) {
			swprintf_s(filePath, 100, L"Texture\\ChoiceButton.png");
			swprintf_s(textureName, 100, L"ChoiceButton");

			bchain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				, 660.f
				, music
				, bchain->GetWidth() * 0.6f
				, bchain->GetHeight()
				, bchain->GetDC()
				, 0, 0
				, bchain->GetWidth()
				, bchain->GetHeight()
				, blend);

			textColor = RGB(255, 255, 255);
			SetTextColor(dc, textColor);
			text = L"배경음";
			GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
			textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬
			TextOut(
				dc,
				textPosX,
				music + 20.f,
				text.c_str(),
				text.length()
			);

			if (MusicIndex == 0) {
				text = L"높음";
			}
			else if (MusicIndex == 1) {
				text = L"중간";
			}
			else if (MusicIndex == 2) {
				text = L"낮음";
			}

			GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
			textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬
			TextOut(
				dc,
				textPosX,
				music + 90.f,
				text.c_str(),
				text.length()
			);

		}
		else {
			swprintf_s(filePath, 100, L"Texture\\NonChoiceButton.png");
			swprintf_s(textureName, 100, L"NonChoiceButton");

			bchain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				, 710.f
				, music
				, bchain->GetWidth() * 0.5f
				, bchain->GetHeight() * 0.8
				, bchain->GetDC()
				, 0, 0
				, bchain->GetWidth()
				, bchain->GetHeight()
				, blend);

			textColor = RGB(191, 166, 174);
			SetTextColor(dc, textColor);
			text = L"배경음";
			GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
			textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬
			TextOut(
				dc,
				textPosX,
				music + 20.f,
				text.c_str(),
				text.length()
			);

			if (MusicIndex == 0) {
				text = L"높음";
			}
			else if (MusicIndex == 1) {
				text = L"중간";
			}
			else if (MusicIndex == 2) {
				text = L"낮음";
			}

			GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
			textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬
			TextOut(
				dc,
				textPosX,
				music + 90.f,
				text.c_str(),
				text.length()
			);
		}

		if (PauseMenuFocusingNum == 3) {
			swprintf_s(filePath, 100, L"Texture\\ChoiceButton.png");
			swprintf_s(textureName, 100, L"ChoiceButton");

			bchain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				, 660.f
				, sound
				, bchain->GetWidth() * 0.6f
				, bchain->GetHeight()
				, bchain->GetDC()
				, 0, 0
				, bchain->GetWidth()
				, bchain->GetHeight()
				, blend);

			textColor = RGB(255, 255, 255);
			SetTextColor(dc, textColor);
			text = L"효과음";
			GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
			textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬
			TextOut(
				dc,
				textPosX,
				sound + 20.f,
				text.c_str(),
				text.length()
			);

			if (SoundIndex == 0) {
				text = L"높음";
			}
			else if (SoundIndex == 1) {
				text = L"중간";
			}
			else if (SoundIndex == 2) {
				text = L"낮음";
			}
			GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
			textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬
			TextOut(
				dc,
				textPosX,
				sound + 90.f,
				text.c_str(),
				text.length()
			);
		}
		else {
			swprintf_s(filePath, 100, L"Texture\\NonChoiceButton.png");
			swprintf_s(textureName, 100, L"NonChoiceButton");

			bchain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				, 660.f
				, sound
				, bchain->GetWidth() * 0.6f
				, bchain->GetHeight()
				, bchain->GetDC()
				, 0, 0
				, bchain->GetWidth()
				, bchain->GetHeight()
				, blend);


			textColor = RGB(191, 166, 174);
			SetTextColor(dc, textColor);
			text = L"효과음";
			GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
			textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬
			TextOut(
				dc,
				textPosX,
				sound + 20.f,
				text.c_str(),
				text.length()
			);


			if (SoundIndex == 0) {
				text = L"높음";
			}
			else if (SoundIndex == 1) {
				text = L"중간";
			}
			else if (SoundIndex == 2) {
				text = L"낮음";
			}

			GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
			textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬
			TextOut(
				dc,
				textPosX,
				sound + 90.f,
				text.c_str(),
				text.length()
			);
		}
		if (PauseMenuFocusingNum == 4) {
			swprintf_s(filePath, 100, L"Texture\\ChoiceButton.png");
			swprintf_s(textureName, 100, L"ChoiceButton");

			bchain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				, 660.f
				, main
				, bchain->GetWidth() * 0.6f
				, bchain->GetHeight()
				, bchain->GetDC()
				, 0, 0
				, bchain->GetWidth()
				, bchain->GetHeight()
				, blend);

			textColor = RGB(255, 255, 255);
			SetTextColor(dc, textColor);
			text = L"메인 화면으로";
			GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
			textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬
			TextOut(
				dc,
				textPosX,
				main + 20.f,
				text.c_str(),
				text.length()
			);
		}
		else {
			swprintf_s(filePath, 100, L"Texture\\NonChoiceButton.png");
			swprintf_s(textureName, 100, L"NonChoiceButton");

			bchain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				, 660.f
				, main
				, bchain->GetWidth() * 0.6f
				, bchain->GetHeight()
				, bchain->GetDC()
				, 0, 0
				, bchain->GetWidth()
				, bchain->GetHeight()
				, blend);


			textColor = RGB(191, 166, 174);
			SetTextColor(dc, textColor);
			text = L"메인 화면으로";
			GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
			textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬
			TextOut(
				dc,
				textPosX,
				main + 20.f,
				text.c_str(),
				text.length()
			);
		}

		//################## chocie

		swprintf_s(filePath, 100, L"Texture\\ritCode0004.png");
		swprintf_s(textureName, 100, L"ritCode0004");

		CTexture* britcode = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		AlphaBlend(dc
			, (vResolution.x - britcode->GetWidth()) /2.f
			, 800.f
			, britcode->GetWidth()
			, britcode->GetHeight()
			, britcode->GetDC()
			, 0, 0
			, britcode->GetWidth()
			, britcode->GetHeight()
			, blend);

		AlphaBlend(dc
			, ((vResolution.x - britcode->GetWidth()) / 2.f) - britcode->GetWidth()
			, 800.f
			, britcode->GetWidth()
			, britcode->GetHeight()
			, britcode->GetDC()
			, 0, 0
			, britcode->GetWidth()
			, britcode->GetHeight()
			, blend);

		AlphaBlend(dc
			, ((vResolution.x - britcode->GetWidth()) / 2.f) + britcode->GetWidth()
			, 800.f
			, britcode->GetWidth()
			, britcode->GetHeight()
			, britcode->GetDC()
			, 0, 0
			, britcode->GetWidth()
			, britcode->GetHeight()
			, blend);
		DeleteObject(hOldFont);
		HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
		ReleaseDC(hwnd, dc);
		DeleteObject(britcode);
		DeleteObject(m_Tex);
		DeleteObject(bchain);
	}


}

void CPlayer::TALKCUTSCENE_RENDER()
{
	PlayDialogue_Start_sound();
	DrawBlackBackground();
	DrawPNGBackground();
	DrawPngCharacter();
	DrawTalk();
}

void CPlayer::DEFAULT_RENDER()
{
	//CObj::Render();
	if (JudmentJump && TalkCutSceneIndex == 1) {
		m_FlipbookJudmentJump->CenterRender(-400.f, -10.f);
	}
	if (VFX_MOVE_RENDER) {
		m_FlipbookMOVEVFXPlayer->Inplace_Render(MoveVFXRenderPos, 50.f);
	}
	if (VFX_HUGE_RENDER) {
		//CCamera::GetInst()->Oscillation(0.01f, 4.f, 1.f);
		HugeCamera();
		m_FlipbookVFXPlayer->Render(50.f);
	}
	if (VFX_KICK_RENDER) {
		if (Move_Direction == D_LEFT) {
			m_FlipbookVFXPlayer->Render(50.f, -90.f, 1.0f);
		}
		else if (Move_Direction == D_RIGHT) {
			m_FlipbookVFXPlayer->Render(50.f, 90.f, 1.0f);
		}
		else if (Move_Direction == D_DOWN) {
			m_FlipbookVFXPlayer->Render(120.f, 0.f, 1.0f);
		}
		else if (Move_Direction == D_UP) {
			m_FlipbookVFXPlayer->Render(-60.f, 0.f, 1.0f);
		}
	}
	m_FlipbookPlayer->Render(10.f + y_offset, x_offset);
	Dialogue_Start = false;
}

void CPlayer::DrawTalk() {

	if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].CutsceneType == CUTSCENE_TYPE::CHOICE_CUTSCENE) {
		ChoiceCutSceneTalk();
	}
	else {
		DefaultTalkCutScene();
	}
}

void CPlayer::DefaultTalkCutScene()
{
	float hg = 700.f;
	CTexture* m_Tex = new CTexture;

	wchar_t filePath[100] = {};
	wchar_t textureName[100] = {};

	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	HFONT hFont = CreateFont(
		60,                    // 글자 높이
		0,                     // 글자 폭 (0으로 자동 설정)
		0,                     // 글자 각도
		0,                     // 글자 기준 각도
		FW_BOLD,			   // 글자 두께
		FALSE,                 // 기울임 여부
		FALSE,                 // 밑줄 여부
		FALSE,                 // 취소선 여부
		ANSI_CHARSET,          // 문자 집합
		OUT_DEFAULT_PRECIS,    // 출력 정밀도
		CLIP_DEFAULT_PRECIS,   // 클리핑 정밀도
		DEFAULT_QUALITY,       // 출력 품질
		DEFAULT_PITCH | FF_SWISS, // 글꼴 가변폭 및 글꼴 패밀리
		L"CrimsonPro-Medium"   // 글꼴 이름
	);

	HDC dc = CEngine::GetInst()->GetSecondDC();
	HFONT hOldFont = (HFONT)SelectObject(dc, hFont);

	SetGraphicsMode(dc, GM_ADVANCED);
	SetBkMode(dc, TRANSPARENT);

	COLORREF textColor = RGB(192, 80, 75);
	SetTextColor(dc, textColor);

	std::wstring text;
	if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::PANDEMONICA) {
		text = L"● 피곤한 악마, 판데모니카 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::MODEUS) {
		text = L"● 음란한 악마, 모데우스 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::CERBERUS) {
		text = L"● 세쌍둥이 악마, 케르베로스 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::MALINA) {
		text = L"● 시큰둥한 악마, 말리나 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::ZDRADA) {
		text = L"● 상스러운 악마, 즈드라다 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::AZAZEL) {
		text = L"● 호기심 많은 천사, 아자젤 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::JUSTICE) {
		text = L"● 끝내주는 악마, 저스티스 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::LUCY) {
		text = L"● 지옥의 CEO, 루시퍼 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::JUDGMENT) {
		text = L"● 고위 기소관, 저지먼트 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::POLICE) {
		text = L"● 경찰, SWAT ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::QUESTION) {
		text = L"● ??? ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::MODEUS) {
		text = L"● 색욕의 악마, 모데우스 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::BEEL_FLY) {
		text = L"● 위대한 파리, 베엘제붑 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::HELLTAKER) {
		text = L"● 헬테이커 ●";
	}

	// 중앙 정렬을 위해 텍스트 가로 길이 계산
	SIZE textSize;
	GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);

	float textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬
	float textPosY = 166 + hg - 150.f;

	TextOut(
		dc,
		textPosX,
		textPosY - 40.f + 50.f,
		text.c_str(),
		text.length()
	);

	DeleteObject(hFont);

	hFont = CreateFont(
		40,                    // 글자 높이
		0,                     // 글자 폭 (0으로 자동 설정)
		0,                     // 글자 각도
		0,                     // 글자 기준 각도
		FW_NORMAL,			   // 글자 두께
		FALSE,                 // 기울임 여부
		FALSE,                 // 밑줄 여부
		FALSE,                 // 취소선 여부
		ANSI_CHARSET,          // 문자 집합
		OUT_DEFAULT_PRECIS,    // 출력 정밀도
		CLIP_DEFAULT_PRECIS,   // 클리핑 정밀도
		DEFAULT_QUALITY,       // 출력 품질
		DEFAULT_PITCH | FF_SWISS, // 글꼴 가변폭 및 글꼴 패밀리
		L"CrimsonPro-Medium"   // 글꼴 이름
	);

	SetTextColor(dc, RGB(255, 255, 255));
	SetBkMode(dc, TRANSPARENT);
	hOldFont = (HFONT)SelectObject(dc, hFont);

	hg = 600.f;

	if (wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText, L"드디어 만나네. 내가 준비한 시험을 통과했으니 그 만한") == 0 && lucy_facecheck) {
		text = NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText;
		GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
		textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬

		TextOut(
			dc,
			textPosX,
			textPosY + 20.f + 50.f,
			text.c_str(),
			text.length()
		);

		text = NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonSecondText;
		GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
		textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬

		TextOut(
			dc,
			textPosX,
			textPosY + 60.f + 50.f,
			text.c_str(),
			text.length()
		);
	}
	else if(wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText, L"드디어 만나네. 내가 준비한 시험을 통과했으니 그 만한") != 0){
		text = NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText;
		GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
		textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬

		TextOut(
			dc,
			textPosX,
			textPosY + 20.f + 50.f,
			text.c_str(),
			text.length()
		);

		text = NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonSecondText;
		GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
		textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬

		TextOut(
			dc,
			textPosX,
			textPosY + 60.f + 50.f,
			text.c_str(),
			text.length()
		);
	}

	DeleteObject(hFont);

	Vec2 x;
	x.x = vResolution.x / 2.f - 10.f;
	x.y = textPosY + 200.f;
	//elapsedTime += DT;
	//if (elapsedTime >= 1.0f && !actionStarted) {
	//	actionStarted = true; // 동작 시작 플래그 설정
	//}
	//if (TalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].CutsceneType == CUTSCENE_TYPE::SUCESS_CUTSCENE) {

	//}
	if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].CutsceneType == CUTSCENE_TYPE::TALK_CUTSCENE || NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].CutsceneType == CUTSCENE_TYPE::DIE_CUTSCENE || NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].CutsceneType == CUTSCENE_TYPE::NEXTINDEXSCENE) {
		m_FlipbookCutSceneBooperPlayer->Inplace_Render(x,50.f);
	}
	//else if (TalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].CutsceneType == CUTSCENE_TYPE::DIE_CUTSCENE) {

	//}
	if (j_Success) {
	//	m_FlipbookCutSceneDemonPlayer->Fire_Render(-800.f, 150.f, 0.9f);
	//	m_FlipbookCutSceneDemonPlayerRight->Fire_Render(800.f, 150.f, 0.9f);
		m_FlipbookCutSceneDemonPlayer->CenterRender(300.f + 50.f, -800.f, 0.9f);
		m_FlipbookCutSceneDemonPlayerRight->CenterRender(300.f + 50.f, 800.f, 0.9f);
	}
	DeleteObject(m_Tex);
	
}

void CPlayer::ChoiceCutSceneTalk()
{
	float hg = 700.f;
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CTexture* m_Tex = new CTexture;
	HDC dc = CEngine::GetInst()->GetSecondDC();

	wchar_t filePath[100] = {};
	wchar_t textureName[100] = {};

	HFONT hFont = CreateFont(
		60,                    // 글자 높이
		0,                     // 글자 폭 (0으로 자동 설정)
		0,                     // 글자 각도
		0,                     // 글자 기준 각도
		FW_BOLD,			   // 글자 두께
		FALSE,                 // 기울임 여부
		FALSE,                 // 밑줄 여부
		FALSE,                 // 취소선 여부
		ANSI_CHARSET,          // 문자 집합
		OUT_DEFAULT_PRECIS,    // 출력 정밀도
		CLIP_DEFAULT_PRECIS,   // 클리핑 정밀도
		DEFAULT_QUALITY,       // 출력 품질
		DEFAULT_PITCH | FF_SWISS, // 글꼴 가변폭 및 글꼴 패밀리
		L"CrimsonPro-Medium"   // 글꼴 이름
	);


	HFONT hOldFont = (HFONT)SelectObject(dc, hFont);

	SetGraphicsMode(dc, GM_ADVANCED);
	SetBkMode(dc, TRANSPARENT);

	COLORREF textColor = RGB(192, 80, 75);
	SetTextColor(dc, textColor);

	std::wstring text;
	if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::PANDEMONICA) {
		text = L"● 피곤한 악마, 판데모니카 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::MODEUS) {
		text = L"● 음란한 악마, 모데우스 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::CERBERUS) {
		text = L"● 세쌍둥이 악마, 케르베로스 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::MALINA) {
		text = L"● 시큰둥한 악마, 말리나 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::ZDRADA) {
		text = L"● 상스러운 악마, 즈드라다 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::AZAZEL) {
		text = L"● 호기심 많은 천사, 아자젤 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::JUSTICE) {
		text = L"● 끝내주는 악마, 저스티스 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::LUCY) {
		text = L"● 지옥의 CEO, 루시퍼 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::JUDGMENT) {
		text = L"● 고위 기소관, 저지먼트 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::POLICE) {
		text = L"● 경찰, SWAT ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::QUESTION) {
		text = L"● ??? ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::MODEUS) {
		text = L"● 색욕의 악마, 모데우스 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::BEEL_FLY) {
		text = L"● 위대한 파리, 베엘제붑 ●";
	}
	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == DEMON_TYPE::HELLTAKER) {
		text = L"● 헬테이커 ●";
	}
	DeleteObject(hFont);

	// 중앙 정렬을 위해 텍스트 가로 길이 계산
	SIZE textSize;
	GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);

	float textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬
	float textPosY = 166 + hg - 150.f;

	TextOut(
		dc,
		textPosX,
		textPosY - 40.f + 50.f,
		text.c_str(),
		text.length()
	);

	swprintf_s(filePath, 100, L"Texture\\NonChoiceButton.png");
	swprintf_s(textureName, 100, L"NonChoiceButton");

	CTexture* pNonchoice = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

	swprintf_s(filePath, 100, L"Texture\\ChoiceButton.png");
	swprintf_s(textureName, 100, L"ChoiceButton");

	CTexture* pchoice = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);


	hFont = CreateFont(
		40,                    // 글자 높이
		0,                     // 글자 폭 (0으로 자동 설정)
		0,                     // 글자 각도
		0,                     // 글자 기준 각도
		FW_NORMAL,			   // 글자 두께
		FALSE,                 // 기울임 여부
		FALSE,                 // 밑줄 여부
		FALSE,                 // 취소선 여부
		ANSI_CHARSET,          // 문자 집합
		OUT_DEFAULT_PRECIS,    // 출력 정밀도
		CLIP_DEFAULT_PRECIS,   // 클리핑 정밀도
		DEFAULT_QUALITY,       // 출력 품질
		DEFAULT_PITCH | FF_SWISS, // 글꼴 가변폭 및 글꼴 패밀리
		L"CrimsonPro-Medium"   // 글꼴 이름
	);

	SetTextColor(dc, RGB(255, 255, 255));
	SetBkMode(dc, TRANSPARENT);
	hOldFont = (HFONT)SelectObject(dc, hFont);


	text = NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText;
	GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
	textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬

	TextOut(
		dc,
		textPosX,
		textPosY + 20.f + 50.f,
		text.c_str(),
		text.length()
	);

	text = NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonSecondText;
	GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
	textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬

	TextOut(
		dc,
		textPosX,
		textPosY + 60.f + 50.f,
		text.c_str(),
		text.length()
	);
	
	text = NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText;
	GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
	textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬

	TextOut(
		dc,
		textPosX,
		textPosY + 20.f + 50.f,
		text.c_str(),
		text.length()
	);

	text = NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonSecondText;
	GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
	textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬

	TextOut(
		dc,
		textPosX,
		textPosY + 60.f + 50.f,
		text.c_str(),
		text.length()
	);

	DeleteObject(hFont);

	hFont = CreateFont(
		35,                    // 글자 높이
		0,                     // 글자 폭 (0으로 자동 설정)
		0,                     // 글자 각도
		0,                     // 글자 기준 각도
		FW_NORMAL,			   // 글자 두께
		FALSE,                 // 기울임 여부
		FALSE,                 // 밑줄 여부
		FALSE,                 // 취소선 여부
		ANSI_CHARSET,          // 문자 집합
		OUT_DEFAULT_PRECIS,    // 출력 정밀도
		CLIP_DEFAULT_PRECIS,   // 클리핑 정밀도
		DEFAULT_QUALITY,       // 출력 품질
		DEFAULT_PITCH | FF_SWISS, // 글꼴 가변폭 및 글꼴 패밀리
		L"CrimsonPro-Medium"   // 글꼴 이름
	);

	SetTextColor(dc, RGB(255, 255, 255));
	SetBkMode(dc, TRANSPARENT);
	hOldFont = (HFONT)SelectObject(dc, hFont);

	text = NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].HeroFirstText;

	GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);
	textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬

	TextOut(
		dc,
		textPosX,
		textPosY + 125.f + 50.f,
		text.c_str(),
		text.length()
	);

	DeleteObject(hFont);

	hFont = CreateFont(
		35,                    // 글자 높이
		0,                     // 글자 폭 (0으로 자동 설정)
		0,                     // 글자 각도
		0,                     // 글자 기준 각도
		FW_NORMAL,			   // 글자 두께
		FALSE,                 // 기울임 여부
		FALSE,                 // 밑줄 여부
		FALSE,                 // 취소선 여부
		ANSI_CHARSET,          // 문자 집합
		OUT_DEFAULT_PRECIS,    // 출력 정밀도
		CLIP_DEFAULT_PRECIS,   // 클리핑 정밀도
		DEFAULT_QUALITY,       // 출력 품질
		DEFAULT_PITCH | FF_SWISS, // 글꼴 가변폭 및 글꼴 패밀리
		L"CrimsonPro-Medium"   // 글꼴 이름
	);

	SetTextColor(dc, RGB(255, 255, 255));
	SetBkMode(dc, TRANSPARENT);
	hOldFont = (HFONT)SelectObject(dc, hFont);

	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	// 두 번째 텍스트 중앙 정렬
	text = NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].HeroSecondText;
	GetTextExtentPoint32(dc, text.c_str(), text.length(), &textSize);

	textPosX = (vResolution.x - textSize.cx) / 2; // 가로 중앙 정렬

	TextOut(
		dc,
		textPosX,
		textPosY + 215.f + 50.f,
		text.c_str(),
		text.length()
	);

	blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;
	float scale = 0.9f;

	if (FocusChoice == 0) {
		//choice 이미지
		AlphaBlend(dc
			, 460.f
			, textPosY + 100.f + 50.f
			, pchoice->GetWidth()
			, pchoice->GetHeight()
			, pchoice->GetDC()
			, 0, 0
			, pchoice->GetWidth()
			, pchoice->GetHeight()
			, blend);

		//Non choice 이미지
		AlphaBlend(dc
			, 460.f + 46.f
			, textPosY + 190.f + 50.f
			, pNonchoice->GetWidth() * scale
			, pNonchoice->GetHeight() * scale
			, pNonchoice->GetDC()
			, 0, 0
			, pNonchoice->GetWidth()
			, pNonchoice->GetHeight()
			, blend);

	}
	else {
		AlphaBlend(dc
			, 460.f + 46.f
			, textPosY + 100.f + 50.f
			, pNonchoice->GetWidth() * scale
			, pNonchoice->GetHeight() * scale
			, pNonchoice->GetDC()
			, 0, 0
			, pNonchoice->GetWidth()
			, pNonchoice->GetHeight()
			, blend);

		AlphaBlend(dc
			, 460.f
			, textPosY + 190.f + 50.f
			, pchoice->GetWidth()
			, pchoice->GetHeight()
			, pchoice->GetDC()
			, 0, 0
			, pchoice->GetWidth()
			, pchoice->GetHeight()
			, blend);
	}
	SelectObject(dc, hOldFont); // 원래 폰트로 복구
	DeleteObject(hFont); // 생성한 폰트 삭제
	DeleteObject(m_Tex);
	DeleteObject(pchoice);
	DeleteObject(pNonchoice);
	DeleteObject(hOldFont);
}

void CPlayer::DrawPngCharacter()
{
	CTexture* m_Tex = new CTexture;
	CTexture* bchain = new CTexture;
	CTexture* m_Texb = new CTexture;
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	wchar_t filePath[100] = {};
	wchar_t textureName[100] = {};


	swprintf_s(filePath, 100, L"Texture\\%s.png", NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].CharacterTexture);
	swprintf_s(textureName, 100, L"%s", NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].CharacterTexture);

	m_Tex = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

	HDC dc = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	if (j_bindAnimNull || (wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText, L"그리고 절망의 사슬이 가장 즐거운 법이지.") == 0 && !Judment_bind)) {

		wchar_t filePath[100] = {};
		wchar_t textureName[100] = {};

		swprintf_s(filePath, 100, L"Texture\\j_bindChainB.png");
		swprintf_s(textureName, 100, L"j_bindChainB");
		bchain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);
		AlphaBlend(dc
			, (vResolution.x - bchain->GetWidth()) / 2.f
			, (vResolution.y - bchain->GetHeight()) / 2.f - 140.f + 50.f
			, bchain->GetWidth()
			, bchain->GetHeight()
			, bchain->GetDC()
			, 0, 0
			, bchain->GetWidth()
			, bchain->GetHeight()
			, blend);

		BLENDFUNCTION blend = {};

		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(dc
			, (vResolution.x - bchain->GetWidth()) / 2.f
			, (vResolution.y - bchain->GetHeight()) / 2.f - 40.f + 50.f
			, bchain->GetWidth()
			, bchain->GetHeight()
			, bchain->GetDC()
			, 0, 0
			, bchain->GetWidth()
			, bchain->GetHeight()
			, blend);

	}

	if ((wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText, L"이제 다시 시련을 시작한다!") == 0 && j_fly)) {
		wchar_t filePath[100] = {};
		wchar_t textureName[100] = {};

		swprintf_s(filePath, 100, L"Texture\\pentaGraphic 1.png");
		swprintf_s(textureName, 100, L"pentaGraphic 1");

		bchain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		AlphaBlend(dc
			, (vResolution.x - bchain->GetWidth()) / 2.f + 350.f
			, (vResolution.y - bchain->GetHeight()) / 2.f + 40.f + 50.f
			, bchain->GetWidth() * 0.6
			, bchain->GetHeight() * 0.6
			, bchain->GetDC()
			, 0, 0
			, bchain->GetWidth()
			, bchain->GetHeight()
			, blend);
		DeleteObject(bchain);
	}
	
	if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].CharacterTexture == L"") {
		return;
	}

	if (wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText, L"죄악의 기계에 시동을 걸어라! 시련을 피할 수는 없다!") == 0 && j_animintro) {
			wchar_t filePath[100] = {};
			wchar_t textureName[100] = {};

			swprintf_s(filePath, 100, L"Texture\\j_hugeChainLeft.png");
			swprintf_s(textureName, 100, L"j_hugeChainLeft");

			bchain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				, (vResolution.x - bchain->GetWidth()) / 2.f + -600.f
				, (vResolution.y - bchain->GetHeight()) + 250.f + 50.f
				, bchain->GetWidth()
				, bchain->GetHeight()
				, bchain->GetDC()
				, 0, 0
				, bchain->GetWidth()
				, bchain->GetHeight()
				, blend);

			DeleteObject(bchain);
			blend = {};

			blend.BlendOp = AC_SRC_OVER;
			blend.BlendFlags = 0;
			blend.SourceConstantAlpha = 255;
			blend.AlphaFormat = AC_SRC_ALPHA;
			swprintf_s(filePath, 100, L"Texture\\j_hugeChainLeft.png");
			swprintf_s(textureName, 100, L"j_hugeChainLeft");

			bchain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				, (vResolution.x - bchain->GetWidth()) / 2.f + -1100.f
				, (vResolution.y - bchain->GetHeight()) / 2.f + 250.f + 50.f
				, bchain->GetWidth() * 0.9
				, bchain->GetHeight() * 0.9
				, bchain->GetDC()
				, 0, 0
				, bchain->GetWidth()
				, bchain->GetHeight()
				, blend);

			swprintf_s(filePath, 100, L"Texture\\j_hugeChainRight.png");
			swprintf_s(textureName, 100, L"j_hugeChainRight");

			CTexture* bRightchain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);
			blend = {};

			blend.BlendOp = AC_SRC_OVER;
			blend.BlendFlags = 0;
			blend.SourceConstantAlpha = 255;
			blend.AlphaFormat = AC_SRC_ALPHA;
			AlphaBlend(dc
				, (vResolution.x - bRightchain->GetWidth()) / 2.f + 800.f
				, (vResolution.y - bRightchain->GetHeight()) / 2.f + 250.f + 50.f
				, bRightchain->GetWidth()
				, bRightchain->GetHeight()
				, bRightchain->GetDC()
				, 0, 0
				, bRightchain->GetWidth()
				, bRightchain->GetHeight()
				, blend);

			DeleteObject(bRightchain);

			swprintf_s(filePath, 100, L"Texture\\j_hugeChainRight.png");
			swprintf_s(textureName, 100, L"j_hugeChainRight");

			bRightchain = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);
			blend = {};

			blend.BlendOp = AC_SRC_OVER;
			blend.BlendFlags = 0;
			blend.SourceConstantAlpha = 255;
			blend.AlphaFormat = AC_SRC_ALPHA;
			AlphaBlend(dc
				, (vResolution.x - bRightchain->GetWidth()) / 2.f + 1200.f
				, (vResolution.y - bRightchain->GetHeight()) / 2.f + 250.f + 50.f
				, bRightchain->GetWidth() * 0.7
				, bRightchain->GetHeight() * 0.7
				, bRightchain->GetDC()
				, 0, 0
				, bRightchain->GetWidth()
				, bRightchain->GetHeight()
				, blend);

			DeleteObject(bchain);
		m_FlipbookCutSceneDemonPlayer->Render(-300.f + 50.f);
	}
	else if (wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText, L"드디어 만나네. 내가 준비한 시험을 통과했으니 그 만한") == 0 && !lucy_facecheck && CutsceneTime > 1.f) {
		
		if (!lucy_facecheck && CutsceneTime > 3.0f) {
			wchar_t filePath[100] = {};
			wchar_t textureName[100] = {};

			swprintf_s(filePath, 100, L"Texture\\LH_swirl_9.png");
			swprintf_s(textureName, 100, L"LH_swirl_9");

			m_Tex = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				, (vResolution.x - m_Tex->GetWidth()) / 2.f
				, (vResolution.y - m_Tex->GetHeight()) / 2.f - 240.f + 50.f
				, m_Tex->GetWidth()
				, m_Tex->GetHeight()
				, m_Tex->GetDC()
				, 0, 0
				, m_Tex->GetWidth()
				, m_Tex->GetHeight()
				, blend);

			m_FlipbookCutSceneLucyEye->Render(-326.f + 50.f, -17.f);
		}
		else if (CutsceneTime > 0.5f) {
			m_FlipbookCutSceneDemonPlayer->Render(-240.f + 50.f);
		}

	}
	else if (wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText, L"그리고 절망의 사슬이 가장 즐거운 법이지.") == 0  && Judment_bind) {
		//m_FlipbookCutSceneDemonPlayer->Render(-240.f, -200.f);
		m_FlipbookCutSceneDemonPlayer->CenterRender(-240.f + 50.f);
	}
	else if (wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText, L"이제 다시 시련을 시작한다!") == 0 && j_fly) {
		m_FlipbookCutSceneDemonPlayer->CenterRender(-200.f + 50.f,70.f,0.8f);
		//m_FlipbookCutSceneDemonPlayer->Fire_Render(0.f,-350.f,0.4f);
	}
	else {
		if (wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText, L"드디어 만나네. 내가 준비한 시험을 통과했으니 그 만한") == 0 && !lucy_facecheck && CutsceneTime < 1.f) {
			wchar_t filePath[100] = {};
			wchar_t textureName[100] = {};

			swprintf_s(filePath, 100, L"Texture\\LH_swirl_0.png");
			swprintf_s(textureName, 100, L"LH_swirl_0");

			m_Tex = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);
		}

		if (lucy_facecheck) {
			wchar_t filePath[100] = {};
			wchar_t textureName[100] = {};

			swprintf_s(filePath, 100, L"Texture\\man_skele.png");
			swprintf_s(textureName, 100, L"man_skele");

			m_Texb = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				, 692.f - 500.f
				, (vResolution.y - m_Texb->GetHeight()) / 2.f - 240.f + 50.f
				, m_Texb->GetWidth()
				, m_Texb->GetHeight()
				, m_Texb->GetDC()
				, 0, 0
				, m_Texb->GetWidth()
				, m_Texb->GetHeight()
				, blend);

			AlphaBlend(dc
				, 692.f + 300.f
				, (vResolution.y - m_Texb->GetHeight()) / 2.f - 240.f + 50.f
				, m_Texb->GetWidth()
				, m_Texb->GetHeight()
				, m_Texb->GetDC()
				, 0, 0
				, m_Texb->GetWidth()
				, m_Texb->GetHeight()
				, blend);
			DeleteObject(m_Texb);
		}

		if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonType == NULLNAME) {
			AlphaBlend(dc
				, (vResolution.x - m_Tex->GetWidth()) / 2.f
				, (vResolution.y - m_Tex->GetHeight()) / 2.f - 140.f + 50.f
				, m_Tex->GetWidth()
				, m_Tex->GetHeight()
				, m_Tex->GetDC()
				, 0, 0
				, m_Tex->GetWidth()
				, m_Tex->GetHeight()
				, blend);
		}
		else {
			AlphaBlend(dc
				, (vResolution.x - m_Tex->GetWidth()) / 2.f
				, (vResolution.y - m_Tex->GetHeight()) / 2.f - 240.f + 50.f
				, m_Tex->GetWidth()
				, m_Tex->GetHeight()
				, m_Tex->GetDC()
				, 0, 0
				, m_Tex->GetWidth()
				, m_Tex->GetHeight()
				, blend);
		}
		if (j_bindAnimNull || (wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].DemonFirstText, L"그리고 절망의 사슬이 가장 즐거운 법이지.") == 0 && !Judment_bind)) {

			wchar_t filePath[100] = {};
			wchar_t textureName[100] = {};

			swprintf_s(filePath, 100, L"Texture\\j_bindChainF.png");
			swprintf_s(textureName, 100, L"j_bindChainF");

			m_Tex = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

			AlphaBlend(dc
				, (vResolution.x - m_Tex->GetWidth()) / 2.f
				, (vResolution.y - m_Tex->GetHeight()) / 2.f - 140.f + 50.f
				, m_Tex->GetWidth()
				, m_Tex->GetHeight()
				, m_Tex->GetDC()
				, 0, 0
				, m_Tex->GetWidth()
				, m_Tex->GetHeight()
				, blend);

			AlphaBlend(dc
				, (vResolution.x - m_Tex->GetWidth()) / 2.f
				, (vResolution.y - m_Tex->GetHeight()) / 2.f - 40.f + 50.f
				, m_Tex->GetWidth()
				, m_Tex->GetHeight()
				, m_Tex->GetDC()
				, 0, 0
				, m_Tex->GetWidth()
				, m_Tex->GetHeight()
				, blend);
		}
	}
	DeleteObject(m_Tex);
	DeleteObject(m_Texb);
	DeleteObject(bchain);
	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	ReleaseDC(hwnd, dc);
}

void CPlayer::DrawPNGBackground()
{
	CTexture* m_Tex = new CTexture;
	HDC dc = CEngine::GetInst()->GetSecondDC();
	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	wchar_t filePath[100] = {};
	wchar_t textureName[100] = {};

	wchar_t* t = NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].BackgroundTexture;

	if (wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].BackgroundTexture, L"cutscene_0000_Layer-197-copy-2") == 0 ||
		wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].BackgroundTexture, L"cutscene_0002_Group-2") == 0 ||
		wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].BackgroundTexture, L"cutscene_0003_Group-3-copy-2") == 0 ||
		wcscmp(NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].BackgroundTexture, L"cutscene_0004_Layer-273-copy") == 0) {
		swprintf_s(filePath, 100, L"Texture\\%s.png", NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].BackgroundTexture);
		swprintf_s(textureName, 100, L"%s", NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].BackgroundTexture);

		m_Tex = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		Vec2 vResolution = CEngine::GetInst()->GetResolution();
		Vec2 vPos = GetRenderPos();
		Vec2 vScale = GetScale();

		BLENDFUNCTION blend = {};

		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(dc
			, (1920.f - m_Tex->GetWidth()) / 2.f
			, m_Tex->GetHeight() / 2.f - 300.f + 50.f
			, m_Tex->GetWidth()
			, m_Tex->GetHeight()
			, m_Tex->GetDC()
			, 0, 0
			, m_Tex->GetWidth()
			, m_Tex->GetHeight()
			, blend);
	}

	else if (NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].BackgroundTexture != L"") {
		swprintf_s(filePath, 100, L"Texture\\%s.png", NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].BackgroundTexture);
		swprintf_s(textureName, 100, L"%s", NewTalkCutScene[TalkCutSceneIndex][CurCutSceneIndex].BackgroundTexture);

		m_Tex = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		Vec2 vResolution = CEngine::GetInst()->GetResolution();
		Vec2 vPos = GetRenderPos();
		Vec2 vScale = GetScale();

		BLENDFUNCTION blend = {};

		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(dc
			, 0.f
			, m_Tex->GetHeight() / 2.f - 150.f + 50.f
			, m_Tex->GetWidth()
			, m_Tex->GetHeight()
			, m_Tex->GetDC()
			, 0, 0
			, m_Tex->GetWidth()
			, m_Tex->GetHeight()
			, blend);
	}
	else {
		int a = 0;
	}
	ReleaseDC(hwnd, dc);
	DeleteObject(m_Tex);

}

void CPlayer::PlayDialogue_Start_sound()
{
	if (!Dialogue_Start) {
		if (CurLevel == STAGE_7) {
			lucifer_intro_dialogue_start_v2->Play();
		}
		else{
			Dialogue_start->Play();
		}
		Dialogue_Start = true;
	}
	
}

void CPlayer::DrawBlackBackground()
{
	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	HBRUSH hBrush = CreateSolidBrush(RGB(2, 2, 27));
	HDC dc = CEngine::GetInst()->GetSecondDC();

	HBRUSH hPrevBrush = (HBRUSH)SelectObject(dc, hBrush);
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	Rectangle(dc
		, 0, vResolution.y - 1080.f
		, GetRenderPos().x + 1920.f
		, GetRenderPos().y + 2000.f);

	SelectObject(dc, hPrevBrush); // 이전 브러시 복원
	SelectObject(dc, hBrush); // 이전 브러시 복원
	DeleteObject(hBrush);
	DeleteObject(hPrevBrush);

	HWND hwnd = CEngine::GetInst()->GetMainWndHwnd();
	ReleaseDC(hwnd, dc);

}

void CPlayer::SetInitDir(int _Dir)
{
	Dir = _Dir;
}

void CPlayer::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Monster" || _OtherObject->GetName() == L"Rock")
	{
		//PLAYER_COLLISION_CHECK = true;
	}
}

void CPlayer::EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void CPlayer::CreatePlayerFlipbook()
{
	//	IDLE_LEFT,
	//	IDLE_RIGHT,
	//	MOVE_LEFT,
	//	MOVE_RIGHT


	//HUGE_VFX_1,
	//HUGE_VFX_2,
	//HUGE_VFX_3

	//CreatePngFlipbook(L"IDLE_LEFT", L"hero_left", 12);
	//CreatePngFlipbook(L"IDLE_RIGHT", L"hero", 12);
	//CreatePngFlipbook(L"MOVE_RIGHT", L"heroMove", 6);
	//CreatePngFlipbook(L"MOVE_LEFT", L"heroMove_left", 6);

	//CreatePngFlipbook(L"KICK_LEFT", L"heroKick_left", 13);
	//CreatePngFlipbook(L"KICK_RIGHT", L"heroKick", 13);

	//CreatePngFlipbook(L"HUGE_VFX_1", L"huge_vfx1", 6);
	//CreatePngFlipbook(L"HUGE_VFX_2", L"huge_vfx2", 6);
	//CreatePngFlipbook(L"HUGE_VFX_3", L"huge_vfx3", 6);
	//  KICK_VFX_1
	//	KICK_VFX_2
	//CreatePngFlipbook(L"KICK_VFX_1", L"Kick_vfx1", 4);
	//CreatePngFlipbook(L"KICK_VFX_2", L"Kick_vfx2", 4);

	//MOVE_VFX_1,
	//	MOVE_VFX_2,
	//	MOVE_VFX_3

	//CreatePngFlipbook(L"MOVE_VFX_1", L"Move_vfx1", 3);
	//CreatePngFlipbook(L"MOVE_VFX_2", L"Move_vfx2", 3);
	//CreatePngFlipbook(L"MOVE_VFX_3", L"Move_vfx3", 3);

	//CreatePngFlipbook(L"BOOPER_CUTSCENE_FLIPBOOK", L"booper", 17);
	//CreatePngFlipbook(L"PLAYER_DEATH_CUTSCENE_FLIPBOOK", L"dialogueDeathExport", 9);
	//CreatePngFlipbook(L"SUCESS_CUTSCENE_FLIPBOOK", L"success", 8);
	//CreatePngFlipbook(L"SMILE", L"heroSmile", 19); 
	//dialogueDeathExport_7
	// FlipbookPlayer 컴포넌트 추가하기

	//CreatePngFlipbook(L"J_introAnim", L"J_introAnim", 7);
	//CreatePngFlipbook(L"LH_swirl", L"LH_swirl", 15);
	//CreatePngFlipbook(L"LH_face", L"LH_face", 4);
	//CreatePngFlipbook(L"j_bindAnim", L"j_bindAnim", 7);
	//CreatePngFlipbook(L"j_flyAnim", L"j_flyAnim", 5);
	//CreatePngFlipbook(L"mainUIexport_oUI_idle", L"mainUIexport_oUI_idle", 8);
	//CreatePngFlipbook(L"mainUIexport_oUI_idleRIGHT", L"mainUIexport_oUI_idleRIGHT", 8);

	//CreatePngFlipbook(L"LUCY_FACE", L"LH_face", 4);
	//CreatePngFlipbook(L"j_glove", L"j_glove", 3);
	//CreatePngFlipbook(L"j_gloveRight", L"j_glove", 3);

	//CreatePngFlipbook(L"judgement_jump", L"judgement_jump", 9);

	m_FlipbookCutSceneDemonPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_FlipbookCutSceneDemonPlayer->AddFlipbook(J_introAnim, CAssetMgr::GetInst()->LoadFlipbook(L"J_introAnim", L"Flipbook\\J_introAnim.flip"));
	m_FlipbookCutSceneDemonPlayer->AddFlipbook(LH_swirl, CAssetMgr::GetInst()->LoadFlipbook(L"LH_swirl", L"Flipbook\\LH_swirl.flip"));
	m_FlipbookCutSceneDemonPlayer->AddFlipbook(LH_face, CAssetMgr::GetInst()->LoadFlipbook(L"LH_face", L"Flipbook\\LH_face.flip"));
	m_FlipbookCutSceneDemonPlayer->AddFlipbook(j_bindAnim, CAssetMgr::GetInst()->LoadFlipbook(L"j_bindAnim", L"Flipbook\\j_bindAnim.flip"));
	m_FlipbookCutSceneDemonPlayer->AddFlipbook(j_flyAnim, CAssetMgr::GetInst()->LoadFlipbook(L"j_flyAnim", L"Flipbook\\j_flyAnim.flip"));
	m_FlipbookCutSceneDemonPlayer->AddFlipbook(mainUIexport_oUI_idle, CAssetMgr::GetInst()->LoadFlipbook(L"mainUIexport_oUI_idle", L"Flipbook\\mainUIexport_oUI_idle.flip"));
	m_FlipbookCutSceneDemonPlayer->AddFlipbook(j_glove, CAssetMgr::GetInst()->LoadFlipbook(L"j_glove", L"Flipbook\\j_glove.flip"));

	m_FlipbookCutSceneLucyEye = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_FlipbookCutSceneLucyEye->AddFlipbook(LUCY_FACE, CAssetMgr::GetInst()->LoadFlipbook(L"LUCY_FACE", L"Flipbook\\LUCY_FACE.flip"));

	m_FlipbookJudmentJump = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_FlipbookJudmentJump->AddFlipbook(judgement_jump, CAssetMgr::GetInst()->LoadFlipbook(L"judgement_jump", L"Flipbook\\judgement_jump.flip"));

	m_FlipbookCutSceneDemonPlayerRight = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_FlipbookCutSceneDemonPlayerRight->AddFlipbook(mainUIexport_oUI_idleRIGHT, CAssetMgr::GetInst()->LoadFlipbook(L"mainUIexport_oUI_idleRIGHT", L"Flipbook\\mainUIexport_oUI_idleRIGHT.flip"));
	m_FlipbookCutSceneDemonPlayerRight->AddFlipbook(j_gloveRight, CAssetMgr::GetInst()->LoadFlipbook(L"j_gloveRight", L"Flipbook\\j_gloveRight.flip"));

	m_FlipbookCutSceneBooperPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_FlipbookCutSceneBooperPlayer->AddFlipbook(BOOPER_CUTSCENE_FLIPBOOK, CAssetMgr::GetInst()->LoadFlipbook(L"BOOPER_CUTSCENE_FLIPBOOK", L"Flipbook\\BOOPER_CUTSCENE_FLIPBOOK.flip"));
	
	m_FlipbookCutSceneDeathPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_FlipbookCutSceneDeathPlayer->AddFlipbook(PLAYER_DEATH_CUTSCENE_FLIPBOOK, CAssetMgr::GetInst()->LoadFlipbook(L"PLAYER_DEATH_CUTSCENE_FLIPBOOK", L"Flipbook\\PLAYER_DEATH_CUTSCENE_FLIPBOOK.flip"));
	
	m_FlipbookCutSceneSucessPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_FlipbookCutSceneSucessPlayer->AddFlipbook(SUCESS_CUTSCENE_FLIPBOOK, CAssetMgr::GetInst()->LoadFlipbook(L"SUCESS_CUTSCENE_FLIPBOOK", L"Flipbook\\SUCESS_CUTSCENE_FLIPBOOK.flip"));

	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_FlipbookPlayer->AddFlipbook(KICK_LEFT, CAssetMgr::GetInst()->LoadFlipbook(L"KICK_LEFT", L"Flipbook\\KICK_LEFT.flip"));
	m_FlipbookPlayer->AddFlipbook(KICK_RIGHT, CAssetMgr::GetInst()->LoadFlipbook(L"KICK_RIGHT", L"Flipbook\\KICK_RIGHT.flip"));
	
	m_FlipbookPlayer->AddFlipbook(IDLE_LEFT, CAssetMgr::GetInst()->LoadFlipbook(L"IDLE_LEFT", L"Flipbook\\IDLE_LEFT.flip"));
	m_FlipbookPlayer->AddFlipbook(IDLE_RIGHT, CAssetMgr::GetInst()->LoadFlipbook(L"IDLE_RIGHT", L"Flipbook\\IDLE_RIGHT.flip"));

	m_FlipbookPlayer->AddFlipbook(MOVE_LEFT, CAssetMgr::GetInst()->LoadFlipbook(L"MOVE_LEFT", L"Flipbook\\MOVE_LEFT.flip"));
	m_FlipbookPlayer->AddFlipbook(MOVE_RIGHT, CAssetMgr::GetInst()->LoadFlipbook(L"MOVE_RIGHT", L"Flipbook\\MOVE_RIGHT.flip"));

	m_FlipbookPlayer->AddFlipbook(SMILE, CAssetMgr::GetInst()->LoadFlipbook(L"SMILE", L"Flipbook\\SMILE.flip"));

	m_FlipbookVFXPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	//HUGE
	m_FlipbookVFXPlayer->AddFlipbook(HUGE_VFX_1, CAssetMgr::GetInst()->LoadFlipbook(L"HUGE_VFX_1", L"Flipbook\\HUGE_VFX_1.flip"));
	m_FlipbookVFXPlayer->AddFlipbook(HUGE_VFX_2, CAssetMgr::GetInst()->LoadFlipbook(L"HUGE_VFX_2", L"Flipbook\\HUGE_VFX_2.flip"));
	m_FlipbookVFXPlayer->AddFlipbook(HUGE_VFX_3, CAssetMgr::GetInst()->LoadFlipbook(L"HUGE_VFX_3", L"Flipbook\\HUGE_VFX_3.flip"));
	//KICK
	m_FlipbookVFXPlayer->AddFlipbook(KICK_VFX_1, CAssetMgr::GetInst()->LoadFlipbook(L"KICK_VFX_1", L"Flipbook\\KICK_VFX_1.flip"));
	m_FlipbookVFXPlayer->AddFlipbook(KICK_VFX_2, CAssetMgr::GetInst()->LoadFlipbook(L"KICK_VFX_2", L"Flipbook\\KICK_VFX_2.flip"));
	m_FlipbookVFXPlayer->AddFlipbook(KICK_VFX_1, CAssetMgr::GetInst()->LoadFlipbook(L"KICK_VFX_1", L"Flipbook\\KICK_VFX_1.flip"));
	//MOVE
	m_FlipbookMOVEVFXPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	m_FlipbookMOVEVFXPlayer->AddFlipbook(MOVE_VFX_1, CAssetMgr::GetInst()->LoadFlipbook(L"MOVE_VFX_1", L"Flipbook\\MOVE_VFX_1.flip"));
	m_FlipbookMOVEVFXPlayer->AddFlipbook(MOVE_VFX_2, CAssetMgr::GetInst()->LoadFlipbook(L"MOVE_VFX_2", L"Flipbook\\MOVE_VFX_2.flip"));
	m_FlipbookMOVEVFXPlayer->AddFlipbook(MOVE_VFX_3, CAssetMgr::GetInst()->LoadFlipbook(L"MOVE_VFX_3", L"Flipbook\\MOVE_VFX_3.flip"));



	// AtlasTexture
	//CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Link", L"Texture\\link_32.bmp");

	//CreateFlipbook(L"LINK_IDLEDOWN", pAtlas, Vec2(0.f, 0.f), Vec2(120.f, 130.), 3);
	//CreateFlipbook(L"LINK_IDLELEFT", pAtlas, Vec2(0.f, 130.f), Vec2(120.f, 130.), 3);
	//CreateFlipbook(L"LINK_IDLEUP", pAtlas, Vec2(0.f, 260.f), Vec2(120.f, 130.), 1);
	//CreateFlipbook(L"LINK_IDLERIGHT", pAtlas, Vec2(0.f, 390.f), Vec2(120.f, 130.), 3);
	//CreateFlipbook(L"LINK_MOVEDOWN", pAtlas, Vec2(0.f, 520.f), Vec2(120.f, 130.), 10);
	//CreateFlipbook(L"LINK_MOVELEFT", pAtlas, Vec2(0.f, 650.f), Vec2(120.f, 130.), 10);
	//CreateFlipbook(L"LINK_MOVEUP", pAtlas, Vec2(0.f, 780.f), Vec2(120.f, 130.), 10);
	//CreateFlipbook(L"LINK_MOVERIGHT", pAtlas, Vec2(0.f, 910.f), Vec2(120.f, 130.), 10);

	//m_FlipbookPlayer->AddFlipbook(TRANSITION, CAssetMgr::GetInst()->LoadFlipbook(L"TRANSITION", L"Flipbook\\TRANSITION.flip"));
	//m_FlipbookPlayer->AddFlipbook(IDLE_DOWN, CAssetMgr::GetInst()->LoadFlipbook(L"LINK_IDLEDOWN" , L"Flipbook\\LINK_IDLEDOWN.flip" ));
	//m_FlipbookPlayer->AddFlipbook(IDLE_LEFT, CAssetMgr::GetInst()->LoadFlipbook(L"LINK_IDLELEFT",  L"Flipbook\\LINK_IDLELEFT.flip" ));
	//m_FlipbookPlayer->AddFlipbook(IDLE_UP,	 CAssetMgr::GetInst()->LoadFlipbook(L"LINK_IDLEUP"	,  L"Flipbook\\LINK_IDLEUP.flip"   ));
	//m_FlipbookPlayer->AddFlipbook(IDLE_RIGHT,CAssetMgr::GetInst()->LoadFlipbook(L"LINK_IDLERIGHT", L"Flipbook\\LINK_IDLERIGHT.flip" ));

	//m_FlipbookPlayer->AddFlipbook(MOVE_DOWN, CAssetMgr::GetInst()->LoadFlipbook( L"LINK_MOVEDOWN"	,L"Flipbook\\LINK_MOVEDOWN.flip" ));
	//m_FlipbookPlayer->AddFlipbook(MOVE_LEFT, CAssetMgr::GetInst()->LoadFlipbook( L"LINK_MOVELEFT"	,L"Flipbook\\LINK_MOVELEFT.flip" ));
	//m_FlipbookPlayer->AddFlipbook(MOVE_UP, CAssetMgr::GetInst()->LoadFlipbook(   L"LINK_MOVEUP"		,L"Flipbook\\LINK_MOVEUP.flip"   ));
	//m_FlipbookPlayer->AddFlipbook(MOVE_RIGHT, CAssetMgr::GetInst()->LoadFlipbook(L"LINK_MOVERIGHT"	,L"Flipbook\\LINK_MOVERIGHT.flip"));

	//CSprite* pSprite = CAssetMgr::GetInst()->FindSprite(L"LINK_IDLERIGHT_1");
}

void CPlayer::CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame)
{
	// Sprite 생성하기
	for (int i = 0; i < MaxFrame; i++)
	{
		wchar_t filePath[100] = {};
		wchar_t textureName[100] = {};
		// 각 프레임에 대한 경로 생성
		swprintf_s(filePath, 100, L"Texture\\%s_%d.png", _Pngname.c_str(), i);
		swprintf_s(textureName, 100, L"%s_%d", _Pngname.c_str(), i);

		CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(textureName, filePath);

		CSprite* pSprite = new CSprite;

		// _RightBot를 그대로 넘기지 않고 크기로 사용해야 합니다.
		int a = pAtlas->GetWidth();
		int b = pAtlas->GetHeight();
		int c = 0;

		Vec2 spriteSize = Vec2(static_cast<float>(pAtlas->GetWidth()), static_cast<float>(pAtlas->GetHeight()));
		Vec2 spritePosition = Vec2(0.0f, 0.0f); // 원하는 위치로 설정, 예를 들어 (0,0)
		pSprite->Create(pAtlas, spritePosition, spriteSize);

		// Key를 만들 때, wstring을 미리 생성 후 사용
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, L"%s_%d", _FlipbookName.c_str(), i);  // 여기서 형식 문자열을 분리하여 사용
		CAssetMgr::GetInst()->AddSprite(Key, pSprite);

		wstring strSavePath = L"Sprite\\";
		strSavePath += pSprite->GetKey();
		pSprite->Save(strSavePath);
	}


	for (int i = 0; i < MaxFrame; ++i)
	{
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
		wstring Path = L"Sprite\\";
		Path += Key;
		CAssetMgr::GetInst()->LoadSprite(Key, Path + L".sprite");
	}

	// Flipbook 생성하기
	CFlipbook* pFlipbook = new CFlipbook;

	for (int i = 0; i < MaxFrame; ++i)
	{
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
		pFlipbook->AddSprite(CAssetMgr::GetInst()->FindSprite(Key));
	}

	CAssetMgr::GetInst()->AddFlipbook(_FlipbookName, pFlipbook);
	wstring Path = L"Flipbook\\";
	pFlipbook->Save(Path + _FlipbookName);
}

void CPlayer::CreateFlipbook(const wstring& _FlipbookName, CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice, int MaxFrame)
{
	//Sprite 생성하기
	for (int i = 0; i < MaxFrame; ++i)
	{
		CSprite* pSprite = new CSprite;
		pSprite->Create(_Atlas, Vec2(_LeftTop.x + (_Slice.x * i), _LeftTop.y), _Slice);

		wchar_t Key[50] = {};
		swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
		CAssetMgr::GetInst()->AddSprite(Key, pSprite);

		wstring strSavePath = L"Sprite\\";
		strSavePath += pSprite->GetKey();
		pSprite->Save(strSavePath);
	}

	for (int i = 0; i < MaxFrame; ++i)
	{
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
		wstring Path = L"Sprite\\";		
		Path += Key;
		CAssetMgr::GetInst()->LoadSprite(Key, Path + L".sprite");
	}


	// Flipbook 생성하기
	CFlipbook* pFlipbook = new CFlipbook;

	for (int i = 0; i < MaxFrame; ++i)
	{
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
		pFlipbook->AddSprite(CAssetMgr::GetInst()->FindSprite(Key));		
	}

	CAssetMgr::GetInst()->AddFlipbook(_FlipbookName, pFlipbook);
	wstring Path = L"Flipbook\\";
	pFlipbook->Save(Path + _FlipbookName);
}

void CPlayer::PlayerDie()
{

	if (CurLevel == LEVEL_CHECK::BOSS_0) {

		CDeathP* pDeath = new CDeathP;
		pDeath->SetScale(100.f, 100.f);
		Vec2 PlayerPos = GetPos();
		pDeath->SetPos(PlayerPos);
		CreateObject(pDeath, LAYER_TYPE::CUTSCENE);
		SetPos(GetStartPos());

		BreakChainSummon0 = false;
		//TalkPartCheck = true;
		bossStartSound = false;
		CurCutSceneIndex = 0;
		CurTime = 0.f;
		SkulMoveDistance = 0.f;
		PistonMoveDistance = 0.f;
		CheckStartPiston = false;
		CheckStartSkul = false;
		CheckStartBridge = false;
		CheckEndPiston = false;
		CheckEndSkul = false;
		bossEndSound = false;
		SpawnJudmentThorn = false;
		curPattonIndex = 0;
		memset(checkPatton, false, sizeof(checkPatton));
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		const vector<CObj*>& vecDamageChain = pCurLevel->GetObjects(LAYER_TYPE::BROKE_CHAIN);
		const vector<CObj*>& vecSkul = pCurLevel->GetObjects(LAYER_TYPE::SKUL);
		const vector<CObj*>& vecUnskul = pCurLevel->GetObjects(LAYER_TYPE::UNDER_SKUL);
		const vector<CObj*>& vecHIGHPiston = pCurLevel->GetObjects(LAYER_TYPE::HIGH_PISTON);
		const vector<CObj*>& vecHIGHUnderPiston = pCurLevel->GetObjects(LAYER_TYPE::HIGH_UNDER_PISTON);
		const vector<CObj*>& vecLowPiston = pCurLevel->GetObjects(LAYER_TYPE::LOW_PISTON);
		const vector<CObj*>& vecLowHUnderPiston = pCurLevel->GetObjects(LAYER_TYPE::LOW_UNDER_PISTON);

		for (int i = 0; i < vecHIGHPiston.size(); i++) {
			DeleteObject(vecHIGHPiston[i]);
			DeleteObject(vecLowHUnderPiston[i]);
			DeleteObject(vecLowPiston[i]);
			DeleteObject(vecHIGHUnderPiston[i]);
		}

		for (int i = 0; i < vecDamageChain.size(); i++) {
			DeleteObject(vecDamageChain[i]);
		}

		for (int i = 0; i < vecSkul.size(); i++) {
			DeleteObject(vecSkul[i]);
			DeleteObject(vecUnskul[i]);
		}

		CJudmentSkul* pSkul = new CJudmentSkul;
		pSkul->Under = false;
		pSkul->dir = 0;
		pSkul->SetPos(180.f, 750.f);
		CreateObject(pSkul, LAYER_TYPE::SKUL);

		pSkul = new CJudmentSkul;
		pSkul->Under = true;
		pSkul->SetPos(180.f, 750.f);
		CreateObject(pSkul, LAYER_TYPE::UNDER_SKUL);

		pSkul = new CJudmentSkul;
		pSkul->Under = false;
		pSkul->dir = 1;
		pSkul->SetPos(1740.f, 750.f);
		CreateObject(pSkul, LAYER_TYPE::SKUL);

		pSkul = new CJudmentSkul;
		pSkul->Under = true;
		pSkul->SetPos(1740.f, 750.f);
		CreateObject(pSkul, LAYER_TYPE::UNDER_SKUL);

		CJudmentPiston* pJud = new CJudmentPiston;
		pJud->SetPos(1740.f, 1210.f);
		pJud->Under = false;
		pJud->TurnPiston = false;
		CreateObject(pJud, LAYER_TYPE::HIGH_PISTON);

		pJud = new CJudmentPiston;
		pJud->SetPos(1740.f, 1210.f);
		pJud->Under = true;
		pJud->TurnPiston = false;
		CreateObject(pJud, LAYER_TYPE::HIGH_UNDER_PISTON);

		pJud = new CJudmentPiston;
		pJud->SetPos(180.f, 1210.f);
		pJud->Under = false;
		pJud->TurnPiston = false;
		CreateObject(pJud, LAYER_TYPE::HIGH_PISTON);

		pJud = new CJudmentPiston;
		pJud->SetPos(180.f, 1210.f);
		pJud->Under = true;
		pJud->TurnPiston = false;
		CreateObject(pJud, LAYER_TYPE::HIGH_UNDER_PISTON);

		pJud = new CJudmentPiston;
		pJud->SetPos(180.f, -70.f);
		pJud->Under = false;
		pJud->TurnPiston = false;
		CreateObject(pJud, LAYER_TYPE::LOW_PISTON);

		pJud = new CJudmentPiston;
		pJud->SetPos(180.f, -70.f);
		pJud->Under = true;
		pJud->TurnPiston = false;
		CreateObject(pJud, LAYER_TYPE::LOW_UNDER_PISTON);

		pJud = new CJudmentPiston;
		pJud->SetPos(1740.f, -70.f);
		pJud->Under = false;
		pJud->TurnPiston = false;
		CreateObject(pJud, LAYER_TYPE::LOW_PISTON);

		pJud = new CJudmentPiston;
		pJud->SetPos(1740.f, -70.f);
		pJud->Under = true;
		pJud->TurnPiston = false;
		CreateObject(pJud, LAYER_TYPE::LOW_UNDER_PISTON);

		JudmentPlayerHealth = 4;

		if (CurLevel == BOSS_0) {
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
			const vector<CObj*>& vecBridge = pCurLevel->GetObjects(LAYER_TYPE::FIRE);
			for (int i = 0; i < vecBridge.size(); i++) {
				CFire* cf = dynamic_cast<CFire*>(vecBridge[i]);
				cf->use = true;
			}
		}

		const vector<CObj*>& vecBridge = pCurLevel->GetObjects(LAYER_TYPE::BRIDGE);

		for (int i = 0; i < vecBridge.size(); i++) {
			CBridge* jud = dynamic_cast<CBridge*>(vecBridge[i]);
			jud->MoveBirdge = false;
		}

	}
	else {
		CDeathP* pDeath = new CDeathP;
		pDeath->SetScale(100.f, 100.f);
		Vec2 PlayerPos = GetPos();
		pDeath->SetPos(PlayerPos);
		CreateObject(pDeath, LAYER_TYPE::CUTSCENE);
		SetPos(GetStartPos());
	}

}

void CPlayer::ResetPlayerCollision()
{
	PLAYER_COLLISION_CHECK = false;
}

