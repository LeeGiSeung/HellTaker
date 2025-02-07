#pragma once


enum DEMON_TYPE {
	AZAZEL,
	CERBERUS,
	HM,
	JUDGMENT,
	JUSTICE,
	LUCY,
	MALINA,
	MODEUS,
	PANDEMONICA,
	POLICE,
	ZDRADA,
	LUCY_HOME,
	QUESTION,
	DEMON_END,
	LOVEPLOSION,
	NULLNAME,
	BEEL_FLY,
	HELLTAKER
};

enum PLAYER_CUTSCENE_BOOPER {
	BOOPER_CUTSCENE_FLIPBOOK,
};

enum PLAYER_CUTSCENE_SUCESS {
	SUCESS_CUTSCENE_FLIPBOOK
};

enum PLAYER_CUTSCENE_DEATH {
	PLAYER_DEATH_CUTSCENE_FLIPBOOK,
};

//enum DEMON_STATE {
//	AZAZEL_IDLE,
//	PANDEMONICA_IDLE,
//	MODEUS,
//	DEMON_END
//};

enum CUTSCENE_TYPE {
	TALK_CUTSCENE,
	CHOICE_CUTSCENE,
	SUCESS_CUTSCENE,
	DIE_CUTSCENE,
	NEXTINDEXSCENE,
	NEXT_LEVELSCENE
};

enum THORN_STATE {
	THORN_UP,
	THORN_DOWN
};

struct CUTSCENE_DATA {
	CUTSCENE_TYPE CutsceneType;
	DEMON_TYPE DemonType;
	wchar_t BackgroundTexture[100] = {};
	wchar_t CharacterTexture[100] = {};
	wchar_t FirstText[100] = {};
	wchar_t SecondText[100] = {};
	int DeathChoice;
};

struct CUTSCENE_DATA_NEW {
	CUTSCENE_TYPE CutsceneType;
	DEMON_TYPE DemonType;
	wchar_t BackgroundTexture[100] = {};
	wchar_t CharacterTexture[100] = {};
	wchar_t DemonFirstText[100] = {};
	wchar_t DemonSecondText[100] = {};
	wchar_t HeroFirstText[100] = {};
	wchar_t HeroSecondText[100] = {};
	int DeathChoice;
	int nextIndex;
	int nextDeathIndex;
	wchar_t Voice[100] = L"NO";
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class BRUSH_TYPE
{
	RED,
	GREEN,
	BLUE,
	GRAY,
	HOLLOW,
	END,
};

enum class LEVEL_TYPE
{
	START,
	STAGE_0,
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_5,
	STAGE_6,
	STAGE_7,
	STAGE_8,
	STAGE_9,
	BOSS_0,
	STAGE_HOME,
	EDITOR,
	STAGE_LOBBY,

	END,
};

enum LEVEL_CHECK
{
	START,
	STAGE_0,
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_5,
	STAGE_6,
	STAGE_7,
	STAGE_8,
	STAGE_9,
	BOSS_0,
	STAGE_HOME,
	EDITOR,
	STAGE_LOBBY,

	END,
};


enum class TASK_TYPE
{
	// Param0 : Object Address, Param1 : Layer Index
	CREATE_OBJECT,

	// Param0 : Object Address
	DELETE_OBJECT,

	// Param0 : Next Level
	CHANGE_LEVEL,
};

enum CUTSCENE_DEMON_FLIPBOOK {
	J_introAnim,
	LH_face,
	LH_swirl,
	j_bindAnim,
	j_flyAnim,
	mainUIexport_oUI_idle,
	j_glove
};

enum CUTSCENE_JUDMENT_JUMP {
	judgement_jump
};

enum LUCY_FACE {
	LUCY_FACE
};

enum CUTSCENE_DEMON_RIGHT_FLIPBOOK {
	mainUIexport_oUI_idleRIGHT,
	j_gloveRight
};

enum class LAYER_TYPE
{
	BACKGROUND,	
	TILE,
	DEFAULT,
	GEAR,
	HIGH_UNDER_PISTON,
	LOW_UNDER_PISTON,
	UNDER_SKUL,
	BRIDGE,
	THORN,
	KEY,
	KEYBOX,
	Rock,
	MONSTER,
	DAMAGE_CHAIN,
	CASTLE,
	CHAIN, //체인
	HIGH_PISTON,//피스톤    //언더 피스톤
	LOW_PISTON,//피스톤    //언더 피스톤
	SKUL, //스컬       //언더 스컬
	BROKE_CHAIN,
	FIREBASE,
	FIRE,
	COUNTUI,
	DEMON,
	PLAYER,
	WALL,
	UI,
	TALKCUTSCENE,
	CUTSCENE,
	SUCCESS,
	END = 32
};

enum PLAYER_VFX_STATE {
	HUGE_VFX_1,
	HUGE_VFX_2,
	HUGE_VFX_3,
	KICK_VFX_1,
	KICK_VFX_2,
	MOVE_VFX_1,
	MOVE_VFX_2,
	MOVE_VFX_3
};

enum COUNT_UI {
	COUNT_UI_LEFT,
	COUNT_UI_RIGHT
};

enum class COMPONENT_TYPE
{
	COLLIDER,
	RIGIDBODY,
	FLIPBOOKPLAYER,
	FSM,
	TILEMAP,
};

enum class ASSET_TYPE
{
	TEXTURE,	// 이미지
	SOUND,		// 소리	
	SPRITE,		// 특정 텍스쳐의 특정 부위
	FLIPBOOK,	// Sprite 의 집합체
};


enum class DEBUG_SHAPE
{
	RECT,
	CIRCLE,
	LINE,
};