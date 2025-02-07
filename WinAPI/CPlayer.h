#pragma once
#include "CObj.h"

class CCollider;
class CTexture;
class CFlipbookPlayer;
class CRigidBody;
class CSound;
class CRestartCutScene;
class CDeathP;
class CThorn;
class CDamageChain;

enum DIRECTION;

class  CPlayer:
    public CObj
{
private:
    float               m_Speed;
    float               m_AttSpeed; // 초당 발사 속도
    float               m_AccTime;  // 시간 누적
    float               m_DetectRange;

    CRestartCutScene*   m_Restart;
    CCollider*          m_HitBox;
    
    CRigidBody*         m_RigidBody;
    CDamageChain*       pDamageChain = nullptr;
    CSound*             pCharacter_Move;
    CSound*             pCharacter_Enemy_Kick;
    CSound*             pCharacter_Rock_Kick;
    CSound*             Dialogue_start;
    CSound*             Dialogue_Success;
    CSound*             Dialogue_Booper;
    CSound*             Dialogue_Next;
    CSound*             KissSound;
    CSound* button_menu_confirm_01 = nullptr;
    CSound* judgement_intro_anim_01 = nullptr;
    CSound* boss_judgement_land_01 = nullptr;
    CSound* judgement_intro_start_01 = nullptr;
    CSound* lucifer_intro_dialogue_start_v2 = nullptr;
    CSound* lucifer_intro_skeleton_01 = nullptr;
    CSound* lucifer_intro_vine_01 = nullptr;

    CSound* judgement_chain_bind_01 = nullptr;
    CSound* judgement_spell_cast_01 = nullptr;
    CSound* judgement_chain_summon_01 = nullptr;

    CSound* boss_machine_end = nullptr;
    CSound* boss_machine_loop = nullptr;
    CSound* boss_machine_start = nullptr;
    CObj*               m_Target;

    bool bossStartSound;
    bool bossEndSound;
    int ChainSound = 1;
    bool UpIndex;

    //######################
    //저지먼트 패턴 변수
    bool MoveBridgePattonDone = false;
    bool CheckEndPiston = false;
    bool CheckEndSkul = false;
    bool j_animintro = false;
    bool j_introsound = false;
    float ActorVolume = 60.f;
    bool BreakChainSummon0;
    bool BreakChainSummon1;
    bool BreakChainSummon2;
    bool BreakChainSummon3;

    bool Actor = false;
    bool SpawnJudmentThorn;
    bool JudmentClear;

    int kickchainsoundindex_Left = 0;
    int kickchainsoundindex_Right = 0;
    CSound* boss_chain_kick_01L = nullptr;
    CSound* boss_chain_kick_02L = nullptr;
    CSound* boss_chain_kick_03L = nullptr;

    CSound* boss_chain_break_01L = nullptr;
    CSound* boss_chain_break_01R = nullptr;

    CSound* boss_chain_kick_01R = nullptr;
    CSound* boss_chain_kick_02R = nullptr;
    CSound* boss_chain_kick_03R = nullptr;
    //######################


    CSound* pThorn_damage0;
    CSound* pThorn_damage1;
    CObj*             m_Target_Thorn;

    DIRECTION Move_Direction;
    float Moving_TickPos;
    Vec2 Moving_CurPos;
    Vec2 Moving_GoalPos;
    Vec2 Moving_MovePos;

    int Dir;


    float elapsedTime = 0.0f;
    bool actionStarted = false; 

    bool Pressed;
    
    bool PLAYER_MOVING_CHECK;
    bool Die;

public:     
    int PlayerMove_Count;
    bool PLAYER_COLLISION_CHECK;
    bool VFX_HUGE_RENDER;
    bool VFX_KICK_RENDER;
    bool VFX_MOVE_RENDER;
    int Init_PlayerMove_Count;
    bool KeyBox_Key;
    int VFX_COUNT;
    bool PlayerMove;

    int JudmentPlayerHealth = 4;

    float PistonMoveDistance = 0.f;
    float SkulMoveDistance = 0.f;
    float MoveDistance = 0.f;
    float AllMoveDistance = 0.f;
    bool CheckStartSkul = false;
    bool CheckStartBridge = false;
    bool CheckStartPiston = false;

    float StartPistonTurnTime = 3.f;
    float StartSkulTime = 2.f;
    float StopPistonTime = 10.f;
    float CurTime = 0;
    bool check = false;

    Vec2 MoveVFXRenderPos;
    CFlipbookPlayer* m_FlipbookPlayer;
    CFlipbookPlayer* m_FlipbookVFXPlayer;
    CFlipbookPlayer* m_FlipbookMOVEVFXPlayer;
    CFlipbookPlayer* m_FlipbookCutSceneBooperPlayer;
    CFlipbookPlayer* m_FlipbookCutSceneDeathPlayer;
    CFlipbookPlayer* m_FlipbookCutSceneSucessPlayer;
    CFlipbookPlayer* m_FlipbookCutSceneDemonPlayer = nullptr;
    CFlipbookPlayer* m_FlipbookCutSceneDemonPlayerRight = nullptr;
    CFlipbookPlayer* m_FlipbookCutSceneLucyEye = nullptr;
    CFlipbookPlayer* m_FlipbookJudmentJump = nullptr;

    bool JudmentJump = false;
    bool DamageChain = false;
    float JudmentJumpTime = 0.f;

    virtual void Begin() override;
    virtual void Tick() override;
    void PauseLogic();
    void ChangeGodMode();
    void TurnPauseMenu();
    void DEFAULT_LOGIC();
    void FlipBookMGR();
    void InplaceSkul(CLevel* pCurLevel);
    void InplacePiston(CLevel* pCurLevel);
    void MoveSkul(CLevel* pCurLevel);
    void StartPiston(CLevel* pCurLevel);
    void StopPiston(CLevel* pCurLevel);
    void TALKCUTSCENE_LOGIC();
    void ResetObject();
    void DeleteAllObject();
    void RespownObject();
    void Check_In_Place_Motion(LAYER_TYPE m_Target_LayerType);
    void IFINPLACETHORNUP(const std::vector<CObj*>& vecThorn);
    void HugeCamera();
    void IFNextPointUpThorn();
    void UsePlayerMoveVFXFlipbook();
    void MoveLogic();
    void PlayHugeVFX();
    bool ChainHuge;
    virtual void Render() override;

    void TALKCUTSCENE_RENDER();

    void DEFAULT_RENDER();

    void DrawTalk();

    void DefaultTalkCutScene();

    void ChoiceCutSceneTalk();

    void DrawPngCharacter();

    void DrawPNGBackground();

    void PlayDialogue_Start_sound();

    void DrawBlackBackground();


    virtual void BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    virtual void EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider);
    void SetInitDir(int _Dir);
    void PlayerDie();
    void SetPlayerMoveCount(int _count) { 
     PlayerMove_Count = _count; 
    Init_PlayerMove_Count = PlayerMove_Count;
    }
    int GetPlayerMoveCount() { return PlayerMove_Count; }

    int CurLevel;
    float x_offset;
    float y_offset;
    void SetOffset(float _x, float _y) { x_offset = _x; y_offset = _y; };
//#####################################
//cutscene
public:
    bool TalkPartCheck;
    int FocusChoice = 0;
    bool uncheckDemon = false;
    bool Dialogue_Start;
    bool SuccessLevel = false;
    int TalkCutSceneIndex = 0;
    int CurCutSceneIndex = 0;
    bool RestartCutsceneEnd;
    CSound* voice = nullptr;
    bool RestartCutsceneStart = true;
    bool SuccessStart = false;
    bool SuccessEnd = false;

    bool j_bindAnimNull = false;
    bool j_Success = false;
    bool j_fly = false;
    float CutsceneTime = 0.f;

    bool lucy_facecheck = false;
    bool Judment_bind = false;

    vector<CUTSCENE_DATA> TalkCutScene[100];
    vector<CUTSCENE_DATA_NEW> NewTalkCutScene[100];
    std::wstring diemessage;
    std::wstring diemessage2;

//#####################################


//#####################################
//     Pause Menu
    bool PauseMenu = false;
    int PauseMenuFocusingNum = 0;

    int SoundIndex;
    int MusicIndex;
    bool GodMode = false;

//#####################################
private:
    void CreatePlayerFlipbook();
    void CreatePngFlipbook(const wstring& _FlipbookName, const wstring& _Pngname, int MaxFrame);
    void CreateFlipbook(const wstring& _FlipbookName, CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice, int MaxFrame);
    void ResetPlayerCollision();
    

public:
    CPlayer();
    void CreateSound();
    ~CPlayer();    
};

